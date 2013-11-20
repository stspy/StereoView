
#ifndef __CG_IMAGE_READER_H__
#define __CG_IMAGE_READER_H__

#ifdef	_EXPORT_TASKDLL
#define TASK_API	extern "C" __declspec(dllexport)
#else
#define TASK_API	extern "C" __declspec(dllimport)
#endif

//#include "CGDef.h"
typedef void* cgHANDLE;
typedef unsigned char BYTE;
typedef enum  {
	cgYUV422		= 0,
	cgRGB888		= 1,
	cgRGB565		= 2,
	cgRGB555		= 3,
	cgRGB8888		= 4,
	cgALL8BIT		= 5,
	//LIMITED8BIT = 6
} cgIMAGE_FORMAT;

typedef struct
{
	BYTE* pImage;
	cgIMAGE_FORMAT eFormat;
	int nWidth;
	int nHeight;

}cgIMAGEINFO;
TASK_API cgHANDLE __stdcall cgInitImageReader(int nDevice);
TASK_API void __stdcall cgWithdrawImageReader(cgHANDLE hCard);
TASK_API void __stdcall cgGetImage(cgHANDLE hCard,cgIMAGEINFO **img);



#endif