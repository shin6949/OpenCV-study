// Created 2020/04/10

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
    // Configure Convert Image Variable
    Mat converted = image.clone();

    for (int j = 0; j < image.rows; j++) {
        for (int i = 0; i < image.cols; i++) {
            // Get The Red Value at Current Pixel
            int red = image.at<Vec3b>(j, i)[2];

            // Fix Value When Over 255
            if (red + 100 > 255) { red = 255; }
            else { red += 100; }

            // Change Red Value
            converted.at<Vec3b>(j, i)[2] = red;
        }
    }

    // Write Converted Image
    imwrite("/users/cocoblue/Desktop/red_inc.jpg", converted);
    cout << "Convert Finished" << endl;
    return 0;
}
