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

#include <iostream>
#include <stdexcept>

#include "detectorsz/detectorsz.hpp"

using namespace std;
using namespace cv;

namespace detectorsz {

void convertAnyMatToRGBA(cv::Mat &src, cv::Mat &dest) {
  convertAnyMatTo8U(src, dest);
  // convert the img type to cv.CV_8UC4
  switch (dest.type()) {
  case CV_8UC1:
    cvtColor(dest, dest, COLOR_GRAY2RGBA);
    break;
  case CV_8UC3:
    cvtColor(dest, dest, COLOR_RGB2RGBA);
    break;
  case CV_8UC4:
    break;
  default:
    throw runtime_error(
        "Bad number of channels (Source image must have 1, 3 or 4 channels)");
    return;
  }
}

void convertAnyMatToRGB(cv::Mat &src, cv::Mat &dest) {
  convertAnyMatTo8U(src, dest);
  // convert the img type to cv.CV_8UC3
  switch (dest.type()) {
  case CV_8UC1:
    cvtColor(dest, dest, COLOR_GRAY2RGB);
    break;
  case CV_8UC3:
    break;
  case CV_8UC4:
    cvtColor(dest, dest, COLOR_RGBA2RGB);
    break;
  default:
    throw runtime_error(
        "Bad number of channels (Source image must have 1, 3 or 4 channels)");
    return;
  }
}

void convertAnyMatToGray(cv::Mat &src, cv::Mat &dest) {
  convertAnyMatTo8U(src, dest);
  // convert the img type to cv.CV_8UC1
  switch (dest.type()) {
  case CV_8UC1:
    break;
  case CV_8UC3:
    cvtColor(dest, dest, COLOR_RGB2GRAY);
    break;
  case CV_8UC4:
    cvtColor(dest, dest, COLOR_RGBA2GRAY);
    break;
  default:
    throw runtime_error(
        "Bad number of channels (Source image must have 1, 3 or 4 channels)");
    return;
  }
}

void convertAnyMatTo8U(cv::Mat &src, cv::Mat &dest) {
  // convert the mat type to cv.CV_8U
  int depth = src.type() % 8;
  double scale = depth <= CV_8S ? 1.0 : (depth <= CV_32S ? 1.0 / 256.0 : 255.0);
  double shift = (depth == CV_8S || depth == CV_16S) ? 128.0 : 0.0;
  src.convertTo(dest, CV_8U, scale, shift);
}

size_t matSize(const cv::Mat &mat) {
  return (mat.total() * mat.elemSize()) / sizeof(unsigned char);
}

} // namespace detectorsz
