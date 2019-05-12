#include<findtarget.h>
using namespace std;
using namespace cv;
void findTarget(cv::Mat target,Point2f  targetPoint[4])
{
    Point2f rect[4];                                                        //用于存放最小包围矩形四个顶点
    cv::GaussianBlur(target,target,cv::Size(3,3),0);
    cv::Mat element=getStructuringElement(cv::MORPH_RECT,cv::Size(3,3));
    cv::cvtColor(target,target,CV_BGR2HSV);
    cv::inRange(target,cv::Scalar(0,10,220),cv::Scalar(40,255,255),target);
    cv::morphologyEx(target,target,cv::MORPH_CLOSE,element);
    vector<vector<cv::Point>>contours;
    vector<cv::Vec4i>hierarchy;
    cv::findContours(target,contours,hierarchy,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_NONE);
    Mat contoursPicture=Mat::zeros(target.size(),CV_8UC1);
    double contourLength;
    for (int i=0;i<contours.size();i++)
    {
        contourLength=cv::arcLength(contours[i],1);
        if(contourLength<280&&contourLength>150)
        {
            cv::drawContours(contoursPicture,contours,i,cv::Scalar(255),1,8,hierarchy);
            /*cout<<"第"<<i<<"个轮廓的长度为";
            cout<<contourLength<<endl;*/
            RotatedRect minRect = minAreaRect(Mat(contours[i]));     //找到最小包围矩形
            minRect.points(rect);
            //cout<<"四个顶点为"<<endl;
            for(int j=0;j<4;j++)
            {
                targetPoint[j]=rect[j];

            }
            for(int j=0;j<4;j++)
            {
                line(contoursPicture,rect[j],rect[(j+1)%4],Scalar(255),2,8);
            }

        }
    }
    imshow("contoursPicture",contoursPicture);

}
