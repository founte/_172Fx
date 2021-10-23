// UARTDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UART.h"
#include "UARTDlg.h"
#include "string.h"
#include "pubData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUARTDlg dialog

CUARTDlg::CUARTDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUARTDlg::IDD, pParent)
	, EditText(_T(""))
{
	//{{AFX_DATA_INIT(CUARTDlg)
	m_RxData = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUARTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUARTDlg)
	DDX_Control(pDX, IDC_COMBO2, m_Uart_Speed);
	DDX_Control(pDX, IDC_COMBO1, m_COM_Num);
	DDX_Control(pDX, IDC_MSCOMM1, m_CMSComm);
	DDX_Text(pDX, IDC_EDIT_Rpond,m_RxData);
	//}}AFX_DATA_MAP

	DDX_Control(pDX, IDC_Display, m_ListCtrl);
	DDX_Text(pDX, IDC_EDIT_Tpond, EditText);
}

BEGIN_MESSAGE_MAP(CUARTDlg, CDialog)
	//{{AFX_MSG_MAP(CUARTDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OpenPort, OnBUTTONOpenPort)
	ON_BN_CLICKED(IDC_BUTTON_Clean, OnBUTTONClean)

	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_AUTOSend, &CUARTDlg::OnBnClickedButtonAutosend)

	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CUARTDlg::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUARTDlg message handlers
void CUARTDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CUARTDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}


HCURSOR CUARTDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//初始化对话框
BOOL CUARTDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	/****************************窗体初始化**************************/	
	// TODO: Add extra initialization here
	pStatic = (CStatic*)GetDlgItem(IDC_LED);//初始化时显示黑色图标
	m_hicn_on =AfxGetApp()->LoadIcon(IDI_ICON2); //定义图标
	m_hicn_off=AfxGetApp()->LoadIcon(IDI_ICON1); //定义图标
	m_COM_Num.SetCurSel(6);//初始化显示COM3
	m_Uart_Speed.SetCurSel(23);//初始化波特率2M
	//SetDlgItemText(IDC_EDIT_Tpond,"");
	SetDlgItemText(IDC_EDIT_AUTO_Timer,"50");//默认自动发送周期为100毫秒
	Send_or_Rece = 0;
	Autosend = 0;
	flag = 0;
	f1=0;
	f2=0;
	EditText=_T("");
	//UpdateData(false);
	memset(Sdata.lights,255,3);
	///**********隐藏窗口********/
	//WINDOWPLACEMENT m_wp;

	//GetWindowPlacement(&m_wp);

	//ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW);
	//WINDOWPLACEMENT	wp;
	//wp.length=sizeof(WINDOWPLACEMENT);
	//wp.flags=WPF_RESTORETOMAXIMIZED;
	//wp.showCmd=SW_HIDE;
	//SetWindowPlacement(&wp);
	//

	/****************Tab控件初始化**********************/	
	/*m_TabCtrl.InsertItem(0,"接受数据包   ");
	TabCtrl_num=0;*/
	//m_TabCtrl.SetCurFocus(TabCtrl_num);//Tab控件初始位置

	 //列表控件初始化
	 CRect rect1;	
	 m_ListCtrl.GetWindowRect( &rect1 );
	 m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES
			|LVS_SHOWSELALWAYS|LVS_EX_ONECLICKACTIVATE|LVS_EDITLABELS |LVCFMT_LEFT);
	 LV_COLUMN Lvcolumn1;
	 for(int i=0; i<4; i++) 
	 {
		 Lvcolumn1.mask = LVCF_FMT|LVCF_SUBITEM|LVCF_TEXT|LVCF_WIDTH|LVCF_ORDER;
		 Lvcolumn1.fmt = LVCFMT_LEFT;
		 if( i==0 )
		 {
			 Lvcolumn1.pszText =_T("   变量名");
			 Lvcolumn1.cx = rect1.Width()/6;
		 }
		 if( i==1 ) 
		 {
			 Lvcolumn1.pszText =_T("         变量含义");
			 Lvcolumn1.cx = rect1.Width()/3;
		 }
		 if( i==2 ) 
		 {
			 Lvcolumn1.pszText =_T(" 变量值");
			 Lvcolumn1.cx = rect1.Width()/8;
		 }
		 if( i==3 ) 
		 {
			 Lvcolumn1.pszText =_T("           备注");
			 Lvcolumn1.cx = rect1.Width()/3;
		 }
		 Lvcolumn1.iSubItem = 1;
		 Lvcolumn1.iOrder = i;
		 m_ListCtrl.InsertColumn(i, &Lvcolumn1);	
	 }
	 //初始化ListCtrl控件显示
	Data_name();//显示数据名
	Equipment_name();//显示设备名称
	Signal_data();//显示数值
	//列表数值清零
	
	for(int j=0;j<76;j++)
	{
		COM_Data[0][j]=0;
	}
	OnBUTTONOpenPort();
	OnBnClickedButtonAutosend();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

//字符转十六进制
unsigned char CUARTDlg::CharToHex(unsigned char iChar)
{
	UCHAR	mBCD;
	if ( iChar >= '0' && iChar <= '9' ) mBCD = iChar -'0';
	else if ( iChar >= 'A' && iChar <= 'F' ) mBCD = iChar - 'A' + 0x0a;
	else if ( iChar >= 'a' && iChar <= 'f' ) mBCD = iChar - 'a' + 0x0a;
	else mBCD = 0;
	return( mBCD );
}
//解数据包
void CUARTDlg::Unlock_Data()
{
	int j;
	for(j=0;j<3;j++)//数据头，3字节
	{
		COM_Data[0][j]=Rxdata[j];
	}

	COM_Data[0][3]=Rxdata[3]*16+Rxdata[4]/162  
		;//2字节
	for(j=0;j<8;j++)//24字节
	{
		COM_Data[0][2*j+4]=Rxdata[5+3*j]*16+Rxdata[6+3*j]/16;
		COM_Data[0][2*j+5]=Rxdata[6+3*j]%16*256+Rxdata[7+3*j];
	}

	for(j=0;j<7;j++)//开关部分，7字节
	{
		COM_Data[0][8*j+20]=Rxdata[29+j]%0x100/0x80;
		COM_Data[0][8*j+21]=Rxdata[29+j]%0x80 /0x40;
		COM_Data[0][8*j+22]=Rxdata[29+j]%0x40 /0x20;
		COM_Data[0][8*j+23]=Rxdata[29+j]%0x20 /0x10;
		COM_Data[0][8*j+24]=Rxdata[29+j]%0x10 /0x08;
		COM_Data[0][8*j+25]=Rxdata[29+j]%0x08 /0x04;
		COM_Data[0][8*j+26]=Rxdata[29+j]%0x04/0x02;
		COM_Data[0][8*j+27]=Rxdata[29+j]%0x02/0x01;
	}

	apBuffer[2]=Rxdata[32];
	apBuffer[1]=Rxdata[33];
	apBuffer[0]=Rxdata[34];
}

//列表控件显示
void CUARTDlg::Data_name()
{
    //数据头
	m_ListCtrl.InsertItem(0 ,"0");
	m_ListCtrl.InsertItem(1 ,"1");
	m_ListCtrl.InsertItem(2 ,"2");
	
	//20AD
	m_ListCtrl.InsertItem(3,"配平手轮");

	m_ListCtrl.InsertItem(4,"燃油混合柄");
	m_ListCtrl.InsertItem(5,"AD3");
	m_ListCtrl.InsertItem(6,"AD4");
	m_ListCtrl.InsertItem(7,"脚蹬");
	m_ListCtrl.InsertItem(8,"AD6");
	m_ListCtrl.InsertItem(9,"周期边距配平开关（前后）");
	m_ListCtrl.InsertItem(10,"操纵左右");
	m_ListCtrl.InsertItem(11,"操纵前后");
	m_ListCtrl.InsertItem(12,"空");
	m_ListCtrl.InsertItem(13,"总距");
	m_ListCtrl.InsertItem(14,"aaa");
	m_ListCtrl.InsertItem(15,"左右");
	m_ListCtrl.InsertItem(16,"油门");
	m_ListCtrl.InsertItem(17,"燃油混合柄");
	m_ListCtrl.InsertItem(18,"周期边距配平开关左右");
	m_ListCtrl.InsertItem(19,"AD17");
	m_ListCtrl.InsertItem(20,"AD18");
	m_ListCtrl.InsertItem(21,"AD19");
	m_ListCtrl.InsertItem(22,"AD20");

	//7开关
	CString list;
	for(int i=0;i<104;i++)
	{
		list.Format("%d_%d 开关%d",34+i/8,i%8,i);
		m_ListCtrl.InsertItem(23+i,list);
	}
}

//第二列数据
void CUARTDlg::Equipment_name()
{
	CString str;
	for(int i=0;i<90;i++)
	{
		str.Format("Comm_Data[%d]",i);
	m_ListCtrl.SetItemText(i,1,str);
	}
}

//给列表赋值
void CUARTDlg::Signal_data()
{
	int i;
	char temp[10];
	Unlock_Data();
	for(i=0;i<76;i++)
	{
		_itoa_s(COM_Data[0][i],temp,10);
		m_ListCtrl.SetItemText(i,2,temp);		
	}
	UpdateData(FALSE);
}


//打开串口按钮
void CUARTDlg::OnBUTTONOpenPort()
{
	//常用波特率
	static long COM_rate[25]={300,600,900,1200,1800,2400,3600,4800,9600,14400,19200,28800,33600,
		             38400,56000,57600,76800,115200,128000,153600,230400,460800,921600,1500000,2000000};
	char COM_Init[30];//串口初始化字符串
	nPort=m_COM_Num.GetCurSel()+1;//获取当前下拉框位置,得到串口号

	uart_speed=COM_rate[m_Uart_Speed.GetCurSel()];//获取当前下拉框位置,得到波特率
	_itoa_s(uart_speed,COM_Init,10);
	strcat_s(COM_Init,",n,8,1");//字符串组合
    ///////////////////初始化串口///////////////////
	if(!m_CMSComm.GetPortOpen())//串口处于关闭时
	{
		m_CMSComm.SetCommPort(nPort);   //选择COM口
		m_CMSComm.SetInputMode(1); //输入方式为二进制方式
		m_CMSComm.SetInBufferSize(1024); //设置输入缓冲区大小
		m_CMSComm.SetOutBufferSize(512); //设置输出缓冲区大小
		m_CMSComm.SetSettings(COM_Init); 
		m_CMSComm.SetRThreshold(1);// 参数1表示每当串口接收缓冲区中有多于或等于1个字符时将引发一个接收数据的OnComm事件
		m_CMSComm.SetPortOpen(TRUE);//打开串口
		m_CMSComm.SetInputLen(0);  //设置当前接收区数据长度为0
		m_CMSComm.GetInput();    //先预读缓冲区以清除残留数据
		SetDlgItemText(IDC_BUTTON_OpenPort,"关闭串口");
		pStatic->SetIcon(m_hicn_on);//打开指示灯
	}
	else//串口已经打开时
	{
		m_CMSComm.SetPortOpen(FALSE);//关闭串口
		SetDlgItemText(IDC_BUTTON_OpenPort,"打开串口");
		pStatic->SetIcon(m_hicn_off);//关闭指示灯
	}
	
}



//自动发送函数
void CUARTDlg::OnBnClickedButtonAutosend()
{
	// TODO: 在此添加控件通知处理程序代码
	char temp[10];
	int timer;
	Autosend=!Autosend;//打开关闭自动发送
	if(Autosend==1)
	{
		
		GetDlgItemText(IDC_EDIT_AUTO_Timer,temp,10);
		timer=atoi(temp);
		SetTimer(1, timer, NULL);
		SetDlgItemText(IDC_BUTTON_AUTOSend,"关闭自动发送");
	}
	else
	{
		KillTimer(1); //关闭定时器
		SetDlgItemText(IDC_BUTTON_AUTOSend,"自动发送"); 	
	}
	//socket测试
	g_send_sock = new SocketUDP();
	if(!g_send_sock->Bind(8888))
	{
		printf("[ERROR]: bind socket fail!\n" );
	}
	m_thread = new Thread(ThreadNetTask,this);
	m_thread->Launch();
}

//socket测试函数
void CUARTDlg::ThreadNetTask(void* param)
{
	CUARTDlg* p = (CUARTDlg*)param;
	memset(&MeterSocketData,0,sizeof(MeterSocketData));
	int ret=0;
	while(1)
	{
		//发送仪表需要的数据
		fillSocketMdata();
		//printf("*****%f*********%d\n", MeterSocketData.fAltimeter,MeterSocketData.show);
		
		int r =  p->g_send_sock->Send((char*)&MeterSocketData,sizeof(MeterSocketData),"192.168.1.41",1111);
		int ret =p->g_send_sock->Receive((char *)&RMeter,sizeof(RMeter), NULL, NULL);
		if(ret==SOCKET_ERROR)
		{
			printf("最后的一个错误为%d\n",GetLastError());
		}
	}
}

float justFlag;//用于保存上次数据防止突变

//socket测试数据
void CUARTDlg::fillSocketMdata()
{
	if(justFlag-Mdata.AirSpeed<20&&justFlag-Mdata.AirSpeed>-20){
	//赋值给网络数据
	MeterSocketData.airspeed=Mdata.AirSpeed;
	
	MeterSocketData.altimeter=(float)Mdata.Altitude;
	MeterSocketData.Bank=-(float)Mdata.Bank;

	MeterSocketData.Pitch=-(float)Mdata.Pitch;
	MeterSocketData.turnSpeed=-(float)Mdata.TurnDegrees;
	MeterSocketData.heading=(float)Mdata.HeadIndicator;
	MeterSocketData.verticalSpeed=(float)Mdata.VerSpeed;
	MeterSocketData.engineRpm=(float)Mdata.EngTachmeter;
	MeterSocketData.navOBS1=(float)Mdata.NavVor1;
	MeterSocketData.navOBS2=(float)Mdata.NavVor2	;
	MeterSocketData.adfCard=(float)Mdata.AdfIndicator;
	MeterSocketData.leftFuelLevel=(float)Mdata.LeftFuel/10.0;
	MeterSocketData.rightFuelLevel=(float)Mdata.RightFuel/10.0;
	MeterSocketData.exhaustTemp=(float)Mdata.ExhaustTmp;
	//printf("%f %f\n",Mdata.RightFuel,Mdata.ExhaustTmp);
	MeterSocketData.fuelFlow=(float)Mdata.FuelFlow;
	MeterSocketData.oilTemp=(float)Mdata.OilTem;
	MeterSocketData.oilPress=(float)Mdata.OilPress;
	MeterSocketData.amp=(float)Mdata.Amps;
	MeterSocketData.vac=(float)Mdata.Suction;
	MeterSocketData.althg=(float)Mdata.Althg;
	MeterSocketData.selectDir=(float)Mdata.SelectDir;
	MeterSocketData.ball=(float)Mdata.ball;
	}
	justFlag=Mdata.AirSpeed;
}

//定时器函数
void CUARTDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent)
	{
	case 1://执行串口读写
		{
			if(Send_or_Rece==0)
			{
				UpdateData(true);
				if(EditText!="") SendInit();
				else
				{
					ComPressData();
					SendData(Sendtemp,56);
				}
			}
			else
			{
				RecvData();
				DataCtrl();
			}
			Send_or_Rece=!Send_or_Rece;
			break;
		}
	case 2://定时器
		{
			time++;
		}
		break;
	}
	CDialog::OnTimer(nIDEvent);
}

void CUARTDlg::SendInit()
{
	char Buffer[1024]="";
	int len,i;
	if(EditText!="")
	{
		len = strlen(EditText);
		for(i=0;i<(len+1)/2;i++)
		{
			Sendtemp[i]=CharToHex(EditText[2*i])*16+CharToHex(EditText[2*i+1]);
		}
		SendData(Sendtemp,i);
	}	
}
//压缩数据
void CUARTDlg::ComPressData()
{
	
	memset(Sendtemp,0,sizeof(Sendtemp));
	FillHead("a55a38",3);
	//自动飞行3字节
		if(apl==0)
	{
		hdl=0;
		navl=0;
		aprl=0;
	}

	if(hdl==1)
	{
		if(navl==1)
			Sdata.lights[3]=2;
		else if(aprl==1)
			Sdata.lights[3]=3;
		else Sdata.lights[3]=1;

	}else 
	{
		if(navl==1)
			Sdata.lights[3]=4;
		else if(aprl==1)
			Sdata.lights[3]=5;
		else Sdata.lights[3]=0;
	}
	
	if(apl)
	{
		Sdata.lights[3]=Sdata.lights[3]|0x80;
	}else Sdata.lights[3]=Sdata.lights[3]|0x00;
	Sendtemp[3]=Sdata.lights[3];
	printf("%02x \n",Sendtemp[3]);
	Sendtemp[4]=(int)Mdata.autoAlt/100;
	Sendtemp[5]=(int)Mdata.autoVspeed/100;
	if(Mdata.autoVspeed<0) 
	{
		Sendtemp[5]=(int)(-Mdata.autoVspeed)/100;
		Sendtemp[5] = Sendtemp[5]|0x80;
	}
	for(int i=6;i<56;i++)
	{
		Sendtemp[i]=0;
	}


}
//取出需要的Fsx数据
void CUARTDlg::DataCtrl()
{
	//前后
	Dpanel.joystickFrontandBack = COM_Data[0][11];
	//左右
	Dpanel.joystickLeftandRight = COM_Data[0][10];

	//燃油混合柄
	Dpanel.fuelHandShank = COM_Data[0][17];
	Dpanel.flap = COM_Data[0][15];
	//油门
	Dpanel.gun=COM_Data[0][16];

	//脚踏板
	Dpanel.footlock = COM_Data[0][7];
	//配平手轮3
	Dpanel.wheel = COM_Data[0][3];
	//刹车 6 5 4 12
	Dpanel.barker1 = COM_Data[0][6];
	Dpanel.barker2 = COM_Data[0][5];
	Dpanel.barker3 = COM_Data[0][4];
	Dpanel.barker4 = COM_Data[0][12];




	//OFF 23 R 26 L27  START 25
	Dpanel.fireOff = (COM_Data[0][36]==0)?true:false;
	Dpanel.fireRight = (COM_Data[0][39]==0)?true:false;
	Dpanel.fireLeft = (COM_Data[0][40]==0)?true:false;
	Dpanel.fireOn =(COM_Data[0][34]==0)?true:false;

	//自动飞行
	Dpanel.ap  = COM_Data[0][45]==0 ? true:false;
	Dpanel.hdg = COM_Data[0][44]==0 ? true:false;
	Dpanel.nav = COM_Data[0][47]==0 ? true:false;
	Dpanel.apr = COM_Data[0][46]==0 ? true:false;
	Dpanel.rev = COM_Data[0][49]==0 ? true:false;
	Dpanel.alt = COM_Data[0][48]==0 ? true:false;
	Dpanel.up  = COM_Data[0][51]==0 ? true:false;
	Dpanel.dn  = COM_Data[0][50]==0 ? true:false;

	//灯开关
	Dpanel.pump=COM_Data[0][41]==0 ? true:false;
	Dpanel.beacon=COM_Data[0][42]==0 ? true:false;
	Dpanel.landing=COM_Data[0][21]==0 ? true:false;
	Dpanel.taxi=COM_Data[0][22]==0 ? true:false;
	Dpanel.strobe=COM_Data[0][20]==0 ? true:false;
	Dpanel.navLight=COM_Data[0][37]==0 ? true:false;
	Dpanel.pitot=COM_Data[0][43]==0 ? true:false;
}
//发送数据函数
void CUARTDlg::SendData(unsigned char snd[], int length)
{
	CByteArray newarray;//定义临时字符型数组缓冲
	newarray.RemoveAll();//清空字符型数组缓冲
	if(!m_CMSComm.GetPortOpen()) return; //检查串口是否打开
	newarray.SetSize(length);//重定义数组长度与有效数据长度一致
	for(int i=0;i<length;i++)
	{
		newarray.SetAt(i,snd[i]);
	}
	m_CMSComm.SetOutput(COleVariant(newarray));//发送数据
}
//接收数据
void CUARTDlg::RecvData()
{
	static char  str[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	for(int i=0;i<1024;i++)
	{
		Rece_temp[i]=0;
	}
	VARIANT variant_inp;
	COleSafeArray safearray_inp;
	CString strtemp;
		if(m_CMSComm.GetCommEvent()==2) //事件值为2表示接收缓冲区内有字符
	{
		variant_inp=m_CMSComm.GetInput(); //读缓冲区
		safearray_inp=variant_inp;  //VARIANT型变量转换为ColeSafeArray型变量
		long len=safearray_inp.GetOneDimSize(); //得到有效数据长度	
		for(long k=0;k<len&&3*k<1021;k++)             //将数组转换为Cstring型变量
		{
			safearray_inp.GetElement(&k,Rxdata+k);//转换为BYTE型数组
			BYTE bt=*(char*)(Rxdata+k);  
		//	printf("%0x\n", *(Rxdata+k));//字符型
			Rece_temp[3*k]=str[bt/16];
			Rece_temp[3*k+1]=str[bt%16]; 
			Rece_temp[3*k+2]=' ';
		}
		m_RxData = Rece_temp;
		Signal_data();	
	}
}
//填充数据头
void CUARTDlg::FillHead(char headChar[], int len)
{
	//数据头
	int i = 0;
	while(*headChar)
	{
		Sdata.head.hd[i] = *headChar;
		headChar++;
		i++;
	}
	//数据头压缩
	for(int i=0; i<len; i++)
	{
		Sendtemp[i] = CharToHex(Sdata.head.hd[2*i])*16+CharToHex(Sdata.head.hd[2*i+1]);
	}
}

//数据接收区清空
void CUARTDlg::OnBUTTONClean()
{
	SetDlgItemText(IDC_EDIT_Rpond," ");
}

//退出按钮
void CUARTDlg::OnBnClickedOk()
{
	KillTimer(1); //关闭定时器
//	delete g_send_sock;
//	delete m_thread;
	FreeConsole();
	CloseHandle(g_hOutput);
	OnOK();
}




