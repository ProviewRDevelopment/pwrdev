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

/* ge_nodelist_command.cpp
   This module contains routines for handling of command line in ge. */

#include <stdlib.h>

#include "co_ccm.h"
#include "co_ccm_msg.h"
#include "co_dcli.h"
#include "co_dcli_msg.h"
#include "co_string.h"
#include "cow_xhelp.h"
#include "cow_statusmon_nodelist.h"

static int nodelist_select_func(void* client_data, void* client_flag);
static int nodelist_open_func(void* client_data, void* client_flag);
static int nodelist_help_func(void* client_data, void* client_flag);

dcli_tCmdTable nodelist_command_table[] = { 
  { "SELECT", &nodelist_select_func, { "dcli_arg1", "/NODE", "" } },
  { "OPEN", &nodelist_open_func, { "dcli_arg1", "dcli_arg2",
      "/WIDTH", "/HEIGHT", "/TITLE", "/NODE", "/FILE", "" } },
  { "HELP", &nodelist_help_func,
      { "dcli_arg1", "dcli_arg2", "dcli_arg3", "dcli_arg4", "/HELPFILE",
          "/POPNAVIGATOR", "/BOOKMARK", "/INDEX", "/BASE", "/RETURNCOMMAND",
          "/WIDTH", "/HEIGHT", "/VERSION", "/STRICT", "" } },
  { "", NULL, { "" } }
};

static int nodelist_help_func(void* client_data, void* client_flag)
{
  Nodelist* nodelist = (Nodelist*)client_data;
  int sts;
  char arg_str[80];
  char file_str[80];
  char bookmark_str[80];
  char key[80];
  char return_str[80];
  int pop;
  int width, height;
  int nr;

  if (ODD(dcli_get_qualifier("/INDEX", file_str, sizeof(file_str)))) {
    if (ODD(dcli_get_qualifier("/HELPFILE", file_str, sizeof(file_str)))) {
      sts = CoXHelp::dhelp_index(navh_eHelpFile_Other, file_str);
      if (EVEN(sts))
        nodelist->message('E', "Unable to find file");
    } else {
      if (ODD(dcli_get_qualifier("/BASE", 0, 0)))
        sts = CoXHelp::dhelp_index(navh_eHelpFile_Base, NULL);
      else
        sts = CoXHelp::dhelp_index(navh_eHelpFile_Project, NULL);
    }
    return 1;
  }

  if (ODD(dcli_get_qualifier("/VERSION", 0, 0))) {
    sts = CoXHelp::dhelp("version", "", navh_eHelpFile_Other,
        "$pwr_load/xtt_version_help.dat", 0);
    if (EVEN(sts))
      nodelist->message('E', "No help on this subject");
    return sts;
  }

  int strict = ODD(dcli_get_qualifier("/STRICT", 0, 0));

  if (EVEN(dcli_get_qualifier("dcli_arg1", arg_str, sizeof(arg_str)))) {
    sts = CoXHelp::dhelp("help command", "", navh_eHelpFile_Base, NULL, strict);
    return 1;
  }
  if (EVEN(dcli_get_qualifier("/BOOKMARK", bookmark_str, sizeof(bookmark_str))))
    strcpy(bookmark_str, "");

  strcpy(key, arg_str);
  if (ODD(dcli_get_qualifier("dcli_arg2", arg_str, sizeof(arg_str)))) {
    strcat(key, " ");
    strcat(key, arg_str);
    if (ODD(dcli_get_qualifier("dcli_arg3", arg_str, sizeof(arg_str)))) {
      strcat(key, " ");
      strcat(key, arg_str);
      if (ODD(dcli_get_qualifier("dcli_arg3", arg_str, sizeof(arg_str)))) {
        strcat(key, " ");
        strcat(key, arg_str);
        if (ODD(dcli_get_qualifier("dcli_arg4", arg_str, sizeof(arg_str)))) {
          strcat(key, " ");
          strcat(key, arg_str);
        }
      }
    }
  }
  if (!ODD(
          dcli_get_qualifier("/RETURNCOMMAND", return_str, sizeof(return_str))))
    strcpy(return_str, "");

  if (ODD(dcli_get_qualifier("/WIDTH", arg_str, sizeof(arg_str)))) {
    // convert to integer
    nr = sscanf(arg_str, "%d", &width);
    if (nr != 1) {
      nodelist->message('E', "Width syntax error");
      return DCLI__SYNTAX;
    }
  } else
    width = 0;

  if (ODD(dcli_get_qualifier("/HEIGHT", arg_str, sizeof(arg_str)))) {
    // convert to integer
    nr = sscanf(arg_str, "%d", &height);
    if (nr != 1) {
      nodelist->message('E', "Height syntax error");
      return DCLI__SYNTAX;
    }
  } else
    height = 0;

  pop = ODD(dcli_get_qualifier("/POPNAVIGATOR", 0, 0));

  if (ODD(dcli_get_qualifier("/HELPFILE", file_str, sizeof(file_str)))) {
    sts = CoXHelp::dhelp(
        key, bookmark_str, navh_eHelpFile_Other, file_str, strict);
    if (EVEN(sts))
      nodelist->message('E', "No help on this subject");
  } else if (ODD(dcli_get_qualifier("/BASE", 0, 0))) {
    sts = CoXHelp::dhelp(key, bookmark_str, navh_eHelpFile_Base, 0, strict);
    if (EVEN(sts))
      nodelist->message('E', "No help on this subject");
  } else {
    sts = CoXHelp::dhelp(key, bookmark_str, navh_eHelpFile_Project, 0, strict);
    if (EVEN(sts)) {
      sts = CoXHelp::dhelp(key, bookmark_str, navh_eHelpFile_Base, 0, strict);
      if (EVEN(sts))
        nodelist->message('E', "No help on this subject");
    }
  }

  return 1;
}

static int nodelist_select_func(void* client_data, void* client_flag)
{
  Nodelist* nl = (Nodelist*)client_data;

  char arg1_str[80];
  int arg1_sts;

  arg1_sts = dcli_get_qualifier("dcli_arg1", arg1_str, sizeof(arg1_str));

  if (str_NoCaseStrncmp(arg1_str, "NODE", strlen(arg1_str)) == 0) {
    // Command is "SELECT NODE"
    char node_str[80];
    int sts;

    if (EVEN(dcli_get_qualifier("/NODE", node_str, sizeof(node_str)))) {
      nl->message('E', "Node is missing");
      return DCLI__QUAL_NODEF;
    }

    sts = nl->nodelistnav->select_node(node_str);   
    if (EVEN(sts))
      nl->message('E', "No such node");
    else
      nl->pop();

  } else {
    nl->message('E', "Unknown qualifier");
    return DCLI__QUAL_NODEF;
  }
  return DCLI__SUCCESS;
}

static int nodelist_open_func(void* client_data, void* client_flag)
{
  Nodelist* nl = (Nodelist*)client_data;

  char arg1_str[80];
  int arg1_sts;

  arg1_sts = dcli_get_qualifier("dcli_arg1", arg1_str, sizeof(arg1_str));

  if (str_NoCaseStrncmp(arg1_str, "GRAPH", strlen(arg1_str)) == 0) {
    // Command is "OPEN GRAPH"
    char graph_str[80];
    int sts;
    int nr;
    char tmp_str[80];
    char title_str[80];
    char *title_p;
    int width;
    int height;

    sts = dcli_get_qualifier("dcli_arg2", graph_str, sizeof(graph_str));

    if (ODD(dcli_get_qualifier("/WIDTH", tmp_str, sizeof(tmp_str)))) {
      nr = sscanf(tmp_str, "%d", &width);
      if (nr != 1) {
	nl->message('E', "Syntax error in width");
	return DCLI__SYNTAX;
      }
    } else
      width = 0;
    
    if (ODD(dcli_get_qualifier("/HEIGHT", tmp_str, sizeof(tmp_str)))) {
      nr = sscanf(tmp_str, "%d", &height);
      if (nr != 1) {
	nl->message('E', "Syntax error in height");
	return DCLI__SYNTAX;
      }
    } else
      height = 0;

    if (ODD(dcli_get_qualifier("/TITLE", title_str, sizeof(title_str)))) {
      title_p = title_str;
    } else
      title_p = 0;

    sts = nl->open_graph(graph_str, title_p, width, height);   
    if (EVEN(sts))
      nl->message('E', "Open graph error");

  } else if (str_NoCaseStrncmp(arg1_str, "XTT", strlen(arg1_str)) == 0) {
    // Command is "OPEN XTT"
    char node_str[80];
    char node_name[80];
    int nix;
    int sts;

    if (EVEN(dcli_get_qualifier("/NODE", node_str, sizeof(node_str)))) {
      nl->message('E', "Node is missing");
      return DCLI__QUAL_NODEF;
    }
    sts = nl->nodelistnav->get_node(node_str, &nix);
    if (EVEN(sts)) {
      nl->message('E', "No such node");
      return DCLI__SUCCESS;
    }

    sts = nl->nodelistnav->get_node_data(nix, node_name, 0, 0, 0, 0);
    if (EVEN(sts))
      return sts;

    pwr_tCmd cmd;
    sprintf(cmd, "ssh pwrp@%s -X rt_xtt&", node_name);
    printf("cmd %s\n", cmd);
    system(cmd);
    
  } else if (str_NoCaseStrncmp(arg1_str, "OPPLACE", strlen(arg1_str)) == 0) {
    // Command is "OPEN OPPLACE"
    char node_str[80];
    char node_name[80];
    pwr_tOName opplace;
    int nix;
    int sts;

    if (EVEN(dcli_get_qualifier("/NODE", node_str, sizeof(node_str)))) {
      nl->message('E', "Node is missing");
      return DCLI__QUAL_NODEF;
    }
    sts = nl->nodelistnav->get_node(node_str, &nix);
    if (EVEN(sts)) {
      nl->message('E', "No such node");
      return DCLI__SUCCESS;
    }

    sts = nl->nodelistnav->get_node_data(nix, node_name, 0, 0, opplace, 0);
    if (EVEN(sts))
      return sts;

    pwr_tCmd cmd;
    sprintf(cmd, "ssh pwrp@%s -X rt_xtt %s&", node_name, opplace);
    printf("cmd %s\n", cmd);
    system(cmd);
    
  } else if (str_NoCaseStrncmp(arg1_str, "RTMONITOR", strlen(arg1_str)) == 0) {
    // Command is "OPEN RTMONITOR"
    char node_str[80];
    char node_name[80];
    int nix;
    int sts;

    if (EVEN(dcli_get_qualifier("/NODE", node_str, sizeof(node_str)))) {
      nl->message('E', "Node is missing");
      return DCLI__QUAL_NODEF;
    }
    sts = nl->nodelistnav->get_node(node_str, &nix);
    if (EVEN(sts)) {
      nl->message('E', "No such node");
      return DCLI__SUCCESS;
    }

    sts = nl->nodelistnav->get_node_data(nix, node_name, 0, 0, 0, 0);
    if (EVEN(sts))
      return sts;

    pwr_tCmd cmd;
    sprintf(cmd, "ssh pwrp@%s -X pwr_rtmon&", node_name);
    printf("cmd %s\n", cmd);
    system(cmd);

  } else if (str_NoCaseStrncmp(arg1_str, "FILE", strlen(arg1_str)) == 0) {
    pwr_tCmd cmd;
    int sts;
    char msg[80];
    pwr_tFileName file_str;

    if (EVEN(dcli_get_qualifier("/FILE", file_str, sizeof(file_str)))) {
      if (EVEN(dcli_get_qualifier("dcli_arg2", file_str, sizeof(file_str)))) {
	nl->message('E', "File is missing");
	return DCLI__QUAL_NODEF;
      }
    }
    strcpy(cmd, "xdg-open ");
    strcat(cmd, file_str);
    sts = system(cmd);
    if (sts != 0) {
      sprintf(msg, "Error from xdg-open %d", sts >> 8);
      nl->message('E', msg);
    }
  } else {
    nl->message('E', "Unknown qualifier");
    return DCLI__QUAL_NODEF;
  }
  return DCLI__SUCCESS;
}

int Nodelist::command(char* input_str)
{
  char command[160];
  int sts, sym_sts;
  char symbol_value[80];

  if (input_str[0] == '@') {
    /* Read command file */
    // char *s;
    // if ( (s = strchr( input_str, ' ')))
    //   dcli_toupper( s, s);
    sts = dcli_replace_symbol(input_str, command, sizeof(command));
    if (EVEN(sts))
      return sts;

    sts = readcmdfile(&command[1], 0);
    if (sts == DCLI__NOFILE) {
      char tmp[200];
      snprintf(tmp, 200, "Unable to open file \"%s\"", &command[1]);
      message('E', tmp);
      return DCLI__SUCCESS;
    } else if (EVEN(sts))
      return sts;
    return DCLI__SUCCESS;
  }

  // dcli_toupper( input_str, input_str);
  sts = dcli_replace_symbol(input_str, command, sizeof(command));
  if (EVEN(sts))
    return sts;

  sts = dcli_cli(
      (dcli_tCmdTable*)&nodelist_command_table, command, (void*)this, 0);
  if (sts == DCLI__COM_NODEF) {
    /* Try to find a matching symbol */
    sym_sts = dcli_get_symbol_cmd(command, symbol_value);
    if (ODD(sym_sts)) {
      if (symbol_value[0] == '@') {
        /* Read command file */
        sts = readcmdfile(&symbol_value[1], 0);
        if (sts == DCLI__NOFILE) {
          char tmp[200];
          snprintf(tmp, 200, "Unable to open file \"%s\"", &symbol_value[1]);
          message('E', tmp);
          return DCLI__SUCCESS;
        } else if (EVEN(sts))
          return sts;
        return DCLI__SUCCESS;
      }
      sts = dcli_cli(
          (dcli_tCmdTable*)&nodelist_command_table, symbol_value, (void*)this, 0);
    } else if (sym_sts == DCLI__SYMBOL_AMBIG)
      sts = sym_sts;
  }
  if (sts == DCLI__COM_AMBIG)
    message('E', "Ambiguous command");
  else if (sts == DCLI__COM_NODEF)
    message('E', "Undefined command");
  else if (sts == DCLI__QUAL_AMBIG)
    message('E', "Ambiguous qualifier");
  else if (sts == DCLI__QUAL_NODEF)
    message('E', "Undefined qualifier");
  else if (sts == DCLI__SYMBOL_AMBIG)
    message('E', "Ambiguous symbol abbrevation");

  return sts;
}

static int nodelist_ccm_deffilename_func(
    char* outfile, char* infile, void* client_data)
{
  dcli_get_defaultfilename(infile, outfile, ".nl_com");
  dcli_translate_filename(outfile, outfile);
  return 1;
}

static int nodelist_ccm_errormessage_func(
    char* msg, int severity, void* client_data)
{
  Nodelist* nl = (Nodelist*)client_data;

  if (EVEN(severity))
    nl->message('I', msg);
  else
    nl->message('E', msg);
  return 1;
}

int nodelist_externcmd_func(char* cmd, void* client_data)
{
  Nodelist* nl = (Nodelist*)client_data;
  int sts;

  nl->scriptmode++;
  sts = nl->command(cmd);
  nl->scriptmode--;
  return sts;
}

/************************************************************************
*
* Name:		readcmdfile()
*
* Type		int
*
* Type		Parameter	IOGF	Description
*
* Description:
*
**************************************************************************/

int Nodelist::readcmdfile(char* incommand, char *script)
{
  char input_str[160];
  int sts;
  int appl_sts;

  if (!ccm_func_registred) {
    ccm_func_registred = 1;

    //script_func_register();

  }

  //script_store_nodelist();

  // Read and execute the command file
  if (incommand) {
    str_trim(input_str, incommand);
    sts = ccm_file_exec(input_str, nodelist_externcmd_func,
        nodelist_ccm_deffilename_func, nodelist_ccm_errormessage_func, &appl_sts,
	verify, 0, NULL, 0, 0, NULL, (void*)this);
  }
  else if (script) {
    sts = ccm_buffer_exec(script, 0, nodelist_externcmd_func,
	nodelist_ccm_deffilename_func, nodelist_ccm_errormessage_func, &appl_sts, verify,
	0, NULL, 0, NULL, (void *)this);
  }
  if (EVEN(sts))
    return sts;
  return 1;
}
