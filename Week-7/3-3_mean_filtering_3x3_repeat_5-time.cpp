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
    imshow("Before", image);

    for (int i = 0; i < 4; i++) {
        blur(image, image, Size(3, 3));
    }

    imshow("After", image);

    waitKey(0);
    return 0;
}

