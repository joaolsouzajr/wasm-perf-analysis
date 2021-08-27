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
#ifndef DZAPP_HHP
#include <chrono>

#define DZAPP_HHP
#include <fstream>
#include <iostream>
#include <mutex>
#include <thread>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "detectorsz/detectorsz.hpp"

using namespace std;
using namespace cv;
using namespace chrono;
using namespace detectorsz;

namespace dzapp {

// constants
enum ScaleResolution { SMALL, MEDIUM, LARGE };
enum Workload { FACE_DETECT, FACE_EYES_DETECT };
const cv::Size SMALL_RESOLUTION = Size(480, 320);  // 153,600
const cv::Size MEDIUM_RESOLUTION = Size(768, 480); // 368,640
const cv::Size LARGE_RESOLUTION = Size(1280, 720); // 921,600

// properties
mutex myMutex;
mutex myMutex2;
vector<cv::Mat> frameStack;
bool videoEnded = false;
bool procEnded = false;
unsigned int frameCount = 0;
unsigned int frameIndex = 0;
int64 totalTime = 0;

// parameters
string datasetName;
string datasetPath;
cv::Size scaleResoution;
Workload workloadSelected;
string resolutionLabel;

void configureParams(int argc, char **argv);

void frameCapture();

void runWorkload(FaceDetect &faceDetect);

void report(FaceDetect &faceDetect);

} // namespace dzapp

#endif
