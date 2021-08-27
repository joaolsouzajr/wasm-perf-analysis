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

#include "detectorsz/detectorsz.hpp"

#include <chrono>
#include <iostream>
#include <stdexcept>

using namespace std;
using namespace cv;
using namespace chrono;

namespace detectorsz {

FaceDetect::FaceDetect() {
  loadCascadeFiles();
  this->dataName = "";
}

FaceDetect::FaceDetect(string dataName) {
  loadCascadeFiles();
  this->dataName = dataName;
}

FaceDetect::~FaceDetect() {
  faceCascade.~CascadeClassifier();
  eyesCascade.~CascadeClassifier();
  if (logs.size()) {
    logs.shrink_to_fit();
  }
}

void FaceDetect::faceDetectWithLog(MatAdapter &srcImg) {
  FaceEyesDetectLog log;
  log.workloadName = this->dataName;
  log.functionName = FACE_DETECT_NAME;
  //-- Pre process
  auto start = high_resolution_clock::now();
  Mat dest;
  convertAnyMatToGray(srcImg.matImg, dest);
  equalizeHist(dest, dest);
  auto end = high_resolution_clock::now();
  log.preProcTime = duration_cast<milliseconds>(end - start).count();
  //-- Detect faces process
  start = high_resolution_clock::now();
  std::vector<Rect> faces;
  faceCascade.detectMultiScale(dest, faces);
  log.numberDetectedFaces = faces.size();
  end = high_resolution_clock::now();
  log.processTime = duration_cast<milliseconds>(end - start).count();
  //-- Tag faces
  start = high_resolution_clock::now();
  for (size_t i = 0; i < faces.size(); i++) {
    Point center(faces[i].x + faces[i].width / 2,
                 faces[i].y + faces[i].height / 2);
    ellipse(srcImg.matImg, center,
            Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360,
            Scalar(255, 0, 255), 4);
  }
  end = high_resolution_clock::now();
  log.tagProcTime = duration_cast<milliseconds>(end - start).count();
  //-- Pos process
  start = high_resolution_clock::now();
  convertAnyMatToRGBA(srcImg.matImg, srcImg.matImg);
  end = high_resolution_clock::now();
  log.posProcTime = duration_cast<milliseconds>(end - start).count();
  logs.push_back(log);
}

void FaceDetect::faceAndEyesDetectWithLog(MatAdapter &srcImg) {
  FaceEyesDetectLog log;
  log.workloadName = this->dataName;
  log.functionName = FACE_EYES_DETECT_NAME;
  //-- Pre process
  auto start = high_resolution_clock::now();
  Mat dest;
  convertAnyMatToGray(srcImg.matImg, dest);
  equalizeHist(dest, dest);
  auto end = high_resolution_clock::now();
  log.preProcTime = duration_cast<milliseconds>(end - start).count();
  //-- Detect faces
  std::vector<Rect> faces;
  start = high_resolution_clock::now();
  faceCascade.detectMultiScale(dest, faces);
  log.numberDetectedFaces = faces.size();
  end = high_resolution_clock::now();
  log.processTime = duration_cast<milliseconds>(end - start).count();
  for (size_t i = 0; i < faces.size(); i++) {
    //-- In each face, detect eyes
    start = high_resolution_clock::now();
    Mat faceROI = dest(faces[i]);
    std::vector<Rect> eyes;
    eyesCascade.detectMultiScale(faceROI, eyes);
    log.numberDetectedEyes = log.numberDetectedEyes + eyes.size();
    end = high_resolution_clock::now();
    log.processTime =
        log.processTime + duration_cast<milliseconds>(end - start).count();
    //-- Tag process
    start = high_resolution_clock::now();
    Point center(faces[i].x + faces[i].width / 2,
                 faces[i].y + faces[i].height / 2);
    ellipse(srcImg.matImg, center,
            Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360,
            Scalar(255, 0, 255), 4);
    for (size_t j = 0; j < eyes.size(); j++) {
      Point eye_center(faces[i].x + eyes[j].x + eyes[j].width / 2,
                       faces[i].y + eyes[j].y + eyes[j].height / 2);
      int radius = cvRound((eyes[j].width + eyes[j].height) * 0.25);
      circle(srcImg.matImg, eye_center, radius, Scalar(255, 0, 0), 4);
      std::cout << "Eyes " << j << endl;
    }
    end = high_resolution_clock::now();
    log.tagProcTime =
        log.tagProcTime + duration_cast<milliseconds>(end - start).count();
  }
  //--Pos process
  start = high_resolution_clock::now();
  convertAnyMatToRGBA(srcImg.matImg, srcImg.matImg);
  end = high_resolution_clock::now();
  log.posProcTime = duration_cast<milliseconds>(end - start).count();
  logs.push_back(log);
}

void FaceDetect::faceDetect(MatAdapter &srcImg) {
  Mat dest;
  //-- Pre process
  convertAnyMatToGray(srcImg.matImg, dest);
  equalizeHist(dest, dest);
  //-- Detect faces
  std::vector<Rect> faces;
  faceCascade.detectMultiScale(dest, faces);
  //-- Tag faces
  for (size_t i = 0; i < faces.size(); i++) {
    Point center(faces[i].x + faces[i].width / 2,
                 faces[i].y + faces[i].height / 2);
    ellipse(srcImg.matImg, center,
            Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360,
            Scalar(255, 0, 255), 4);
  }
  //-- Pos process
  convertAnyMatToRGBA(srcImg.matImg, srcImg.matImg);
}

void FaceDetect::faceAndEyesDetect(MatAdapter &srcImg) {
  Mat dest;
  convertAnyMatToGray(srcImg.matImg, dest);
  equalizeHist(dest, dest);
  //-- Detect faces
  std::vector<Rect> faces;
  faceCascade.detectMultiScale(dest, faces);
  for (size_t i = 0; i < faces.size(); i++) {
    Point center(faces[i].x + faces[i].width / 2,
                 faces[i].y + faces[i].height / 2);
    ellipse(srcImg.matImg, center,
            Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360,
            Scalar(255, 0, 255), 4);
    Mat faceROI = dest(faces[i]);
    //-- In each face, detect eyes
    std::vector<Rect> eyes;
    eyesCascade.detectMultiScale(faceROI, eyes);
    for (size_t j = 0; j < eyes.size(); j++) {
      Point eye_center(faces[i].x + eyes[j].x + eyes[j].width / 2,
                       faces[i].y + eyes[j].y + eyes[j].height / 2);
      int radius = cvRound((eyes[j].width + eyes[j].height) * 0.25);
      circle(srcImg.matImg, eye_center, radius, Scalar(255, 0, 0), 4);
      std::cout << "Eyes " << j << endl;
    }
  }
  convertAnyMatToRGBA(srcImg.matImg, srcImg.matImg);
  dest.release();
}

void FaceDetect::loadCascadeFiles() {
  if (!faceCascade.load(FACE_CASCADE_PATH)) {
    std::cerr << "--(!)Error loading face cascade\n" << endl;
    throw runtime_error("--(!)Error loading face cascade\n");
    return;
  };
  if (!eyesCascade.load(EYES_CASCADE_PATH)) {
    std::cerr << "--(!)Error loading eyes cascade\n" << endl;
    throw runtime_error("--(!)Error loading eyes cascade\n");
    return;
  };
}

string FaceDetect::logsToString() {
  string alllog = "id,dataset,workload,faces_detected,eyes_detected,process_"
                  "time_us,total_time_ms\n";
  for (unsigned int i = 0; i < logs.size(); i++) {
    alllog = alllog + to_string(i) + "," + logs[i].toString() + "\n";
  }
  return alllog;
}

string FaceDetect::logsToStringAndAddCommon(string head, string columns) {
  string alllog =
      "id,dataset,workload,faces_detected,eyes_detected,"
      "process_time_ms,pre_time_ms,tag_time_ms,pos_time_ms,total_time_ms" +
      head + "\n";
  for (unsigned int i = 0; i < logs.size(); i++) {
    alllog = alllog + to_string(i) + "," + logs[i].toString() + columns + "\n";
  }
  return alllog;
}

void FaceDetect::updateTotalTime(int frameIndex, int time) {
  logs[frameIndex].totalTime = (int64)time;
}

FaceEyesDetectLog::FaceEyesDetectLog() {}
FaceEyesDetectLog::~FaceEyesDetectLog() {}
string FaceEyesDetectLog::toString() {
  return this->workloadName + "," + this->functionName + "," +
         to_string(this->numberDetectedFaces) + "," +
         to_string(this->numberDetectedEyes) + "," +
         to_string(this->processTime) + "," + to_string(this->preProcTime) +
         ", " + to_string(this->tagProcTime) + ", " +
         to_string(this->posProcTime) + ", " + to_string(this->totalTime);
}

} // namespace detectorsz
