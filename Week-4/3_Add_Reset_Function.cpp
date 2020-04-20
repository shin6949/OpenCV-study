// Created 2020/04/10

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat image, roi, clone;
int mx1, my1, mx2, my2;
bool cropping = false;
bool showing = false;

void onMouse(int event, int x, int y, int flags, void *param);

void refresh();

int main() {
    image = imread("/users/cocoblue/test.JPG");
    if (image.empty()) {
        cout << "Cannot Read Image" << endl;
        return -1;
    }
    imshow("Image", image);
    clone = image.clone();

    setMouseCallback("Image", onMouse);

    while (1) {
        int key = waitKey(100);
        if (key == 'q') {
            break;
        } else if (key == 'c') {
            roi = clone(Rect(mx1, my1, mx2 - mx1, my2 - my1));
            imwrite("/users/cocoblue/Desktop/result.jpg", roi);
        }
    }
    return 0;
}

void onMouse(int event, int x, int y, int flags, void *param) {
    if (event == EVENT_LBUTTONDOWN) {
        mx1 = x;
        my1 = y;
        cropping = true;
        showing = false;
        refresh();

    } else if (event == EVENT_LBUTTONUP) {
        mx2 = x;
        my2 = y;
        cropping = false;
        showing = true;
        rectangle(image, Rect(mx1, my1, mx2 - mx1, my2 - my1), Scalar(0, 255, 0), 2);
        imshow("Image", image);
    }
}

// Restore to Original Picture
void refresh() {
    for (int row = 0; row < clone.rows; row++) {
        for (int col = 0; col < clone.cols; col++) {
            int blue = clone.at<Vec3b>(row, col)[0];
            int green = clone.at<Vec3b>(row, col)[1];
            int red = clone.at<Vec3b>(row, col)[2];

            image.at<Vec3b>(j, i)[0] = blue;
            image.at<Vec3b>(j, i)[1] = green;
            image.at<Vec3b>(j, i)[2] = red;
        }
    }
}
