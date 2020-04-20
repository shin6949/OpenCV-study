// Created on 2020/04/20.

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat image = imread("/users/cocoblue/test.JPG", IMREAD_GRAYSCALE);
    if (image.empty()) {
        cout << "Cannot Read Image" << endl;
        return -1;
    }

    imshow("Input Image", image);
    int histogram[256] = {0};

    for (int y = 0; y < image.rows; y++) {
        for (int x = 0; x < image.cols; x++) {
            histogram[(int) image.at<uchar>(y, x)]++;
        }
    }

    for (int count : histogram) {
        cout << count << ",";
    }

    waitKey(0);
    return 0;
}