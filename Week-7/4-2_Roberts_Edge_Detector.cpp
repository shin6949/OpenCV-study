// Created 2020/04/28.

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    Mat image = imread("/users/cocoblue/test.JPG", IMREAD_GRAYSCALE);
    if (image.empty()) {
        cout << "Cannot Read Image" << endl;
        return -1;
    }

    float x_weight[] = {
            0, 0 - 1,
            0, 1, 0,
            0, 0, 0
    };

    float y_weight[] = {
            -1, 0, 0,
            0, 1, 0,
            0, 0, 0
    };

    Mat x_mask = Mat(3, 3, CV_16S, x_weight);
    Mat y_mask = Mat(3, 3, CV_16S, y_weight);

    Mat dst_x, dst_y, dst;

    filter2D(image, dst_x, -1, x_mask);
    filter2D(image, dst_y, -1, y_mask);

    addWeighted(dst_x, 0.5, dst_y, 0.5, 0, dst);

    imshow("Before", image);
    imshow("After", dst);

    waitKey(0);
    return 0;
}

