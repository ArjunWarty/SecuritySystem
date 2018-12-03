#include "syssec.h"
#include "ui_syssec.h"
#include "opencv2/shape.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/core/utility.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

static vector<Point> simpleContour( const Mat& currentQuery, int n=300 )
{
    vector<vector<Point> > _contoursQuery;
    vector <Point> contoursQuery;
    findContours(currentQuery, _contoursQuery, RETR_LIST, CHAIN_APPROX_NONE);
    for (size_t border=0; border<_contoursQuery.size(); border++)
    {
        for (size_t p=0; p<_contoursQuery[border].size(); p++)
        {
            contoursQuery.push_back( _contoursQuery[border][p] );
        }
    }

    // In case actual number of points is less than n
    int dummy=0;
    for (int add=(int)contoursQuery.size()-1; add<n; add++)
    {
        contoursQuery.push_back(contoursQuery[dummy++]); //adding dummy values
    }

    // Uniformly sampling
    cv::randShuffle(contoursQuery);
    vector<Point> cont;
    for (int i=0; i<n; i++)
    {
        cont.push_back(contoursQuery[i]);
    }
    return cont;
}

void capture_img(void)
{
   // local variable declaration
	cv::Mat result;
        Size sz2Sh(200,200);
	cv::VideoCapture cap(0); // open the default camera
	cv::Mat frame,gray,BW;
	cap >> frame; // get a new frame from camera
 	resize(frame, frame, sz2Sh, 0, 0, INTER_LINEAR);
	cv::imwrite("image1.png", frame);   
	cv::cvtColor(frame, gray, COLOR_BGR2GRAY);
	cv::threshold( gray, result, 100, 255, THRESH_BINARY_INV );
	cv::imwrite("image2.png", result);
}

void image_recog (void) 
{

    string path = "/home/debian/Desktop/app/shape_sample/"; //fixme 
    cv::Ptr <cv::ShapeContextDistanceExtractor> mysc = cv::createShapeContextDistanceExtractor();

    Size sz2Sh(200,200);
    Mat query= imread("image2.png",IMREAD_GRAYSCALE); //Image capture function
    vector<Point> contQuery = simpleContour(query);
    int bestMatch = 0;
    float bestDis=FLT_MAX;
    for ( int ii=1; ii<=21; ii++ )
    {

        waitKey(30);
        stringstream iiname;
        iiname<<path<<ii<<".png";
        cout<<"name: "<<iiname.str()<<endl;
        Mat iiIm=imread(iiname.str(), 0);
        vector<Point> contii = simpleContour(iiIm);
        float dis = mysc->computeDistance( contQuery, contii );
        if ( dis<bestDis )
        {
            bestMatch = ii;
            bestDis = dis;
        }
        std::cout<<" distance between input image and "<<iiname.str()<<" is: "<<dis<<std::endl;
    }
    stringstream bestname;
    bestname<<path<<bestMatch<<".png";
    Mat iiIm=imread(bestname.str(), 0);
    resize(iiIm, iiIm, sz2Sh, 0, 0, INTER_LINEAR);
    imwrite("BEST_MATCH.png", iiIm);
}




SysSec::SysSec(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SysSec)
{
    ui->setupUi(this);

}

SysSec::~SysSec()
{
    delete ui;
}

void SysSec::on_Capture_clicked()
{
    capture_img();
    QPixmap img = QPixmap("/home/debian/Desktop/app/image1.png");
    ui->img_label->setPixmap(img);
    image_recog();
    QPixmap result_img = QPixmap("/home/debian/Desktop/app/BEST_MATCH.png");
    ui->img_label->setPixmap(result_img);
 

}


