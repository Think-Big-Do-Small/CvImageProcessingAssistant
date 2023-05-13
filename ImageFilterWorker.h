#ifndef IMAGE_FILTER_WORKER_H 
#define IMAGE_FILTER_WORKER_H

#include <opencv2/opencv.hpp>
#include <opencv2/xphoto.hpp>
#include <QPixmap>
#include <QThread> 

#include "QtImageFormatOpStack.h"

using namespace cv; 

class ImageFilterWorker : public QThread 
{
    Q_OBJECT

    public: 
    ImageFilterWorker(); 
    void runFilterTask(); 
    cv::Mat getDst() const; 
    void setSrc(cv::Mat src); 
    void setDst(cv::Mat dst); 
    void setFilterMethod(QString filterMethod);

    private: 
    bool ThreadActive; 
    cv::Mat src; 
    cv::Mat dst; 
    QString filterMethod;
    
    protected:
    void run() override; 

    signals:
    void pixMsg(QPixmap pix);

    private:
    void stop(); 
    void ColorReverseFilterCpu(cv::Mat & src, cv::Mat & dst);
}; 

#endif 
