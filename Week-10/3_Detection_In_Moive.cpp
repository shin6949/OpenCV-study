#include "opencv2/opencv.hpp"
#include "opencv2/core/ocl.hpp"
#include <iostream>

using namespace std;
using namespace cv;

// 영상을 -90도 하는 함수
Mat RotateFrame(Mat src);

int main() {
    Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));

    // 병렬 처리용 OpenCL 활성화
    ocl::setUseOpenCL(false);
    // 동영상 파일 읽기
    VideoCapture Video("/users/cocoblue/Downloads/IMG_2956.MOV");
    // 동영상 파일이 열렸는지 확인
    if (!Video.isOpened()) {
        cout << "Can Not Open The Video File" << endl;
        return -1;
    }

    // 실행 시간 측정용
    int64 start = getTickCount();

    // 영상의 첫번째 프레임은 배경이다. 배경을 정의하고 첫번째 프레임을 읽어와서 background 변수에 저장한다.
    Mat background;
    Video.read(background);

    // 영상을 -90도 회전하여 background에 저장 후 평활화.
    background = RotateFrame(background);

    // 평활화를 위해 GRAYSCALE로 변경
    cvtColor(background, background, COLOR_RGB2GRAY);
    equalizeHist(background, background);

    // 각각의 프레임이 저장될 변수
    Mat frame;

    // 2번째 프레임부터 끝까지 읽어옴.
    while (Video.read(frame)) {
        // 영상을 -90도 회전
        frame = RotateFrame(frame);
        imshow("Original", frame);

        // 컬러에서 그레이스케일로 변경
        cvtColor(frame, frame, COLOR_RGB2GRAY);

        // 평활화 해서 이진화가 제대로 되게 조절
        equalizeHist(frame, frame);

        // 배경을 제거
        absdiff(frame, background, frame);

        // 2진화 작업 진행
        threshold(frame, frame, 127, 255, THRESH_BINARY);

        // 형태학적 처리
        morphologyEx(frame, frame, MORPH_HITMISS, element);

        // 결과 표시
        imshow("Result", frame);

        // 각 프레임 당 딜레이 1ms 부여 -> 60프레임 영상 기준 프레임당 16ms지만 처리되는데로 표시하도록 1ms로 처리
        waitKey(1);
    }

    int64 end = getTickCount();
    float time = (end - start) / getTickFrequency();
    cout << "Processing Time : " << time << " sec. " << endl;
    return 0;
}

Mat RotateFrame(Mat src) {
    // 영상을 -90도 회전
    Mat matRotation = getRotationMatrix2D(Point(src.cols / 2, src.rows / 2), -90, 1);
    Mat matRotatedFrame;
    warpAffine(src, matRotatedFrame, matRotation, src.size());
    return matRotatedFrame;
}