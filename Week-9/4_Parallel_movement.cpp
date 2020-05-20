// Created on 2020/05/14.

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void onMouse(int event, int x, int y, int flags, void *param);

struct point {
    int down_x = 0, down_y = 0;
} input_point;

int main() {
    Mat image = imread("/users/cocoblue/test.JPG", IMREAD_COLOR);
    if (image.empty()) { cout << "Can Not Read Image" << endl; } //이미지를 읽을 수 없을 때

    namedWindow("Image");
    setMouseCallback("Image", onMouse, &image);
    imshow("Image", image);

    waitKey(0);
    return true;
}

void onMouse(int event, int x, int y, int flags, void *param) {
    Mat *received = (Mat *) param;
    if (event == EVENT_LBUTTONDOWN) {
        input_point.down_x = x;
        input_point.down_y = y;
    } else if (event == EVENT_LBUTTONUP) {
        Mat tmat = (Mat_<double>(2, 3) << 1, 0, x - input_point.down_x,
                0, 1, y - input_point.down_y);
        Mat dst;
        warpAffine(*received, dst, tmat, received->size());
        imshow("Image", dst);
    }
}