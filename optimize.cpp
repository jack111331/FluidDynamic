#include "Optimization.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

static void costFunction() {
  int imageWidth, imageHeight, imageChannels;
  uint8_t * data = stbi_load("targetImage.png", &imageWidth, &imageHeight, &imageChannels, 0);
  if(data) {
  } else {
    // std::cout << __FILE__ << " Failed to Load Image " << TextureFilenameInstance.c_str() << std::endl;
  }
  stbi_image_free(data);
} 
