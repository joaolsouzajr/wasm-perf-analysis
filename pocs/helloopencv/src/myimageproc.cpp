#include "helloopencv/myimageproc.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

namespace  helloopencv
{
  MyImageProc::MyImageProc()
  {
    this->cols = 512;
    this->rows = 512;
    dataResult =  nullptr;
    dataSrc =  nullptr;
    allocDataSrc();
  }

  MyImageProc::MyImageProc(int rows, int cols)
  {
    this->cols = cols;
    this->rows = rows;
    dataResult = nullptr;
    dataSrc = nullptr;
    allocDataSrc();
  }



  MyImageProc::~MyImageProc()
  {
    if(dataResult != NULL || dataResult != nullptr)
    {
      delete[] dataResult;
    }
    if(dataSrc != NULL || dataSrc != nullptr)
    {
      delete[] dataSrc;
    }
  }

  void MyImageProc::transformToGray(unsigned char* _dataSrc, unsigned char* dataDest)
  {
    Mat src{ rows, cols, CV_8UC3, _dataSrc};
    //imwrite("lena_src_transformToGray.jpg", src);
    Mat dest;
    cvtColor(src, dest, COLOR_BGR2GRAY);
    memcpy(dataDest, dest.data, dest.total());
    src.release();
    dest.release();
  }

  void MyImageProc::gray()
  {
    Mat src{ rows, cols, CV_8UC4, dataSrc};
    //imwrite("lena_src_gray.jpg", src);
    //int type = src.type();
    string sst = typeToString(src.type());
    Mat dest;
    cvtColor(src, dest, COLOR_BGR2GRAY);

    Mat img;
    fitImageToWeb(dest, img);

    //imwrite("lena_dest_gray.jpg", dest);
    setDataResult(img);
    //srcO.release();
    src.release();
    dest.release();
    img.release();
  }

  void MyImageProc::hsv()
  {
    Mat src{ rows, cols, CV_8UC4, dataSrc};

    //imwrite("lena_src_hsv.jpg", src);
    int type = src.type();
    string sst = typeToString(src.type());
    Mat dest;
    cvtColor(src, dest, COLOR_RGBA2RGB);
    cvtColor(dest, dest, COLOR_RGB2HSV);
    //imwrite("lena_dest_hsv.jpg", dest);

    Mat img;
    fitImageToWeb(dest, img);

    setDataResult(img);
    src.release();
    dest.release();
    img.release();
  }


  void MyImageProc::faceDetect()
  {
    String face_cascade_name = "assets/haarcascade_frontalface_alt.xml";
    String eyes_cascade_name = "assets/haarcascade_eye_tree_eyeglasses.xml";
    std::cout << "Detect faces" << endl;
    //-- 1. Load the cascades
    if( !face_cascade.load( face_cascade_name ) )
    {
        std::cerr << "--(!)Error loading face cascade\n" << endl;
        throw runtime_error("--(!)Error loading face cascade\n");
        return;
    };
    if( !eyes_cascade.load( eyes_cascade_name ) )
    {
        std::cerr << "--(!)Error loading eyes cascade\n" << endl;
        throw runtime_error("--(!)Error loading eyes cascade\n");
        return;
    };
    std::cout << "FOi" << endl;
    Mat src{ rows, cols, CV_8UC4, dataSrc};
    // // Mat src;
    // // cvtColor(src0, src, COLOR_RGB2RGBA);
    cvtColor(src, src, COLOR_RGBA2RGB);
    // imwrite("lena_dest_face_1.jpg", src);
    Mat dest;
    cvtColor(src, dest, COLOR_RGB2GRAY);
    // imwrite("lena_dest_face_2.jpg", dest);
    equalizeHist( dest, dest );
    // imwrite("lena_dest_face_3.jpg", dest);
    //-- Detect faces
    std::cout << "Detect faces" << endl;
    std::vector<Rect> faces;
    face_cascade.detectMultiScale( dest, faces );
    for ( size_t i = 0; i < faces.size(); i++ )
    {
        Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
        ellipse( src, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4 );
        Mat faceROI = dest( faces[i] );
         std::cout << "Face " << i << endl;
        //-- In each face, detect eyes
        std::vector<Rect> eyes;
        eyes_cascade.detectMultiScale( faceROI, eyes );
        for ( size_t j = 0; j < eyes.size(); j++ )
        {
            Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
            int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
            circle( src, eye_center, radius, Scalar( 255, 0, 0 ), 4 );
            std::cout << "Eyes " << j << endl;
        }
    }
    // imwrite("lena_dest_face_4.jpg", src);
    Mat img;
    fitImageToWeb(src, img);
    // imwrite("lena_dest_face_5.jpg", img);
    setDataResult(img);
    src.release();
    //dest.release();
    img.release();
  }

  void MyImageProc::setDataResult(cv::Mat& dest)
  {
    if(dataResult != NULL || dataResult != nullptr)
    {
      delete[] dataResult;
    }
    this->sizeResult = dataSizeFrom(dest);
    dataResult = new unsigned char[this->sizeResult];
    memcpy(dataResult, dest.data, this->sizeResult);
  }

  void MyImageProc::allocDataSrc()
  {
    Mat src{ rows, cols, CV_8UC4};
    if(dataSrc != nullptr)
    {
      delete[] dataSrc;
    }
    this->sizeSrc = dataSizeFrom(src);
    dataSrc = new unsigned char[this->sizeSrc];
    src.release();
  }

  void MyImageProc::setDataSrc(unsigned char* _dataSrc, long _size)
  {
    if(dataSrc != NULL || dataSrc != nullptr)
    {
      delete[] dataSrc;
    }
    dataSrc = new unsigned char[_size];
    dataSrc = _dataSrc;
    this->sizeSrc = _size;
    //memcpy(dataResult, _dataSrc, this->sizeSrc);
  }

  long MyImageProc::getSizeSrc()
  {
    return this->sizeSrc;
  }

  long MyImageProc::getSizeResult()
  {
    return this->sizeResult;
  }

  int MyImageProc::getCols()
  {
    return this->cols;
  }

  int MyImageProc::getRows()
  {
    return this->rows;
  }

  long dataSizeFrom(cv::Mat& mat)
  {
    return (mat.total()*mat.elemSize())/sizeof(unsigned char);
  }

  void fitImageToWeb(cv::Mat& src, cv::Mat& img)
  {
    // convert the mat type to cv.CV_8U
    int depth = src.type()%8;
    int scale = depth <= CV_8S? 1.0 : (depth <= CV_32S? 1.0/256.0 : 255.0);
    int shift = (depth == CV_8S || depth == CV_16S)? 128.0 : 0.0;
    src.convertTo(img, CV_8U, scale, shift);

    //convert the img type to cv.CV_8UC4
    switch (img.type()) {
        case CV_8UC1:
            cvtColor(img, img, COLOR_GRAY2RGBA);
            break;
        case CV_8UC3:
            cvtColor(img, img, COLOR_RGB2RGBA);
            break;
        case CV_8UC4:
            break;
        default:
            throw runtime_error("Bad number of channels (Source image must have 1, 3 or 4 channels)");
            return;
    }
  }

}
