
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#include <fstream>


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

#define LED_PATH "sys/class/leds/beaglebone:green:usr0"

static int person = 0; 

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

void SendData (void)
 
{
    int sfd =0;
    int b;
    char rbuff[1024];    
    char sendbuffer[100];

    struct sockaddr_in serv_addr;

    memset(rbuff, '0', sizeof(rbuff));
    sfd = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);
    serv_addr.sin_addr.s_addr = inet_addr("192.168.1.4");

    b=connect(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    FILE *fp = fopen("/home/debian/Desktop/app/image1.png", "rb");

    while( (b = fread(sendbuffer, 1, sizeof(sendbuffer), fp))>0 ){
        send(sfd, sendbuffer, b, 0);
    }

    fclose(fp);

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
//        SendData();
	cv::cvtColor(frame, gray, COLOR_BGR2GRAY);
	cv::threshold( gray, result, 100, 255, THRESH_BINARY_INV );
	cv::imwrite("image2.png", result);
}

float image_recog (void)
{

    string path = "/home/debian/Desktop/app/sample_set/"; //fixme 
    cv::Ptr <cv::ShapeContextDistanceExtractor> mysc = cv::createShapeContextDistanceExtractor();

    Size sz2Sh(200,200);
    Mat query= imread("image2.png",IMREAD_GRAYSCALE); //Image capture function
    vector<Point> contQuery = simpleContour(query);
    int bestMatch = 0;
    float bestDis=FLT_MAX;
    for ( int ii=1; ii<=7; ii++ )
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
    person = bestMatch;
    bestname<<path<<bestMatch<<".png";
    Mat iiIm=imread(bestname.str(), 0);
    resize(iiIm, iiIm, sz2Sh, 0, 0, INTER_LINEAR);
    imwrite("BEST_MATCH.png", iiIm);
    return bestDis;
}

void LED_Func(bool n){
    if (n == true){
       cout<< "True";
    }
    else {
       cout<< "False";
    }
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
    float bestDis =  image_recog();
    if (bestDis < 10){
	    if(person < 8){
	    QPixmap result_img = QPixmap("/home/debian/Desktop/app/Arjun.png");
	    ui->img_label->setPixmap(result_img);
	    }
	    else{
	    QPixmap result_img = QPixmap("/home/debian/Desktop/app/Arjun.png");
	    ui->img_label->setPixmap(result_img);
	    }
    }
    else{
    ui->img_label->setText("Match Not Found \nNotifying Owner\nSecurity Breach");
    }
}


