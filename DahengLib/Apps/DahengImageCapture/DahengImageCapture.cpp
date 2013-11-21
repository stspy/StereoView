#define _EXPORT_DH_CAPTURE_DLL
#include "DahengImageCapture.h"

DahengImageCapture::DahengImageCapture():cap(0)
{}

DahengImageCapture::DahengImageCapture(int device):cap(0)
{
	open(device);
}

DahengImageCapture::~DahengImageCapture()
{
	cvReleaseImage(&m_imgIpl);
	cgWithdrawImageReader(cap);
	m_imgMatOrigin.data=NULL;
	//cap.release();
	//m_img.release();
}

bool DahengImageCapture::open(int device)
{
	if (!isOpened())
	{
		m_imgIpl=cvCreateImage(cvSize(768,576),8,3);
		cap = cgInitImageReader(device);
		m_height=576;
		m_width=768;
		m_imgMatOrigin.create(768,576,CV_8UC3);
	}
	return isOpened();
}

bool DahengImageCapture::isOpened() const { return cap!=0; }

// void DahengImageCapture::release()
// {
// 	//cap.release();
// }

bool DahengImageCapture::set(int propId, double value)
{
	if (propId==DH_PROP_FRAME_HEIGHT)
	{
		m_height=value;
		return 1;
	}
	else if(propId==DH_PROP_FRAME_WIDTH)
	{
		m_width=value;
		return 1;
	}
	return 0;
	
	//return cvSetCaptureProperty(cap, propId, value) != 0;
}

double DahengImageCapture::get(int propId)
{
	if (propId==DH_PROP_FRAME_HEIGHT)
	{
		return m_height;
	}
	else
	if(propId==DH_PROP_FRAME_WIDTH)
	{
		return m_width;
	}
	return 0;
}

bool DahengImageCapture::read(Mat& image)
{
	getOneframeOrigin();
	if (m_width==768&&m_height==576)
	{
		image=m_imgMatOrigin;
	}
	else
	{
		Size dsize = Size(m_width,m_height);

		resize(m_imgMatOrigin,m_imgMatResize,dsize);
		image=m_imgMatResize;
	}
	return 1;
// 	if(grab())
// 		retrieve(image);
// 	else
// 		image.release();
// 	return !image.empty();
}

bool DahengImageCapture::getOneframeOrigin()
{
	cgGetImage(cap,&m_cgImg);
	m_imgIpl->imageData=(char*)m_cgImg->pImage;
	m_imgMatOrigin=m_imgIpl;
	return 1;
}

DahengImageCapture& DahengImageCapture::operator >> (Mat& image)
{
	read(image);
	return *this;
}