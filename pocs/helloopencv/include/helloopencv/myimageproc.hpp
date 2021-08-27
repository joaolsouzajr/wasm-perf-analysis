#include "helloopencv/myimage.hpp"

#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
// #include <opencv2/highgui.hpp>


#ifndef MYIMAGEPROC_HPP
#define MYIMAGEPROC_HPP

namespace  helloopencv
{


  class MyImageProc
  {
    private:
      int rows;
      int cols;
      long sizeSrc;
      long sizeResult;
      cv::CascadeClassifier face_cascade;
      cv::CascadeClassifier eyes_cascade;
      void setDataResult(cv::Mat& mat);
      void allocDataSrc();


    public:
      unsigned char* dataSrc;
      unsigned char* dataResult;


      MyImageProc();

      MyImageProc(int rows, int cols);

      ~MyImageProc();

      void transformToGray(unsigned char* dataSrc, unsigned char* dataDest);

      void gray();

      void hsv();

      void faceDetect();

      int getCols();

      int getRows();

      long getSizeSrc();

      long getSizeResult();

      void setDataSrc(unsigned char* dataSrc, long size);
  };

  long dataSizeFrom(cv::Mat& mat);

  void fitImageToWeb(cv::Mat& src, cv::Mat& img);
}

#endif




