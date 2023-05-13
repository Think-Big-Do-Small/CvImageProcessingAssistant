#ifndef IMAGE_ENHANCE_WORKER_H 
#define IMAGE_ENHANCE_WORKER_H

#include <opencv2/opencv.hpp>
#include <opencv2/xphoto.hpp>
#include <QPixmap>
#include <QThread> 

#include "QtImageFormatOpStack.h"

using namespace cv; 

class ImageEnhanceWorker : public QThread 
{
    Q_OBJECT

    public: 
    ImageEnhanceWorker(); 
    void runEnhanceTask (); 
    cv::Mat getDst() const; 
    void setSrc(cv::Mat src); 
    void setDst(cv::Mat dst); 
    void setEnhanceMethod(QString enhanceMethod);

    private: 
    bool ThreadActive; 
    cv::Mat src; 
    cv::Mat dst; 
    QString enhanceMethod;


    protected:
    void run() override; 

    signals:
    void pixMsg(QPixmap pix);

    private:
    void stop(); 
    void ColorXEnhanceCpu(cv::Mat & src, cv::Mat & dst);
}; 

#endif 



