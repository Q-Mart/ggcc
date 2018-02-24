#include <iostream>
#include <cv.h>
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include <highgui.h>

#define WIDTH 1920
#define HEIGHT 1080

using namespace std;
char key;
int main()
{
  cv::namedWindow("opencv-show", CV_WINDOW_NORMAL || CV_WINDOW_FREERATIO);    //Create window
  cv::setWindowProperty("opencv-show", CV_WINDOW_FULLSCREEN, CV_WINDOW_FULLSCREEN);
  cv::moveWindow("opencv-show", 0, 0);
  cv::VideoCapture capture(CV_CAP_ANY);  //Capture using any camera connected to your system
  while(1) //Create infinte loop for live streaming
  {
    cv::Mat frame;
    capture >> frame; //Create image frames from capture
    // Resize to make full screen
    cv::resize(frame, frame, cv::Size(1920, 1080), 0, 0, CV_INTER_LINEAR);

    // Draw scores
    cv::rectangle(frame, cv::Point(0, 800), cv::Point(500, 1000), cv::Scalar(0,0,200), -1, 8);
    cv::rectangle(frame, cv::Point(WIDTH, 800), cv::Point(WIDTH-500, 1000), cv::Scalar(200,100,0), -1, 8);
    cv::putText(frame, "Team 1", cv::Point(125, 850), cv::FONT_HERSHEY_DUPLEX, 2, cv::Scalar(0, 0, 0), 2, CV_AA);
    cv::putText(frame, "Team 2", cv::Point(WIDTH-325, 850), cv::FONT_HERSHEY_DUPLEX, 2, cv::Scalar(0, 0, 0), 2, CV_AA);
    cv::imshow("opencv-show", frame);   //Show image frames on created window
    key = cvWaitKey(10);     //Capture Keyboard stroke
    if (char(key) == 27){
      break;      //If you hit ESC key loop will break.
    }
  }
  capture.release(); //Release capture.
  cv::destroyAllWindows(); //Destroy Window
  return 0;
}
