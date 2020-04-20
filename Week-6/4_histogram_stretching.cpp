// Created on 2020/04/21.

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int stretch(int x, int r1, int s1, int r2, int s2);

int main() {
    Mat image = imread("/users/cocoblue/test.JPG", IMREAD_COLOR);
    if (image.empty()) {
        cout << "Cannot Read Image" << endl;
        return -1;
    }

    Mat new_image = image.clone();

    int r1, s1, r2, s2;
    cout << "r1을 입력하시오: ";
    cin >> r1;
    cout << "r2을 입력하시오: ";
    cin >> r2;
    cout << "s1을 입력하시오: ";
    cin >> s1;
    cout << "s2을 입력하시오: ";
    cin >> s2;

    for (int y = 0; y < image.rows; y++) {
        for (int x = 0; x < image.cols; x++) {
            for (int c = 0; c < 3; c++) {
                int output = stretch(image.at<Vec3b>(y, x)[c], r1, s1, r2, s2);
                new_image.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(output);
            }
        }
    }

    imshow("Input Image", image);
    imshow("new_image", new_image);
    waitKey(0);
    return 0;
}

int stretch(int x, int r1, int s1, int r2, int s2) {
    float result;
    if (0 <= x && x <= r1) {
        result = s1 / r1 * x;
    } else if (r1 < x && x <= r2) {
        result = ((s2 - s1) / (r2 - r1)) * (x - r1) + s1;
    } else if (r2 < x && x <= 255) {
        result = ((255 - s2) / (255 - r2)) * (x - r2) + s2;
    }

    return (int) result;
}