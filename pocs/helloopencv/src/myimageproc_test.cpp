#include <iostream>
#include "helloopencv/myimageproc.hpp"


using namespace std;

// OpenCV includes
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"


using namespace cv;

int main(int argc, const char** argv)
{
    // Read images
  Mat color = imread("D:/Users/joao_lourenco/labs/tccwasm/pocs/helloopencv/images/lena.png", IMREAD_COLOR);

  if (!color.data) // Check for invalid input
  {
    cout << "Could not open or find the image" << std::endl;
    return -1;
  }

  // helloopencv::MyImageProc myproc{color.rows, color.cols};
  // int type = color.type();
  // string sst =typeToString(color.type());
  // unsigned char* bufferImage = new unsigned char[color.total()];
  // myproc.transformToGray(color.data, bufferImage);
  // Mat gray{ color.rows, color.cols, CV_8UC1, bufferImage};
  // imwrite("lenaGray.jpg", gray);

  cvtColor(color, color, COLOR_RGB2BGRA);
  helloopencv::MyImageProc myproc2{color.rows, color.cols};
  //myproc2.setDataSrc(color.data, (color.total()*color.elemSize())/sizeof(unsigned char));
  myproc2.dataSrc = color.data;
  // myproc2.gray();
  // Mat gray2{color.rows, color.cols, CV_8UC4, myproc2.dataResult};
  // imwrite("lenaGray2.jpg", gray2);

  myproc2.faceDetect();
  Mat hsv{color.rows, color.cols, CV_8UC3, myproc2.dataResult};
  imwrite("lenaHasv.jpg", hsv);

  // myproc.~MyImageProc();
  myproc2.~MyImageProc();
}
