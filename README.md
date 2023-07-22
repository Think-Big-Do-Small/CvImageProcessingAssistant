# CvImageProcessingAssistant
### Image Processing Assistant with OpenCV Toolkit.

![GithubHeader](https://user-images.githubusercontent.com/37477845/92315782-e1255d80-f025-11ea-80e0-e62fc08c7a1e.gif)
# CvImageProcessingAssistant
NOTES. <br><br>
Run Programs with CMake, OpenCV 4.7.0 and Visual Studio 2019. 

# Download 
- [快乐图像下载](https://github.com/Think-Big-Do-Small/CvImageProcessingAssistant/releases/download/v1.0/JoyfulImage-v1.0-x86-x64-setup.exe)
  
# QT_IMAGE_FORMAT_CONVERT
```bash 
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
```

- Release Version - [CvImageProcessingAssistant](https://github.com/Think-Big-Do-Small/CvImageProcessingAssistant/tree/main/Release)

- Demo 1 : enhance image 
- ![GithubHeader](https://github.com/Think-Big-Do-Small/CvImageProcessingAssistant/blob/main/demos/test_demo.gif) <br>
- Demo 2 : denoise image 
- ![GithubHeader](https://github.com/Think-Big-Do-Small/CvImageProcessingAssistant/blob/main/demos/test_denoise_demo.gif)




### CvImageProcessingAssistant NOTES  
- CvImageProcessingAssistant - [CvImageProcessingAssistant](https://github.com/Think-Big-Do-Small/CvImageProcessingAssistant/blob/main/main.cpp)
```bash

#include <iostream>
#include "mainwindow.h"

#include <QApplication>


int main(int argc, char* argv[]) {
    QApplication app(argc,argv); 
    MainWindow mainwindow; 
    mainwindow.show(); 
    return app.exec();
}



```

### About Me 
- Computer Science, Master, Shenzhen University
- I am a software engineer 
- I am familar with computer languages, like c++,java,python,c,matlab,html,css,jquery
- I am familar with databases such as mysql, postgresql
- I am familar with flask, apache tomcat
- I am familar with libraries qt, opencv, caffe, keras, tensorflow, openvino
- I am familar with gpu libraries like cuda, cudnn
- I am recently doing some image segmentation projects with c++, python and cuda background matting etc. <br> 

### About Software Development Experience
- 图像数据集多边形标注助手 - [ImageMaskLabelAssistant](https://github.com/Think-Big-Do-Small/ImageMaskLabelAssistant)
- CvImageProcessingAssistant - [CvImageProcessingAssistant](https://github.com/Think-Big-Do-Small/CvImageProcessingAssistant) <br>
- Cuda-OpenCV-Object-Detection-Demo - [CvImageProcessingAssistant](https://github.com/Think-Big-Do-Small/Cuda-OpenCV-Object-Detection-Demo)<br> 
- RabbitRun(smart file packaging with high speed and efficiency)  <br> 
visit site: www.aizaozhidao.vip/tuzikuaipao 
- AI早知道(ai related projects for demostration) <br> 
visit site: www.aizaozhidao.vip 

