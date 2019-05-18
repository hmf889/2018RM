#ifndef FINDTARGET_H
#define FINDTARGET_H
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<stdio.h>
#include<time.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<opencv/cv.hpp>
#include <math.h>
void findTarget(cv::Mat target,cv::Point2f [4]);
//void correctPoints(cv::Point2f example[4],cv::Point2f  targetPoint[4]);
#endif // FINDTARGET_H
