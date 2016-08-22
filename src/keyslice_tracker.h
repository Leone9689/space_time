#ifndef KEYFRAME_SLICE_H_
#define KEYFRAME_SLICE_H_

#include <fstream> 
#include <iostream>
#include <string>
#include <vector>
//using namespace std;
 
// OpenCV 库
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class KeySlice
{
  public:
    KeySlice();
    void findKeySlice(int d,int pixelChange);
  public:
    // cv::Mat bluePixels;
     cv::Mat keySlice; 
     std::vector<cv::Mat>rgbImage; 
  private:
    int d; 
    int pixelThreshold;  
};

#endif

