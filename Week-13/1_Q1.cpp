#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void shuffleDFT(Mat &src) {
    int cX = src.cols / 2;
    int cY = src.rows / 2;

    Mat q1(src, Rect(0, 0, cX, cY));
    Mat q2(src, Rect(cX, 0, cX, cY));
    Mat q3(src, Rect(0, cY, cX, cY));
    Mat q4(src, Rect(cX, cY, cX, cY));

    Mat tmp;
    q1.copyTo(tmp);
    q4.copyTo(q1);
    tmp.copyTo(q4);
    q2.copyTo(tmp);
    q3.copyTo(q2);
    tmp.copyTo(q3);
}

Mat getFilter(Size size) {
    Mat filter = Mat::ones(size, CV_32FC2);
    circle(filter, size / 2, 40, Vec2f(0, 0), -1);
    return filter;
}

Mat HPF(Mat src) {
    src.convertTo(src, CV_32FC1, 1.0 / 255.0);
    dft(src, src, DFT_COMPLEX_OUTPUT);
    shuffleDFT(src);

    Mat highpass = getFilter(src.size());
    Mat result;

    multiply(src, highpass, result);

    Mat inverted_image;
    shuffleDFT(result);
    idft(result, inverted_image, DFT_SCALE | DFT_REAL_OUTPUT);
    return inverted_image;
}

Mat Sharpening(Mat src) {
    // 그레이스케일 영상을 실수 영상으로 변환한다.
    src.convertTo(src, CV_32FC1, 1.0 / 255.0);
    Mat dft_image;
    dft(src, dft_image, DFT_COMPLEX_OUTPUT);
    shuffleDFT(dft_image);
    Mat highpass = getFilter(dft_image.size());

    Mat result;
    // 원형 필터와 DFT 영상을 서로 곱한다. 역퓨리에 변환
    multiply(dft_image, 0.5 + 0.75 * highpass, result);
    Mat inverted_image;
    shuffleDFT(result);
    idft(result, inverted_image, DFT_SCALE | DFT_REAL_OUTPUT);
    return inverted_image;
}

Mat equalize(Mat &src) {
    src.convertTo(src, CV_8UC1, 255);
    equalizeHist(src, src);
    return src;
}

int main() {
    Mat image = imread("/users/cocoblue/Q1.tif", IMREAD_GRAYSCALE);
    imshow("Orig", image);

    if (image.empty()) {
        cout << "Can't Read Image" << endl;
        return -1;
    }

    // 고역통과 필터링
    Mat result = HPF(image);
    imshow("HPF", result);

    // 평활화
    result = equalize(result);
    imshow("Equlized", result);

    // 강조
    result = Sharpening(image);
    imshow("Sharpening", result);

    waitKey(0);
    return 0;
}