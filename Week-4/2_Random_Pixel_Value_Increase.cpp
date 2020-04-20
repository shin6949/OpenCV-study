// Created 2020/04/11
// Increase Pixel Value Randomly Between -50 to 50 From The Original Pixel Value.

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    Mat image, new_img;
    image = imread("/users/cocoblue/test.JPG", IMREAD_COLOR);
    if (image.empty()) {
        cout << "Cannot Read Image" << endl;
        return -1;
    }
    new_img = image.clone();

    imshow("Before", image);

    /*
        According to OpenCV Online Documentation, cv::randu takes (InputOutputArray dst, InputArray low, InputArray high) as an argument.

        dst = cv::Scalar Value Of The Current Pixel
        low = The -50 cv::Scalar Value From The Current Pixel
        low = The +50 cv::Scalar Value From The Current Pixel
        It is possible to change the cv::Scalar value of each pixel as the problem means.

        cv::randu is fixed at 0 as the min value for 8-Bit even if a negative value is given as or high.
        Conversely, even if a value of 256 or more is given as low or high, the max value of 8-Bit is fixed at 255.
        That means InputArray given to low and high do not need to handle exceptions for min or max values.
    */

    for (int row = 0; row < new_img.rows; row++) {
        for (int col = 0; col < new_img.cols; col++) {
            // Get the Blue, Green, Red Value at the Current Pixel
            int blue = new_img.at<Vec3b>(row, col)[0];
            int green = new_img.at<Vec3b>(row, col)[1];
            int red = new_img.at<Vec3b>(row, col)[2];

            randu(new_img.at<Vec3b>(row, col), Scalar(blue - 50, green - 50, red - 50),
                  Scalar(blue + 50, green + 50, red + 50));
        }
    }

    // Showing Converted Image
    imshow("After", new_img);
    waitKey(0);
    return 0;
}
