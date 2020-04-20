// Created on 2020/04/20.

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat image = imread("/users/cocoblue/test.JPG", IMREAD_COLOR);
    if (image.empty()) {
        cout << "Cannot Read Image" << endl;
        return -1;
    }

    vector<Mat> bgr_planes;
    split(image, bgr_planes);
    int histSize = 256;
    float range[] = {0, 256};
    const float *histRange = {range};
    bool uniform = true, accumulate = false;
    Mat b_hist, g_hist, r_hist;

    calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double) hist_w / histSize);
    Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

    normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

    for (int i = 0; i < 255; i++) {
        line(histImage, Point(bin_w * (i), hist_h), Point(bin_w * (i), hist_h - b_hist.at<float>(i)),
             Scalar(255, 0, 0));
        line(histImage, Point(bin_w * (i), hist_h), Point(bin_w * (i), hist_h - g_hist.at<float>(i)),
             Scalar(0, 255, 0));
        line(histImage, Point(bin_w * (i), hist_h), Point(bin_w * (i), hist_h - r_hist.at<float>(i)),
             Scalar(0, 0, 255));
    }

    imshow("Input Image", image);
    imshow("Color Histogram", histImage);
    waitKey(0);
    return 0;
}