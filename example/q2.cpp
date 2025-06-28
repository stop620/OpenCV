#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

Mat img;
Mat img2;
Point startP;
Point endP;
void on_mouse(int event, int x, int y, int flags, void*) {
	switch (event) {
	case EVENT_LBUTTONDOWN:
		startP = Point(x, y);
		break;
	case EVENT_LBUTTONUP:
		endP = Point(x, y);
		img2 = img(Rect(startP, endP)).clone();
		rectangle(img, startP, endP, Scalar(0, 0, 255), 2);
		imshow("img", img);
		break;
	case EVENT_MOUSEMOVE:
		if (flags & EVENT_FLAG_LBUTTON) {

		}
		break;
	default:
		break;
	}
}

void on_level_change(int pos, void* userdata) {
	int br = pos - 120;
	Mat src = *(Mat*)userdata;
	Mat dst = src + Scalar(br, br, br);
	imshow("img", dst);
}

int main(void)
{
	int value = 120;
	img = imread("images/airplane.bmp");

	namedWindow("img");
	createTrackbar("bright", "img", &value, 255, on_level_change, (void*)&img);
	setMouseCallback("img", on_mouse);

	imshow("img", img);

	waitKey(0);

	return 0;
}