// Created 2020/03/30

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

// MouseCallBack Function
void onMouse(int event, int x, int y, int flags, void *param) {
    // The Event When Click Mouse Left Button
    if (event == EVENT_LBUTTONDOWN) {
        Mat &img = *(Mat *) (param);
        // Make Rectangle at The Click Point
        rectangle(img, Point(x, y), Point(x + 200, y + 300), Scalar(0, 0, 255), 5);
        // Refresh Image
        imshow("Image", img);
    }
    // The Event When Click Mouse Right Button
    else if (event == EVENT_RBUTTONDOWN) {
        Mat &img = *(Mat *) (param);
        // Make Rectangle at The Click Point
        circle(img, Point(x, y), 150, Scalar(255, 0, 0), 5);
        // Refresh Image
        imshow("Image", img);
    }
}

int main() {
    // Create Image filled by Black
    Mat image = Mat(800, 600, CV_8UC3, Scalar(0, 0, 0));
    if (image.empty()) {
        cout << "Cannot Read Image" << endl;
        return -1;
    }
    // Showing image(Mat)
    imshow("Image", image);

    // Set the MouseCallBack
    setMouseCallback("Image", onMouse, &image);

    // Waiting for Press Key
    waitKey(0);
    return 0;
}
