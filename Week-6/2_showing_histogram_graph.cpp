// Created on 2020/04/20.

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void drawHist(int histogram[]);

int main() {
    Mat image = imread("/users/cocoblue/test.JPG", IMREAD_GRAYSCALE);
    if (image.empty()) {
        cout << "Cannot Read Image" << endl;
        return -1;
    }

    imshow("Input Image", image);
    int histogram[256] = {0};

    for (int y = 0; y < image.rows; y++) {
        for (int x = 0; x < image.cols; x++) {
            histogram[(int) image.at<uchar>(y, x)]++;
        }
    }

    drawHist(histogram);
    waitKey(0);
    return 0;
}

void drawHist(int histogram[]) {
    int hist_w = 512;
    int hist_h = 400;
    int bin_w = cvRound((double) hist_w / 256);

    Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));

    int max = histogram[0];
    for (int i = 1; i < 256; i++) {
        if (max < histogram[i]) {
            max = histogram[i];
        }
    }

    for (int i = 0; i < 255; i++) {
        histogram[i] = floor(((double) histogram[i] / max) * histImage.rows);
    }

    for (int i = 0; i < 255; i++) {
        line(histImage, Point(bin_w * (i), hist_h), Point(bin_w * (i), hist_h - histogram[i]), Scalar(0, 0, 255));
    }

    imshow("Histogram", histImage);
}