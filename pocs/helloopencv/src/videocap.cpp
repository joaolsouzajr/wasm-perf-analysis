#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

using namespace std;
using namespace cv;

int main(int argc, const char **argv)
{
  VideoCapture capture;
  Mat frame;
  Mat edges;
  //-- 2. Read the video stream
  if (capture.open("D:/Users/joao_lourenco/labs/tccwasm/pocs/helloopencv/videos/car_chase_01.mp4"))
  {
    double fps = capture.get(CAP_PROP_FPS);
    cout << "Frames per second using video.get(CAP_PROP_FPS) : " << fps << endl;
    while (true)
    {
      capture.read(frame); // another usage can be like    capture >> frame;

      //-- 3. Apply the classifier to the frame
      if (!frame.empty())
      {
        imshow("Capture - Camera", frame);
        if( cv::waitKey(10) == 27 )
        {
            break; // escape
        }
      }
      else
      {
        printf(" --(!) No captured frame -- Break!");
        break;
      }
    }
    capture.release();
  }
  else
  {
    std::cerr << "ERROR: Could not open camera" << std::endl;
    return 1;
  }
  return 0;
}
/*
int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat edges;
    namedWindow("edges",1);
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        cvtColor(frame, edges, COLOR_BGR2GRAY);
        GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        Canny(edges, edges, 0, 30, 3);
        imshow("edges", edges);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}*/
