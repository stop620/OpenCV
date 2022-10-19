#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main(void)
{
	Mat img = imread("images/lenna.bmp");

	if (img.empty()) {
		cerr << "image load fail" << endl;
		return -1;
	}

	namedWindow("img");
	imshow("img", img);

	while (true) {
		int keycode = waitKey();

		if (keycode == 'r' || keycode == 'R') {
			for (int j = 0; j < img.rows; j++) {
				for (int i = 0; i < img.cols; i++) {
					Vec3b p = img.at<Vec3b>(j, i);
					img.at<Vec3b>(j, i)[2] = 255 - p[2];
				}
			}
			imshow("img", img);
		}
		else if (keycode == 'g' || keycode == 'G') {
			for (int j = 0; j < img.rows; j++) {
				for (int i = 0; i < img.cols; i++) {
					Vec3b p = img.at<Vec3b>(j, i);
					img.at<Vec3b>(j, i)[1] = 255 - p[1];
				}
			}
			imshow("img", img);
		}
		else if (keycode == 'b' || keycode == 'B') {
			for (int j = 0; j < img.rows; j++) {
				for (int i = 0; i < img.cols; i++) {
					Vec3b p = img.at<Vec3b>(j, i);
					img.at<Vec3b>(j, i)[0] = 255 - p[0];
				}
			}
			imshow("img", img);
		}
		else {
			break;
		}
	}
	return 0;
}