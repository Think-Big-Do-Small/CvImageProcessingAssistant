
#include <QtWidgets>
#include <QtCore> 
#include <QtGui> 

#include "QtImageFormatOpStack.h"

QImage ImageFormatOpStack::Mat2QImage(cv::Mat const& src)
{
    if (3 != src.channels()) return QImage();
     cv::Mat temp; 
     cvtColor(src, temp,cv::COLOR_BGR2RGB); 
     QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
     dest.bits(); 
     return dest;
}

cv::Mat ImageFormatOpStack::QImage2Mat(QImage const& src)
{
    QImage img = src.convertToFormat(QImage::Format_RGB888, Qt::ColorOnly).rgbSwapped();
    return cv::Mat(img.height(), img.width(), CV_8UC3, img.bits(), img.bytesPerLine()).clone();
}

QPixmap ImageFormatOpStack::Mat2QPixmap(cv::Mat const& src) {
    return QPixmap::fromImage(Mat2QImage(src));
}

cv::Mat ImageFormatOpStack::QPixmap2Mat(QPixmap const& pix) {
    return QImage2Mat(pix.toImage());
}

