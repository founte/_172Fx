#pragma once

#include "simconnect.h"


class Fsx
{
public:
	Fsx(void);
	static void startFsx(void *param);
	void dealFsx();
	
	//��Ϣӳ�亯��
    void MapEventToSim();
	//�ص�����
	static void CALLBACK MyDispatchProcRD(SIMCONNECT_RECV* pData, DWORD cbData, void *pContext);
	
public:
	int lastWheel;
	int lastHead;
	int a;
	~Fsx(void);
};


