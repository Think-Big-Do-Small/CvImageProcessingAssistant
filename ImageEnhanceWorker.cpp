#include <iostream>
#include <QtWidgets>
#include <QtCore> 
#include <QtGui> 

#include "ImageEnhanceWorker.h" 

using namespace std; 

ImageEnhanceWorker::ImageEnhanceWorker() 
: QThread() 
{
    ThreadActive = true; 
}

void ImageEnhanceWorker::setSrc(cv::Mat src){
    this->src = src; 
} 
void ImageEnhanceWorker::setDst(cv::Mat dst){
    this->dst = dst; 
} 
void ImageEnhanceWorker::setEnhanceMethod(QString enhanceMethod){
    this->enhanceMethod = enhanceMethod;
}

cv::Mat ImageEnhanceWorker::getDst() const {
    return this->dst; 
}

void ImageEnhanceWorker::runEnhanceTask () {
    // Perform color enhancement
    if (this->enhanceMethod == "X_METHOD") {
        ColorXEnhanceCpu(this->src,this->dst);
    }

    QPixmap pixEnhance = ImageFormatOpStack::GetInstance().Mat2QPixmap(this->dst);
    emit (pixMsg( pixEnhance ));
    // stop 
    stop(); 
}


void ImageEnhanceWorker::ColorXEnhanceCpu(cv::Mat & src, cv::Mat & dst) {
    // Perform color enhancement
    Ptr<xphoto::SimpleWB> wb = xphoto::createSimpleWB();
    wb->balanceWhite(src, dst);
}


void ImageEnhanceWorker::run() {
    if (ThreadActive) {
        runEnhanceTask();
    }
}


void ImageEnhanceWorker::stop() {
    ThreadActive = false; 
    this->quit();
}

