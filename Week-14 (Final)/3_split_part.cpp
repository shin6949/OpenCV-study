#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    Mat image = imread("/users/cocoblue/Fig1.tif", IMREAD_GRAYSCALE);
    if (image.empty()) {
        cout << "Can't Open Image!" << endl;
        return -1;
    }
    imshow("Original", image);

    // 세포 분할
    Mat cell;
    threshold(image, cell, 44, 255, THRESH_BINARY);

    // 핵 분할
    Mat cell_nucleus;
    threshold(image, cell_nucleus, 124, 255, THRESH_BINARY);

    Mat background;
    // 임계 값의 결과에 반대로 해야 배경이 1이 됨.
    threshold(image, background, 44, 255, THRESH_BINARY_INV);

    // 각 영역에 색을 주기 위해 GRAYSCALE 에서 COLOR로 변경
    cvtColor(cell, cell, COLOR_GRAY2BGR);
    cvtColor(cell_nucleus, cell_nucleus, COLOR_GRAY2BGR);
    cvtColor(background, background, COLOR_GRAY2BGR);

    cell -= Scalar(255, 0, 0);
    cell_nucleus -= Scalar(0, 0, 255);
    background -= Scalar(0, 255, 0);

    // 합성
    Mat colored = background.clone();
    bitwise_or(colored, cell_nucleus, colored);
    bitwise_or(colored, cell, colored);

    // 결과 표시
    imshow("colored", colored);
    waitKey(0);
    return 0;
}