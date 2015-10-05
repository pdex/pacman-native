// -*- C++ -*-
#ifndef CANVAS_IMAGE_DATA_H
#define CANVAS_IMAGE_DATA_H

#include "Canvas.h"

class CanvasImageData : public Canvas {
  std::shared_ptr<pp::ImageData> image;
public:
  CanvasImageData(std::shared_ptr<pp::ImageData> image)
    : Canvas(
	static_cast<uint32_t*>(image->data()),
	image->size().width(),
	image->size().height()
    )
    , image(image)
  {
  }
};

#endif//CANVAS_IMAGE_DATA_H
