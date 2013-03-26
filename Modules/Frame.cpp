/* 
*	frame.cpp
*/

#include "Frame.h"

using namespace cv;
using namespace std;

Frame::Frame(cv::Mat image,cv::Mat probMap) : image(image),probMap(probMap)  {}

void Frame::drawObjects(Scalar color)
{
	for (std::vector<Object>::iterator it = objects.begin(); it != objects.end(); ++it)
	{
		if(it->isParent)
			color = Scalar(0, 255, 0);
		if(it->isChild)
			color = Scalar(0, 255, 255);
		if(it->isLost)
			color = Scalar(255, 255, 0);

		int x = it->x - it->width/2;
		int y = it->y - it->height/2;
		int x_w = it->x + it->width/2;
		int y_h = it->y + it->height/2;

		rectangle(image, Point(x, y), 
						 Point(x_w, y_h), 
						 color, 1, 8);
		line(image, Point(it->x, it->y), Point(it->x + (int)(it->dx*30), it->y + (int)(it->dy*30)), color, 2 ,8);

		std::string objectText = "("+std::to_string(it->x)+","+std::to_string(it->y)+") id:"+std::to_string(it->id);
		int fontFace = CV_FONT_HERSHEY_COMPLEX;
		double fontScale = 0.3;
		int thickness = (int)0.3;
		putText(image, objectText, Point(x, y+10+it->height), fontFace, fontScale, Scalar::all(255), thickness, 8);
	}
}

void Frame::drawObjectsPrediction(Scalar color)
{
	for (std::vector<Object>::iterator it = objects.begin(); it != objects.end(); ++it)
	{
		if(it->isLost)
			color = Scalar(255, 255, 0);

		int x = (int)it->xHat - it->width/2;
		int y = (int)it->yHat - it->height/2;
		int x_w = (int)it->xHat + it->width/2;
		int y_h = (int)it->yHat + it->height/2;

		rectangle(image, Point(x, y), 
							Point(x_w, y_h), 
							color, 1, 8);
		line(image, Point(x_w, y_h), Point(x_w + (int)(it->dx), y_h + (int)(it->dy)), color, 2 ,8);

		std::string objectText = "("+std::to_string(it->x)+","+std::to_string(it->y)+") id:"+std::to_string(it->id);
		int fontFace = CV_FONT_HERSHEY_COMPLEX;
		double fontScale = 0.3;
		int thickness = (int)0.3; 
		putText(image, objectText, Point(x, y+10+it->height), fontFace, fontScale, Scalar::all(255), thickness, 8);
	}
}

void Frame::drawObjects(std::vector<Object> & objects, Scalar color)
{
	for (std::vector<Object>::iterator it = objects.begin(); it != objects.end(); ++it)
	{
		rectangle(image, Point(it->x, it->y), 
							Point(it->x + it->width, it->y + it->height), 
							color, 1, 8);
		line(image, Point(it->x, it->y), Point(it->x + (int)(it->dx), it->y + (int)(it->dy)), color, 2 ,8);

		std::string objectText = "("+std::to_string(it->x)+","+std::to_string(it->y)+") id:"+std::to_string(it->id);
		int fontFace = CV_FONT_HERSHEY_COMPLEX;
		double fontScale = 0.3;
		int thickness = (int)0.3;
		putText(image, objectText, Point(it->x-it->width/2, it->y-10), fontFace, fontScale, Scalar::all(255), thickness, 8);
	}
}


/////////////////////////////////////////////// Showimage //////////////////////////////////////////////////////

void Frame::showObjects()
{
	for (std::vector<Object>::iterator it = objects.begin(); it != objects.end(); ++it)
	{
		it->info();
	}
}

void Frame::showImageRaw(string windowID)
{
	namedWindow( windowID, CV_WINDOW_AUTOSIZE );		// Create a window for display.
    imshow( windowID, image );						// Show our image inside it.
}

void Frame::showImageProbMap(string windowID)
{
	namedWindow( windowID, CV_WINDOW_AUTOSIZE );		    // Create a window for display.
    imshow( windowID, probMap );						// Show our image inside it.
}





