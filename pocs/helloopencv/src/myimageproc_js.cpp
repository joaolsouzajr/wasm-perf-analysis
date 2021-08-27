#include "helloopencv/myimageproc.hpp"
#include <emscripten/bind.h>

using namespace helloopencv;

namespace myimageprocjs
{

  emscripten::val setDataSrc(MyImageProc& proc, intptr_t dataSrc, long size)
  {
      proc.setDataSrc(reinterpret_cast<unsigned char*>(dataSrc), size);
      return emscripten::val::undefined();
  }

  emscripten::val getDataResult(MyImageProc& proc)
  {
    return emscripten::val(
      emscripten::memory_view<unsigned char>(proc.getSizeResult(), proc.dataResult));
  }

  emscripten::val getCols(MyImageProc& proc)
  {
    return emscripten::val(proc.getCols());
  }

  emscripten::val getRows(MyImageProc& proc)
  {
    return emscripten::val(proc.getRows());
  }

  emscripten::val transformToGray(MyImageProc& proc, intptr_t dataSrc, intptr_t dataDest)
  {
    proc.transformToGray(reinterpret_cast<unsigned char*>(dataSrc),
      reinterpret_cast<unsigned char*>(dataDest));
    return emscripten::val::undefined();
  }

  emscripten::val gray(MyImageProc& proc)
  {
    if(proc.dataSrc == nullptr)
    {
      return emscripten::val::undefined();
    }
    proc.gray();
    return emscripten::val(
      emscripten::memory_view<unsigned char>(proc.getSizeResult(), proc.dataResult));
  }

  emscripten::val hsv(MyImageProc& proc)
  {
    if(proc.dataSrc == nullptr)
    {
      return emscripten::val::undefined();
    }
    proc.hsv();
    return emscripten::val(emscripten::memory_view<unsigned char>(proc.getSizeResult(), proc.dataResult));
  }

  emscripten::val faceDetect(MyImageProc& proc)
  {
    if(proc.dataSrc == nullptr)
    {
      return emscripten::val::undefined();
    }
    proc.faceDetect();
    return emscripten::val(emscripten::memory_view<unsigned char>(proc.getSizeResult(), proc.dataResult));
  }

} // namespace myimageprocjs


EMSCRIPTEN_BINDINGS(myimageprocjs) {
  emscripten::class_<MyImageProc>("MyImageProc")
    .constructor<>()
    .constructor<int, int>()
    .function("gray", &myimageprocjs::gray)
    .function("hsv", &myimageprocjs::hsv)
    .function("faceDetect", &myimageprocjs::faceDetect)
    .function("getCols", &myimageprocjs::getCols)
    .function("getRows", &myimageprocjs::getRows)
    .function("getDataResult", &myimageprocjs::getDataResult)
    .function("transformToGray", &myimageprocjs::transformToGray, emscripten::allow_raw_pointers())
    .function("setDataSrc", &myimageprocjs::setDataSrc, emscripten::allow_raw_pointers());
}
