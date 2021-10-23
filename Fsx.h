#pragma once

#include "simconnect.h"


class Fsx
{
public:
	Fsx(void);
	static void startFsx(void *param);
	void dealFsx();
	
	//消息映射函数
    void MapEventToSim();
	//回调函数
	static void CALLBACK MyDispatchProcRD(SIMCONNECT_RECV* pData, DWORD cbData, void *pContext);
	
public:
	int lastWheel;
	int lastHead;
	int a;
	~Fsx(void);
};


