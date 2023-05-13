#include <iostream>
#include <QtWidgets>
#include <QtCore> 
#include <QtGui> 

#include "ImageFilterWorker.h" 

using namespace std; 

ImageFilterWorker::ImageFilterWorker() 
: QThread() 
{
    ThreadActive = true; 
}

void ImageFilterWorker::setSrc(cv::Mat src){
    this->src = src; 
} 
void ImageFilterWorker::setDst(cv::Mat dst){
    this->dst = dst; 
} 
void ImageFilterWorker::setFilterMethod(QString filterMethod){
    this->filterMethod = filterMethod;
}

cv::Mat ImageFilterWorker::getDst() const {
    return this->dst; 
}

void ImageFilterWorker::runFilterTask () {
    // Perform color reverse
    if (this->filterMethod == "REVERSE_METHOD") {
        ColorReverseFilterCpu(this->src,this->dst);
    }

    QPixmap pixEnhance = ImageFormatOpStack::GetInstance().Mat2QPixmap(this->dst);
    emit (pixMsg( pixEnhance ));
    // stop 
    stop(); 
}


void ImageFilterWorker::ColorReverseFilterCpu(cv::Mat & src, cv::Mat & dst) {
    // Perform color reverse 
    //dst = cv::Scalar(255, 255, 255) - src; 
    cv::bitwise_not(src, dst); 
}


void ImageFilterWorker::run() {
    if (ThreadActive) {
        runFilterTask();
    }
}


void ImageFilterWorker::stop() {
    ThreadActive = false; 
    this->quit();
}

