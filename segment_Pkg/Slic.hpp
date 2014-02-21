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
	LabPointInfo(double l, double a, double b) : lVal(l), aVal(a), bVal(b) {}
};

class Slic{
	int rowNum, colNum;
	Mat image, labImage;
	tr1::unordered_map<int, tr1::unordered_map<int, LabPointInfo *> > labImageMatrix;

public:
	Slic(Mat &image){
		this->image = image;
		rowNum = image.rows;
		colNum = image.cols;
		cvtColor(this->image, this->labImage, CV_BGR2Lab);
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
		int rowSeg = 1, colSeg = 1;
		if(isPrime(k))
			(this->rowNum > this->colNum) ? (rowSeg = k) : (colSeg = k);
		else
			decomNum(k, rowSeg, colSeg);

		cout << rowSeg << ", " << colSeg << endl;
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
};
