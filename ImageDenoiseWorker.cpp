#include <iostream>
#include <QtWidgets>
#include <QtCore> 
#include <QtGui> 

#include "ImageDenoiseWorker.h" 

using namespace std; 

ImageDenoiseWorker::ImageDenoiseWorker() 
: QThread() 
{
    ThreadActive = true; 
}

void ImageDenoiseWorker::setSrc(cv::Mat src) {
    this->src = src; 
}

void ImageDenoiseWorker::setDst(cv::Mat dst) {
    this->dst = dst; 
}

void ImageDenoiseWorker::setDenoiseMethod(QString denoiseMethod) {
    this->denoiseMethod = denoiseMethod; 
}

cv::Mat ImageDenoiseWorker::getDst() const {
    return this->dst; 
}

void ImageDenoiseWorker::runDenoiseTask () {
    // Perform color denoise
    if (this->denoiseMethod == "X_METHOD") {
        ColorDenoisingXMethodCpu(this->src,this->dst);
    } 
    if (this->denoiseMethod == "BILATERAL_METHOD") {
        ColorDenoisingBilateralCpu(this->src,this->dst);
    }

    QPixmap pixDenoised = ImageFormatOpStack::GetInstance().Mat2QPixmap(this->dst);
    emit (pixMsg( pixDenoised ));
    // stop 
    stop(); 
}

void ImageDenoiseWorker::ColorDenoisingBilateralCpu(cv::Mat & src, cv::Mat & dst) {
    cv::bilateralFilter(src,dst,20,60,20);  /* 15 20 20; 15,50,20; 15,30,20 */
}

void ImageDenoiseWorker::ColorDenoisingBilateralExtraCpu(cv::Mat & src, cv::Mat & dst, int d, double sigmaColor, double sigmaSpace) {
    cv::bilateralFilter(src, dst, d, sigmaColor, sigmaSpace);
}

void ImageDenoiseWorker::ColorDenoisingXMethodCpu(cv::Mat & src, cv::Mat & dst) {
    cv::Mat noisyImageYCrCb;
    cv::cvtColor(src, noisyImageYCrCb, cv::COLOR_BGR2YCrCb);

    cv::Mat denoisedImageYCrCb;
    cv::xphoto::dctDenoising(noisyImageYCrCb, denoisedImageYCrCb, 10, 10);

    cv::cvtColor(denoisedImageYCrCb, dst, cv::COLOR_YCrCb2BGR);
}

void ImageDenoiseWorker::run() {
    if (ThreadActive) {
        runDenoiseTask();
    }
}

void ImageDenoiseWorker::stop() {
    ThreadActive = false; 
    this->quit();
}

