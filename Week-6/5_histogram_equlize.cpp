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

    Mat dst = image.clone();
    equalizeHist(image, dst);

    imshow("Image", image);
    imshow("Equalized", dst);
    waitKey(0);
    return 0;
}