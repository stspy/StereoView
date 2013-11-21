#include "DahengImageCapture.h"
#include <opencv.hpp>
using namespace cv;

void main(void)
{
	DahengImageCapture Cap1(1);
	DahengImageCapture Cap2(4);
	Cap1.set(DH_PROP_FRAME_WIDTH,500);
	Cap1.set(DH_PROP_FRAME_HEIGHT,500);
	Cap2.set(DH_PROP_FRAME_WIDTH,640);
	Cap2.set(DH_PROP_FRAME_HEIGHT,480);
	Mat mat1;
	Mat mat2;
	while (1)
	{
		Cap1>>mat1;
		Cap2>>mat2;
		imshow("mat1",mat1);
		char b=waitKey(10);
		imshow("mat2",mat2);
		char a=waitKey(10);
		if (a==27||b==27)
		{
			break;
		}
	}
	

}