// Created 2020/03/30

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat img;
int red, green, blue, bold;
int drawing = false;

void on_trackbar(int, void *);

void drawCircle(int event, int x, int y, int, void *param);

int main() {
    image = imread("/users/cocoblue/test.JPG");
    if (image.empty()) {
        cout << "Cannot Read Image" << endl;
        return -1;
    }

    // Make Window before define TrackBar
    namedWindow("Image", 1);

    // Set the MouseCallBack
    setMouseCallback("Image, drawCircle);
    // Make 3-TrackBar what control RGB Value When Drawing Circle By Mouse
    createTrackbar("R", "Image", &red, 255, on_trackbar);
    createTrackbar("G", "Image", &green, 255, on_trackbar);
    createTrackbar("B", "Image", &blue, 255, on_trackbar);
    createTrackbar("Bold", "Image", &bold, 255, on_trackbar);

    // Showing Image.
    imshow("Image", img);
    waitKey(0);
    return 0;
}

void on_trackbar(int, void *) {}

// MouseCallBack Function
void drawCircle(int event, int x, int y, int, void *param) {
    if (event == EVENT_LBUTTONDOWN) { drawing = true; }
    else if (event == EVENT_MOUSEMOVE) {
        if (drawing == true) {
            circle(img, Point(x, y), 3, Scalar(blue, green, red), bold);
        }
    } else if (event == EVENT_LBUTTONUP) { drawing = false; }

    // Refresh Image
    imshow("img", img);
}
