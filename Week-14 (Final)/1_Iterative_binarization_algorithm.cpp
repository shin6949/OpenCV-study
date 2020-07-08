#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 이미지를 불러옴.
    Mat image = imread("/users/cocoblue/test.JPG", IMREAD_GRAYSCALE);
    if (image.empty()) {
        cout << "Can't Open Image" << endl;
        return -1;
    }

    // 초기 추정치 정의
    short Estimate = 127;

    // 평균 값 구하기
    float mean[2] = {0,};

    // while 1로 U1 = U2가 될 때까지 반복
    while (1) {
        // R1 = 추정치보다 큰 영역, R2 = 추정치보다 작은 영역
        // { R1 픽셀의 밝기 합, R2 픽셀의 밝기 합 }
        int value[2] = {0,};

        // { R1 픽셀의 갯수, R2 픽셀의 갯수 }
        int count[2] = {0,};

        // AREA 판단
        for (int i = 0; i < image.rows; i++) {
            for (int j = 0; j < image.cols; j++) {
                if (image.at<uchar>(i, j) > Estimate) {
                    // 추정치보다 클 때
                    value[0] += image.at<uchar>(i, j);
                    count[0] += 1;
                } else {
                    // 추정치보다 작을 때
                    value[1] += image.at<uchar>(i, j);
                    count[1] += 1;
                }
            }
        }

        // 새로 구한 평균 임계 값이 이전과 같으면, break
        if (((float) value[0] / (float) count[0] == mean[0]) && ((float) value[1] / (float) count[1] == mean[1])) {
            break;
        }

        // 평균 구하기
        for (int i = 0; i < 2; i++) {
            mean[i] = (float) value[i] / (float) count[i];
        }

        // 새로운 임계 값 설정
        Estimate = (mean[0] + mean[1]) / 2;
    }

    threshold(image, image, Estimate, 255, THRESH_BINARY);
    imshow("Image", image);
    waitKey(0);
    return 0;
}