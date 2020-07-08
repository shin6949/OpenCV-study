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

Mat getFilter_horizon(Size size) {
    Mat tmp = Mat(size, CV_32F);

    for (int i = 0; i < tmp.rows; i++) {
        for (int j = 0; j < tmp.cols; j++) {
            if (j > (tmp.cols / 2 - 10) && j < (tmp.cols / 2 + 10) && i > (tmp.rows / 2 + 10)) {
                tmp.at<float>(i, j) = 0;
            } else if (j > (tmp.cols / 2 - 10) && j < (tmp.cols / 2 + 10) && i < (tmp.rows / 2 - 10)) {
                tmp.at<float>(i, j) = 0;
            } else {
                tmp.at<float>(i, j) = 1;
            }
        }
    }

    Mat toMerge[] = {tmp, tmp};
    Mat filter;
    merge(toMerge, 2, filter);

    return filter;
}

Mat getFilter_vertical(Size size) {
    Mat tmp = Mat(size, CV_32F);
    for (int i = 0; i < tmp.rows; i++) {
        for (int j = 0; j < tmp.cols; j++) {
            if (j > (tmp.cols / 2 - 10) && j < (tmp.cols / 2 + 10)
                && i > (tmp.rows / 2 + 10)) {
                tmp.at<float>(i, j) = 1;
            } else if (j > (tmp.cols / 2 - 10) && j < (tmp.cols / 2 + 10) &&
                       i < (tmp.rows / 2 - 10)) {
                tmp.at<float>(i, j) = 1;
            } else {
                tmp.at<float>(i, j) = 0;
            }
        }
    }

    Mat toMerge[] = {tmp, tmp};
    Mat filter;
    merge(toMerge, 2, filter);
    return filter;
}

Mat show_DFT(Mat &source) {
    Mat src_float;
    source.convertTo(src_float, CV_32FC1, 1.0 / 255.0);

    Mat dft_image;
    dft(src_float, dft_image, DFT_COMPLEX_OUTPUT);
    shuffleDFT(dft_image);
    threshold(dft_image, dft_image, 127, 255, THRESH_BINARY);

    Mat image_array[2] = {Mat::zeros(dft_image.size(), CV_32F), Mat::zeros(dft_image.size(), CV_32F)};
    split(dft_image, image_array);
    Mat mag_image;

    magnitude(image_array[0], image_array[1], mag_image);

    mag_image += Scalar::all(1);
    log(mag_image, mag_image);

    normalize(mag_image, mag_image, 0, 1, NORM_MINMAX);
    return mag_image;
}

Mat del_horizon_Pattern(Mat &src) {
    src.convertTo(src, CV_32FC1, 1.0 / 255.0);
    dft(src, src, DFT_COMPLEX_OUTPUT);
    shuffleDFT(src);

    Mat lowpass = getFilter_horizon(src.size());

    Mat result;

    // 필터와 DFT 영상을 서로 곱한다.
    multiply(src, lowpass, result);

    Mat inverted_image;
    shuffleDFT(result);
    idft(result, inverted_image, DFT_SCALE | DFT_REAL_OUTPUT);
    return inverted_image;
}

Mat del_vertical_Pattern(Mat &src) {
    src.convertTo(src, CV_32FC1, 1.0 / 255.0);
    dft(src, src, DFT_COMPLEX_OUTPUT);
    shuffleDFT(src);

    Mat lowpass = getFilter_vertical(src.size());
    Mat result;
    multiply(src, lowpass, result);

    Mat inverted_image;
    shuffleDFT(result);

    idft(result, inverted_image, DFT_SCALE | DFT_REAL_OUTPUT);
    return inverted_image;
}

int main() {
    Mat image = imread("/users/cocoblue/Q2.tif", IMREAD_GRAYSCALE);
    if (image.empty()) {
        cout << "Can't Read Image" << endl;
        return -1;
    }
    Mat vert_img = image.clone();

    imshow("Orig", image);
    imshow("DFT", show_DFT(image));
    imshow("horizon", del_horizon_Pattern(image));
    imshow("vertical", del_vertical_Pattern(vert_img));

    waitKey(0);
    return 0;
}