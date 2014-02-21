/*
 * Slic.hpp
 *
 *  Description: This class performs SLIC algorithm for super-pixel segmentation.
 *  Created on: Feb 19, 2014
 *      Author: napolenli
 */


#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <tr1/unordered_map>

using namespace cv;
using namespace std;

struct LabPointInfo{
	double lVal;
	double aVal;
	double bVal;
	int label;
	double distance;
	LabPointInfo(double l, double a, double b) : lVal(l), aVal(a), bVal(b) {}
};

class Slic{
	int rowNum, colNum;
	Mat image, labImage, grayImage;
	tr1::unordered_map<int, tr1::unordered_map<int, LabPointInfo *> > labImageMatrix;

public:
	Slic(Mat &image){
		this->image = image;
		rowNum = image.rows;
		colNum = image.cols;
		cvtColor(this->image, this->labImage, CV_BGR2Lab);
		cvtColor(this->image, this->grayImage, CV_BGR2GRAY);
		readLabImage();
	}

	~Slic(){
		for(int i = 0; i < rowNum; i++){
			for(int j = 0; j < colNum; j++){
				delete this->labImageMatrix[i][j];
			}
		}
	}

	void cluster(int k){
		cout << this->rowNum << ", " << this->colNum << endl;
		int rowSeg = 1, colSeg = 1;
		if(isPrime(k))
			(this->rowNum > this->colNum) ? (rowSeg = k) : (colSeg = k);
		else
			decomNum(k, rowSeg, colSeg);

		double rowPos = this->rowNum / rowSeg / 2;
		for(int i = 0; i < rowSeg; i++){
			double colPos = this->colNum / colSeg / 2;
			for(int j = 0; j < colSeg; j++){
				int coorVal[] = {rowPos, colPos};
				adjustCenter(coorVal);
				markCenter(coorVal);
				colPos += this->colNum / colSeg;
			}
			rowPos += this->rowNum / rowSeg;
		}
		cout << rowSeg * colSeg << endl;

		namedWindow("Lena", CV_WINDOW_AUTOSIZE);
		imshow("Lena", image);
		waitKey(0);
		destroyWindow("Lena");
	}

private:
	void readLabImage(){
		for(int i = 0; i < rowNum; i++){
			tr1::unordered_map<int, LabPointInfo *> newMap;
			for(int j = 0; j < colNum; j++){
				double labVal[] = {this->labImage.at<Vec3b>(i, j)[0] * 100.0 / 255.0,
						this->labImage.at<Vec3b>(i, j)[1] - 128,
						this->labImage.at<Vec3b>(i, j)[2] - 128};
				LabPointInfo *labPointInfo = new LabPointInfo(labVal[0], labVal[1], labVal[2]);
				labPointInfo->label = -1;
				labPointInfo->distance = DBL_MAX;
				newMap.insert(pair<int, LabPointInfo *>(j, labPointInfo));
			}
			this->labImageMatrix.insert(pair<int, tr1::unordered_map<int, LabPointInfo *> >(i, newMap));
		}
	}

	bool isPrime(int number){

		if(number <= 1 || (!(number % 2) && number != 2)){
			return false;
		}else{
			int limit = sqrt(number) + 1;
			for(int i = 3; i <= limit; i += 2){
				if(!(number % i))
					return false;
			}
		}

		return true;
	}

	void decomNum(int number, int &rowSeg, int &colSeg){
		int iniVal = sqrt(number) + 1;
		while(true){
			if(iniVal * (int)(number / iniVal) == number){
				break;
			}else{
				iniVal--;
			}
		}
		if(iniVal < number / iniVal)
			iniVal = number / iniVal;
		if(this->rowNum > this->colNum)
			rowSeg = iniVal, colSeg = number / iniVal;
		else
			colSeg = iniVal, rowSeg = number / iniVal;
	}

	void adjustCenter(int coorVal[]){
		int newCoorVal[] = {coorVal[0]- 1, coorVal[1] - 1};
		int diff = 0, markPos[] = {newCoorVal[0], newCoorVal[1]};
		for(int i = 0; i < 3; i++){
			newCoorVal[0] += i;
			newCoorVal[1] = coorVal[1] - 1;
			for(int j = 0; j < 3; j++){
				newCoorVal[1] += j;
				if((int)grayImage.at<uchar>(newCoorVal[0], newCoorVal[1])
						- (int)grayImage.at<uchar>(coorVal[0], coorVal[1]) > diff){
					diff = ((int)grayImage.at<uchar>(newCoorVal[0], newCoorVal[1])
							- (int)grayImage.at<uchar>(coorVal[0], coorVal[1]));
					markPos[0] = newCoorVal[0];
					markPos[1] = newCoorVal[1];
				}
			}
		}
		if(coorVal[0] == markPos[0] || coorVal[1] == markPos[1])
			cout << "Unchanged" << endl;
		else
			cout << "Changed" << endl;
		coorVal[0] = markPos[0];
		coorVal[1] = markPos[1];
	}

	// Auxiliary functions.
	void markCenter(int coorVal[]){
		coorVal[0] -= 2;
		coorVal[1] -= 2;
		for(int i = 0; i < 4; i++){
			for(int j = 0; j < 4; j++){
				this->image.at<Vec3b>(coorVal[0] + i, coorVal[1] + j)[0] = 255;
				this->image.at<Vec3b>(coorVal[0] + i, coorVal[1] + j)[1] = 255;
				this->image.at<Vec3b>(coorVal[0] + i, coorVal[1] + j)[2] = 255;
			}
		}
	}
};
