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
#include<getfile.h>
using namespace std;
using namespace cv;
using namespace cv::ml;
/*int main()
{
    VideoCapture camera;
    camera.open(0);
    Mat in,outGRAY,outHSV,out;
    vector<Mat>hsvSplit;
    while(1)
           {
              waitKey(20);
              camera>>in;//等价于camera.read(In);
                if(in.empty())//如果某帧为空则退出循环
                    continue;
               cvtColor(in,outGRAY,COLOR_BGR2GRAY);
               imshow("GRAY",outGRAY);
               cvtColor(in,outHSV,COLOR_BGR2HSV);
               imshow("HSV",outHSV);
               split(outHSV,hsvSplit);
               equalizeHist(hsvSplit[2],hsvSplit[2]);
               merge(hsvSplit,outHSV);
               imshow("HSV2",outHSV);



       }
}*/
int main( int argc, char** argv )
{
   VideoCapture cap(0); //capture the video from web cam

   if ( !cap.isOpened() )  // if not success, exit program
   {
        cout << "Cannot open the web cam" << endl;
        return -1;
   }

 namedWindow("Control"); //create a window called "Control"

 int iLowH = 100;
 int iHighH = 360;

 int iLowS = 90;
 int iHighS = 255;

 int iLowV = 90;
 int iHighV = 255;

 //Create trackbars in "Control" window
 createTrackbar("LowH", "Control", &iLowH, 360); //Hue (0 - 360)
 createTrackbar("HighH", "Control", &iHighH, 360);

 createTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
 createTrackbar("HighS", "Control", &iHighS, 255);

 createTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
 createTrackbar("HighV", "Control", &iHighV, 255);

   while (true)
   {
       Mat imgOriginal;

       bool bSuccess = cap.read(imgOriginal); // read a new frame from video

        if (!bSuccess) //if not success, break loop
       {
            cout << "Cannot read a frame from video stream" << endl;
            break;
       }

  Mat imgHSV;
  vector<Mat> hsvSplit;
  cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
  split(imgHSV, hsvSplit);
  equalizeHist(hsvSplit[2],hsvSplit[2]);
  merge(hsvSplit,imgHSV);
  Mat imgThresholded;

  inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
  //去除一些噪点
  Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
  morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
  //连接一些连通域
  morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);

  imshow("Thresholded Image", imgThresholded); //show the thresholded image
  imshow("Original", imgOriginal); //show the original image

  char key = (char) waitKey(30);
  if(key == 27)
        break;
   }

  return 0;

}
/*int main()
{
    VideoCapture video;
    video.open("C:/Users/hmf889/Desktop/2018RoboMaster/read.avi");
    if(!video.isOpened())
    return 0;
    Mat picture;
    while(1)
    {
        video>>picture;
        if(picture.empty())
            break;
        imshow("test",picture);
        waitKey(30);
    }
    return 0;
}*/
/*vector<Mat>trainingImages;
vector<int>trainingLabels;
void openfile(int flag,const char *dpath);
int main()
{
        Mat classes;
        string onePath,zeroPath;
        onePath="/\data-front";
        zeroPath="/\data-against";
        openfile(1,onePath.c_str());
        openfile(0,zeroPath.c_str());
        Mat trainingData(trainingImages.size(), trainingImages[0].cols, CV_32FC1);
        for (int i = 0; i < trainingImages.size(); i++)
        {
            Mat temp(trainingImages[i]);
            temp.copyTo(trainingData.row(i));
        }
        trainingData.convertTo(trainingData, CV_32FC1);
        Mat(trainingLabels).copyTo(classes);
        classes.convertTo(classes, CV_32SC1);

        Ptr<SVM> model = SVM::create();//以下是设置SVM训练模型的配置
        model->setType(SVM::C_SVC);
        model->setKernel(SVM::LINEAR);
        model->setGamma(1);
        model->setC(1);
        model->setCoef0(0);
        model->setNu(0);
        model->setP(0);
        model->setTermCriteria(cvTermCriteria(CV_TERMCRIT_ITER, 20000, 0.0001));


        Ptr<TrainData> tdata = TrainData::create(trainingData, ROW_SAMPLE, classes);
        //model->train(trainingData, ROW_SAMPLE, classes);
        model->train(tdata);
        model->save("car.xml");//保存

        return 0;



    //Ptr<SVM> svm=SVM::create();
    //svm->setType(SVM::Types::C_SVC);
    //svm->setKernel(SVM::KernelTypes::LINEAR);
    //svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER,100,1e-6));
    //Ptr<TrainData> tData=TrainData::create();

}
void openfile(int flag,const char *dpath)
{
    vector<string>files;
    DIR *dir;
    struct dirent64 *ptr;
    dir=opendir(dpath);
    while ((ptr=readdir64(dir))!=NULL)
    {
        if(ptr->d_type>4)
        {
            //char name[30];
            char path[200];
            sprintf(path,"%s",ptr->d_name);
            cout<<ptr->d_name;
            files.push_back(path);
        }
    }
    closedir(dir);
    for(int i=0;i<files.size();i++)
    {
        Mat img=imread(files[i].c_str());
        Mat line_i=img.reshape(1,1);
        trainingImages.push_back(line_i);
        trainingLabels.push_back(flag);
    }

}*/
/*int main(void)
{
    VideoCapture camera(1);
    if(!camera.isOpened())
        return 0;
    int lowH,lowS,lowV,highH,highS,highV;
    lowH=100;
    highH=124;
    lowS=43;
    highS=255;
    lowV=46;
    highV=255;
    while (1)
    {
     Mat inPicture;
     Mat imgHSV;
     Mat imgBinarization;
     camera>>inPicture;
     cvtColor(inPicture,imgHSV,COLOR_BGR2HSV);
     inRange(imgHSV,Scalar(lowH,lowS,lowV),Scalar(highH,highS,highV),imgBinarization);
     imshow("1",imgBinarization);
     waitKey(20);
    }
}*/
/*int main(void)
{
    DIR *dir;
         char basePath[1000];

         ///get the current absoulte path
         memset(basePath,'\0',sizeof(basePath));
         getcwd(basePath, 999);
         printf("the current dir is : %s\n",basePath);

         ///get the file list
         memset(basePath,'\0',sizeof(basePath));
         strcpy(basePath,"/");//the path of data
         getFile(basePath);
         return 0;
}*/















