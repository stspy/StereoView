//#include "opencv.hpp"
#include "cgImageReader.h"
//#include "windows.h"
#include "highgui.h"
int main(void)
{

 	cvNamedWindow("picShow0",1);
 	cvNamedWindow("picShow1",1);
 	
  	IplImage *imgshow1=cvCreateImage(cvSize(768,576),8,3);
 	IplImage *imgshow2=cvCreateImage(cvSize(768,576),8,3);
	cgHANDLE hcard1=cgInitImageReader(1);
	cgHANDLE hcard2=cgInitImageReader(4);
	cgIMAGEINFO *pImg1=NULL;
	cgIMAGEINFO *pImg2=NULL;
	int i=0;
 	while(1)
 	{
		cgGetImage(hcard1,&pImg1);
		cgGetImage(hcard2,&pImg2);
		
 		imgshow1->imageData=(char *)pImg1->pImage;
 		imgshow2->imageData=(char*)pImg2->pImage;
		cvShowImage("picShow0",imgshow1);
		if (cvWaitKey(1)==27)
		{
			break;
		}
		
		cvShowImage("picShow1",imgshow2);
		if (cvWaitKey(1)==27)
		{
			break;
		}
	
	}
 	cgWithdrawImageReader(hcard1);
 	cgWithdrawImageReader(hcard2);
 	cvReleaseImage(&imgshow1);
 	cvReleaseImage(&imgshow2);
 	cvDestroyWindow("picshow0");
 	cvDestroyWindow("picShow1");
	return 0;
}