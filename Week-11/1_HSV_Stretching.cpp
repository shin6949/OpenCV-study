// Created on 2020/05/28.

#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void doing_Stretching(Mat orig, Mat &result);

// 색을 해치지 않고 스트레칭
int main() {
    // 사진 읽기
    Mat image = imread("/users/cocoblue/test_contrast.JPG", IMREAD_COLOR);

    // 사진이 열렸는지 확인
    if (image.empty()) {
        cout << "Can Not Open The Picture File" << endl;
        return -1;
    }

    imshow("Original", image);

    // HSV로 색영역 변경
    cvtColor(image, image, COLOR_BGR2HSV);

    /*
     * HSV: Hue (색조), Saturation (채도), Value (밝기)
     * 색을 해치지 않기 위해서는 H 값은 유지하고 SV 값만 변경하면 됨.
     */
    Mat hsv_array[3];
    split(image, hsv_array);
    Mat result[3];

    for (int i = 0; i < 3; i++) {
        // clone을 하지 않는다면, result의 rows, cols를 참조하는데 문제가 생겨서, 메모리 예외가 발생함.
        result[i] = hsv_array[i].clone();
        // 색을 해치지 않기 위해 Hue는 스트래칭 하지 않음.
        if (i >= 1) {
            doing_Stretching(hsv_array[i], result[i]);
        }
    }

    // split한 데이터를 merge
    merge(result, 3, image);

    // 원래 색 영역으로 변경
    cvtColor(image, image, COLOR_HSV2BGR);

    imshow("Result", image);
    waitKey(0);
    return 0;
}

void doing_Stretching(Mat orig, Mat &result) {
    int low, high;

    // 이미지에서 제일 높은 값, 제일 낮은 값 판단
    for (int i = 0; i < orig.rows; i++) {
        for (int j = 0; j < orig.cols; j++) {
            // 출력시켜보니 이미지의 값이 이상하게 찍힘. 그러므로 (0, 0)일 때를 기준으로 초기 값을 설정하고 low, high를 판단
            if (i == 0 && j == 0) {
                low = (int) orig.at<uchar>(i, j);
                high = (int) orig.at<uchar>(i, j);
            }

            // low 값인지 판단
            if (low > (int) orig.at<uchar>(i, j)) {
                low = (int) orig.at<uchar>(i, j);
            }

            // high 값인지 판단
            if (high < (int) orig.at<uchar>(i, j)) {
                high = (int) orig.at<uchar>(i, j);
            }
        }
    }

    // Stretching
    // 범위 값을 설정. high, low 모두 int라서 float으로 캐스팅하지 않으면 나누기의 결과 값이 int로 반환 됨.
    float mult = 255 / (float) (high - low);

    // 스트레칭 진행
    for (int i = 0; i < orig.rows; i++) {
        for (int j = 0; j < orig.cols; j++) {
            result.at<uchar>(i, j) = (float) (orig.at<uchar>(i, j) - low) * mult;
        }
    }
}