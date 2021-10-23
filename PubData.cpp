
#include "stdafx.h"
#include "PubData.h"


HANDLE  hSimConnect=NULL;
int     quit=0;
HANDLE g_hOutput=NULL;//输出窗口句柄

int oldhd=0;
int oldhdbug=0;
int oldalt=0;
int oldvor1=0;
int oldvor2=0;
int oldadf=0;

int apf=0;
int hdf=0;
int navf=0;
int aprf=0;
int revf=0;
int altf=0;

int apl=0;
int hdl=0;
int navl=0;
int aprl=0;
int revl=0;
int altl=0;

unsigned char apBuffer[3];

//数据包
struct DatePanel Dpanel;
struct MeterData Mdata;
struct SendData Sdata;
struct MeterDataSocket MeterSocketData;
struct RecMeter RMeter; //面板旋钮数据
//刹车
float barker[3]={	2.0	,		0,	1200.0	};
float barker1[2]={	0.0	,	   		16383.0	};

//燃油混合手柄
float fuelHandShank[3]={2.0,1050,3950.0};
float fuelHandShank1[2]={0,16383.0};


//驾驶杆前后
float joystickFrontandBack[6]={	5.0	,544, 1560, 1660, 1760, 3000};
float joystickFrontandBack1[5]={				-16383.0,  0, 0.0, 0	, 16383.0	};

//驾驶杆左右
float joystickLeftandRight[4]={	3.0	,		300.0,		1500.0	,	2700.0	};
float joystickLeftandRight1[3]={				-16383.0,	     0.0	,	16383.0	};


//油门
float gun[3]={		2.0	,		6.0,		3840.0	};
float gun1[2]={0.0	,16383.0	};

//脚踏板
float footlock[6]={	5.0	,	850.0 ,		1400,1600.0	,1700,	2700.0	};
float footlock1[5]={		    -16383.0,	     0, 0.0	,0,	16383.0 };

//襟翼
float flap[3] ={	2.0,	1970.0	,	2500.0	};
float flap1[2] ={	0.0	,	    	16383.0	};

//配平手轮
float wheel[4]={	3.0	,		0,		50.0	,	100};
float wheel1[3]={				 -16383.0,	   0	,	16383.0	};

//预定航向
float selectdir[3]={2.0,80.0,3970.0};
float selectdir1[2]={0.0,360.0};

//设定场压
float selectpa[3]={2.0,0.0,3900.00};
float selectpa1[2]={15200.0,17100.0};