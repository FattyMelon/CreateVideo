#include "opencv\cv.h"
#include "opencv\cxcore.h"
#include "opencv\highgui.h"
#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"

#define IMG_WIDTH			800
#define IMG_HEIGHT			500


#define DEBUG2


#ifdef DEBUG1
int main ()
{
	cvNamedWindow("video", CV_WINDOW_AUTOSIZE);

	CvCapture* capture = cvCreateFileCapture("E:\\input\\test1.avi");
	IplImage* frame; 
	IplImage* imageSize;
	imageSize = cvCreateImage(cvSize(800, 500), IPL_DEPTH_8U, 3);

	while (1)
	{	
		frame = cvQueryFrame(capture);
		if (!frame) break;
		cvResize(frame, imageSize, CV_INTER_LINEAR);
		CvFont font;
		CvPoint origin = cvPoint(10, 480);
		cvInitFont(&font, CV_FONT_HERSHEY_COMPLEX, 0.5, 0.5, 1, 2, 8);
		cvPutText(imageSize,"Chen Sinong, 2011301500154", origin, &font, CV_RGB(100, 125, 255));

		cvShowImage("video", imageSize);
		
		char c = cvWaitKey(33);
		if (c == 27)	break;
	}

	cvReleaseCapture(&capture);
	cvDestroyWindow("video");

	return 0;
}

#elif defined DEBUG2

int imageToVideo(CvVideoWriter* video);
int addVideo(CvVideoWriter* video);
void addName(IplImage* img);

int main ()
{
	cvNamedWindow("change", CV_WINDOW_AUTOSIZE);

	CvVideoWriter* video = cvCreateVideoWriter("E:/input/output1.avi", CV_FOURCC('P','I','M','1'), 
													33, cvSize(IMG_WIDTH, IMG_HEIGHT), 1);

	if(!imageToVideo(video))	return -1;
	//if(!addVideo(video))	return -1;

	
	cvReleaseVideoWriter(&video);

	cvDestroyWindow("change");

	return 0;
}

int imageToVideo(CvVideoWriter* video)
{
	char filename1[100];
	char filename2[100];

	IplImage* img1; 
	IplImage* img2;
	IplImage* dest;
	IplImage* imgSizeA;
	IplImage* imgSizeB;
	//imageSize = cvCreateImage(cvSize(800, 500), IPL_DEPTH_8U, 3);

	for (int i = 0; i < 4; ++i) 
	{
		sprintf(filename1, "E:/input/xiaomai%d.jpg", i);
		sprintf(filename2, "E:/input/xiaomai%d.jpg", i+1);
		img1 = cvLoadImage(filename1, 1);
		img2 = cvLoadImage(filename2, 1);

		if (!img1)	return 0;
		if (!img2)	return 0;

		imgSizeA = cvCreateImage(cvSize(IMG_WIDTH, IMG_HEIGHT), IPL_DEPTH_8U, 3);
		imgSizeB = cvCreateImage(cvSize(IMG_WIDTH, IMG_HEIGHT), IPL_DEPTH_8U, 3);
		dest = cvCreateImage(cvSize(IMG_WIDTH, IMG_HEIGHT), IPL_DEPTH_8U, 3);
		cvResize(img1, imgSizeA, CV_INTER_LINEAR);
		cvResize(img2, imgSizeB, CV_INTER_LINEAR);

		//添加姓名
		addName(imgSizeA);

		//幻灯片播放每个图片3秒，100张图片
		for (int j = 0; j < 100; ++j)
			cvWriteFrame(video, imgSizeA);

		double alpha = 1.0;
		double beta = 0.0;

		//模糊变换，33帧播放1秒
		for (int j = 0; j < 33; ++j)
		{
			cvAddWeighted(imgSizeA, alpha, imgSizeB, beta, 0.0, dest);
			alpha -= 0.0303;
			beta += 0.0303;

			//cvShowImage("change", dest);
			addName(dest);
			cvWriteFrame(video, dest);

			/*if (j == 0)
				cvWaitKey(5000);
			else
				char c = cvWaitKey(33);*/
		}

		//当图片为第4张时，将第5张的图片添加100次
		addName(imgSizeB);

		if (i == 3)
			for (int j = 0; j < 100; ++j)
				cvWriteFrame(video, imgSizeB);
	}

	cvReleaseImage(&img1);
	cvReleaseImage(&img2);
	cvReleaseImage(&imgSizeA);
	cvReleaseImage(&imgSizeB);
	cvReleaseImage(&dest);

	return 1;
}

int addVideo(CvVideoWriter* video)
{
	CvCapture* capture = cvCreateFileCapture("E:/input/test.avi");

	if (!capture)	return 0;

	IplImage* frame; 
	IplImage* newFrame;
	newFrame = cvCreateImage(cvSize(IMG_WIDTH, IMG_HEIGHT), IPL_DEPTH_8U, 3);

	while (1)
	{	
		frame = cvQueryFrame(capture);
		if (!frame) break;
		cvResize(frame, newFrame, CV_INTER_LINEAR);

		//cvShowImage("video", imageSize);
		addName(newFrame);
		cvWriteFrame(video, newFrame);
	}

	return 1;
}

void addName(IplImage* img)
{
	CvFont font;
	CvPoint origin = cvPoint(10, 485);
	cvInitFont(&font, CV_FONT_HERSHEY_COMPLEX, 1, 1, 1, 2, 8);
	cvPutText(img,"Chen Sinong, 2011301500154", origin, &font, CV_RGB(32, 180, 180));
}
#elif defined DEBUG3

#endif