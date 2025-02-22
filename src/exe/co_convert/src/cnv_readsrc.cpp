/*
 * ProviewR   Open Source Process Control.
 * Copyright (C) 2005-2025 SSAB EMEA AB.
 *
 * This file is part of ProviewR.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ProviewR. If not, see <http://www.gnu.org/licenses/>
 *
 * Linking ProviewR statically or dynamically with other modules is
 * making a combined work based on ProviewR. Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * In addition, as a special exception, the copyright holders of
 * ProviewR give you permission to, from the build function in the
 * ProviewR Configurator, combine ProviewR with modules generated by the
 * ProviewR PLC Editor to a PLC program, regardless of the license
 * terms of these modules. You may copy and distribute the resulting
 * combined work under the terms of your choice, provided that every
 * copy of the combined work is accompanied by a complete copy of
 * the source code of ProviewR (the version used to produce the
 * combined work), being distributed under the terms of the GNU
 * General Public License plus this exception.
 */

extern "C" {
#include "co_dcli.h"
#include "co_cdh.h"
#include "co_time.h"
}
#include "co_string.h"

#include "cnv_readsrc.h"
#include "cnv_wblto.h"

int CnvReadSrc::read_src(char* filename)
{
  int sts;
  char orig_line[400];
  char line[400];
  char line_part[4][80];
  int nr = 0;
  FILE* fp;

  fp = fopen(filename, "r");
  if (!fp)
    return 0;

  state = 0;
  doc_fresh = 0;

  html_init(filename);

  while (1) {
    sts = CnvCtx::read_line(orig_line, sizeof(orig_line), fp);
    if (!sts)
      linetype = cread_eLine_EOF;
    else {
      str_trim(line, orig_line);
      if (streq(line, ""))
        continue;

      if (!str_StartsWith(line, "/*_*") && !(state & cread_mState_Doc)) {
        html_line(orig_line);
        continue;
      }

      nr = dcli_parse(line, " 	=", "", (char*)line_part,
          sizeof(line_part) / sizeof(line_part[0]), sizeof(line_part[0]), 0);

      if (streq(low(line_part[0]), "/*_*"))
        linetype = cread_eLine_Doc;
      else if (streq(low(line_part[0]), "*/"))
        linetype = cread_eLine_DocEnd;

      switch (linetype) {
      case cread_eLine_Doc:
        state |= cread_mState_Doc;
        strcpy(src_aref, "");
        strcpy(src_aref_text, "");
        break;
      case cread_eLine_DocEnd:
        state &= ~cread_mState_Doc;
        break;
      case cread_eLine_EOF:
        break;

      default:
        printf("Error, unknown linetype\n");
      }
    }
    if (state & cread_mState_Doc) {
      if (streq(low(line_part[0]), "@aref")) {
        if (nr > 1)
          strcpy(src_aref, line_part[1]);
        if (nr > 2)
          strcpy(src_aref_text, line_part[2]);
        html_aref();
      }
      if (strstr(line, "*/"))
        state &= ~cread_mState_Doc;
    }

    if (linetype == cread_eLine_EOF)
      break;
  }

  if (ctx->generate_html && ctx->wblto && ctx->wblto->class_open())
    ctx->wblto->class_close();
  if (ctx->generate_xtthelp && ctx->wblto && ctx->wblto->index_open())
    ctx->wblto->class_close();

  fclose(fp);
  html_close();
  return 1;
}

int CnvReadSrc::html_init(char* filename)
{
  char fname[200];
  char dir_fname[200];
  char timestr[80];

  time_AtoAscii(0, time_eFormat_DateAndTime, timestr, sizeof(timestr));

  filename_to_html(fname, filename);
  strcpy(dir_fname, ctx->dir);
  strcat(dir_fname, fname);

  // Open html file
  fp_src_html.open(dir_fname);
#if defined OS_LINUX
  if (!fp_src_html.good()) {
    printf("Unable to open file \"%s\"\n", dir_fname);
    return 0;
  }
#endif

  fp_src_html << "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 "
                 "Frameset//EN\"\"http://www.w3.org/TR/REC-html40/"
                 "frameset.dtd\">\n"
              << "<!--NewPage-->\n"
              << "<HTML>\n"
              << "<HEAD>\n"
              << "<!-- Generated by co_convert " << timestr << " -->\n"
              << "<TITLE>\n"
              << filename << '\n'
              << "</TITLE>\n"
	      << "<link rel=\"stylesheet\" type=\"text/css\" href=\"orm.css\">\n"
              << "</HEAD>\n"
              << "<BODY BGCOLOR=\"white\">\n"
              << "<CODE><PRE>\n";

  return 1;
}

int CnvReadSrc::html_close()
{
  fp_src_html << "</PRE></CODE>\n"
              << "</BODY>\n"
              << "</HTML>\n";
  fp_src_html.close();

  return 1;
}

int CnvReadSrc::html_line(char* line)
{
  char hline[1000];
  char* s = line;
  char* t = hline;

  for (s = line; *s; s++) {
    switch (*s) {
    case '<':
      strcpy(t, "&#60;");
      t += 5;
      break;
    case '>':
      strcpy(t, "&#62;");
      t += 5;
      break;
    case '"':
      strcpy(t, "&#34;");
      t += 5;
      break;
    case '&':
      strcpy(t, "&#38;");
      t += 5;
      break;
    default:
      *t = *s;
      t++;
    }
  }
  *t = 0;

  fp_src_html << hline << '\n';

  return 1;
}

int CnvReadSrc::html_aref()
{
  fp_src_html << "</pre></code>\n"
              << "<hr>\n"
              << "<a name=\"" << src_aref << "\"><h3>" << src_aref_text
              << "</h3></a>\n"
              << "<hr><code><pre>\n";

  return 1;
}

void CnvReadSrc::filename_to_html(char* fname, char* filename)
{
  char* s;

  // Convert filename ...name.ext... -> name_ext.html
  if ((s = strrchr(filename, '/')))
    strcpy(fname, s + 1);
  else if ((s = strrchr(filename, '>')))
    strcpy(fname, s + 1);
  else if ((s = strrchr(filename, ']')))
    strcpy(fname, s + 1);
  else if ((s = strrchr(filename, ':')))
    strcpy(fname, s + 1);
  else
    strcpy(fname, filename);

  if ((s = strrchr(fname, ';')))
    *s = 0;
  if ((s = strrchr(fname, '.')))
    *s = '_';
  strcat(fname, ".html");
}

char* CnvReadSrc::low(char* in)
{
  static char str[400];

  str_ToLower(str, in);
  return str;
}
