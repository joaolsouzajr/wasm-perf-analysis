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

Module['readImage'] = (imageSource) => {
  let canvas = Module._extractCanvasElement(imageSource);
  let imgData = canvas.getContext('2d').getImageData(
    0, 0, canvas.width, canvas.height);
  return Module.matAdapterFromImageData(imgData);
};

Module['showImage'] = (canvasSource, matAdapter) => {
  let canvas = Module._getCanvasElement(canvasSource)
  let imgData = new ImageData(new Uint8ClampedArray(
    matAdapter.data), matAdapter.getCols(), matAdapter.getRows());
  let ctx = canvas.getContext('2d');
  ctx.clearRect(0, 0, canvas.width, canvas.height);
  canvas.width = imgData.width;
  canvas.height = imgData.height;
  ctx.putImageData(imgData, 0, 0);
};

Module['VideoCapture'] = function (videoSource) {
  let video = Module._getVideoElement(videoSource);
  let canvas = document.createElement('canvas');
  canvas.width = video.width;
  canvas.height = video.height;
  let ctx = canvas.getContext('2d');
  this.video = video;
  this.read = () => {
    ctx.drawImage(video, 0, 0, video.width, video.height);
    return Module.matAdapterFromImageData(ctx.getImageData(0, 0, video.width, video.height));
  };
};

Module['_freeArray'] = (heapBytes) => {
  Module._free(heapBytes.byteOffset);
}

Module['_arrayToHeap'] = (typedArray) => {
  var numBytes = typedArray.length * typedArray.BYTES_PER_ELEMENT;
  var ptr = Module._malloc(numBytes);
  heapBytes = Module.HEAPU8.subarray(ptr, ptr + numBytes);
  heapBytes.set(typedArray);
  return heapBytes;
}

Module['_extractCanvasElement'] = (imageSource) => {
  let img = null;
  if (typeof imageSource === 'string') {
    img = document.getElementById(imageSource);
  } else {
    img = imageSource;
  }
  let canvas = null;
  if (img instanceof HTMLImageElement) {
    canvas = document.createElement('canvas');
    canvas.width = img.width;
    canvas.height = img.height;
    canvas.getContext('2d').drawImage(img, 0, 0, img.width, img.height);
  } else if (img instanceof HTMLCanvasElement) {
    canvas = img;
  } else {
    throw new Error('Please input the valid canvas or img id.');
  }
  return canvas;
}

Module['_getVideoElement'] = (videoSource) => {
  let video = null;
  if (typeof videoSource === 'string') {
    video = document.getElementById(videoSource);
  } else {
    video = videoSource;
  }
  if (!(video instanceof HTMLVideoElement)) {
    throw new Error('Please input the valid video element or id.');
  }
  return video;
}

Module['_getCanvasElement'] = (canvasSource) => {
  let canvas = null;
  if (typeof canvasSource === 'string') {
    canvas = document.getElementById(canvasSource);
  } else {
    canvas = canvasSource;
  }
  if (!(canvas instanceof HTMLCanvasElement)) {
    throw new Error('Please input the valid canvas element or id.');
  }
  return canvas;
}


Module['matAdapterFromImageData'] = function(imageData) {
  let mat = new Module.MatAdapter(imageData.height, imageData.width);
  mat.data.set(imageData.data);
  return mat;
};
