/*
 * test.cpp
 *
 *  Created on: Feb 16, 2014
 *      Author: napolenli
 */


#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "../segment_Pkg/Slic.hpp"

#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char **argv){

	Mat image = imread("Extra_Resources/Images/Original/testImage.jpg", 1);
	Slic *sol = new Slic(image);

	sol->cluster(10);

	delete sol;
	return 0;
}
