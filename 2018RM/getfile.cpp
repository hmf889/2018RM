#include<getfile.h>
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<stdio.h>
#include<time.h>
#include<opencv2/ml/ml.hpp>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<opencv/cv.hpp>
#include<unistd.h>
#include<unistd.h>
#include<cstdio>
#include<cstring>
using namespace cv;
using namespace std;
int getFile(char *basePath)
{
    int i=0;
    DIR *dir;
    struct dirent *ptr;
    char base[1000];
    char fileName[100];

    if ((dir=opendir(basePath)) == NULL)
    {
        perror("Open dir error...");
        exit(1);
    }

    while ((ptr=readdir(dir)) != NULL)
    {
        if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0)    ///current dir OR parrent dir
            continue;
        else if(ptr->d_type == 8)    //file
            printf("d_name:%s/%s\n",basePath,ptr->d_name);
        else if(ptr->d_type == 10)    //link file
            printf("d_name:%s/%s\n",basePath,ptr->d_name);
        else if(ptr->d_type == 4)    //dir
        {
            memset(base,'\0',sizeof(base));
            strcpy(base,basePath);
            strcat(base,"/");
            strcat(base,ptr->d_name);
            getFile(base);
        }
    }
    closedir(dir);

    return 1;
 }
