#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string.h>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    VideoCapture cap(0);
    Mat img_orig, img_HSV, img_threshold;
    if(!cap.isOpened())
    {
        cerr << "Cannot open the source" << endl;
        return -1;
    }

    namedWindow("Control Window", CV_WINDOW_AUTOSIZE);

    int min_hue = 0;
    int max_hue = 179;

    int min_sat = 0;
    int max_sat = 255;

    int min_vib = 0;
    int max_vib = 255;

    cvCreateTrackbar("Hue Min", "Control Window", &min_hue, 179);
    cvCreateTrackbar("Hue Max", "Control Window", &max_hue, 179);

    cvCreateTrackbar("Min Sat", "Control Window", &min_sat, 255);
    cvCreateTrackbar("Max Sat", "Control Window", &max_sat, 255);

    cvCreateTrackbar("Min Vib", "Control Window", &min_vib, 255);
    cvCreateTrackbar("Max Vib", "Control Window", &max_vib, 255);

    while(true)
    {
        bool sucess = cap.read(img_orig);
        if(!sucess)
        {
            cerr << "Cannot read a frame from video stream" << endl;
            break;
        }

        cvtColor(img_orig, img_HSV, COLOR_BGR2HSV);

        inRange(img_HSV, Scalar(min_hue, min_sat,min_vib), Scalar(max_hue, max_sat, max_vib), img_threshold);

        erode(img_threshold, img_threshold, getStructuringElement(MORPH_ELLIPSE, Size(5,5)) );
        dilate(img_threshold, img_threshold, getStructuringElement(MORPH_ELLIPSE, Size(5,5)) );

        dilate(img_threshold, img_threshold, getStructuringElement(MORPH_ELLIPSE, Size(5,5)) );
        erode(img_threshold, img_threshold, getStructuringElement(MORPH_ELLIPSE, Size(5,5)) );

        imshow("Thresholded Image", img_threshold);
        imshow("HSV", img_HSV);
        imshow("Original", img_orig);

        if(waitKey(30) == 27)
            break;
    }

    return 0;
}
