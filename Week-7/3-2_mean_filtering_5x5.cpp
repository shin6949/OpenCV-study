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
    Mat dst;

    blur(image, dst, Size(5, 5));
    imshow("Before", image);
    imshow("After", dst);

    waitKey(0);
    return 0;
}

