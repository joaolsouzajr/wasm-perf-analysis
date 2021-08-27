#include "helloopencv/myimage.hpp"

namespace helloopencv
{

MyImage::MyImage(int cols, int rows, int channels)
{
  this->cols = cols;
  this->rows = rows;
  this->channels = channels;
  this->dataSize = cols * rows * channels;
}

MyImage::~MyImage()
{
  delete[] data;
}

unsigned char *MyImage::getData()
{
  return this->data;
}

void MyImage::setData(unsigned char *data)
{
  this->data = data;
}

long MyImage::getDataSize()
{
  return this->dataSize;
}

} // namespace helloopencv
