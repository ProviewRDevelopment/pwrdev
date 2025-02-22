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


package jpwr.rt;

/**
 * Declarations for base classes, class volume pwrb.
 * @author	cs
 */
public class Pwrb {
  public static final int eWebTargetEnum_RightFrame = 0;
  public static final int eWebTargetEnum_ParentWindow = 1;
  public static final int eWebTargetEnum_SeparateWindow = 2;

  public static final int mXttMethodsFlagsMask_IsConfigured = 1;

  public static final int mXttOpMethodsMask_OpenGraph      = 1;
  public static final int mXttOpMethodsMask_OpenObjectGraph = 2;
  public static final int mXttOpMethodsMask_OpenTrend      = 4;
  public static final int mXttOpMethodsMask_OpenHistory    = 8;
  public static final int mXttOpMethodsMask_OpenFast       = 16;
  public static final int mXttOpMethodsMask_Camera         = 32;
  public static final int mXttOpMethodsMask_HistEvent      = 64;
  public static final int mXttOpMethodsMask_BlockEvents    = 128;
  public static final int mXttOpMethodsMask_Help           = 256;
  public static final int mXttOpMethodsMask_Photo          = 512;
  public static final int mXttOpMethodsMask_Note           = 1024;
  public static final int mXttOpMethodsMask_ParentObjectGraph = 2048;

  public static final int mXttMntMethodsMask_OpenObject    = 1;
  public static final int mXttMntMethodsMask_OpenTrace     = 2;
  public static final int mXttMntMethodsMask_RtNavigator   = 4;
  public static final int mXttMntMethodsMask_OpenCrossref  = 8;
  public static final int mXttMntMethodsMask_HelpClass     = 16;
  public static final int mXttMntMethodsMask_DataSheet     = 32;
  public static final int mXttMntMethodsMask_CircuitDiagram = 64;
  public static final int mXttMntMethodsMask_Simulate      = 1 << 31;

  public static final int cClass_AAnalyse = 131080;
  public static final int cClass_aarithm = 131088;
  public static final int cClass_adelay = 131096;
  public static final int cClass_Ai = 131104;
  public static final int cClass_Ai_7436 = 131112;
  public static final int cClass_Ai_AI32uP = 133288;
  public static final int cClass_Ai_HVAI32 = 131128;
  public static final int cClass_AiArea = 131136;
  public static final int cClass_Ai_Vmic3113A = 133168;
  public static final int cClass_and = 131144;
  public static final int cClass_Ao = 131152;
  public static final int cClass_Ao_7455_20 = 131160;
  public static final int cClass_Ao_7455_30 = 131168;
  public static final int cClass_Ao_HVAO4 = 131176;
  public static final int cClass_AoArea = 131192;
  public static final int cClass_Ao_Vmic4800 = 133176;
  public static final int cClass_ApCollect = 133224;
  public static final int cClass_ApDistribute = 133232;
  public static final int cClass_AppGraph = 135960;
  public static final int cClass_ApplDistribute = 131208;
  public static final int cClass_AppLink = 136000;
  public static final int cClass_ASup = 131216;
  public static final int cClass_Av = 131224;
  public static final int cClass_AvArea = 131232;
  public static final int cClass_Backup = 131248;
  public static final int cClass_Backup_Conf = 131256;
  public static final int cClass_bcddo = 131264;
  public static final int cClass_BodyText = 131272;
  public static final int cClass_carithm = 131280;
  public static final int cClass_CaArea = 131288;
  public static final int cClass_ChanAi = 131296;
  public static final int cClass_ChanAit = 131304;
  public static final int cClass_ChanAo = 131312;
  public static final int cClass_ChanCo = 131320;
  public static final int cClass_ChanDi = 131336;
  public static final int cClass_ChanDo = 131344;
  public static final int cClass_ClassVolumeConfig = 131352;
  public static final int cClass_ClassVolumeLoad = 131360;
  public static final int cClass_Co = 131368;
  public static final int cClass_CommonClassDistribute = 131376;
  public static final int cClass_comph = 131384;
  public static final int cClass_compl = 131392;
  public static final int cClass_ConAnalog = 131400;
  public static final int cClass_ConBlueStrOneArr = 131408;
  public static final int cClass_ConDaMeNoArr = 131416;
  public static final int cClass_ConDaMeOneArr = 131424;
  public static final int cClass_ConDaMeTwoArr = 131432;
  public static final int cClass_ConData = 131440;
  public static final int cClass_ConDataFeedback = 131448;
  public static final int cClass_ConDaThinNoArr = 131456;
  public static final int cClass_ConDaThinOneArr = 131464;
  public static final int cClass_ConDaThintwoArr = 131472;
  public static final int cClass_ConDigital = 131480;
  public static final int cClass_ConExecuteOrder = 131488;
  public static final int cClass_ConFeedbackAnalog = 131496;
  public static final int cClass_ConFeedbackDigital = 131504;
  public static final int cClass_ConGrafcet = 131512;
  public static final int cClass_ConGreenTwoArr = 131520;
  public static final int cClass_ConMeNoArr = 131528;
  public static final int cClass_ConMeOneArr = 131536;
  public static final int cClass_ConMeTwoArr = 131544;
  public static final int cClass_ConReMeNoArr = 131552;
  public static final int cClass_ConReMeOneArr = 131560;
  public static final int cClass_ConReMeTwoArr = 131568;
  public static final int cClass_ConStrMeNoArr = 131576;
  public static final int cClass_ConThinNoArr = 131584;
  public static final int cClass_ConThinOneArr = 131592;
  public static final int cClass_ConThintwoArr = 131600;
  public static final int cClass_ConTrace = 131608;
  public static final int cClass_corder = 131616;
  public static final int cClass_count = 131624;
  public static final int cClass_Co_7435_33 = 131632;
  public static final int cClass_Co_7437_33 = 131640;
  public static final int cClass_Co_IpQuadrature = 133184;
  public static final int cClass_Co_PI24BO = 131648;
  public static final int cClass_CoArea = 131656;
  public static final int cClass_cstoai = 131664;
  public static final int cClass_cstoao = 131672;
  public static final int cClass_cstoap = 131680;
  public static final int cClass_cstoav = 131688;
  public static final int cClass_cstoip = 131696;
  public static final int cClass_Document = 131824;
  public static final int cClass_windowplc = 133120;
  public static final int cClass_csub = 131704;
  public static final int cClass_curve = 131712;
  public static final int cClass_CycleSup = 133320;
  public static final int cClass_DAnalyse = 131720;
  public static final int cClass_dataarithm = 133240;
  public static final int cClass_DataCollect = 133248;
  public static final int cClass_darithm = 131728;
  public static final int cClass_DbConfig = 131736;
  public static final int cClass_DbDistribute = 131744;
  public static final int cClass_Di = 131760;
  public static final int cClass_dibcd = 131768;
  public static final int cClass_Di_7437_37 = 131784;
  public static final int cClass_Di_DIX2 = 131792;
  public static final int cClass_DiArea = 131808;
  public static final int cClass_DirectoryDbConfig = 131776;
  public static final int cClass_Do = 131816;
  public static final int cClass_DocUser1 = 131832;
  public static final int cClass_DocUser2 = 131840;
  public static final int cClass_dorder = 131848;
  public static final int cClass_Do_7437_83 = 131856;
  public static final int cClass_Do_HVDO32 = 131864;
  public static final int cClass_DoArea = 131880;
  public static final int cClass_DpCollect = 133256;
  public static final int cClass_DpDistribute = 133264;
  public static final int cClass_drive = 131896;
  public static final int cClass_DsFast = 131904;
  public static final int cClass_DsFastConf = 131912;
  public static final int cClass_DsFastCurve = 133616;
  public static final int cClass_DsHist = 131920;
  public static final int cClass_DsHistServer = 131928;
  public static final int cClass_DsTrend = 131936;
  public static final int cClass_DsTrendConf = 131944;
  public static final int cClass_DsTrendCurve = 135816;
  public static final int cClass_DSup = 131952;
  public static final int cClass_Dv = 131960;
  public static final int cClass_DvArea = 131968;
  public static final int cClass_edge = 131984;
  public static final int cClass_EventPrinter = 131992;
  public static final int cClass_ExternRef = 132000;
  public static final int cClass_filter = 132008;
  public static final int cClass_Form = 132016;
  public static final int cClass_Frame = 132024;
  public static final int cClass_FriendNodeConfig = 133360;
  public static final int cClass_GetAgeneric = 133352;
  public static final int cClass_GetAi = 132032;
  public static final int cClass_GetAo = 132040;
  public static final int cClass_GetAp = 132048;
  public static final int cClass_GetAv = 132056;
  public static final int cClass_GetData = 133272;
  public static final int cClass_GetDgeneric = 133328;
  public static final int cClass_GetDi = 132064;
  public static final int cClass_GetDo = 132072;
  public static final int cClass_GetDp = 132080;
  public static final int cClass_GetDv = 132088;
  public static final int cClass_getip = 132096;
  public static final int cClass_GetPi = 132104;
  public static final int cClass_Graph = 132112;
  public static final int cClass_GraphDistribute = 132120;
  public static final int cClass_gray = 132128;
  public static final int cClass_Group = 132136;
  public static final int cClass_Head = 132144;
  public static final int cClass_inc3p = 132152;
  public static final int cClass_initstep = 132160;
  public static final int cClass_inv = 132168;
  public static final int cClass_IOHandler = 132176;
  public static final int cClass_IpMux = 133192;
  public static final int cClass_Ii = 133664;
  public static final int cClass_Io = 133672;
  public static final int cClass_Iv = 133680;
  public static final int cClass_IvArea = 133312;
  public static final int cClass_limit = 132192;
  public static final int cClass_Line_LAT = 132208;
  public static final int cClass_ListConfig = 133152;
  public static final int cClass_ListDescriptor = 132216;
  public static final int cClass_lorder = 132224;
  public static final int cClass_maxmin = 132232;
  public static final int cClass_MessageHandler = 132240;
  public static final int cClass_mode = 132248;
  public static final int cClass_MuxMod = 133200;
  public static final int cClass_mvalve = 132344;
  public static final int cClass_NodeConfig = 132352;
  public static final int cClass_NodeLinkSup = 132360;
  public static final int cClass_OpAppl = 132368;
  public static final int cClass_OpApplMsg = 132376;
  public static final int cClass_OpPlace = 132384;
  public static final int cClass_or = 132392;
  public static final int cClass_windowcond = 133104;
  public static final int cClass_windoworderact = 133112;
  public static final int cClass_order = 132400;
  public static final int cClass_OrderAct = 132408;
  public static final int cClass_out2p = 132416;
  public static final int cClass_PackAttrRef = 132424;
  public static final int cClass_PackAttrRef10 = 132432;
  public static final int cClass_PackOperator = 132440;
  public static final int cClass_PackTest = 132448;
  public static final int cClass_PageRef = 133144;
  public static final int cClass_Pd_7435_26 = 132456;
  public static final int cClass_pid = 132464;
  public static final int cClass_pipos = 132472;
  public static final int cClass_pispeed = 132480;
  public static final int cClass_PlcThread = 133160;
  public static final int cClass_PlcProcess = 133304;
  public static final int cClass_plc = 132488;
  public static final int cClass_PlotGroup = 132496;
  public static final int cClass_Po = 132504;
  public static final int cClass_Point = 132512;
  public static final int cClass_porder = 132520;
  public static final int cClass_pos3p = 132528;
  public static final int cClass_posit = 132536;
  public static final int cClass_pulse = 132544;
  public static final int cClass_Queue = 132552;
  public static final int cClass_Rack_RTP = 132568;
  public static final int cClass_Rack_SSAB = 132576;
  public static final int cClass_Rack_VME = 133216;
  public static final int cClass_RemoteConfig = 133984;
  public static final int cClass_ramp = 132584;
  public static final int cClass_resdi = 132592;
  public static final int cClass_resdo = 132600;
  public static final int cClass_resdp = 132608;
  public static final int cClass_resdv = 132616;
  public static final int cClass_reset_so = 132624;
  public static final int cClass_RootVolumeConfig = 132632;
  public static final int cClass_RootVolumeLoad = 132640;
  public static final int cClass_RttConfig = 133280;
  public static final int cClass_RTP_DIOC = 132648;
  public static final int cClass_ScanTime = 133296;
  public static final int cClass_select = 132664;
  public static final int cClass_setcond = 132672;
  public static final int cClass_setdi = 132680;
  public static final int cClass_setdo = 132688;
  public static final int cClass_setdp = 132696;
  public static final int cClass_setdv = 132704;
  public static final int cClass_SharedVolumeConfig = 132712;
  public static final int cClass_SharedVolumeLoad = 132720;
  public static final int cClass_ShowPlcAttr = 132728;
  public static final int cClass_sorder = 132736;
  public static final int cClass_speed = 132744;
  public static final int cClass_sr_r = 132760;
  public static final int cClass_sr_s = 132768;
  public static final int cClass_ssbegin = 132776;
  public static final int cClass_ssend = 132784;
  public static final int cClass_step = 132792;
  public static final int cClass_StepConv = 132800;
  public static final int cClass_StepDiv = 132808;
  public static final int cClass_StoAgeneric = 133336;
  public static final int cClass_stoai = 132816;
  public static final int cClass_stoao = 132824;
  public static final int cClass_stoap = 132832;
  public static final int cClass_stoav = 132840;
  public static final int cClass_StoDgeneric = 133344;
  public static final int cClass_stodi = 132848;
  public static final int cClass_stodo = 132856;
  public static final int cClass_stodp = 132864;
  public static final int cClass_stodv = 132872;
  public static final int cClass_stoip = 132880;
  public static final int cClass_stopi = 132888;
  public static final int cClass_Store = 132896;
  public static final int cClass_StoreFormat = 132904;
  public static final int cClass_StoreTrig = 132912;
  public static final int cClass_Sv = 133496;
  public static final int cClass_windowsubstep = 133128;
  public static final int cClass_substep = 132920;
  public static final int cClass_sum = 132944;
  public static final int cClass_SubVolumeConfig = 132928;
  public static final int cClass_SubVolumeLoad = 132936;
  public static final int cClass_SystemDistribute = 132952;
  public static final int cClass_table = 132960;
  public static final int cClass_Text = 132968;
  public static final int cClass_timer = 132976;
  public static final int cClass_timint = 132984;
  public static final int cClass_Title = 132992;
  public static final int cClass_TraceDbConfig = 131752;
  public static final int cClass_trans = 133008;
  public static final int cClass_TransConv = 133016;
  public static final int cClass_TransDiv = 133024;
  public static final int cClass_User = 133032;
  public static final int cClass_valve = 133040;
  public static final int cClass_VIPC616 = 133208;
  public static final int cClass_VolumeDistribute = 133048;
  public static final int cClass_wait = 133064;
  public static final int cClass_waith = 133072;
  public static final int cClass_WebBrowserConfig = 133488;
  public static final int cClass_WebHandler = 133440;
  public static final int cClass_WebSocketServer = 136704;
  public static final int cClass_OpPlaceWeb = 136528;
  public static final int cClass_OpPlaceApp = 136536;
  public static final int cClass_WebGraph = 133472;
  public static final int cClass_WebLink = 133480;
  public static final int cClass_xor = 133136;
  public static final int cClass_XttGraph = 133464;
}
