#pragma once
#include "vision/VisionPipeline.h"

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/contrib/contrib.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include <string>
#include <math.h>
#include "WPILib.h"

namespace grip {

/**
* GripPipeline class.
* 
* An OpenCV pipeline generated by GRIP.
*/
class GripPipeline : public VisionPipeline {
	private:
		cv::Mat cvResizeOutput;
		cv::Mat hsvThresholdOutput;
		std::vector<std::vector<cv::Point> > findContoursOutput;
		std::vector<std::vector<cv::Point> > filterContoursOutput;
		void cvResize(cv::Mat &, cv::Size &, double , double , int , cv::Mat &);
		void hsvThreshold(cv::Mat &, double [], double [], double [], cv::Mat &);
		void findContours(cv::Mat &, bool , std::vector<std::vector<cv::Point> > &);
		void filterContours(std::vector<std::vector<cv::Point> > &, double , double , double , double , double , double , double [], double , double , double , double , std::vector<std::vector<cv::Point> > &);

	public:
		GripPipeline();
		void Process(cv::Mat & source0);
		cv::Mat* getcvResizeOutput();
		cv::Mat* gethsvThresholdOutput();
		std::vector<std::vector<cv::Point> >* getfindContoursOutput();
		std::vector<std::vector<cv::Point> >* getfilterContoursOutput();
};


} // end namespace grip
