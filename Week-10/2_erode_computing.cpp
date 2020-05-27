// Created on 2020/05/20.

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/* 풀이 순서
 * 1. 사진을 이진화
 * 2. 이진화된 사진을 주어진 형태소를 이용해서 침식 연산을 수행
 */
int main() {
    // 이미지를 일단 그레이스케일로 불러온다.
    Mat image = imread("/users/cocoblue/test.JPG", IMREAD_GRAYSCALE);
    if (image.empty()) {
        cout << "Can Not Read Image" << endl;
        return -1;
    }

    // 0과 1의 경계를 127로 설정 (255/2)
    int threshold_value = 127;
    // 결과를 저장할 Mat 정의
    Mat threshold_image;
    // 이진화 -> 127 미만 = 0, 127 이상 = 1로 변환함.
    threshold(image, threshold_image, threshold_value, 255, THRESH_BINARY);

    // 5x5 요소 정의
    Mat element_5 = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));
    // 3x3 마스크 정의
    Mat element_3 = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));

    // 결과 정의
    Mat result_3, result_5;

    // 침식 연산 수행
    erode(threshold_image, result_5, element_5);
    erode(threshold_image, result_3, element_3);

    // 각각의 결과를 표시
    imshow("threshold", threshold_image);
    imshow("3x3", result_3);
    imshow("5x5", result_5);

    waitKey(0);
    return 0;
}