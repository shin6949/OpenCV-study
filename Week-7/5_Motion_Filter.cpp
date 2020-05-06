// Created 2020/04/28.

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    Mat image = imread("/users/cocoblue/test.JPG", IMREAD_COLOR);
    if (image.empty()) {
        cout << "Cannot Read Image" << endl;
        return -1;
    }

    float weights[30][30] = {0,};
    for (int i = 0; i < 30; i++) { weights[14][i] = 1 / 30.0F; }
    Mat mask = Mat(30, 30, CV_32F, weights);

    Mat dst;
    dst.convertTo(dst, CV_8UC3);

    filter2D(image, dst, -1, mask, Point(-1, -1), 0, BORDER_DEFAULT);

    imshow("Before", image);
    imshow("After", dst);

    waitKey(0);
    return 0;
}

