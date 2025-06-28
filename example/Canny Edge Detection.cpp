	#include <iostream>
	#include "opencv2/opencv.hpp"

	using namespace std;
	using namespace cv;

	void main() {
		Mat src = imread("images/lenna.bmp", IMREAD_GRAYSCALE);

		Mat dst1, dst2;
		Canny(src, dst1, 50, 100);
		Canny(src, dst2, 50, 150);

		imshow("src", src);
		imshow("dst1", dst1);
		imshow("dst2", dst2);

		waitKey();
		destroyAllWindows();
	}
