#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void shuffleDFT(Mat &src);

Mat getFilter(Size size);

Mat HPF(Mat src);

int main() {
    Mat src = imread("/users/cocoblue/Q3.tif", IMREAD_GRAYSCALE);
    if (src.empty()) {
        cout << "Can't Open Image" << endl;
        return -1;
    }

    imshow("Orig", src);

    // 고주파 필터링
    Mat inverted = HPF(src);
    imshow("invert", inverted);

    // 이진화
    Mat threshold_image;
    threshold(inverted, threshold_image, 0.1, 255, THRESH_BINARY_INV);
    imshow("threshold_image", threshold_image);

    waitKey(0);
    return 0;
}

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
    Mat filter(size, CV_32FC2, Vec2f(1, 1));
    circle(filter, size / 2, 50, Vec2f(0, 0), -1);
    return filter;
}

Mat HPF(Mat src) {
    src.convertTo(src, CV_32FC1, 1.0 / 255.0);
    dft(src, src, DFT_COMPLEX_OUTPUT);
    shuffleDFT(src);

    Mat highpass = getFilter(src.size());

    multiply(src, highpass, src);
    shuffleDFT(src);
    idft(src, src, DFT_SCALE | DFT_REAL_OUTPUT);

    return src;
}