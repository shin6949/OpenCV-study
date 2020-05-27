#include "opencv2/opencv.hpp"
#include "opencv2/core/ocl.hpp"
#include <iostream>

using namespace std;
using namespace cv;


int main() {
    // 병렬 처리용 OpenCL 활성화
    ocl::setUseOpenCL(true);

    // 동영상 파일 읽기
    VideoCapture cap("/users/cocoblue/Downloads/IMG_2956.MOV");

    // 동영상 파일이 열렸는지 확인
    if (!cap.isOpened()) {
        cout << "Cannot open the video file" << endl;
        return -1;
    }

    // 실행 시간 측정용
    static int64 start, end;
    static float time;

    start = getTickCount();
    /* 프레임당 표시될 ms 구하기
     * 1s = 1000ms 이므로 비디오의 FPS(Frame Per Second)를 구하고 난 뒤,
     * 1000 / FPS를 하면, 한 프레임당 배정되는 ms를 구할 수 있다.
     * 한 프레임이 표시될 때 1000 / FPS 만큼 표시하게 설정하면 된다.
     */
    int ms = 1000 / (int) cap.get(CAP_PROP_FPS); // 60FPS 기준 16~17

    while (true) {
        UMat matOriginalFrame;
        if (!cap.read(matOriginalFrame)) {
            break;
        }

        Mat matRotation = getRotationMatrix2D(Point(matOriginalFrame.cols / 2, matOriginalFrame.rows / 2), -90, 1);
        UMat umatRotation = matRotation.getUMat(ACCESS_READ);

        UMat matRotatedFrame;
        warpAffine(matOriginalFrame, matRotatedFrame, umatRotation, matOriginalFrame.size());

    }

    // 동영상 파일 읽기
    VideoCapture cap2("/users/cocoblue/Downloads/IMG_2956.MOV");

    // 동영상 파일이 열렸는지 확인
    if (!cap2.isOpened()) {
        cout << "Cannot open the video file" << endl;
        return -1;
    }

    end = getTickCount();
    time = (end - start) / getTickFrequency();
    cout << "Enabled --- Done. Processing Time : " << time << " sec. " << endl;

    ocl::setUseOpenCL(false);
    start = getTickCount();
    while (true) {
        Mat matOriginalFrame;
        if (!cap2.read(matOriginalFrame)) {
            break;
        }

        Mat matRotation = getRotationMatrix2D(Point(matOriginalFrame.cols / 2, matOriginalFrame.rows / 2), -90, 1);

        Mat matRotatedFrame;
        warpAffine(matOriginalFrame, matRotatedFrame, matRotation, matOriginalFrame.size());


        imshow("Movie", matOriginalFrame);
    }
    end = getTickCount();
    time = (end - start) / getTickFrequency();
    cout << "Disabled --- Done. Processing Time : " << time << " sec. " << endl;

    return 0;
}