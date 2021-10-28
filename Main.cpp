#include "Main.hpp"
#include "ImageData.hpp"
#include <cstdint>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

double gammaCorrection = 1 / 2.2;

int main(int argc, char** argv) {
	ifstream in(argv[1], ios::binary);
	if (!in.good()) {
		cout << "Can not open file." << endl;
		return -1;
	}
	ImageData::setWidth(atoi(argv[3]));
	ImageData::setHeight(atoi(argv[4]));
	int imagesCount = atoi(argv[5]);
	in.seekg(32); //skip header
	int valuesCount = ImageData::getWidth() * ImageData::getHeight();
	VideoWriter writer(argv[2],
		VideoWriter::fourcc('x', '2', '6', '4'),
		30,
		*(new Size(ImageData::getWidth(), ImageData::getHeight())),
		true);
	if (!writer.isOpened()) {
		cout << "Can not open output video" << endl;
		return -1;
	}
	for (int j = 0; j < imagesCount; j++) {
		unsigned short* values = new unsigned short[valuesCount];
		in.read((char*)values, sizeof(short) * valuesCount);
		ImageData image = ImageData(valuesCount, values);
		char* valuesChar = image.getValues(gammaCorrection);
		Mat mat = createImageMat(valuesChar);
		writer.write(mat);
		delete[] valuesChar;
	}
	writer.release();
	return 0;
}

Mat createImageMat(char* values) {
	Mat mat = Mat(ImageData::getHeight(), ImageData::getWidth(), CV_8U, values);
	vector<Mat> channels = { mat, mat, mat };
	Mat threeChannelMat;
	merge(channels, threeChannelMat);
	return threeChannelMat;
}
