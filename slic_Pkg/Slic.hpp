/*
 * slic.hpp
 *
 *  Created on: Feb 20, 2014
 *      Author: napolenli
 */


#ifndef SLIC_H
#define SLIC_H

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <stdio.h>
#include <math.h>
#include <vector>
#include <float.h>
using namespace std;

/* 2d matrices are handled by 2d vectors. */
#define vec2dd vector<vector<double> >
#define vec2di vector<vector<int> >
#define vec2db vector<vector<bool> >
/* The number of iterations run by the clustering algorithm. */
#define NR_ITERATIONS 10

/*
 * class Slic.
 *
 * In this class, an over-segmentation is created of an image, provided by the
 * step-size (distance between initial cluster locations) and the colour
 * distance parameter.
 */
class Slic {
    private:
        /* The cluster assignments and distance values for each pixel. */
        vec2di clusters;
        vec2dd distances;

        /* The LAB and xy values of the centers. */
        vec2dd centers;
        /* The number of occurences of each center. */
        vector<int> center_counts;

        /* The step size per cluster, and the colour (nc) and distance (ns)
         * parameters. */
        int step, nc, ns;

        /* Compute the distance between a center and an individual pixel. */
        double compute_dist(int ci, CvPoint pixel, CvScalar colour);
        /* Find the pixel with the lowest gradient in a 3x3 surrounding. */
        CvPoint find_local_minimum(IplImage *image, CvPoint center);

        /* Remove and initialize the 2d vectors. */
        void clear_data();
        void init_data(IplImage *image);

    public:
        /* Class constructors and deconstructors. */
        Slic();
        ~Slic();

        /* Generate an over-segmentation for an image. */
        void generate_superpixels(IplImage *image, int step, int nc);
        /* Enforce connectivity for an image. */
        void create_connectivity(IplImage *image);

        /* Draw functions. Resp. displayal of the centers and the contours. */
        void display_center_grid(IplImage *image, CvScalar colour);
        void display_contours(IplImage *image, CvScalar colour);
        void colour_with_cluster_means(IplImage *image);
        void saveWeightedPoints();
};

#endif
