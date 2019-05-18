#include<findtarget.h>
using namespace std;
using namespace cv;
/*第一方案*/
//void findTarget(cv::Mat target,Point2f  targetPoint[4])
//{
//    imshow("test2",target);
//    Point2f rectExternal[4];//用于存放最小包围矩形四个顶点
//    int number=0;
//    cv::GaussianBlur(target,target,cv::Size(3,3),0);
//    cv::Mat element=getStructuringElement(cv::MORPH_RECT,cv::Size(3,3));
//    cv::cvtColor(target,target,CV_BGR2HSV);
//    cv::inRange(target,cv::Scalar(90,70,220),cv::Scalar(150,255,255),target);
//    cv::morphologyEx(target,target,cv::MORPH_CLOSE,element);
//    cv::imshow("test",target);
//    vector<vector<cv::Point>>contoursExternal;
//    vector<cv::Vec4i>hierarchyExternal;
//    cv::findContours(target,contoursExternal,hierarchyExternal,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_NONE);
//    Mat contoursPicture=Mat::zeros(target.size(),CV_8UC1);
//    double contourLength;
//    for (int i=0;i<contoursExternal.size();i++)
//    {
//        contourLength=cv::arcLength(contoursExternal[i],1);
//        if(contourLength<260&&contourLength>190)
//        {
//            number++;
//            cv::drawContours(contoursPicture,contoursExternal,i,cv::Scalar(255),1,8,hierarchyExternal);
//            cout<<"第"<<i<<"个轮廓的长度为";
//            cout<<contourLength<<endl;
//            RotatedRect minRectExternal = minAreaRect(Mat(contoursExternal[i]));     //找到最小包围矩形
//            minRectExternal.points(rectExternal);
//            //cout<<"四个顶点为"<<endl;
//            if(number==1)
//            {
//                //correctPoints(rectExternal,targetPoint);
//                for(int j=0;j<4;j++)
//                {
//                    targetPoint[j]=rectExternal[j];
//                }
//            }
//            else if(number>2||number==2)
//            {
//                for (int j=0;j<4;j++)
//                {
//                    targetPoint[j].x=0;
//                    targetPoint[j].y=0;

//                }
//                return ;
//            }

//        }

//    }
//    /*如果装甲板外轮廓和内轮廓连在一起*/
//    if(number==0)
//    {

//        for(int i=0;i<contoursExternal.size();i++)
//        {
//            contourLength=cv::arcLength(contoursExternal[i],1);
//            if(contourLength>100)
//            {
//                int result[4];
//                for (int a=0;a<4;a++)

//                {
//                    result[a]=-1;

//                }
//                for(int j=0;j<4;j++)
//                {
//                    result[j]=pointPolygonTest(contoursExternal[i],targetPoint[j],false);
//                }
//                if(result[0]!=-1||result[1]!=-1||result[2]!=-1||result[3]!=-1)
//                {
//                    RotatedRect minRectList = minAreaRect(Mat(contoursExternal[i]));     //找到最小包围矩形
//                    minRectList.points(rectExternal);
//                    //correctPoints(rectExternal,targetPoint);
//                    for(int b=0;b<4;b++)
//                    {
//                        targetPoint[b]=rectExternal[b];
//                    }
//                }
//            }
//        }
//    }
//
//    for(int j=0;j<4;j++)
//    {
//        line(contoursPicture,targetPoint[j],targetPoint[(j+1)%4],Scalar(255),2,8);
//    }
//    imshow("contoursPicture",contoursPicture);

//}
/*矫正装甲板四个顶点*/
//void correctPoints(cv::Point2f example[4],Point2f  targetPoint[4])
//{
//    int direction;
//    direction=0;                                                                             //1:up;-1:down
//    if(example[0].y>targetPoint[0].y&&example[0].x>targetPoint[0].x)
//    {
//        direction=-1;
//    }
//    if(example[0].y>targetPoint[0].y&&example[0].x<targetPoint[0].x)
//    {
//        direction=1;
//    }
//    if(example[0].y<targetPoint[0].y&&example[0].x>targetPoint[0].x)
//    {
//        direction=-1;
//    }
//    if(example[0].y<targetPoint[0].y&&example[0].x<targetPoint[0].x)
//    {
//        direction=1;
//    }
//    float lineOne,lineTwo,correctX,correctY;
//    lineOne=sqrt(pow(example[0].x-example[1].x,2)+pow(example[0].y-example[1].y,2));
//    lineTwo=sqrt(pow(example[1].x-example[2].x,2)+pow(example[1].y-example[2].y,2));
//    if(lineOne<60)
//    {
//        if(direction==1)
//        {
//            float k;
//            k=(example[0].y-example[1].y)/(example[0].x-example[1].x);
//            correctX=example[0].x-sqrt(2025/((pow(k,2)+1)));
//            correctY=k*(correctX-example[0].x)+example[0].y;
//            example[1].x=correctX;
//            example[1].y=correctY;
//            correctX=example[3].x-sqrt(2025/((pow(k,2)+1)));
//            correctY=k*(correctX-example[3].x)+example[3].y;
//            example[2].x=correctX;
//            example[2].y=correctY;
//            return ;
//        }
//        if(direction==-1)
//        {
//            float k;
//            k=(example[0].y-example[1].y)/(example[0].x-example[1].x);
//            correctX=example[1].x+sqrt(2025/((pow(k,2)+1)));
//            correctY=k*(correctX-example[0].x)+example[0].y;
//            example[0].x=correctX;
//            example[0].y=correctY;
//            correctX=example[2].x+sqrt(2025/((pow(k,2)+1)));
//            correctY=k*(correctX-example[2].x)+example[3].y;
//            example[3].x=correctX;
//            example[3].y=correctY;
//            return ;
//        }
//    }
//    /*if(lineTwo<60)
//    {
//        if(direction==1)
//        {

//        }
//    }*/
//}



/*第二方案*/
void findTarget(cv::Mat target,cv::Point2f targetPoint[4])
{
    cv::Point2f rectExternal[4],rectList[4];
    cv::Mat contoursPicture=Mat::zeros(target.size(),CV_8UC1);
    cv::GaussianBlur(target,target,cv::Size(3,3),0);
    cv::cvtColor(target,target,CV_BGR2HSV);
    cv::inRange(target,cv::Scalar(0,10,220),cv::Scalar(40,255,255),target);
    cv::Mat elemnt=getStructuringElement(cv::MORPH_CROSS,cv::Size(3,3));
    cv::morphologyEx(target,target,cv::MORPH_CLOSE,elemnt);
    vector<vector<cv::Point>> contoursExternal,contoursList,contoursTarget;
    vector<cv::Vec4i>hierarchyExternal,hierarchyList,hierarchyTarget;
    cv::findContours(target,contoursExternal,hierarchyExternal,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_NONE);
    cv::findContours(target,contoursList,hierarchyList,cv::RETR_LIST,cv::CHAIN_APPROX_NONE);
    double contoursExternalLength,contoursListLength;
    for(int i=0;i<contoursExternal.size();i++)
    {
        contoursExternalLength=cv::arcLength(contoursExternal[i],1);
        //cv::drawContours(contoursPicture,contoursList,i,cv::Scalar(255),1,8,hierarchyList);
        if(contoursExternalLength<260&&contoursExternalLength>190)
        {
            RotatedRect minRectExternal = minAreaRect(Mat(contoursExternal[i]));
            minRectExternal.points(rectExternal);
            for(int j=0;j<4;j++)
            {
                targetPoint[j]=rectExternal[j];
            }
        }
    }
    for(int j=0;j<4;j++)
    {
        line(contoursPicture,targetPoint[j],targetPoint[(j+1)%4],Scalar(255),1,8);
    }
    cv::findContours(contoursPicture,contoursTarget,hierarchyTarget,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_NONE);
    contoursPicture=Mat::zeros(target.size(),CV_8UC1);
    imshow("test",contoursPicture);
    for(int i=0;i<contoursList.size();i++)
    {
        contoursListLength=cv::arcLength(contoursList[i],1);
        if(contoursListLength>100&&contoursListLength<260)
        {

            RotatedRect minRectList=minAreaRect(Mat(contoursList[i]));
            minRectList.points(rectList);
            int result[4];
            for (int j=0;j<4;j++)
            {
                result[j]=-1;
            }
            for(int j=0;j<4;j++)
            {
                result[j]=pointPolygonTest(contoursTarget[0],rectList[j],false);
            }
            if(result[0]==1&&result[1]==1&&result[2]==1&&result[3]==1)
            {
                for(int a=0;a<4;a++)
                {
                    targetPoint[a]=rectList[a];
                }
            }
        }
    }
    for(int j=0;j<4;j++)
    {
        line(contoursPicture,targetPoint[j],targetPoint[(j+1)%4],Scalar(255),2,8);
    }
    cv::imshow("contoursPicture",contoursPicture);
    cv::waitKey(30);
}





















