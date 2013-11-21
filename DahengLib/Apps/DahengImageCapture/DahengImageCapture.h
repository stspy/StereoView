#ifndef __DH_IMAGE_CAPTURE_H__
#define __DH_IMAGE_CAPTURE_H__

#ifdef	_EXPORT_DH_CAPTURE_DLL
#define DH_API	/*extern "C"*/ __declspec(dllexport)
#else
#define DH_API	/*extern "C"*/ __declspec(dllimport)
#endif
#include <opencv2/opencv.hpp>
#include "cgImageReader.h"
using namespace cv;
#define DH_PROP_FRAME_WIDTH 1
#define DH_PROP_FRAME_HEIGHT 2
class DH_API DahengImageCapture
{
public:
	DahengImageCapture();
	DahengImageCapture(int device);
	virtual ~DahengImageCapture();
	
	virtual bool open(int device);
	virtual bool isOpened() const;
	//virtual void release();

	//virtual bool grab();
	//virtual bool retrieve(CV_OUT Mat& image, int channel=0);
	virtual DahengImageCapture& operator >> ( Mat& image);
	virtual bool read( Mat& image);

	virtual bool set(int propId, double value);
	virtual double get(int propId);
private:
	virtual bool getOneframeOrigin();
	//Ptr<cgCapture> cap;
	cgHANDLE cap;
	double m_width;
	double m_height;
	//Ptr<>
	cgIMAGEINFO * m_cgImg;
	IplImage *m_imgIpl;
	Mat m_imgMatOrigin;
	Mat m_imgMatResize;
	//Ptr<IplImage> m_img;//=cvCreateImage(cvSize(768,576),8,3);
};
#endif