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

#include "detectorsz/dzwebapp.hpp"

namespace dzwebapp {

emscripten::val matRows(detectorsz::MatAdapter &matW) {
  return emscripten::val(matW.matImg.rows);
}

emscripten::val matCols(detectorsz::MatAdapter &matW) {
  return emscripten::val(matW.matImg.cols);
}

emscripten::val matData(const detectorsz::MatAdapter &matW) {
  return emscripten::val(emscripten::memory_view<unsigned char>(
      detectorsz::matSize(matW.matImg), matW.matImg.data));
}

} // namespace dzwebapp

EMSCRIPTEN_BINDINGS(dzwebapp) {
  emscripten::class_<detectorsz::MatAdapter>("MatAdapter")
      .constructor<>()
      .constructor<int, int>()
      .function("getRows", &dzwebapp::matRows)
      .function("getCols", &dzwebapp::matCols)
      .property("data", &dzwebapp::matData);
  emscripten::class_<detectorsz::ImageProcess>("ImageProcess")
      .constructor<>()
      .function("gray", &detectorsz::ImageProcess::gray)
      .function("hsv", &detectorsz::ImageProcess::hsv);
  emscripten::class_<detectorsz::FaceDetect>("FaceDetect")
      .constructor<>()
      .constructor<string>()
      .function("logsToString", &detectorsz::FaceDetect::logsToString)
      .function("logsToStringAndAddCommon", &detectorsz::FaceDetect::logsToStringAndAddCommon)
      .function("faceDetect", &detectorsz::FaceDetect::faceDetect)
      .function("faceAndEyesDetect", &detectorsz::FaceDetect::faceAndEyesDetect)
      .function("faceDetectWithLog", &detectorsz::FaceDetect::faceDetectWithLog)
      .function("faceAndEyesDetectWithLog",
                &detectorsz::FaceDetect::faceAndEyesDetectWithLog)
      .function("updateTotalTime", &detectorsz::FaceDetect::updateTotalTime);
}
