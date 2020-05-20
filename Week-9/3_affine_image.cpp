// Created on 2020/05/13.

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

struct Tri {
    Point2f srcTri[3] = {Point2f(0, 0),};
    Point2f dstTri[3] = {Point2f(0, 0),};
} tri_array;

void onMouse(int event, int x, int y, int flags, void *param);

void input_data(int x, int y, bool is_lclick);

void judge_data();

void show_result();


Mat image;

int main() {
    image = imread("/users/cocoblue/test.JPG", IMREAD_COLOR);
    if (image.empty()) {
        cout << "Cannot Read Image" << endl;
        return -1;
    }
    imshow("Image", image);
    setMouseCallback("Image", onMouse);

    waitKey(0);
    return 1;
}

void onMouse(int event, int x, int y, int flags, void *param) {
    if (event == EVENT_LBUTTONDOWN) {
        input_data(x, y, true);
        judge_data();
    } else if (event == EVENT_RBUTTONDOWN) {
        input_data(x, y, false);
        judge_data();
    }
}

void input_data(int x, int y, bool is_lclick) {
    if (is_lclick) {
        for (int i = 0; i < 3; i++) {
            if (tri_array.srcTri[i] == Point2f(0, 0)) {
                tri_array.srcTri[i] = Point2f(x, y);
                break;
            }
        }
    } else {
        for (int i = 0; i < 3; i++) {
            if (tri_array.dstTri[i] == Point2f(0, 0)) {
                tri_array.dstTri[i] = Point2f(x, y);
                break;
            }
        }
    }
}

void judge_data() {
    bool data_stat = true;
    for (int i = 0; i < 3; i++) {
        if (tri_array.srcTri[i] == Point2f(0, 0)) {
            data_stat = false;
            break;
        }

        if (tri_array.dstTri[i] == Point2f(0, 0)) {
            data_stat = false;
            break;
        }
    }
    if (data_stat) { show_result(); }
}

void show_result() {
    Mat warp_mat = getAffineTransform(tri_array.srcTri, tri_array.dstTri);
    Mat warp_dst = Mat::zeros(image.rows, image.cols, image.type());
    warpAffine(image, warp_dst, warp_mat, warp_dst.size());

    imshow("dst", warp_dst);
}