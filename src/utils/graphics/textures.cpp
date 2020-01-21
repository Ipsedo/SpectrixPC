//
// Created by samuel on 20/10/18.
//

#include "textures.h"

imgRGB loadImage(string imageFile) {
	int width, height;
	unsigned char *img = SOIL_load_image(imageFile.c_str(), &width, &height, nullptr, SOIL_LOAD_RGB);
	return {width, height, img};
}
