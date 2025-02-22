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

/*************************************************************************
*
*	Help texts in pwr_rtt is defined here.
*
**************************************************************************/

extern rtt_t_helptext rtt_edit_helptext[];
rtt_t_helptext rtt_edit_helptext[] = { { 1, "HELP", "", "\
Help is avalible on the following subjects.\n\n\
command				paste\n\
picture				select\n\
update field			unselect\n\
update parameters		include\n\
edit				connect\n\
set				dualconnect\n\
write				rtt\n\
save				link\n\
create				show\n\
modify				show collection\n\
exit				edit\n\
quit				compile\n\
delete				run\n\
cut				undo\n\
copy				syntax\n\
" },
  { 1, "PICTURE", "", "\
In edit mode it is possible to edit a picture.\n\
The following keys are defined.\n\n\
ARROWS		Navigate in the work area.\n\
PF1		Open an update field.\n\
PF2		Select.\n\
PF3		Copy selected area to paste buffer.\n\
PF4 or CTRL/R	Return to menu.\n\
CTRL/Z		Back to root menu.\n\
CTRL/W		Redraw the picture.\n\
CTRL/N		Show collection picture.\n\
CTRL/V		Connect update item with selected object in collection picture.\n\
CTRL/F		Paste.\n\
HELP		Help.\n\
DO or CTRL/B	Command mode.\n\
" },
  { 1, "UPDATE FIELD", "", "\
The update field picture displays data of an update field.\n\
Enter an update field picture by placing the cursor on the first charachter\n\
of the field and press PF1.\n\
it is possible to select a parameter and modify data by a modify command\n\
The following keys are defined.\n\n\
ARROWS		Navigate in the menu and select parameter.\n\
PF4 or CTRL/R	Go back to previous menu.\n\
CTRL/Z		Back to root menu.\n\
HELP or CTRL/H	Help.\n\
DO or CTRL/B	Command mode.\n\n\
rtt_edit> help update parameters\n\
gives help on the parameter of the update field.\n\
" },
  { 1, "MENU", "", "\
In a menu picture it is possible to create new imenu items and\n\
children of menuitems. The items can be of type menu, picture, exit\n\
or objects.\n\
The following keys are defined.\n\n\
ARROWS		Navigate in the menu and select an item.\n\
RETURN		Go down to menu or picture.\n\
PF4 or CTRL/R	Go back to previous menu.\n\
NEXT SIDE or CTRL/F	Go to next side of the menu.\n\
PREV SIDE or CTRL/D	Go to previous side of the menu.\n\
CTRL/Z		Back to root menu.\n\
CTRL/W		Redraw the picture.\n\
HELP or CTRL/H	Help.\n\
DELETE		Delete an item in the menu.\n\
DO or CTRL/B	Command mode.\n\n\
New items can be create with 'create/menu', 'create/picture', 'create/exit',\n\
'create/objecthierarchy' or 'create/command=. New childs to a menu item\n\
can be created with 'create/child/...'.\n\
" },
  { 1, "UPDATE PARAMETERS", "", "\
Parameter of an update field.\n\n\
Number		The order in which the fields will be selected.\n\n\
Text		Text that will be highlighted when the update field is\n\
		selected. I text is equal to '%' no text will be written.\n\
Type		Type of function: update, set, reset, set_reset, toggle,\n\
		dual_set, dual_reset, dual_set_reset, dual_toggle, \n\
		set_dualset, toggle_dualtoggle, command.\n\
Parameter	Name of object and parameter sho show in the field.\n\
Text/Dualpar	Output text, command or parameter to activate with dual \n\
		functions.\n\
Privileges	Privileges to modify data: OP, EL, PROC, SYS, NOOP, NO.\n\
Outputflags	Type of presentation of a boolean: ONOFF, AUTOMAN, OPENCLOSED,\n\
		TRUEFALSE, TEXT, NO.\n\
Characters	Number of characters the value will be displayed with.\n\
Decimals	Number or decimals for a float variable.\n\
Maxlimit	Maxlimit at value changed.\n\
Minlimit	Minlimit at value changed.\n\
Database	GDH: gdh object, RTT: rtt local database.\n\
Declaration	Only when database is RTT. BOOLEAN, INT, FLOAT, CHAR, STRING,\n\
		STRING4, STRING10, STRING20, STRING40.\
" },
  { 1, "COMMAND", "", "\
The command prompt is reached by the 'DO' key or CTRL/B\n\
You exit command mode by PF4\n\n\
rtt_edit> set line		rtt_edit> select\n\
rtt_edit> set ascii		rtt_edit> unselect\n\
rtt_edit> set inverse		rtt_edit> show command, function\n\
rtt_edit> set noinverse		rtt_edit> create /menu/picture/exit/objecthier\n\
rtt_edit> write			rtt_edit> create /exit/command=/func=/child\n\
rtt_edit> include		rtt_edit> create /time/fulltime\n\
rtt_edit> save			rtt_edit> create 'text'\n\
rtt_edit> exit			rtt_edit> modify /maintitle='title'\n\
rtt_edit> quit			rtt_edit> modify\n\
rtt_edit> delete		rtt_edit> edit [help] [functions]\n\
rtt_edit> delete item		rtt_edit> compile [vms] [eln]\n\
rtt_edit> cut			rtt_edit> link [vms] [eln]\n\
rtt_edit> copy			rtt_edit> run\n\
rtt_edit> paste			rtt_edit> help 'subject'\n\
" },
  { 1, "SET", "", "\
Set charachter mode in edit picture.\n\n\
Allowed qualifiers are:	\n\n\
rtt_edit> set line\n\
rtt_edit> set ascii\n\
rtt_edit> set inverse\n\
rtt_edit> set noinverse\n\
" },
  { 1, "WRITE", "", "\
Write a picture or menue tree. With the write command the picture can be saved\n\
in a specified file and copied by the include command.\n\
The update items can also be written on a file, edited and included.\n\n\
With the /all qualifier the update items in all pictures are written in the\n\
file.\n\n\
rtt_edit> write picture 'filename'\n\
rtt_edit> write items [/all] 'filename'\n\
rtt_edit> write menu [/all] 'filename'\n\
" },
  { 1, "INCLUDE", "", "\
Include a picture, menu or update items stored with the write command in the\n\
current picture buffer or menu. If update items are included the items in the\n\
buffer should first be cleared with the 'clear items' command, or if\n\
udate items should be added to the items in the curren buffer use the\n\
/add qualifier.\n\n\
rtt_edit> include picture 'filename'\n\
rtt_edit> include items [/add] 'filename'\n\
rtt_edit> include menu 'filename'\n\
" },
  { 1, "CLEAR", "", "\
Clear the buffer or remove the update items in the current buffer.\n\n\
rtt_edit> clear picture\n\
rtt_edit> clear items\n\
" },
  { 1, "SAVE", "", "\
Save the menu and/or the current picture.\n\
If the save command is given in a picture the picture and the menues\n\
are saved. If the command is given in a menu the menues are saved\n\n\
rtt_edit> save\n\
" },
  { 1, "EXIT", "", "\
Saves the menues and the current picture and terminates the execution.\n\
" },
  { 1, "QUIT", "", "\
Terminates the execution without saveing.\n\
" },
  { 1, "DELETE", "", "\
Delete a update field (delete item) or a selected area in a picture.\n\n\
rtt_edit> delete\n\
rtt_edit> delete item\n\
" },
  { 1, "UNDO", "", "\
Recovers a deleted item in a menu. The recovered item i positioned\n\
next to the selected menu item. The command can be used to move menu items.\n\n\
rtt_edit> undo delete\n\
" },
  { 1, "CUT", "", "\
Delete selected area an copy to paste buffer (CTRL/N).\n\n\
rtt_edit> cut\n\
" },
  { 1, "COPY", "", "\
Copy selected area to paste buffer (PF3).\n\n\
rtt_edit> copy\n\
" },
  { 1, "SELECT", "", "\
Select an area (PF2).\n\n\
rtt_edit> select\n\
" },
  { 1, "UNSELECT", "", "\
Unselect a selected area.\n\n\
rtt_edit> unselect\n\
" },
  { 1, "CREATE", "", "\
Create menu items and update fields.\n\n\
create /menu 'title'		create a new menu item.\n\
create /picture 'title'		create a new picture.\n\
create /pict/func=fff 'title'	create a new picture item\n\
					with an user function.\n\
create /exit 'title'		create a new exit item.\n\
create /objecthier 'title' 	create a new objects item.\n\
create /command='com' 'title'	create a new command item.\n\
create /vmscommand='com' 'title' create a new vmscommand item.\n\
create /vmsconfirm= /vmshold= /vmsnowait= create new vmscommands items.\n\
create /syspict=fff 'title'	create a new command item.\n\
create /permpicture 'title'	create a new permanent picture.\n\
create /permpict/func=fff 'title' create a new permanent picture\n\
				item with an user function.\n\
create /keys 'title'		create a fastkey menu item.\n\
create /child			create a new item as a child to\n\
				the current menu item.\n\
create				create a update field in a picture.\n\
create /[full]time		create a update field in a picture\n\
					that display the time.\n\
" },
  { 1, "MODIFY", "", "\
Modify the title or data of the current menu item or update field.\n\n\
rtt_edit> modify /maintitle='title'\n\
rtt_edit> modify\n\
rtt_edit> modify /number/text/type/par/dual\n\
rtt_edit> modify /priv/output\n\
rtt_edit> modify /text='title'\n\
" },
  { 1, "RTT", "", "\
Starts rtt and displays the object hierarchy.\n\n\
rtt_edit> rtt\n\
" },
  { 1, "EDIT", "", "\
Edit the file with user defined functions, the functions specified with\n\
the 'create /picture/function=' command, or edit the application help file.\n\n\
rtt_edit> edit functions\n\
rtt_edit> edit help\n\
" },
  { 1, "RUN", "", "\
Execute the created rtt program\n\
A subprocess is spawned which executes the program\n\n\
rtt_edit> run\n\
" },
  { 1, "COMPILE", "", "\
Compile the file with user defined functions, the functions specified with\n\
the 'create /picture/function=' command.\n\n\
rtt_edit> compile\n\
rtt_edit> compile vms\n\
rtt_edit> compile eln\n\
" },
  { 1, "LINK", "", "\
Compile and link of the program. If only a version for vms or eln is\n\
wanted this can be specified.\n\n\
rtt_edit> link\n\
rtt_edit> link vms\n\
rtt_edit> link eln\n\
" },
  { 1, "CONNECT", "", "\
Connect the parameter of an update field to a rtdb object.\n\
Puts the selected object in the collection picture in the parameter\n\
element of the current update field (also as CTRL/V).\n\n\
rtt_edit> connect\n\
" },
  { 1, "DUALCONNECT", "", "\
Connect the dualparameter of an update field to a rtdb object.\n\
Puts the selected object in the collection picture in the dualparameter\n\
element of the current update field.\n\n\
rtt_edit> dualconnect\n\
" },
  { 1, "SHOW", "", "\
Display command or function of an menu item or display \n\
the collection picture.\n\n\
rtt_edit> show command\n\
rtt_edit> show vmscommand\n\
rtt_edit> show syspicture\n\
rtt_edit> show function\n\
rtt_edit> show collection\n\
" },
  { 1, "SHOW COLLECTION", "", "\
Display the collection picture (also CTRL/N).\n\
The objects has to be collected in rtt mode.\n\n\
rtt_edit> show collection\n\
" },
  { 1, "SHOW COMMAND", "", "\
Display the command of the current command menu item\n\n\
rtt_edit> show command\n\
" },
  { 1, "SHOW VMSCOMMAND", "", "\
Display the vms command of the current command menu item\n\n\
rtt_edit> show command\n\
" },
  { 1, "SHOW SYSPICTURE", "", "\
Display the system picture of the current syspicture menu item\n\n\
rtt_edit> show command\n\
" },
  { 1, "SHOW FUNCTION", "", "\
Display the function of the current function menu item\n\n\
rtt_edit> show function\n\
" },
  { 1, "EXPORT", "", "\
Export and list info of database references\n\n\
rtt_edit> export gdhreflist 'filname'\n\
Lists the gdh references of all the pictures in the specified file.\n\n\
rtt_edit> export externref 'filname'\n\
Creates a commandfile that inserts gdhreferences as ExternRef objects\n\
into the development database. The rtt references will then be shown in the\n\
crossreferens lists.\n\
" },
  { 1, "LIST", "", "\
List information of items in pictures\n\n\
rtt_edit> list items 'filname'\n\
" },
  { 1, "SYNTAX", "", "\
Syntax check in a picture. Check of syntax in the update items\n\n\
rtt_edit> syntax\n\
" },
  {
      0, "",
  } };
