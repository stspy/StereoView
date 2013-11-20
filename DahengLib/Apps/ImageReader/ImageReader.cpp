#define _EXPORT_TASKDLL
#include <Windows.h>
#include "cgImageReader.h"
#include "CGVideo.h"
#include "CGVidEx.h"


using namespace std;
typedef struct
{
	HCG hCard;
	cgIMAGEINFO *Img;
}CARD_IMAGE_CON;
CARD_IMAGE_CON * gCardImg[4];


int findcard(HCG hCard)
{
	for (int i=0;i!=4;i++)
	{
		if (gCardImg[i]!=NULL)
		{
			if (gCardImg[i]->hCard==hCard)
				return i;
		}
	}
	return -1;
}

void withdrawCardImage(HCG hCard)
{
	int i=findcard(hCard);
	delete[] gCardImg[i]->Img->pImage;
	delete gCardImg[i]->Img;
	delete gCardImg[i];
// 	for (int i=0;i!=4;i++)
// 	{
// 		if (gCardImg[i]!=NULL)
// 		{
// 			delete[] gCardImg[i]->Img->pImage;
// 			delete gCardImg[i]->Img;
// 			delete gCardImg[i];
// 		}
// 	}
}


cgHANDLE __stdcall cgInitImageReader(int nDevice)
{
	HCG hCard;
	CGSTATUS status = CG_OK;
	status=BeginCGCard(nDevice,&hCard);
	CG_VERIFY(status);
	VIDEO_SOURCE source={COMPOSITE_VIDEO,1};
	status = CGSetVideoStandard(hCard,PAL);
	status = CGSetVideoSource(hCard, source);
	status = CGSetVideoFormat(hCard, RGB888);
	status = CGSetScanMode(hCard, FRAME);
	status = CGSetInputWindow(hCard,0,0,768,576);
	CG_VERIFY(status);
	status = CGSetOutputWindow(hCard,0,0,768,576);
	CG_VERIFY(status);
	gCardImg[nDevice-1]=new CARD_IMAGE_CON;
	gCardImg[nDevice-1]->hCard=hCard;
	gCardImg[nDevice-1]->Img=new cgIMAGEINFO;
	gCardImg[nDevice-1]->Img->pImage=new BYTE[768*576*3];
	gCardImg[nDevice-1]->Img->eFormat=cgRGB888;
	gCardImg[nDevice-1]->Img->nWidth=768;
	gCardImg[nDevice-1]->Img->nHeight=576;
	return (cgHANDLE)hCard;
}

void __stdcall cgWithdrawImageReader(cgHANDLE hCard)
{
	
	withdrawCardImage((HCG)hCard);
	//CGStopSnap((HCG)hCard);
	EndCGCard((HCG)hCard);
	
}

 void __stdcall cgGetImage(cgHANDLE hCard,cgIMAGEINFO **img)
{
	int status=CG_OK;
	BYTE *pStaticBuffer		= NULL;
	HANDLE handle			= NULL;	
	int i=findcard((HCG)hCard);
	if(i!=-1)
	{
		status = CGSnapShot((HCG)hCard, 0, 0, TRUE, 1);
		status = CGStaticMemLock(0, 768*576*3, &handle, (VOID **)&pStaticBuffer);
		CGDataTransform(gCardImg[i]->Img->pImage, 		//Í¼Ïñ»º³åÇø
			pStaticBuffer, 		//¾²Ì¬ÄÚ´æ
			768, 				//Í¼Ïñ¿í¶È
			576, 				//Í¼Ïñ¸ß¶È
			24, 				//Í¼ÏñÎ»Éî¶È
			TRUE				//ÊÇ·ñµ¹ÖÃÍ¼Ïñ
			);
		CGStaticMemUnlock(handle);
		*img=gCardImg[i]->Img;
	}
	
}

// void InitCGCard(HCG hcg,int x)//int nIndex;	
// {
// 	CGSTATUS status = CG_OK;
// 	VIDEO_SOURCE source={COMPOSITE_VIDEO,1};
// 	status = CGSetVideoStandard(hcg,PAL);
// 	status = CGSetVideoSource(hcg, source);
// 	status = CGSetVideoFormat(hcg, RGB8888);
// 
// 	status = CGSetScanMode(hcg, FRAME);
// 
// // 	CGAdjustVideo(hcg, BRIGHTNESS, m_byBrightness);
// // 	CGAdjustVideo(hcg, CONTRAST, m_byContrast);
// // 	CGAdjustVideo(hcg, HUE, m_byHue);
// // 	CGAdjustVideo(hcg, SATURATION, m_bySaturation);
// 
// /*	CGSetPLLFrequency(hcg, m_byPLLFrequency);*/
// 
// 	status = CGSetInputWindow(hcg,x,0,768,576
// 		);
// 	CG_VERIFY(status);
// }
// /*	CGSelectCryOSC(hcg, m_CryOsc);*/
// // }
// // typedef struct
// // {
// // 	HCG hCard;
// // 
// // }CardShow;
// 
// int main()
// {
// 	
// 	CGSTATUS status = CG_OK;
// 	int nCardTotal=0;
// 	CGGetCardTotal(&nCardTotal);
// 	HCG hCard1;
// 	HCG hCard2;
// 	status=BeginCGCard(1,&hCard1);
// 	CG_VERIFY(status);
// 	//status=BeginCGCard(4,&hCard2);
// 	CG_VERIFY(status);
// 	InitCGCard(hCard1,0);
// 	//InitCGCard(hCard2,0);
// 	status = CGSetOutputWindow(hCard1,0,0,768,576);
// 	CG_VERIFY(status);
// 	
// 	//status = CGSetOutputWindow(hCard2,768,0,768,576);
// 	CG_VERIFY(status);
// 	//status=CGCapture(hCard1,TRUE);
// 	cvNamedWindow("picShow");
// 	HWND cvHandle=(HWND)cvGetWindowHandle("picShow");
// 	//CGCaptureEx(hCard1,cvHandle,TRUE);
// 	DWORD totalsize=0;
// 	status=CGGetStaticMem(&totalsize);
// 	DWORD dwImageSize=768*576*4;
// 	HANDLE Handle;
// 	PVOID pLineAddr;
// 
// 	/******************************/
// 	IplImage *imgshow=cvCreateImage(cvSize(768,576),8,3);
// 	/*status=CGStaticMemLock(0,dwImageSize*2,&Handle,&pLineAddr);*/
// 	CG_VERIFY(status);
// //	status = CGStartSnap(hCard1,0,TRUE,2);
// // 	status=CGSnapShot(hCard1,0,0,TRUE,1);
// // 	CG_VERIFY(status);
// // 	imgshow->imageData=(char *)pLineAddr;
// // 	cvShowImage("picShow",imgshow);
// 
// 	status = CGStartSnap(hCard1,0,TRUE,2);
// 	int i=0;
// 	BOOL bComplete=FALSE;
// 	
// 	while (cvWaitKey(1)!=27)
// 	{
// 		
// 		//Sleep(10);
// 		CGGetSnappingNumber(hCard1,&i);
// 		if ((i == 2) && (! bComplete) ) {
// 			
// 			bComplete	= TRUE;
// 		}
// 		if ((i == 0) && bComplete) {
// 			
// 			bComplete	= FALSE;
// 		}
// 		if (bComplete==TRUE)
// 		{
// 		//Sleep(1);
// 		status=CGStaticMemLock(0,dwImageSize,&Handle,&pLineAddr);
// 			
// 			CGDataTransform((BYTE *)imgshow->imageData,(BYTE *)pLineAddr,768,576,24,FALSE);
// 			//imgshow->imageData=(char *)pLineAddr;
// 			cvShowImage("picShow",imgshow);
// 			status=CGStaticMemUnlock(Handle);
// 			//cout<<"pic"<<endl;
// 		}
// 		
// 
// 	
// 		
// 	}
// 	CGStopSnap(hCard1);
// 	//cvShowImage()
// 	
// 	
// 		/******************************/
// 
// 
// // 	status=CGCapture(hCard1,TRUE);
// // 		CG_VERIFY(status);
// // 		status=CGCapture(hCard2,TRUE);
// // 		CG_VERIFY(status);
// 
// 
// 
// 
// 	cvWaitKey(0);
// 	//CGCaptureEx(hCard1,cvHandle,FALSE);
// // 	CGCapture(hCard1,FALSE);
// // 	CGCapture(hCard2,FALSE);
// // 	string strImgFileName = "E:/Features/test_1.bmp";
// // 
// // 	Mat iImgData;
// // 
// // 	// get image
// // 	iImgData = imread(strImgFileName);
// // 
// // 	if (iImgData.empty())
// // 	{
// // 		return 0;
// // 	}
// // 
// // 	imshow("Image", iImgData);
// //  imwrite("E:/Features/test_2.bmp", iImgData);
// 	EndCGCard(hCard1);
// 	return 0;
// }
