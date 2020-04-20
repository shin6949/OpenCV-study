// Created on 2020/04/13.

/* LookUpTable f(x) = y
    From 0 to 99: y = x Graph.
    From 100 to 192: 0 = x Graph.
    From 193 to 255: y = x Graph.
*/
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int *configure_lookup_table(int x[], int len);

int main() {

    // Configure Lookup Table that matches the graph.
    int table[256] = {0,};

    // Execute a function that puts data in the table that fits the graph presented in the problem
    configure_lookup_table(table, sizeof(table) / sizeof(int));

    Mat image = imread("/users/cocoblue/test.JPG", IMREAD_COLOR);
    if (image.empty()) {
        cout << "Cannot Read Image" << endl;
        return -1;
    }

    imshow("BEFORE", image);

    for (int row = 0; j < image.rows; row++) {
        for (int col = 0; i < image.cols; col++) {
            // Based on the input color information, It finds it in the table and changes the value.
            image.at<Vec3b>(row, col)[0] = table[image.at<Vec3b>(row, col)[0]];
            image.at<Vec3b>(row, col)[1] = table[image.at<Vec3b>(row, col)[1]];
            image.at<Vec3b>(row, col)[2] = table[image.at<Vec3b>(row, col)[2]];
        }
    }

    cout << "Convert Finished" << endl;
    imshow("AFTER", image);
    waitKey(0);

    return 0;
}

/*  A Function to put data in a table
    Construct this Function with a pointer to return an array.
 */

int *configure_lookup_table(int x[], int len) {
    for (int i = 0; i < len; i++) {
        if (i >= 100 && i <= 192) { x[i] = 0; }
        else { x[i] = i; }
    }

    return x;
}