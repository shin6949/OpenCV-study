#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void change_value(int value, void *received);

int main() {
    int value = 0;

    Mat cell, nucleus, bg, dst;
    Mat image = imread("/users/cocoblue/Fig1.tif", IMREAD_GRAYSCALE);
    if (image.empty()) {
        cout << "Can't Open Image!" << endl;
        return -1;
    }

    namedWindow("Image", WINDOW_AUTOSIZE);
    createTrackbar("Value", "Image", &value, 255, change_value, (void *) &image);
    imshow("Image", image);

    waitKey(0);
    return 0;
}

void change_value(int value, void *received) {
    Mat *source = (Mat *) received;
    cout << value << endl;
    Mat result;
    threshold(*source, result, value, 255, THRESH_BINARY);
    imshow("Image", result);
}
