#ifndef QT_IMAGE_FORMAT_OP_STACK_H
#define QT_IMAGE_FORMAT_OP_STACK_H

#include <opencv2/opencv.hpp> 

using namespace cv; 


class ImageFormatOpStack {
    public: 
    static ImageFormatOpStack& GetInstance() { 
        static ImageFormatOpStack m_instance;
        return m_instance;
        }
    ImageFormatOpStack(ImageFormatOpStack const&) = delete;
    void operator=(ImageFormatOpStack const&) = delete;

    protected:
    ImageFormatOpStack() {};

    public:
    QPixmap Mat2QPixmap(cv::Mat const& src); 
    cv::Mat QPixmap2Mat(QPixmap const& pix); 
    QImage Mat2QImage(cv::Mat const& src);
    cv::Mat QImage2Mat(QImage const& src);
    
};

#endif 

