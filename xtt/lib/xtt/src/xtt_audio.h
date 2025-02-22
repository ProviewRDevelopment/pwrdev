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

#ifndef xtt_audio_h
#define xtt_audio_h

/* xtt_audio.h -- soundcard bell routines.
*/
#if defined PWRE_CONF_ALSA

#include <alsa/asoundlib.h>

#include "pwr.h"

#define ALSA_PCM_NEW_HW_PARAMS_API
#ifndef XTTAUDIO_H
#define XTTAUDIO_H
#endif

#define XTT_AUDIO_AALARM 0x01
#define XTT_AUDIO_BALARM 0x02
#define XTT_AUDIO_INFO 0x03

#define AUDIO_QUESIZE 20

class CoWow;
class CoWowTimer;

class XttAudio {
public:
  static int audio_ok;
  XttAudio(
      CoWow* a_wow, const char* OSS_device = 0, const char* ALSA_device = 0);
  ~XttAudio();
  int init(char* OSS_device = 0, char* ALSA_device = 0);
  int beep(pwr_tAttrRef* arp);

private:
  static int number_of;
  static int OSS_audio_ok;
  static int ALSA_audio_ok;
  static int OSS_handle;
  static snd_pcm_t* ALSA_handle;
  static snd_pcm_uframes_t frames;
  static snd_pcm_hw_params_t* hw_params;
  static int srate;
  static CoWow* wow;
  double freq[100];
  short* write_buffer;
  int hw_buff_size;
  int write_buffer_size;
  int write_buffer_asize;
  int write_buffer_idx;
  CoWowTimer* timerid;
  pwr_tAttrRef queue[AUDIO_QUESIZE];
  int queue_prio[AUDIO_QUESIZE];
  int queue_cnt;

  int Init_ALSA(char*, unsigned int);
  int Init_OSS(char*, int);
  double envelope(double time, double endtime, double attack, double decay,
      double sustain, double release);
  void MakeSine(short* buffer, int buffersize, double time, double starttime,
      double endtime, int tone, double volume_ch1, double volume_ch2,
      double attack, double decay, double sustain, double release,
      double tremolo);
  void MakeSquare(short* buffer, int buffersize, double time, double starttime,
      double endtime, int tone, double volume_ch1, double volume_ch2,
      double attack, double decay, double sustain, double release,
      double tremolo);
  static void audio_write(void* data);
  static void audio_stop(void* data);
  static void audio_write_buff(void* data);
};

#else
// Dummy for platforms without ALSA
class CoWow;

class XttAudio {
public:
  static int audio_ok;
  XttAudio(CoWow* a_wow, const char* OSS_device = "/dev/dsp",
      const char* ALSA_device = "plughw:0,0")
  {
  }
  ~XttAudio()
  {
  }
  int init(char* OSS_device = "/dev/dsp", char* ALSA_device = "plughw:0,0")
  {
    return 1;
  }
  int beep(pwr_tAttrRef* arp)
  {
    return 1;
  }
};

#endif

#endif
