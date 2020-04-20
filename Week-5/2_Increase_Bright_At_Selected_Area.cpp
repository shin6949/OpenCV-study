// Created on 2020/04/13.

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// A struct that contains current status.
struct now_status {
    Mat original;
    Mat img;
    int mx1, my1, mx2, my2;
    bool cropping = false;
    bool showing = false;
} now;

void onMouse(int event, int x, int y, int flags, void *param);

void refresh();


int main() {
    now.img = imread("/users/cocoblue/test.JPG");
    if (now.img.empty()) {
        cout << "Cannot Read Image" << endl;
        return -1;
    }
    imshow("image", now.img);

    now.original = now.img.clone();
    setMouseCallback("image", onMouse);
    waitKey(0);
    return 0;
}

void onMouse(int event, int x, int y, int flags, void *param) {
    if (event == EVENT_LBUTTONDOWN) {
        now.mx1 = x;
        now.my1 = y;
        now.cropping = true;
        now.showing = false;
        refresh();
        imshow("image", now.img);
    } else if (event == EVENT_LBUTTONUP) {
        now.mx2 = x;
        now.my2 = y;
        now.cropping = false;
        now.showing = true;

        now.img(Rect(now.mx1, now.my1, now.mx2 - now.mx1, now.my2 - now.my1)) *= 2;
        imshow("image", now.img);
    }
}

void refresh() {
    for (int row = 0; row < now.original.rows; row++) {
        for (int col = 0; i < now.original.cols; col++) {
            int blue = now.original.at<Vec3b>(row, col)[0];
            int green = now.original.at<Vec3b>(row, col)[1];
            int red = now.original.at<Vec3b>(row, col)[2];

            now.img.at<Vec3b>(row, col)[0] = blue;
            now.img.at<Vec3b>(row, col)[1] = green;
            now.img.at<Vec3b>(row, col)[2] = red;

        }
    }
}
