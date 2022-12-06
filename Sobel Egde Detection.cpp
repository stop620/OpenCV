#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void main() {
	Mat src = imread("images/lenna.bmp", IMREAD_GRAYSCALE);

	Mat dx, dy;
	//영상을 미분해 dx, dy에 저장
	Sobel(src, dx, CV_32FC1, 1, 0);
	Sobel(src, dy, CV_32FC1, 0, 1);

	Mat fmag, mag;
	magnitude(dx, dy, fmag);
	fmag.convertTo(mag, CV_8UC1);

	Mat edge = mag > 150;

	imshow("src", src);
	imshow("mag", mag);
	imshow("edge", edge);

	waitKey();
	destroyAllWindows();
}
