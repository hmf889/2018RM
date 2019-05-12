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
#include<cstdio>
#include<cstring>
#include<sl/Camera.hpp>
#include<SaveDepth.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <assert.h>
#include <cuda_runtime.h>
#include<findtarget.h>
using namespace std;
//using namespace sl;
using namespace cv;
//using namespace cv::ml;
//cv::Mat slMat2cvMat(Mat& input);
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

    return 0;


}*/
/*int main( void )
{
   VideoCapture cap; //capture the video from web cam
   cap.open("/home/dukeye/桌面/Video/read_light.avi");

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
    //Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
    //morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
    //连接一些连通域
    //morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);

    imshow("Thresholded Image", imgThresholded); //show the thresholded image
    imshow("Original", imgOriginal); //show the original image

    char key = (char) waitKey(30);
    if(key == 27)
    break;
    }

  return 0;

}*/
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
int getFile(int flag,char *basePath);
int main()
{
        Mat classes;
        char onePath[1000];
        memset(onePath,'\0',sizeof(onePath));
        strcpy(onePath,"/home/dukeye/desktop/data-front");
        char zeroPath[1000];
        memset(zeroPath,'\0',sizeof(zeroPath));
        strcpy(zeroPath,"/home/dukeye/desktop/data-against");
        getFile(1,onePath);
        getFile(0,zeroPath);
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
        model->train(trainingData, ROW_SAMPLE, classes);
        model->train(tdata);
        model->save("car.xml");//保存
        cout<<"finsh";
        return 0;



    //Ptr<SVM> svm=SVM::create();
    //svm->setType(SVM::Types::C_SVC);
    //svm->setKernel(SVM::KernelTypes::LINEAR);
    //svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER,100,1e-6));
    //Ptr<TrainData> tData=TrainData::create();

}
int getFile(int flag,char *basePath)
{
    int i=0;
    DIR *dir;
    struct dirent *ptr;
    char base[1000];
    char fileName[1000];
    vector<string>files;
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
        {//printf("d_name:%s/%s\n",basePath,ptr->d_name);
            memset(fileName,'\0',sizeof (fileName));
            strcpy(fileName,basePath);
            strcat(fileName,"/");
            strcat(fileName,ptr->d_name);
            files.push_back(fileName);
            cout<<fileName;
            cout<<endl;

        }
        else if(ptr->d_type == 10)    //link file
            printf("d_name:%s/%s\n",basePath,ptr->d_name);
        else if(ptr->d_type == 4)    //dir
        {
            memset(base,'\0',sizeof(base));
            strcpy(base,basePath);
            strcat(base,"/");
            strcat(base,ptr->d_name);
            getFile(flag,base);
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
    return 1;
 }
*/
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

         char basePath[1000];

         ///get the current absoulte path
         memset(basePath,'\0',sizeof(basePath));
         getcwd(basePath, 999);
         printf("the current dir is : %s\n",basePath);

         ///get the file list
         memset(basePath,'\0',sizeof(basePath));
         strcpy(basePath,"/home/dukeye/desktop/data-front");//the path of data
         getFile(basePath);
}*/
/*int  main(int argc, char **argv)
{
    Camera zed;
    InitParameters init_params;
    init_params.camera_resolution = RESOLUTION_HD720;
    init_params.depth_mode = DEPTH_MODE_PERFORMANCE;
    init_params.coordinate_units = UNIT_METER;
    if (argc > 1) init_params.svo_input_filename.set(argv[1]);
    RuntimeParameters runtime_parameters;
        runtime_parameters.sensing_mode = SENSING_MODE_STANDARD;

        // Prepare new image size to retrieve half-resolution images
        Resolution image_size = zed.getResolution();
        int new_width = image_size.width / 2;
        int new_height = image_size.height / 2;

        // To share data between sl::Mat and cv::Mat, use slMat2cvMat()
        // Only the headers and pointer to the sl::Mat are copied, not the data itself
        Mat image_zed(new_width, new_height, MAT_TYPE_8U_C4);
        cv::Mat image_ocv = slMat2cvMat(image_zed);
        Mat depth_image_zed(new_width, new_height, MAT_TYPE_8U_C4);
        cv::Mat depth_image_ocv = slMat2cvMat(depth_image_zed);
        Mat point_cloud;

        // Loop until 'q' is pressed
        char key = ' ';
        while (key != 'q') {

            if (zed.grab(runtime_parameters) == SUCCESS) {

                // Retrieve the left image, depth image in half-resolution
                zed.retrieveImage(image_zed, VIEW_LEFT, MEM_CPU, new_width, new_height);
                zed.retrieveImage(depth_image_zed, VIEW_DEPTH, MEM_CPU, new_width, new_height);

                // Retrieve the RGBA point cloud in half-resolution
                // To learn how to manipulate and display point clouds, see Depth Sensing sample
                zed.retrieveMeasure(point_cloud, MEASURE_XYZRGBA, MEM_CPU, new_width, new_height);

                // Display image and depth using cv:Mat which share sl:Mat data
                cv::imshow("Image", image_ocv);
                cv::imshow("Depth", depth_image_ocv);

                // Handle key event
                key = cv::waitKey(10);
                processKeyEvent(zed, key);
            }
        }
        zed.close();
    return 0;

    return 0;
}

cv::Mat slMat2cvMat(Mat& input) {
    // Mapping between MAT_TYPE and CV_TYPE
    int cv_type = -1;
    switch (input.getDataType()) {
        case MAT_TYPE_32F_C1: cv_type = CV_32FC1; break;
        case MAT_TYPE_32F_C2: cv_type = CV_32FC2; break;
        case MAT_TYPE_32F_C3: cv_type = CV_32FC3; break;
        case MAT_TYPE_32F_C4: cv_type = CV_32FC4; break;
        case MAT_TYPE_8U_C1: cv_type = CV_8UC1; break;
        case MAT_TYPE_8U_C2: cv_type = CV_8UC2; break;
        case MAT_TYPE_8U_C3: cv_type = CV_8UC3; break;
        case MAT_TYPE_8U_C4: cv_type = CV_8UC4; break;
        default: break;
    }

    // Since cv::Mat data requires a uchar* pointer, we get the uchar1 pointer from sl::Mat (getPtr<T>())
    // cv::Mat and sl::Mat will share a single memory structure
    return cv::Mat(input.getHeight(), input.getWidth(), cv_type, input.getPtr<sl::uchar1>(MEM_CPU));
}*/
/*void on_mouse(int EVENT, int x, int y, int flags, void* userdata);
sl::Mat img_zed;
sl::Mat img_zed_depth;
sl::Mat Point_3D;//3D点云图
cv::Mat img_cv;
cv::Mat img_cv_depth;//cv深度图
cv::String text;//存贮显示的文字
cv::Point mouse_point;
int main() {
            Camera zed;
            sl::InitParameters param;
            param.camera_fps = 30;
            param.depth_mode = sl::DEPTH_MODE_PERFORMANCE;//性能模式
            param.coordinate_units = sl::UNIT_METER;//单位：米
            zed.open(param);
            cv::namedWindow("img_cv");
            cv::setMouseCallback("img_cv", on_mouse);
            while (true) {
                    zed.grab();
                    zed.retrieveImage(img_zed, VIEW_LEFT);//左边相机图像
                    img_cv = cv::Mat(img_zed.getHeight(), img_zed.getWidth(), CV_8UC4, img_zed.getPtr<sl::uchar1>(MEM_CPU));
                    zed.retrieveImage(img_zed_depth, VIEW_DEPTH);//深度矩阵存储32位浮点值，其表示每个（X>，Y）像素的深度（Z）
           //默认情况下，深度值以毫米表示。可以使用更改单位InitParameters::coordinate_units。高级用户可以
    //使用CPU内存（默认）或GPU内存中的图像，深度和点云检索retrieveMeasure(*, *, MEM_GPU)。
                    img_cv_depth = cv::Mat(img_zed_depth.getHeight(), img_zed_depth.getWidth(), CV_8UC4, img_zed_depth.getPtr<sl::uchar1>(MEM_CPU));
                    zed.retrieveMeasure(Point_3D, MEASURE_XYZRGBA);//选择从 CPU中 获得数据
                    cv::putText(img_cv,
                            text,
                            cv::Point(20, 30),
                            cv::FONT_HERSHEY_SIMPLEX,
                            0.5,
                            cv::Scalar(0, 255, 0));//将距离显示在图像上
                    cv::circle(img_cv, mouse_point, 10, cv::Scalar(255, 0, 0),3);
                    cv::imshow("img_cv", img_cv);
                    //cv::imshow("depth", img_cv_depth);
                    cv::waitKey(30);
            }
    }

void on_mouse(int EVENT, int x, int y, int flags, void* userdata) {
        sl::float4 point3D;//点云图数据
        //点云将其数据存储在4个通道上，每个通道使用32位浮点数。
        //最后一个浮点数用于存储颜色信息，其中R，G，B和alpha通道（4 x 8位）连接成一个32位浮点数
        switch (EVENT) {
                case cv::EVENT_LBUTTONDOWN: {
                        img_zed_depth.getValue(x, y, &point3D);
                        Point_3D.getValue(x, y, &point3D);
                        //float _x = point3D.x;
                        //float _y = point3D.y;
                        //float _z = point3D.z;
                        //float color = point3D.w;
                        float distance= sqrt(point3D.x*point3D.x + point3D.y*point3D.y + point3D.z*point3D.z);
                        text = "distance: " + std::to_string(distance) + " m";
                        mouse_point = cv::Point(x, y);
                }
                break;
                default:break;
        }
}*/
/*int main(void)
{
    Camera zed;
    sl::InitParameters param;
    param.camera_fps = 30;
    param.camera_resolution=RESOLUTION_HD2K;
    param.depth_mode = sl::DEPTH_MODE_PERFORMANCE;//性能模式
    param.coordinate_units = sl::UNIT_METER;//单位：米
    zed.open(param);
    cv::Mat test,gray,auto_image,manual_image,test2;
    sl::Mat zedTest;
    while (1)
    {
          zed.grab();
          zed.retrieveImage(zedTest,VIEW_LEFT);
          test=cv::Mat(zedTest.getHeight(),zedTest.getWidth(),CV_8UC4,zedTest.getPtr<sl::uchar1>(sl::MEM_CPU));
          cv::imshow("test",test);
          //cv::
          cv::cvtColor(test,test,CV_BGR2HSV);
          cv::imshow("hsv",test); 
          cv::cvtColor(test,gray,CV_BGR2GRAY);
          cv::imshow("gray",gray);
          cv::threshold(gray,manual_image,100,255,0);
          cv::imshow("manual",manual_image);
          cv::adaptiveThreshold(gray,auto_image,255,CV_ADAPTIVE_THRESH_MEAN_C,CV_THRESH_BINARY,31,10);
          cv::imshow("auto",auto_image);
          cv::waitKey(30);
    }
    return 0;
}*/
int main(void)
{
    cv::VideoCapture video_light;
    video_light.open("/home/dukeye/桌面/Video/read_light.avi");
    if(!video_light.isOpened())
        return 0;
    cv::Mat testLight;
    Point2f targetPoint[4];
    while(1)
    {

        video_light>>testLight;
        findTarget(testLight, targetPoint);
        cout<<"四个顶点为："<<endl;
        for(int j=0;j<4;j++)
        {
            cout<<targetPoint[j];
            cout<<endl;
        }
        cv::waitKey(30);
    }


    return 0;
}
/*int main(void)
{
    for(int a=1;a<5;a++)
    {
        cout<<a;
    }
    return 0;
}*/














