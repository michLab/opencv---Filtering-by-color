#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/features2d.hpp>
#include <math.h>

using namespace std;
using namespace cv;

void on_trackbar(int, void*)
{
    cout << "Trackbar working" << endl;
}

int main()
{
    Mat image_rgb, image_hsv, mask, result;
    VideoCapture cap;

    /* Try to open the video: */
    if (!cap.open(0))
    {
        cout << "Cannot open the video stream!" << endl;
    }

    /* Define a color to find on image: */
    int lower_slider = 70;
    int upper_slider = 255;
    Scalar lower_limit(110,lower_slider,lower_slider);
    Scalar upper_limit(135,upper_slider,upper_slider);

    /* Create a trackbar: */
    namedWindow("Result");
    createTrackbar("lower_trackbar", "Result", &lower_slider, 255, on_trackbar);
    createTrackbar("upper_trackbar", "Result", &upper_slider, 255, on_trackbar);
    /* Loop for image processing: */
    while(true)
    {
        Mat mask, result;
        lower_limit = Scalar(110,lower_slider,lower_slider);
        upper_limit = Scalar(135,upper_slider,upper_slider);
        cap.read(image_rgb);
        cvtColor(image_rgb, image_hsv, COLOR_BGR2HSV);
        /* Using inRange to find values between lower and upper limit: */
        inRange(image_hsv, lower_limit, upper_limit, mask);
        /* Bitwise AND on frame and mask: */
        bitwise_and(image_rgb, image_rgb, result, mask);
        /* Display results: */
        imshow("Original", image_rgb);
        imshow("Mask", mask);
        imshow("Result", result);
        mask.release();
        result.release();
        int k = waitKey(1);
        if (k == 27)
        {
           break;
        }
    }
    return 0;
}
