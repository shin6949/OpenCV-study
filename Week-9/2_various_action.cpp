// Created on 2020/05/13.

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void on_trackbar(int value, void *param);

void onMouse(int event, int x, int y, int flags, void *param);

void Parallel_movement(Mat source);

void change_size(int value, void *param);

void rotate_image(int value, void *param);

int action_num = 0, xscale = 0, yscale = 0;

int main() {
    Mat image = imread("/users/cocoblue/test.JPG", IMREAD_COLOR);
    if (image.empty()) {
        cout << "Cannot Read Image" << endl;
        return -1;
    }

    namedWindow("Image");
    createTrackbar("Action Select", "Image", &action_num, 2, on_trackbar, (void *) &image);
    imshow("Image", image);
    setMouseCallback("Image", onMouse, &image);

    waitKey(0);
    return 1;
}

void on_trackbar(int value, void *param) {
    Mat *received = (Mat *) param;
    switch (value) {
        case 0:
            destroyWindow("Image");
            namedWindow("Image");
            createTrackbar("Action Select", "Image", &action_num, 2, on_trackbar, param);
            setMouseCallback("Image", onMouse, param);
            imshow("Image", *received);
            break;
        case 1:
            destroyWindow("Image");
            namedWindow("Image");
            createTrackbar("Action Select", "Image", &action_num, 2, on_trackbar, param);
            createTrackbar("x Scale", "Image", &xscale, 10, change_size, param);
            createTrackbar("y Scale", "Image", &yscale, 10, change_size, param);
            setMouseCallback("Image", onMouse, param);
            imshow("Image", *received);
            break;
        case 2:
            destroyWindow("Image");
            namedWindow("Image");
            createTrackbar("Action Select", "Image", &action_num, 2, on_trackbar, param);
            createTrackbar("angle", "Image", &xscale, 360, rotate_image, param);
            setMouseCallback("Image", onMouse, param);
            imshow("Image", *received);
            break;
    }
}

void onMouse(int event, int x, int y, int flags, void *param) {
    Mat *received = (Mat *) param;
    if (event == EVENT_LBUTTONDOWN) {
        if (action_num == 0) {
            Parallel_movement(*received);
        }
    } else if (event == EVENT_RBUTTONDOWN) {
        imshow("Image", *received);
    }
}

void Parallel_movement(Mat source) {
    int x = 0, y = 0;
    cout << "x, y 값 입력" << endl;
    cin >> x;
    cin >> y;

    Mat dst = Mat();
    Mat tmat = (Mat_<double>(2, 3) << 1, 0, x, 0, 1, y);

    warpAffine(source, dst, tmat, source.size());
    imshow("Image", dst);
}

void change_size(int value, void *param) {
    Mat *received = (Mat *) param;
    Mat dst = Mat();
    resize(*received, dst, Size(), xscale + 1, yscale + 1);
    imshow("Image", dst);
}

void rotate_image(int value, void *param) {
    Mat *source = (Mat *) param;

    Mat dst = Mat();
    Size dsize = Size(source->cols, source->rows);
    Point center = Point(source->cols / 2.0, source->rows / 2.0);
    Mat M = getRotationMatrix2D(center, value, 1.0);
    warpAffine(*source, dst, M, dsize, INTER_LINEAR);
    imshow("Image", dst);
}