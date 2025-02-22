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

#include "rt_rtt_menu.h"
#include "dtt_appl_rttsys_m.rdecl"

RTT_HELP_START

RTT_HELP_SUBJ("PWR_RTT")
RTT_HELP_INFO("      Select subject with the arrow keys and press RETURN")
RTT_HELP_TEXT("\
	rt_rtt show info about the realtime database.\n\r\n\r\
DATABASE		Show the Plant and Node hierarchy.\n\r\
ALARM LIST		Show the alarm list.\n\r\
EVENT LIST		Show the event list.\n\r\
EXIT			Terminate.")

RTT_HELP_SUBJ("RTT ALARM LIST")
RTT_HELP_INFO(
    "  Ctrl/A Open object             Ctrl/E Acknowledge    Ctrl/R Back   ")
RTT_HELP_TEXT("\
	Alarmlist visar larmlistan.\n\r\n\r\
	** 	markerar att larmet �r aktivt.\n\r\
	!! 	markerar att larmet �r okvitterat.\n\r\
	A,B,C,D eller I anger larmets prioritet.\n\r\n\r\
	Larm-namn f�r utvalt larm visas med PF1, om larm-namnet �r ett objekt\n\r\
	�ppnas objektet.\n\r\
	Samtliga okvitterade larm kvitteras med PF3.\n\r\
	G� ur larmlistan med PF4")

RTT_HELP_SUBJ("RTT EVENT LIST")
RTT_HELP_INFO(
    "                                                   Ctrl/R Back   ")
RTT_HELP_TEXT("\
	Eventlist visar h�ndelselistan.\n\r\n\r\
	*A,*B,C,D eller I anger larmets prioritet.\n\r\
	r	markerar tid f�r retur av larmstatus.\n\r\
	a	markerar tid f�r kvittens.\n\r\n\r\
	G� ur h�ndelselistan med PF4")

RTT_HELP_END

RTT_DB_START
RTT_DB_CONTINUE
RTT_DB_END

RTT_MENU_START(dtt_menu_m8)
RTT_MENU_SYSEDIT_NEW("SHOW NODES", 0, &RTTSYS_SHOW_NODES)
RTT_MENU_SYSEDIT_NEW("SHOW SUBSCRIPTION CLIENT", 0, &RTTSYS_SHOW_SUBCLI)
RTT_MENU_SYSEDIT_NEW("SHOW SUBSCRIPTION SERVER", 0, &RTTSYS_SHOW_SUBSRV)
RTT_MENU_END(dtt_menu_m8)

RTT_MENU_START(dtt_menu_m10)
RTT_MENU_SYSEDIT_NEW("QCOM NODES", 0, &RTTSYS_QCOM_NODES)
RTT_MENU_SYSEDIT_NEW("QCOM LINKS", 0, &RTTSYS_QCOM_LINKS)
RTT_MENU_SYSEDIT_NEW("QCOM APPLICATIONS", 0, &RTTSYS_QCOM_APPL)
RTT_MENU_SYSEDIT_NEW("QCOM QUEUES", 0, &RTTSYS_QCOM_ALLQUEUES)
RTT_MENU_END(dtt_menu_m10)

RTT_MENU_START(dtt_menu_m9)
RTT_MENU_NEW("NETHANDLER", dtt_menu_m8)
RTT_MENU_NEW("QCOM", dtt_menu_m10)
RTT_MENU_SYSEDIT_NEW("REMNODE", 0, &RTTSYS_REMNODE)
RTT_MENU_SYSEDIT_NEW("REMTRANS", 0, &RTTSYS_REMTRANS)
RTT_MENU_END(dtt_menu_m9)

RTT_MENU_START(dtt_menu_m6)
RTT_MENU_SYSEDIT_NEW("SHOW POOL", 0, &RTTSYS_POOLS)
RTT_MENU_NEW("COMMUNICATION", dtt_menu_m9)
RTT_MENU_SYSEDIT_NEW("PLCPGM", 0, &RTTSYS_PLCPGM)
RTT_MENU_SYSEDIT_NEW("GRAFCET", 0, &RTTSYS_GRAFCET)
RTT_MENU_SYSEDIT_NEW("DEVICE", 0, &RTTSYS_DEVICE)
RTT_MENU_SYSEDIT_NEW("PLCTHREAD", 0, &RTTSYS_PLCTHREAD)
RTT_MENU_SYSEDIT_NEW("PID", 0, &RTTSYS_PID)
RTT_MENU_SYSEDIT_NEW("RUNNINGTIME", 0, &RTTSYS_RUNNINGTIME)
RTT_MENU_SYSEDIT_NEW("LOGGING", 0, &RTTSYS_LOGGING)
RTT_MENU_END(dtt_menu_m6)

RTT_MAINMENU_START("PWR_RTT/RTT-'RTT_NODE'-'RTT_SYS'")
RTT_MENUITEM_OBJECTS("DATABASE")
RTT_MENUITEM_COMMAND("ALARM LIST", "ALARM SHOW")
RTT_MENUITEM_COMMAND("EVENT LIST", "ALARM LIST")
RTT_MENU_NEW("SYSTEM", dtt_menu_m6)
RTT_MENUITEM_COMMAND("STORE", "SHOW FILE")
RTT_MENUITEM_EXIT("EXIT")
RTT_MAINMENU_END
