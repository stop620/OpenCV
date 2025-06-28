#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <ctime>
#include "opencv2\opencv.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"
#include <format>

using namespace cv;
using namespace std;


vector<vector<Point> > contour(Mat dilated) {
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(dilated, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	return contours;
}

Mat diffimg(Mat frame1, Mat frame2) {
	Mat diff, gray, blur, thresh, dilated;
	absdiff(frame1, frame2, diff);
	cvtColor(diff, gray, COLOR_BGR2GRAY);
	GaussianBlur(gray, blur, Size(15, 15), 0);
	threshold(blur, thresh, 50, 255, THRESH_BINARY);
	dilate(thresh, dilated, NULL, Point(-1, -1), 3);

	return dilated;
}

Mat imgProcess(Mat frame) {
	Mat bright, cont, gray, gaus, bluri;
	float alpha = -0.4;
	bright = frame + 50;
	cont = bright + (bright - 128) * alpha;
	cvtColor(cont, gray, COLOR_BGR2GRAY);
	GaussianBlur(gray, gaus, Size(15, 15), 0);
	blur(gaus, bluri, Size(5, 5));

	return bluri;
}

Mat getDiff(Mat frame1, Mat frame2) {
	Mat diff, thresh, dilated;
	absdiff(frame1, frame2, diff);
	threshold(diff, thresh, 60, 255, THRESH_BINARY);
	dilate(thresh, dilated, NULL, Point(-1, -1), 3);

	return dilated;
}

int main() {
	int keyValue;
	int count = 0;
	time_t temp;
	struct tm* timeinfo;
	VideoCapture cap(0); // 파일 경로, 0 = 카메라

	int frame_width = cvRound(cap.get(CAP_PROP_FRAME_WIDTH));
	int frame_height = cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));

	int fourcc = VideoWriter::fourcc('X', 'V', 'I', 'D');
	double fps = cap.get(CAP_PROP_FPS);
	VideoWriter output("output.mp4", fourcc, 6, Size(frame_width, frame_height)); //파일 fps, 카메라 6
	Mat frame1, frame2, frame3, sub;

	Mat fframe, bframe;

	cap >> fframe;
	bframe = imgProcess(fframe);

	while (1) {
		time(&temp);
		timeinfo = localtime(&temp);
		String time = asctime(timeinfo);
		vector<vector<Point> > contours;
		vector<Rect> ROIs;

		cap >> frame1;
		
		frame2 = imgProcess(frame1);

		sub = getDiff(bframe, frame2);
		contours = contour(sub);

		for (int i = 0; i < contours.size(); i++) {
			if (contourArea(contours[i]) < 1000) continue;
			ROIs.push_back(boundingRect(contours[i]));
		}

		for (auto& ROI : ROIs) {
			rectangle(frame1, ROI, Scalar(0, 0, 255), 2);
		}

		Mat image;
		resize(frame1, image, Size(1080, 720));
		putText(image, time, Point(50, 680), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0));
		putText(image, "Count: " + to_string(ROIs.size()), Point(50, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0), 2);
		imshow("image", image);
		imshow("diff image", sub);

		output << frame1;

		keyValue = waitKey(1); //파일 1000/fps, 카메라 1
		if (keyValue == 27) { //esc 종료
			break;
		}
		else if (keyValue == ' ') { //space 일시정지
			waitKey(0) == ' ';
		}
		else if (keyValue == 'p' || keyValue == 'P') { //p 캡쳐
			imwrite("./capture" + to_string(count) + ".png", frame1);
			count++;
		}
	}

	cap.release();
	output.release();

	return 0;
}
