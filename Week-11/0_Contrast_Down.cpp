// Created on 2020/05/27.

#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main() {
    // 사진 읽기
    Mat image = imread("/users/cocoblue/test.JPG", IMREAD_COLOR);

    // 사진이 열렸는지 확인
    if (image.empty()) {
        cout << "Can Not Open The Picture File" << endl;
        return -1;
    }

    Mat img_lower_contrast;

    // Contrast 조절
    image.convertTo(img_lower_contrast, -1, 0.5, 0);

    imwrite("/users/cocoblue/test_contrast.JPG", img_lower_contrast);
    return 0;
}