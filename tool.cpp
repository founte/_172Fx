#include "stdafx.h"
#include "tool.h"
void ErrorMassageBox(LPCTSTR msg)
{
	TCHAR buffer[128] = {0};
	sprintf_s(buffer, _T("%s ÊÇ·ñ¼ÌÐø?"), msg);
	if(IDNO == MessageBox(AfxGetApp()->m_pMainWnd->m_hWnd, 
							buffer, _T("ERROR"), 
							MB_YESNO|MB_ICONERROR|MB_DEFBUTTON2|MB_TOPMOST))
	{
		exit(1);
	}
}

int RangedRandDemo( int range_min, int range_max)
{
   // Generate random numbers in the half-closed interval
   // [range_min, range_max). In other words,
   // range_min <= random number < range_max

   return (int)(double)rand() / (RAND_MAX + 1) * (range_max - range_min)
            + range_min;
}

float ymsvfi(float xin,float xtab[],float utab[])
{
	int arrylen,it,at;
	float y,frac;

	it=0;
	arrylen=(int)xtab[0];
	at=arrylen-2;
	if(xin>xtab[arrylen]){
		it=at;
		frac=1;
	}
	else if(xin<xtab[1]){	
		it=0;
		frac=0;
	}
	else if(xin>=xtab[it+1]){
loop1:		it++;
		if(xin>xtab[it+1]) goto loop1;
		it=it-1;
		frac=(xin-xtab[it+1])/(xtab[it+2]-xtab[it+1]);
	}
	else{ 
loop2:		it--;
		if(xin<xtab[it+1]) goto loop2;
		frac=(xin-xtab[it+1])/(xtab[it+2]-xtab[it+1]);
	}
	y=utab[it]+frac*(utab[it+1]-utab[it]);

	return (y);
}


