// Created on 2020/05/28.
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main() {
    // 사진 읽기
    Mat image = imread("/users/cocoblue/unnamed.JPG", IMREAD_COLOR);

    // 사진이 열렸는지 확인
    if (image.empty()) {
        cout << "Can Not Open The Picture File" << endl;
        return -1;
    }

    // 하얀색 부분을 제외
    Mat imgThresholded;
    inRange(image, Scalar(242, 242, 242),
            Scalar(255, 255, 255), imgThresholded);

    // 하얀색 부분을 0, 얼굴 부분을 1로 변경
    bitwise_not(imgThresholded, imgThresholded);
    // 결과 Mat 정의
    Mat result;
    // and 연산으로 얼굴 부분만 result에 할당
    bitwise_and(image, image, result, imgThresholded);

    imshow("Original", image);
    imshow("Result", result);
    waitKey(0);
    return 0;
}