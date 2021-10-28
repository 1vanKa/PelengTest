#pragma once

/**
 * Class contains raw information about brightness of single channel image.
 */
class ImageData {
	unsigned short* values;
	unsigned short* max;
	unsigned short* min;
	static int width;
	static int height;
public:
	/**
	 * Creates an object with specified values of brightness.
	 * Also finds max and min brightness.
	 * valuesCount - size of array
	 * values - raw data array
	 */
	ImageData(int valuesCount, unsigned short* values);
	/**
	 * Returns raw data.
	 */
	unsigned short* getRawValues();
	/**
	 * Returns procecced data which contains values from 0 to 255.
	 * gammaCorrection - parameter for gamma correction.
	 */
	char* getValues(float gammaCorrection);
	/**
	 * Sets raw data values.
	 */
	void setValues(unsigned short* values);
	/**
	 * Finds if value is max or min value of data and saves it.
	 */
	void setMinMax(unsigned short* value);
	/**
	 * Returns width of the image in pixels.
	 */
	static int getWidth();
	/**
	 * Sets width of the image in pixels.
	 */
	static void setWidth(int value);
	/**
	 * Returns height of the image in pixels.
	 */
	static int getHeight();
	/**
	 * Sets height of the image in pixels.
	 */
	static void setHeight(int value);

	~ImageData();
};

