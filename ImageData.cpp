#include "ImageData.hpp"
#include <cmath>

int ImageData::width = 0;
int ImageData::height = 0;

ImageData::ImageData(int valuesCount, unsigned short* values) {
	this->max = new unsigned short(0);
	this->min = new unsigned short(USHRT_MAX);
	for (int i = 0; i < valuesCount; i++) {
		this->setMinMax(&values[i]);
	}
	this->setValues(values);
}

unsigned short* ImageData::getRawValues() {
	int valuesCount = ImageData::getWidth() * ImageData::getHeight();
	unsigned short* values = new unsigned short[valuesCount];
	for (int i = 0; i < valuesCount; i++) {
		values[i] = this->values[i];
	}
	return values;
}

char* ImageData::getValues(float gammaCorrection) {
	int valuesCount = ImageData::getWidth() * ImageData::getHeight();
	char* values = new char[valuesCount];
	double divider = (*max - *min) / 255.0;
	for (int i = 0; i < valuesCount; i++) {
		double value = (this->values[i] - *min) / divider;
		values[i] = 255 - (char)(255 * pow(value / 255, gammaCorrection));

	}
	return values;
}

void ImageData::setValues(unsigned short* values) {
	this->values = values;
}

void ImageData::setMinMax(unsigned short* value) {
	if (*value > *max) *max = *value;
	if (*value < *min) *min = *value;
}

int ImageData::getWidth() {
	return width;
}

void ImageData::setWidth(int value) {
	width = value;
}

int ImageData::getHeight() {
	return height;
}

void ImageData::setHeight(int value) {
	height = value;
}

ImageData::~ImageData() {
	delete[] values;
	delete max;
	delete min;
}
