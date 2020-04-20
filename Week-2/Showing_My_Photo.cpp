// Created on 2020/03/22.

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    Mat image = imread("/users/cocoblue/test.JPG", IMREAD_COLOR);
    if (image.empty()) {
        cout << "Cannot Read Image" << endl;
        return -1;
    }
    imshow("Image", image);
    waitKey(0);
    return 0;
}