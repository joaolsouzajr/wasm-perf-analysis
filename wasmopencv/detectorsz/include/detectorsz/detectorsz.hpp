/*
Copyright 2019, Joao Lourenco Souza Junior, all rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef DETECTORSZ_HHP
#define DETECTORSZ_HHP

#include <iostream>
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>

using namespace std;

namespace detectorsz {

/********* Constants ******/

const int CV_TYPE_DEFAULT = CV_8UC4;

const string FACE_CASCADE_PATH = "assets/haarcascade_frontalface_alt.xml";
const string EYES_CASCADE_PATH = "assets/haarcascade_eye_tree_eyeglasses.xml";

const string FACE_DETECT_NAME = "FACE_DETECT";
const string FACE_EYES_DETECT_NAME = "FACE_EYES_DETECT";

/********* Utils ******/

struct ProcessLog {
  string system;
  string workload;
  string function;
  int frameIndex;
  int numberDetectedObjects;
  long aquisitionTime;
  long processTime;
  long posProcessTime;
};

/**
 * @brief Information about processes executed on Face Detect functions.
 */
class FaceEyesDetectLog {
public:
  FaceEyesDetectLog();
  ~FaceEyesDetectLog();
  string workloadName;
  string functionName;
  string systemName;
  int numberDetectedFaces = 0;
  int numberDetectedEyes = 0;
  int64 processTime = 0;
  int64 totalTime = 0;
  int64 preProcTime = 0;
  int64 tagProcTime = 0;
  int64 posProcTime = 0;
  string toString();

private:
};

/**
 * @brief Convert any cv::Mat to type RGBA.
 * @param src cv::Mat
 * @param dest cv::Mat
 */
void convertAnyMatToRGBA(cv::Mat &src, cv::Mat &dest);

/**
 * @brief Convert any cv::Mat to gray scale.
 * (CV_8U)
 * @param src cv::Mat
 * @param dest cv::Mat
 */
void convertAnyMatToRGB(cv::Mat &src, cv::Mat &dest);

/**
 * @brief Convert any cv::Mat to gray scale.
 * (CV_8U)
 * @param src cv::Mat
 * @param dest cv::Mat
 */
void convertAnyMatToGray(cv::Mat &src, cv::Mat &dest);

/**
 * @brief Convert any cv::Mat to represent data as an array of unsigned char
 * (CV_8U).
 * @param src cv::Mat
 * @param dest cv::Mat
 */
void convertAnyMatTo8U(cv::Mat &src, cv::Mat &dest);

/**
 * @brief Calc the size of data cv::Mat
 * @param mat cv::Mat
 */
size_t matSize(const cv::Mat &mat);

/********* Image Processs ******/

/**
 * @brief Image data abstraction. It is an adapter to opencv cv::Mat class.
 */
class MatAdapter {
public:
  /**
   * cv::Mat image wrapper
   */
  cv::Mat matImg;

  /**
   * @brief Create a default image
   */
  MatAdapter();

  /**
   * @brief Create a image with rows and coloumns passed by param
   */
  MatAdapter(int rows, int cols);

  /**
   * @brief Create a image with rows and coloumns passed by param
   */
  MatAdapter(int rows, int cols, int cvType);

  /**
   * @brief Destruct any resources used by MatAdapter instance.
   */
  ~MatAdapter();

  /**
   * @brief Return pointer with data from MatAdapter::matImg
   * @see MatAdapter::matImg
   * @return cv:Mat::data
   */
  unsigned char *getData();

  // void setData(unsigned char *_data);

private:
};

/**
 * @brief Class with functions to process and tranform images.
 */
class ImageProcess {
public:
  /**
   * @brief Create a default instance of ImageProcess.
   */
  ImageProcess();

  /**
   * @brief Destruct any resources of ImageProcess instance.
   */
  ~ImageProcess();

  /**
   * @brief From original image create the new gray image with type RGBA.
   * @see MatAdapter
   * @param srcImg MatAdapter original image
   * @param destImg MatAdapter new gray image with type RGBA.
   */
  void gray(MatAdapter &srcImg, MatAdapter &destImg);

  /**
   * @brief From original image create the new gray image with type RGBA.
   * @see MatAdapter
   * @param srcImg MatAdapter original image
   * @param destImg MatAdapter new gray image with type RGBA.
   */
  void hsv(MatAdapter &srcImg, MatAdapter &destImg);

private:
};

/**
 * @brief Class with funcions to detect faces on frame.
 */
class FaceDetect {
public:
  string dataName;
  /**
   * Log with proscess time for every workload image.
   */
  vector<FaceEyesDetectLog> logs;

  /**
   * @brief Create a default instance of FaceDetect.
   */
  FaceDetect();

  FaceDetect(string dataName);

  /**
   * @brief Destruct any resources of FaceDetect instance.
   */
  ~FaceDetect();

  /**
   * @brief Detect face in image data and draw a elpse in this region
   * @see MatAdapter
   * @param src MatAdapter with image data.
   */
  void faceDetect(MatAdapter &src);

  /**
   * @brief Detect face in image data, draw a elpse in this region and record
   * process time.
   * @see MatAdapter
   * @param src MatAdapter with image data.
   */
  void faceDetectWithLog(MatAdapter &src);

  /**
   * @brief Detect face and eyes in image data and draw a elpses in those
   * regions.
   * @see MatAdapter
   * @param src MatAdapter with image data.
   */
  void faceAndEyesDetect(MatAdapter &src);

  /**
   * @brief Detect face and eyes in image data, draw a elpses in those regions
   * and record process time.
   * @param src MatAdapter with image data.
   */
  void faceAndEyesDetectWithLog(MatAdapter &src);

  /**
   * Return all logs recorded in the FaceDetecte instance.
   * @see FaceEyesDetectLog
   * @return A vector of FaceEyesDetectLog
   */
  string logsToString();

  string logsToStringAndAddCommon(string head, string columns);

  void updateTotalTime(int frameIndex, int time);

private:
  cv::CascadeClassifier faceCascade;
  cv::CascadeClassifier eyesCascade;
  void loadCascadeFiles();
};

} // namespace detectorsz

#endif
