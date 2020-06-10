// Created on 2020/05/28.
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

// 색을 해치지 않고 스트레칭
int main() {
    // 사진 읽기
    Mat image = imread("/users/cocoblue/IMG_3855.JPG", IMREAD_COLOR);

    // 사진이 열렸는지 확인
    if (image.empty()) {
        cout << "Can Not Open The Picture File" << endl;
        return -1;
    }

    CascadeClassifier face;
    if (!face.load("/usr/local/Cellar/opencv/4.2.0_3/share/opencv4/haarcascades/haarcascade_frontalface_default.xml")) {
        cout << "Can Not Open The Cascade File" << endl;
        return -1;
    }

    vector<Rect> face_pos;
    face.detectMultiScale(image, face_pos, 1.1, 3, 0 | CASCADE_SCALE_IMAGE, Size(10, 10));

    for (int i = 0; i < (int) face_pos.size(); i++) {
        rectangle(image, face_pos[i], Scalar(0, 255, 0), 2);
    }

    imshow("Result", image);
    waitKey(0);
    return 0;
}


