/*
 * test.cpp
 *
 *  Created on: Feb 16, 2014
 *      Author: napolenli
 *  Just a test.
 */


#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "../slic_Pkg/Slic.hpp"

#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char **argv){

	//Mat image = imread("Extra_Resources/Images/Original/lights.jpg", 1);
    /* Load the image and convert to Lab colour space. */
    IplImage *image = cvLoadImage("Extra_Resources/Images/Original/lena.jpg", 1);
    IplImage *lab_image = cvCloneImage(image);
    cvCvtColor(image, lab_image, CV_BGR2Lab);

    /* Yield the number of superpixels and weight-factors from the user. */
    int w = image->width, h = image->height;
    int nr_superpixels = 100;
    int nc = 40;

    double step = sqrt((w * h) / (double) nr_superpixels);

    /* Perform the SLIC superpixel algorithm. */
    Slic *slic = new Slic();
    slic->generate_superpixels(lab_image, step, nc);
    slic->create_connectivity(lab_image);

    slic->saveWeightedPoints();
    /* Display the contours and show the result. */
    /*
    slic->display_contours(image, CV_RGB(255,0,0));
    cvShowImage("result", image);
    cvWaitKey(0);
    cvSaveImage(argv[4], image);
    */
    delete slic;
	return 0;
}
