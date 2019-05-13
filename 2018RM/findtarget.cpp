#include<findtarget.h>
using namespace std;
using namespace cv;
void findTarget(cv::Mat target,Point2f  targetPoint[4])
{
    Point2f rectExternal[4];//用于存放最小包围矩形四个顶点
    int number=0;
    cv::GaussianBlur(target,target,cv::Size(3,3),0);
    cv::Mat element=getStructuringElement(cv::MORPH_RECT,cv::Size(3,3));
    cv::cvtColor(target,target,CV_BGR2HSV);
    cv::inRange(target,cv::Scalar(0,10,220),cv::Scalar(40,255,255),target);
    cv::morphologyEx(target,target,cv::MORPH_CLOSE,element);
    cv::imshow("test",target);
    vector<vector<cv::Point>>contoursExternal,contoursList;
    vector<cv::Vec4i>hierarchyExternal,hierarchyList;
    cv::findContours(target,contoursExternal,hierarchyExternal,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_NONE);
    Mat contoursPicture=Mat::zeros(target.size(),CV_8UC1);
    double contourLength;
    for (int i=0;i<contoursExternal.size();i++)
    {
        contourLength=cv::arcLength(contoursExternal[i],1);
        if(contourLength<260&&contourLength>190)
        {
            number++;
            cv::drawContours(contoursPicture,contoursExternal,i,cv::Scalar(255),1,8,hierarchyExternal);
            cout<<"第"<<i<<"个轮廓的长度为";
            cout<<contourLength<<endl;
            RotatedRect minRectExternal = minAreaRect(Mat(contoursExternal[i]));     //找到最小包围矩形
            minRectExternal.points(rectExternal);
            //cout<<"四个顶点为"<<endl;
            if(number==1)
            {
                for(int j=0;j<4;j++)
                {
                    targetPoint[j]=rectExternal[j];
                }
            }
            else if(number>2||number==2)
            {
                for (int j=0;j<4;j++)
                {
                    targetPoint[j].x=0;
                    targetPoint[j].y=0;

                }
                return ;
            }


        }



    }
    /*如果装甲板外轮廓和内轮廓连在一起*/
    if(number==0)
    {
        cv::findContours(target,contoursList,hierarchyList,cv::RETR_LIST,cv::CHAIN_APPROX_NONE);
        for(int i=0;i<contoursList.size();i++)
        {
            contourLength=cv::arcLength(contoursList[i],1);
            if(contourLength>100)
            {
                int result[4];
                for (int a=0;a<4;a++)

                {
                    result[a]=-1;

                }
                for(int j=0;j<4;j++)
                {
                    result[j]=pointPolygonTest(contoursList[i],targetPoint[j],false);
                }
                if(result[0]!=-1||result[1]!=-1||result[2]!=-1||result[3]!=-1)
                {
                    RotatedRect minRectList = minAreaRect(Mat(contoursExternal[i]));     //找到最小包围矩形
                    minRectList.points(rectExternal);
                    for(int b=0;b<4;b++)
                    {
                        targetPoint[b]=rectExternal[b];
                    }
                }

            }

        }
    }
    for(int j=0;j<4;j++)
    {
        line(contoursPicture,targetPoint[j],targetPoint[(j+1)%4],Scalar(255),2,8);
    }
    imshow("contoursPicture",contoursPicture);

}

