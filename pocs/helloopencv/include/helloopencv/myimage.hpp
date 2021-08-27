
#ifndef MYIMAGE_HPP
#define MYIMAGE_HPP

namespace  helloopencv
{
  class MyImage
  {
    private:
      int rows;
      int cols;
      int channels;
      unsigned char* data;
      long dataSize;

    public:
      MyImage(int cols, int rows, int channels);

      ~MyImage();

      unsigned char* getData();

      void setData(unsigned char* data);

      long getDataSize();
  };
}

#endif




