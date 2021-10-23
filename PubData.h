#ifndef NETDATA_H
#define NETDATA_H


//下位机数据
struct DatePanel
{
	int	barker1;					//刹车
	int	barker2;					//刹车
	int	barker3;					//刹车
	int	barker4;					//刹车

	int	fuelHandShank;			//燃油混合柄
	int	joystickFrontandBack;	//驾驶杆前后
	int	joystickLeftandRight;	//驾驶杆左右
	int gun;					//油门						
	int footlock;				//脚蹬
	int flap;                   //襟翼
	int wheel;					//配平手轮
	int zongju;					//总距
	bool retract;				//起落架收起
	bool laydown;				//放下
	bool middel;				//中间
	
	bool aileronl;				//左转向
	bool aileronr;				//右转向
	bool autofly;				//自动飞行
	bool fireOn;				//点火
	bool fireOff;
	bool fireLeft;
	bool fireRight;

	//灯开关
	bool pump;
	bool beacon;
	bool landing;
	bool taxi;
	bool navLight;
	bool strobe;
	bool pitot;

	//电源开关
	bool masterBattery;
	bool masterAlt;
	bool masterStatic;

	//面板灯开关
	bool PLightOn;
	bool PLightOff;

	//fuelControl
	bool fuelControl;

	//油箱选择
	bool tankAll;
	bool tankLeft;
	bool tankRight;

	//自动飞行按钮
	bool	ap;				
	bool	hdg;			
	bool	nav;			
	bool	apr;			
	bool	rev;									
	bool	alt;			
	bool    up;				
	bool    dn;		



};

//仪表数据
struct MeterData
{
	double	AirSpeed;					//速度
	double  Altitude;					//高度
	double  Bank;						//地平仪数据
	double  Pitch;						//地平仪数据
	double  TurnDegrees;				//转弯角
	double  HeadIndicator;				//方向角
	double  VerSpeed;					//垂直速度
	double  EngTachmeter;				//发动机转速
	double  NavVor1;
	double  NavVor2;					
	double  AdfIndicator;
	double  LeftFuel;					//左油箱
	double  RightFuel;					//右油箱
	double  ExhaustTmp;					//排气温度
	double  FuelFlow;					//油流量
	double  OilTem;						//燃油温度
	double  OilPress;					//燃油压力
	double  Althg;						//高度表设定气压
	double  SelectDir;					//预定航向
	double  Suction;					//进气压力
	double  Amps;						//电压
	double  autoAlt;					//自动飞行高度
	double  autoVspeed;                 //自动飞行垂直速度
	double ball;//侧滑角
};

struct MeterDataSocket
{
	float airspeed;//空速 空速表
	float altimeter;//气压高度 高度表
	float Bank;//滚转角	地平仪
	float Pitch;//俯仰角		地平仪
	float turnSpeed;//转弯率 偏航指示器
	float heading;//当前航向 无线电罗盘
	float verticalSpeed;//升将速度 垂直速率表
	float engineRpm;//发动机转速 转速表
	float navOBS1;//航道下滑道指示器
	float	navOBS2;//航道指示器
	float adfCard;//adf指示器
	float leftFuelLevel;//左油箱油量 油量表
	float rightFuelLevel;//右油箱油量 油量表
	float exhaustTemp;//排气温度 燃油流量及排气温度表
	float fuelFlow;//燃油流量 燃油流量及排气温度表
	float oilTemp;//滑油温度
	float oilPress;//滑油压力
	float amp;//真空吸力 真空吸力电流表
	float vac;//电流 真空吸力电流表
	float althg;//高度表设定气压
	float selectDir;//预定航向
	float ball;//侧滑角
};

struct RecMeter{
int HD;//航向
int ALT;//高度
int HDBUG;//HDG
int VOR1;//vor1
int VOR2;//VOR2
int ADF;//ADF_CARD
};


//数据头
struct HeadData
{
	char hd[6];//16进制
};

//上位机发送数据
struct SendData
{
	HeadData head;				//数据头 3字节
	//short meter[18];			//仪表数据 36字节
	char lights[3];				//灯开关 9字节
	//char reserveByte[8];		//保留数据 8字节
};

static enum DATA_DEFINE_ID {
    DEFINITION_1
};

static enum EVENT_ID{
	EVENT1,
	EVENT_ENGON,	//引擎关
	EVENT_ENGOFF,
	EVENT_MAGNETOON,
	EVENT_MAGNETOOFF,
	EVENT_MAGNETOL,
	EVENT_MAGNETOR,
	EVENT_MAGNETOB,
	EVENT_MASTERBATT,
	EVENT_MASTERALTERNATE,
	EVENT_ALTERNATE,

	EVENT_ENGINE1,
	EVENT_THROTTLE,
	EVENT_HEADING,
	EVENT_BANK,
	EVENT_RUDDER,
	EVENT_MIXTURE,
	EVENT_FLAP,
	EVENT_ELEVATORTRIM,
	EVENT_BRAKES,

	EVENT_PANELLIGHTSON,
	EVENT_PANELLIGHTSOFF,

	EVENT_NAVLIGHTS,
	EVENT_BACONLIGHTS,
	EVENT_FUELPUMP,
	EVENT_LANDINGLIGHTS,
	EVENT_TAIXLIGHTS,
	EVENT_STROBE,
	EVENT_TANKALL,
	EVENT_TANKLEFT,
	EVENT_TANKRIGHT,
	EVENT_PITOT_ON,
	EVENT_PITOT_OFF,

	//面板旋钮
	EVENT_ALTINC,
	EVENT_ALTDEC,
	EVENT_HDINC,
	EVENT_HDDEC,
	EVENT_HDBUGDEC,
	EVENT_HDBUGINC,
	EVENT_VOR1DEC,
	EVENT_VOR1INC,
	EVENT_VOR2DEC,
	EVENT_VOR2INC,
	EVENT_ADFDEC,
	EVENT_ADFINC,

	//自动飞行
	EVENT_AP_ON,
	EVENT_AP_OFF,
	EVENT_HD_ON,
	EVENT_HD_OFF,
	EVENT_NAV_ON,
	EVENT_NAV_OFF,
	EVENT_APR_ON,
	EVENT_APR_OFF,
	EVENT_REV_ON,
	EVENT_REV_OFF,
	EVENT_AT_ON,
	EVENT_AT_OFF,
	EVENT_AT_INC,
	EVENT_AT_DEC,
	EVENT_VR_INC,
	EVENT_VR_DEC,
	//系统事件
	EVENT_SIM_START,
	EVENT_SIM_RESTRAR,


};

static enum DATA_REQUEST_ID {
    REQUEST_1,
};

static enum GROUP_ID
{
	GROUP1,
};

//数据包
extern struct DatePanel Dpanel; //接收数据
extern struct MeterData Mdata;
extern struct MeterDataSocket MeterSocketData;	//测试仪表数据
extern struct SendData Sdata;	//发送数据
extern struct RecMeter RMeter; //面板旋钮数据

//socket 通讯仪表
//extern struct Meter ;
//fsx需要变量
extern HANDLE  hSimConnect;
extern int     quit;

extern HANDLE g_hOutput;		//输出窗口句柄




//刹车
extern float barker[3];
extern float barker1[2];

//燃油混合手柄
extern float fuelHandShank[3];
extern float fuelHandShank1[2];

//驾驶杆前后
extern float joystickFrontandBack[6];
extern float joystickFrontandBack1[5];

//驾驶杆左右
extern float joystickLeftandRight[4];
extern float joystickLeftandRight1[3];

//总距
extern float zongju[3];
extern float zongju1[2];

//油门
extern float gun[3];
extern float gun1[2];

//脚踏板
extern float footlock[6];
extern float footlock1[5];

//襟翼
extern float flap[3];
extern float flap1[2];

extern float wheel[4];
extern float wheel1[3];

extern float selectdir[3];
extern float selectdir1[2];

//设定场压
extern float selectpa[3];
extern float selectpa1[2];

extern int oldhd;
extern int oldhdbug;
extern int oldalt;
extern int oldvor1;
extern int oldvor2;
extern int oldadf;
extern int apf;
extern int hdf;
extern int navf;
extern int aprf;
extern int revf;
extern int altf;

extern int apl;
extern int hdl;
extern int navl;
extern int aprl;
extern int revl;
extern int altl;

//自驾检测数据
extern unsigned char apBuffer[3];
#endif