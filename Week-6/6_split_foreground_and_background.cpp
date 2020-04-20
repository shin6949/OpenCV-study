// Created on 2020/04/21.

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

    Mat dst, threshold_image;
    threshold(image, threshold_image, 0, 255, THRESH_BINARY | THRESH_OTSU);

    imshow("Thresholded", threshold_image);
    waitKey(0);
    return 0;
}