#ifndef NETDATA_H
#define NETDATA_H


//��λ������
struct DatePanel
{
	int	barker1;					//ɲ��
	int	barker2;					//ɲ��
	int	barker3;					//ɲ��
	int	barker4;					//ɲ��

	int	fuelHandShank;			//ȼ�ͻ�ϱ�
	int	joystickFrontandBack;	//��ʻ��ǰ��
	int	joystickLeftandRight;	//��ʻ������
	int gun;					//����						
	int footlock;				//�ŵ�
	int flap;                   //����
	int wheel;					//��ƽ����
	int zongju;					//�ܾ�
	bool retract;				//���������
	bool laydown;				//����
	bool middel;				//�м�
	
	bool aileronl;				//��ת��
	bool aileronr;				//��ת��
	bool autofly;				//�Զ�����
	bool fireOn;				//���
	bool fireOff;
	bool fireLeft;
	bool fireRight;

	//�ƿ���
	bool pump;
	bool beacon;
	bool landing;
	bool taxi;
	bool navLight;
	bool strobe;
	bool pitot;

	//��Դ����
	bool masterBattery;
	bool masterAlt;
	bool masterStatic;

	//���ƿ���
	bool PLightOn;
	bool PLightOff;

	//fuelControl
	bool fuelControl;

	//����ѡ��
	bool tankAll;
	bool tankLeft;
	bool tankRight;

	//�Զ����а�ť
	bool	ap;				
	bool	hdg;			
	bool	nav;			
	bool	apr;			
	bool	rev;									
	bool	alt;			
	bool    up;				
	bool    dn;		



};

//�Ǳ�����
struct MeterData
{
	double	AirSpeed;					//�ٶ�
	double  Altitude;					//�߶�
	double  Bank;						//��ƽ������
	double  Pitch;						//��ƽ������
	double  TurnDegrees;				//ת���
	double  HeadIndicator;				//�����
	double  VerSpeed;					//��ֱ�ٶ�
	double  EngTachmeter;				//������ת��
	double  NavVor1;
	double  NavVor2;					
	double  AdfIndicator;
	double  LeftFuel;					//������
	double  RightFuel;					//������
	double  ExhaustTmp;					//�����¶�
	double  FuelFlow;					//������
	double  OilTem;						//ȼ���¶�
	double  OilPress;					//ȼ��ѹ��
	double  Althg;						//�߶ȱ��趨��ѹ
	double  SelectDir;					//Ԥ������
	double  Suction;					//����ѹ��
	double  Amps;						//��ѹ
	double  autoAlt;					//�Զ����и߶�
	double  autoVspeed;                 //�Զ����д�ֱ�ٶ�
	double ball;//�໬��
};

struct MeterDataSocket
{
	float airspeed;//���� ���ٱ�
	float altimeter;//��ѹ�߶� �߶ȱ�
	float Bank;//��ת��	��ƽ��
	float Pitch;//������		��ƽ��
	float turnSpeed;//ת���� ƫ��ָʾ��
	float heading;//��ǰ���� ���ߵ�����
	float verticalSpeed;//�����ٶ� ��ֱ���ʱ�
	float engineRpm;//������ת�� ת�ٱ�
	float navOBS1;//�����»���ָʾ��
	float	navOBS2;//����ָʾ��
	float adfCard;//adfָʾ��
	float leftFuelLevel;//���������� ������
	float rightFuelLevel;//���������� ������
	float exhaustTemp;//�����¶� ȼ�������������¶ȱ�
	float fuelFlow;//ȼ������ ȼ�������������¶ȱ�
	float oilTemp;//�����¶�
	float oilPress;//����ѹ��
	float amp;//������� �������������
	float vac;//���� �������������
	float althg;//�߶ȱ��趨��ѹ
	float selectDir;//Ԥ������
	float ball;//�໬��
};

struct RecMeter{
int HD;//����
int ALT;//�߶�
int HDBUG;//HDG
int VOR1;//vor1
int VOR2;//VOR2
int ADF;//ADF_CARD
};


//����ͷ
struct HeadData
{
	char hd[6];//16����
};

//��λ����������
struct SendData
{
	HeadData head;				//����ͷ 3�ֽ�
	//short meter[18];			//�Ǳ����� 36�ֽ�
	char lights[3];				//�ƿ��� 9�ֽ�
	//char reserveByte[8];		//�������� 8�ֽ�
};

static enum DATA_DEFINE_ID {
    DEFINITION_1
};

static enum EVENT_ID{
	EVENT1,
	EVENT_ENGON,	//�����
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

	//�����ť
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

	//�Զ�����
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
	//ϵͳ�¼�
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

//���ݰ�
extern struct DatePanel Dpanel; //��������
extern struct MeterData Mdata;
extern struct MeterDataSocket MeterSocketData;	//�����Ǳ�����
extern struct SendData Sdata;	//��������
extern struct RecMeter RMeter; //�����ť����

//socket ͨѶ�Ǳ�
//extern struct Meter ;
//fsx��Ҫ����
extern HANDLE  hSimConnect;
extern int     quit;

extern HANDLE g_hOutput;		//������ھ��




//ɲ��
extern float barker[3];
extern float barker1[2];

//ȼ�ͻ���ֱ�
extern float fuelHandShank[3];
extern float fuelHandShank1[2];

//��ʻ��ǰ��
extern float joystickFrontandBack[6];
extern float joystickFrontandBack1[5];

//��ʻ������
extern float joystickLeftandRight[4];
extern float joystickLeftandRight1[3];

//�ܾ�
extern float zongju[3];
extern float zongju1[2];

//����
extern float gun[3];
extern float gun1[2];

//��̤��
extern float footlock[6];
extern float footlock1[5];

//����
extern float flap[3];
extern float flap1[2];

extern float wheel[4];
extern float wheel1[3];

extern float selectdir[3];
extern float selectdir1[2];

//�趨��ѹ
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

//�Լݼ������
extern unsigned char apBuffer[3];
#endif