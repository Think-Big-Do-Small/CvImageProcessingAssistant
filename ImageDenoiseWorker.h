#ifndef IMAGE_DENOISE_WORKER_H
#define IMAGE_DENOISE_WORKER_H

#include <opencv2/opencv.hpp>
#include <opencv2/xphoto.hpp>
#include <QPixmap>
#include <QThread> 

#include "QtImageFormatOpStack.h"

using namespace cv; 

class ImageDenoiseWorker : public QThread 
{
    Q_OBJECT
    
    public: 
    ImageDenoiseWorker(); 
    void runDenoiseTask (); 
    cv::Mat getDst() const; 
    void setSrc(cv::Mat src); 
    void setDst(cv::Mat dst); 
    void setDenoiseMethod(QString denoiseMethod);
    void ColorDenoisingBilateralExtraCpu(cv::Mat & src, cv::Mat & dst, int d, double sigmaColor, double sigmaSpace);

    private: 
    bool ThreadActive; 
    cv::Mat src; 
    cv::Mat dst; 
    QString denoiseMethod;


    protected:
    void run() override; 

    signals:
    void pixMsg(QPixmap pix);

    private:
    void stop(); 
    void ColorDenoisingXMethodCpu(cv::Mat & src, cv::Mat & dst);
    void ColorDenoisingBilateralCpu(cv::Mat & src, cv::Mat & dst);
    
}; 

#endif 
