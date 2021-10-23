
#include "stdafx.h"
#include "Fsx.h"
#include "tool.h"
#include "PubData.h"

Fsx::Fsx(void)
{
	a = 0;
	oldhd = RMeter.HD;
	oldhdbug = RMeter.HDBUG;
	oldalt = RMeter.ALT;
	oldvor1 = RMeter.VOR1;
	oldvor2 = RMeter.VOR2;
	oldadf = RMeter.ADF;
}

void Fsx::startFsx(void *param)
{
	 if (SUCCEEDED(SimConnect_Open(&hSimConnect, "UART", NULL, 0, 0, 0)))
	 {
		Fsx *fsx = (Fsx*)param;
		printf("\nConnected to Flight Simulator!\n");
		fsx->dealFsx();
	 }
	 exit(1);
}

void Fsx::dealFsx()
{
	//172仪表数据
	int hr;
	//速度
	hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "AIRSPEED INDICATED", "Knots",SIMCONNECT_DATATYPE_FLOAT64);
	//高度
	hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "Indicated Altitude", "feet",SIMCONNECT_DATATYPE_FLOAT64);

	//俯仰横滚
	hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "Plane Bank Degrees","degrees");
	hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "Plane Pitch Degrees","degrees");
	//转弯角
	hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "TURN INDICATOR RATE","degree per second");
	//方向角
	hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "PLANE HEADING DEGREES GYRO","degrees");
	//升降速度表
	hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "VERTICAL SPEED", "ft/min",SIMCONNECT_DATATYPE_FLOAT64);		
	//发动机转速
	hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "GENERAL ENG RPM:1","Rpm",SIMCONNECT_DATATYPE_FLOAT64);

	//vor1
	hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "NAV OBS:1","degrees",SIMCONNECT_DATATYPE_FLOAT64);
	//vor2
	hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "NAV OBS:2","degrees",SIMCONNECT_DATATYPE_FLOAT64);
	//hdg
	hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "ADF CARD","degrees",SIMCONNECT_DATATYPE_FLOAT64);

	//左右油箱油量
	hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "FUEL TANK LEFT MAIN LEVEL","gallons",SIMCONNECT_DATATYPE_FLOAT64);
	hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "FUEL TANK RIGHT MAIN LEVEL","gallons",SIMCONNECT_DATATYPE_FLOAT64);

	//排气温度
	hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "GENERAL ENG EXHAUST GAS TEMPERATURE:1","farenheit",SIMCONNECT_DATATYPE_FLOAT64);
	//油流量
	hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "ENG FUEL FLOW GPH:1","Gallons per hour",SIMCONNECT_DATATYPE_FLOAT64);

	//燃油温度
	hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "GENERAL ENG OIL TEMPERATURE:1","farenheit");
	//燃油压力
	hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "GENERAL ENG OIL PRESSURE:1","psi");

	//设定场压
	hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "KOHLSMAN SETTING HG","inHg");
	//设定航向
	hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "AUTOPILOT HEADING LOCK DIR","Degrees");

	//进气压力
	hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "SUCTION PRESSURE","inhg");
	//电压
	hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "ELECTRICAL TOTAL LOAD AMPS","Amperes");

	//自动飞行高度和垂直速度
	hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "AUTOPILOT ALTITUDE LOCK VAR","Feet");
	hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "AUTOPILOT VERTICAL HOLD VAR","Feet/minute");
	//侧滑角
	hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "TURN COORDINATOR BALL", "Position 128");
	


	//映射自定义事件到模拟器
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT1,"My.event");

	//点火开关5
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_MAGNETOOFF,"MAGNETO_OFF");
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_MAGNETOL,"MAGNETO_LEFT");
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_MAGNETOR,"MAGNETO_RIGHT");
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_MAGNETOB,"MAGNETO_BOTH");
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_MAGNETOON,"ENGINE_AUTO_START");

	//双船形开关2
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_MASTERBATT,"TOGGLE_MASTER_BATTERY");
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_MASTERALTERNATE,"TOGGLE_MASTER_ALTERNATOR");
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_ALTERNATE,"TOGGLE_ALTERNATE_STATIC");

	//面板灯开关1
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_PANELLIGHTSON,"PANEL_LIGHTS_ON");
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_PANELLIGHTSOFF,"PANEL_LIGHTS_OFF");

	//fule switch1
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_ENGINE1,"TOGGLE_FUEL_VALVE_ALL");

	//油门
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_THROTTLE,"THROTTLE_SET");
	//前后
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_HEADING,"ELEVATOR_SET");
	//左右
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_BANK,"AILERON_SET");
	//脚踏板
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_RUDDER,"RUDDER_SET");
	//燃油混合柄
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_MIXTURE,"MIXTURE_SET");
	//配平手轮
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_ELEVATORTRIM,"ELEVATOR_TRIM_SET");
	//襟翼开关
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_FLAP,"FLAPS_SET");
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_BRAKES,"BRAKES");	

	//油泵开关
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_FUELPUMP,"FUEL_PUMP");
	//旋转灯塔
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_BACONLIGHTS,"TOGGLE_BEACON_LIGHTS");
	//降落灯
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_LANDINGLIGHTS,"LANDING_LIGHTS_TOGGLE");
	//滑行灯
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_TAIXLIGHTS,"TOGGLE_TAXI_LIGHTS");	
	//航向灯
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_NAVLIGHTS,"TOGGLE_NAV_LIGHTS");
	//频闪灯
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_STROBE,"STROBES_TOGGLE");
	//PITOT
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_PITOT_ON,"PITOT_HEAT_SET");
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_PITOT_OFF,"KEY_PITOT_HEAT_OFF");
	//油箱选择
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_TANKALL,"FUEL_SELECTOR_ALL");
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_TANKLEFT,"FUEL_SELECTOR_LEFT");
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_TANKRIGHT,"FUEL_SELECTOR_RIGHT");

	//航向增加
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_HDDEC,"GYRO_DRIFT_DEC");
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_HDINC,"GYRO_DRIFT_INC");

	//高度增加减少
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_ALTDEC,"KOHLSMAN_SET");
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_ALTINC,"KOHLSMAN_INC");


	//HDG
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_HDBUGDEC,"HEADING_BUG_SET");
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_HDBUGINC,"HEADING_BUG_INC");

	//VOR1
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_VOR1DEC,"VOR1_SET");
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_VOR1INC,"VOR1_OBI_INC");

	//vor2
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_VOR2DEC,"VOR2_OBI_DEC");
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_VOR2INC,"VOR2_OBI_DEC");

	//ADF_CARD
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_ADFDEC,"ADF_CARD_DEC");
	SimConnect_MapClientEventToSimEvent(hSimConnect,EVENT_ADFINC,"ADF_CARD_INC");


	//自动飞行
	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_AP_ON, "AUTOPILOT_ON");
	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_AP_OFF, "AUTOPILOT_OFF");

	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_HD_ON, "AP_PANEL_HEADING_ON");
	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_HD_OFF, "AP_PANEL_HEADING_OFF");

	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_NAV_ON, "AP_NAV1_HOLD_ON");
	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_NAV_OFF, "AP_NAV1_HOLD_OFF");

	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_APR_ON, "AP_APR_HOLD_ON");
	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_APR_OFF, "AP_APR_HOLD_OFF");

	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_REV_ON, "AP_BC_HOLD_ON");
	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_REV_OFF, "AP_BC_HOLD_OFF");

	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_AT_ON, "AP_ALT_HOLD_ON");
	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_AT_OFF, "AP_ALT_HOLD_OFF");


	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_AT_INC, "AP_ALT_VAR_INC");
	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_AT_DEC, "AP_ALT_VAR_DEC");

	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_VR_INC, "AP_VS_VAR_INC");
	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_VR_DEC, "AP_VS_VAR_DEC");



	//将事件添加到通知组中
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT1);

	//点火开关
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_MAGNETOON);
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_MAGNETOOFF);
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_MAGNETOL);
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_MAGNETOR);
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_MAGNETOB);
	//船型开关
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_MASTERALTERNATE);
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_MASTERBATT);
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_ALTERNATE);
	//面板灯开关
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_PANELLIGHTSON);
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_PANELLIGHTSOFF);
	//油控制开关
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_ENGINE1);
	//操纵量
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_THROTTLE);
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_HEADING);
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_BANK);
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_RUDDER);
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_MIXTURE);
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_ELEVATORTRIM);
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_FLAP);
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_BRAKES);

	//六个灯开关
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_FUELPUMP);
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_NAVLIGHTS);
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_BACONLIGHTS);
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_LANDINGLIGHTS);
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_TAIXLIGHTS);
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_STROBE);
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_PITOT_ON);
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_PITOT_OFF);
	//油箱选择开关
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_TANKALL);
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_TANKLEFT);
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_TANKRIGHT);

	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_HDDEC);
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_HDINC);

	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_ALTDEC);
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_ALTINC);

	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_HDBUGDEC);
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_HDBUGINC);

	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_VOR1DEC);
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_VOR1INC);

	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_VOR2DEC);
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_VOR2INC);		

	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_ADFDEC);
	SimConnect_AddClientEventToNotificationGroup(hSimConnect,GROUP1,EVENT_ADFINC);	

	//自动飞行
	hr = SimConnect_AddClientEventToNotificationGroup(hSimConnect, GROUP1, EVENT_AP_ON);
	hr = SimConnect_AddClientEventToNotificationGroup(hSimConnect, GROUP1, EVENT_AP_OFF);

	hr = SimConnect_AddClientEventToNotificationGroup(hSimConnect, GROUP1, EVENT_HD_ON);
	hr = SimConnect_AddClientEventToNotificationGroup(hSimConnect, GROUP1, EVENT_HD_OFF);


	hr = SimConnect_AddClientEventToNotificationGroup(hSimConnect, GROUP1, EVENT_NAV_ON);
	hr = SimConnect_AddClientEventToNotificationGroup(hSimConnect, GROUP1, EVENT_NAV_OFF);
	hr = SimConnect_AddClientEventToNotificationGroup(hSimConnect, GROUP1, EVENT_APR_ON);
	hr = SimConnect_AddClientEventToNotificationGroup(hSimConnect, GROUP1, EVENT_APR_OFF);
	hr = SimConnect_AddClientEventToNotificationGroup(hSimConnect, GROUP1, EVENT_REV_ON);
	hr = SimConnect_AddClientEventToNotificationGroup(hSimConnect, GROUP1, EVENT_REV_OFF);

	hr = SimConnect_AddClientEventToNotificationGroup(hSimConnect, GROUP1, EVENT_AT_ON);
	hr = SimConnect_AddClientEventToNotificationGroup(hSimConnect, GROUP1, EVENT_AT_OFF);
	hr = SimConnect_AddClientEventToNotificationGroup(hSimConnect, GROUP1, EVENT_AT_INC);
	hr = SimConnect_AddClientEventToNotificationGroup(hSimConnect, GROUP1, EVENT_AT_DEC);
	hr = SimConnect_AddClientEventToNotificationGroup(hSimConnect, GROUP1, EVENT_VR_INC);
	hr = SimConnect_AddClientEventToNotificationGroup(hSimConnect, GROUP1, EVENT_VR_DEC);
		

	hr = SimConnect_SubscribeToSystemEvent(hSimConnect, EVENT_SIM_START, "SimStart");
	int i=0;
	//设置通知组优先级
	SimConnect_SetNotificationGroupPriority(hSimConnect,GROUP1,SIMCONNECT_GROUP_PRIORITY_HIGHEST);
	while( 0 == quit )
	{
		SimConnect_CallDispatch(hSimConnect,MyDispatchProcRD , NULL);
		if(S_OK==SimConnect_TransmitClientEvent(hSimConnect,0,EVENT1,0,SIMCONNECT_GROUP_PRIORITY_HIGHEST,SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY))
		{
			//printf("函数调用成功\n");	
		}
		MapEventToSim();
		Sleep(50);
	}
	SimConnect_Close(hSimConnect);  
}
void Fsx::MapEventToSim()
{
	//printf("**********************************\n");
	//驾驶杆前后
	if(Dpanel.joystickFrontandBack<544)
		Dpanel.joystickFrontandBack=544;
	else if(Dpanel.joystickFrontandBack>3000)
		Dpanel.joystickFrontandBack=3000;
	int h = -(int)ymsvfi((Dpanel.joystickFrontandBack/50)*50,joystickFrontandBack,joystickFrontandBack1);
	SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_HEADING, h, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	//驾驶杆左右
	if(Dpanel.joystickLeftandRight<300)
		Dpanel.joystickLeftandRight=300;
	else if(Dpanel.joystickLeftandRight>2700)
		Dpanel.joystickLeftandRight=2700;
	h=-(int)ymsvfi((Dpanel.joystickLeftandRight/50)*50,joystickLeftandRight,joystickLeftandRight1);
	SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_BANK, h, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	
	//油门
	h=(int)ymsvfi((Dpanel.gun/50)*50,gun,gun1);
	SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_THROTTLE, h, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	//燃油混合柄
	h=(int)ymsvfi((Dpanel.fuelHandShank/50)*50,fuelHandShank,fuelHandShank1);
	SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_MIXTURE, h, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	//脚蹬
	
	h=(int)ymsvfi((Dpanel.footlock/50)*50,footlock,footlock1);
	SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_RUDDER,-h, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);

	//襟翼
	h=(int)ymsvfi((Dpanel.flap/50)*50,flap,flap1);
	SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_FLAP,h, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);

	//配平手轮
	/*if(Dpanel.wheel > 2099) Dpanel.wheel = 2099;
	if(Dpanel.wheel < 2000) Dpanel.wheel = 2000;*/
	int w = (int)ymsvfi((float)(Dpanel.wheel%100),wheel,wheel1);
	//printf("配平手轮：%d\n", w);
	SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_ELEVATORTRIM, -w , SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	
	//刹车;
	int barkerNum1 = (int)ymsvfi((float)Dpanel.barker1,barker,barker1);
	int barkerNum2 = (int)ymsvfi((float)Dpanel.barker2,barker,barker1);
	
	int barkerNum3 = (int)ymsvfi((float)Dpanel.barker3,barker,barker1);
	//刹车溢出需要做处理
	if(Dpanel.barker4>2000 ) Dpanel.barker4 =0;
	int barkerNum4 = (int)ymsvfi((float)Dpanel.barker4,barker,barker1);
	
	
	if(barkerNum1>12000 || barkerNum2>12000 || barkerNum3>12000||barkerNum4>12000)
	{
		int barkerNum =16383;
		printf("刹车: %d\n", barkerNum);
	    SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_BRAKES, barkerNum, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	}

	//点火开关
	if(Dpanel.fireOn == true)
	{
		 SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_MAGNETOON, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	}
	else if(Dpanel.fireRight == true)
	{
		 SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_MAGNETOR, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	}
	else if(Dpanel.fireLeft == true)
	{
		 SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_MAGNETOL, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	}
	if(Dpanel.fireOff == true)
	{
		 SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_MAGNETOOFF, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	}
	
	//灯控制
	//if(Dpanel.pump == true)
	//{
	//	SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_FUELPUMP, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	//	printf("1");
	//}
	//else
	//{
	//	SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_FUELPUMP, 1, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	//	printf("2");
	//}
	//定义一个变量保存上次接受的数
	static bool bpubf=false;

	//和上一次的数做比较
	if(bpubf!=Dpanel.pump)
	{
		SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_FUELPUMP, 1, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	}
	bpubf=Dpanel.pump;
	////落地灯
	//if(Dpanel.landing == true)
	//{
	//	SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_LANDINGLIGHTS, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	//}
	//else
	//{
	//	SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_LANDINGLIGHTS, 1, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	//}
	static bool bland=false;
	if(Dpanel.landing!=bland)
	{
		SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_LANDINGLIGHTS, 1, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	}
	bland=Dpanel.landing;
	////航向灯
	//if(Dpanel.navLight == true)
	//{
	//	SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_NAVLIGHTS, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	//}
	//else
	//{
	//	SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_NAVLIGHTS, 1, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	//}
	static bool bnavlight=false;
	if(Dpanel.navLight!=bnavlight)
	{
		SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_NAVLIGHTS, 1, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	}
	bnavlight=Dpanel.navLight;
	////指引灯
	//if(Dpanel.beacon == true)
	//{
	//	SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_BACONLIGHTS, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	//}
	//else
	//{
	//	SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_BACONLIGHTS, 1, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	//}
	static bool bbeacon=true;
	if(Dpanel.beacon!=bbeacon)
	{
		SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_BACONLIGHTS, 1, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	}
	bbeacon=Dpanel.beacon;
	if(Dpanel.pitot == true)
	{
		SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_PITOT_ON, 1, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	}
	else
	{
		SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_PITOT_ON, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	}
	
	/*static bool bpitot=true;
	if(Dpanel.pitot!=bpitot)
	{
		SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_MAGNETOOFF, 1, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	}
	bpitot=Dpanel.pitot;*/
	////频闪灯
	//if(Dpanel.strobe == true)
	//{
	//	SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_STROBE, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	//}
	//else
	//{
	//	SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_STROBE, 1, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	//}
	static bool bstrobe=false;
	if(bstrobe!=Dpanel.strobe)
	{
		SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_STROBE, 1, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	}
	bstrobe=Dpanel.strobe;
	////滑行灯
	//if(Dpanel.taxi == true)
	//{
	//	SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_TAIXLIGHTS, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	//}
	//else
	//{
	//	SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_TAIXLIGHTS, 1, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	//}
	static bool btaxi=false;
	if(btaxi!=Dpanel.taxi)
	{
		SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_TAIXLIGHTS, 1, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	}
	btaxi=Dpanel.taxi;
	//船型开关控制
	if(Dpanel.masterBattery == true)
	{
		SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_MASTERBATT, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	}
	if(Dpanel.masterAlt == true)
	{
		SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_MASTERALTERNATE, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	}
	if(Dpanel.masterStatic == true)
	{
		SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_ALTERNATE, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	}


	//面板灯开关
	if(Dpanel.PLightOn == true)
	{
		SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_PANELLIGHTSON, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	}
	else
	{
		SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_PANELLIGHTSOFF, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	}

	//fule switch1
	if(Dpanel.fuelControl == true)
	{
		SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_ENGINE1, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	}
	
	//油箱选择
	if(Dpanel.tankAll == true)
	{
		SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_TANKALL, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	}
	else if(Dpanel.tankLeft == true)
	{
		SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_TANKLEFT, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	}
	else if(Dpanel.tankRight == true)
	{
		SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_TANKRIGHT, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	}

	//面板旋钮电位计
	if(RMeter.HD > oldhd)
	{
		SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_HDINC, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
		oldhd = RMeter.HD;
	}
	else if(RMeter.HD < oldhd)
	{
		SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_HDDEC, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
		oldhd = RMeter.HD;
	}
	if(RMeter.HDBUG<80)
		RMeter.HDBUG=80;
	else if(RMeter.HDBUG>3970)
		RMeter.HDBUG=3970;
	RMeter.HDBUG=(RMeter.HDBUG/50)*50;
	SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_HDBUGDEC,(int)ymsvfi(RMeter.HDBUG,selectdir,selectdir1), SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	/*if(RMeter.HDBUG > oldhdbug)
	{
		SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_HDBUGINC, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
		oldhdbug = RMeter.HDBUG;
	}
	else if(RMeter.HDBUG < oldhdbug)
	{
		SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_HDBUGDEC, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
		oldhdbug = RMeter.HDBUG;
	}*/

	/*printf("Vor1:%d \n",RMeter.VOR1);
	printf("Vor2:%d \n",RMeter.VOR2);
	printf("ALT:%d \n",RMeter.ALT);
	printf("HD:%d \n",RMeter.HD);
	printf("HDBUG:%d \n",RMeter.HDBUG);
	printf("ADF:%d \n",RMeter.ADF);
	printf("****************************************************\n");*/
	if(RMeter.ALT<80)
		RMeter.ALT=80;
	else if(RMeter.ALT>3970)
		RMeter.ALT=3970;
	RMeter.ALT=(RMeter.ALT/50)*50;
	SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_ALTDEC,ymsvfi(RMeter.ALT,selectpa,selectpa1), SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	/*if(RMeter.ALT > oldalt)
	{
		SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_ALTINC, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
		oldalt = RMeter.ALT;
	}
	else if(RMeter.ALT < oldalt)
	{
		SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_ALTDEC, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
		oldalt = RMeter.ALT;
	}*/

	/*if(RMeter.VOR1 > oldvor1)
	{
		SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_VOR1INC, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
		oldvor1 = RMeter.VOR1;
	}
	else if(RMeter.VOR1 < oldvor1)
	{
		SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_VOR1DEC, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
		oldvor1 = RMeter.VOR1;
	}*/
	
	SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_VOR1INC, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	if(RMeter.VOR2 > oldvor2)
	{
		SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_VOR2INC, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
		oldvor2 = RMeter.VOR2;
	}
	else if(RMeter.VOR2 < oldvor2)
	{
		SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_VOR2DEC, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
		oldvor2 = RMeter.VOR2;
	}

	if( RMeter.ADF > oldadf)
	{
		SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_ADFINC, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
		oldadf = RMeter.ADF;
	}
	else if( RMeter.ADF < oldadf)
	{
		SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_ADFDEC, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
		oldadf = RMeter.ADF;
	}

	//自动飞行开关
	if(apBuffer[0]==apBuffer[1]&&apBuffer[2]==apBuffer[1]&&apBuffer[2]==apBuffer[0]){
	static bool bapf=true;
	if(Dpanel.ap==true)
	{
		apf=1;
	}
	else if(Dpanel.ap==false&&apf==1)
	{
		if(bapf&&apl==0)
		{
			apl=1;
			SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_AP_ON, 0 , SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
		}else
		{
			apl=0;
			SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_AP_OFF, 0 , SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
		}
		apf=0;
		bapf=!bapf;
	}

	//自动航向
	static bool bhdg = true;
	if(Dpanel.hdg == true)
	{
		hdf=1;
	}
	else if(Dpanel.hdg ==false &&hdf==1)
	{
		if(bhdg||hdl==0)
		{
			hdl=1;
			apl=1;
			SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_HD_ON, 0 , SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
		}
		else
		{
			hdl=0;
			SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_HD_OFF, 0 , SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
		}
		hdf=0;
		bhdg =!bhdg;
	}

	//导航
	static bool bnav = true;
	if(Dpanel.nav == true)
	{
		navf=1;
	}
	else if(Dpanel.nav ==false &&navf==1)
	{
		if(bnav||navl==0)
		{
			navl=1;
			aprl=0;
			apl=1;
			SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_NAV_ON, 0 , SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
		}
		else
		{
			navl=0;
			SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_NAV_OFF, 0 , SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
		}
		navf=0;
		bnav =!bnav;
	}


	//apr
	static bool bapr = true;
	if(Dpanel.apr == true)
	{
		aprf=1;
	}
	else if(Dpanel.apr ==false &&aprf==1)
	{
		if(bapr||aprl==0)
		{
			aprl=1;
			navl=0;
			apl=1;
			SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_APR_ON, 0 , SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
		}
		else
		{
			aprl=0;
			SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_APR_OFF, 0 , SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
		}
		aprf=0;
		bapr =!bapr;
	}

	//rev
	static bool brev = true;
	if(Dpanel.rev == true)
	{
		revf=1;
	}
	else if(Dpanel.rev ==false &&revf==1)
	{
		if(brev)
		{
			revl=1;
			apl=1;
			SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_REV_ON, 0 , SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
		}
		else
		{
			revl=0;
			SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_REV_OFF, 0 , SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
		}
		revf=0;
		brev =!brev;
	}

	//alt
	static bool balt = true;
	if(Dpanel.alt == true)
	{
		altf=1;
	}
	else if(Dpanel.alt ==false &&altf==1)
	{
		if(balt)
		{
			altl=1;
			apl=1;
			SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_AT_ON, 0 , SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
		}
		else
		{
			altl=0;
			SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_AT_OFF, 0 , SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
		}
		altf=0;
		balt =!balt;
	}

};
	/*if(Dpanel.up == true)
	{
		SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_AT_INC, 100, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	}
	

	if(Dpanel.dn == true)
	{
		SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_AT_DEC, 100, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	}*/
	static int iup=0;
	static int idn=0;
	if(Dpanel.up == true){
	iup++;
	}
	if(Dpanel.dn == true){
	idn++;
	}

	if(iup>4)
	{
		iup=0;
		SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_AT_INC, 100, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	}
	

	if(idn>4)
	{
		idn=0;
		SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_AT_DEC, 100, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	}
}


void CALLBACK Fsx::MyDispatchProcRD(SIMCONNECT_RECV *pData, DWORD cbData, void *pContext)
{
	HRESULT hr;
    switch(pData->dwID)
    {
      
		case SIMCONNECT_RECV_ID_EVENT:
        {
            SIMCONNECT_RECV_EVENT *evt = (SIMCONNECT_RECV_EVENT*)pData;
            switch(evt->uEventID)
            {
				case EVENT1:
					hr = SimConnect_RequestDataOnSimObjectType(hSimConnect, REQUEST_1, DEFINITION_1, 0, SIMCONNECT_SIMOBJECT_TYPE_USER);
					break;
					case EVENT_SIM_START:
						printf("START\n");
						break;
                default:
                   break;
            }
            break;
        }

		case SIMCONNECT_RECV_ID_SIMOBJECT_DATA_BYTYPE:
        {
            SIMCONNECT_RECV_SIMOBJECT_DATA_BYTYPE *pObjData = (SIMCONNECT_RECV_SIMOBJECT_DATA_BYTYPE*)pData;
            switch(pObjData->dwRequestID)
            {
                case REQUEST_1:
                {
					memset(&Mdata,0,sizeof(MeterData));
                    MeterData * pS = (MeterData*)&pObjData->dwData;	
					//printf("*********************↓******************\n");	
					memcpy(&Mdata,pS,sizeof(MeterData));
				/*	printf("空速：%2.2f\n",Mdata.airSpeed);
					printf("升降速度：%2.2f\n",Mdata.verSpeed);
					printf("高度：%2.2f\n",Mdata.altmeter);
					printf("俯仰角：%2.2f\n",Mdata.bank);
					printf("翻滚角：%2.2f\n",Mdata.pitch);

					
					printf("总油量：%2.2f\n",Mdata.totalFuel);
					printf("TK1：%2.2f\n",Mdata.fuelTK1);
					printf("TKSEL：%2.2f\n",Mdata.fuelTKSEL);
					printf("LTK：%2.2f\n",Mdata.fuelLTK);

					printf("RTK：%2.2f\n",Mdata.fuelRTK);
					printf("TK4：%2.2f\n",Mdata.fuelTK4);
					printf("LEXT：%2.2f\n",Mdata.fuelLEXT);
					printf("CEXT：%2.2f\n",Mdata.fuelCEXT);
					printf("REXT：%2.2f\n",Mdata.fuelREXT);
					printf("hsel：%2.2f\n",Mdata.hsel);
					printf("head：%2.2f\n",Mdata.head);
					printf("n1：%2.2f\n",Mdata.n1);
					printf("n2：%2.2f\n",Mdata.n2);
					printf("temT4：%2.2f\n",Mdata.temT4);*/
					//printf("n1：%2.2f\n",Mdata.autoAlt);
					//printf("n2：%2.2f\n",Mdata.autoVspeed);
					break;
                }
                default:
                   break;
            }
            break;
        }

        case SIMCONNECT_RECV_ID_QUIT:
        {
            quit = 1;
            break;
        }

        default:
           // printf("\nReceived:%d\n",pData->dwID);
            break;
    }
}
Fsx::~Fsx(void)
{
}
