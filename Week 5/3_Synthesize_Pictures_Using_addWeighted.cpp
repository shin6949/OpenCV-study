// Created on 2020/04/13

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void on_trackbar(int, void *);

// A struct that contains Two of Image
struct mat_family {
    Mat first, second;
};

int main() {
    mat_family imgs;

    imgs.first = imread("/users/cocoblue/test.JPG", IMREAD_COLOR);
    if (imgs.first.empty()) {
        cout << "Cannot Read First Image" << endl;
        return -1;
    }

    imgs.second = imread("/users/cocoblue/test2.JPG", IMREAD_COLOR);
    if (imgs.second.empty()) {
        cout << "Cannot Read Second Image" << endl;
        return -1;
    }

    // Alpha Variable
    int alpha = 0;

    namedWindow("Image", 1);
    /*
        Add TrackBar
        According to OpenCV Online Documentation,
        "createTrackbar" takes (const String& trackbarname, const String& winname, int* value, int count, TrackbarCallback onChange, void* userdata) as arguments.

        trackbarname = The name to be displayed on the Trackbar
        winname = The name of the window to display the Trackbar
        value = (int) Variable name to be reflected when changing via the Trackbar
        count = (int) Max value that can be changed via the Trackbar
        onChange = (Optional) Event function name to be executed when the value of the Trackbar value is changed
        userdata = (Optional) Extradata

        if the memory address of the structure variable defined in main is cast to void *, the Trackbar event can be handled without using the global variable.
     */

    createTrackbar("Alpha Value", "Image", &alpha, 10, on_trackbar, (void *) &imgs);
    Mat out;
    // Since the default value of the track bar is 0, when the alpha value is 0, only the second image appears, so only the second image is exported. (Minimize unnecessary computation)
    imshow("Image", imgs.second);

    waitKey(0);
    return 1;
}

// TrackBar Event
void on_trackbar(int alpha, void *received) {
    Mat out;
    //mSince we can't do anything with void *. so, cast it back into a structure.
    mat_family *imgs = (mat_family *) received;

    /*
        In the Trackbar event, we only receive an int, so we receive it as an int and cast it as a double. Then divide by 10 to convert it to a decimal point.
        * When dividing without casting, there was a problem that the decimal point was cut off.
    */
    double real_alpha = (double) alpha / 10;

    // Synthesize Pictures
    addWeighted(imgs->first, real_alpha, imgs->second, 1 - real_alpha, 0.0, out);

    // Refresh the Image
    imshow("Image", out);
}
