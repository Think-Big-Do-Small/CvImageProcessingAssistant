
#include <QtWidgets> 
#include <QtGui> 
#include <QtCore> 
#include <iostream> 

using namespace std; 

#include "QtDragWidgetOpStack.h"

QtDragQLabel::QtDragQLabel(QLabel *parent) : 
QLabel(parent) 
{
    setAcceptDrops(true);
}

QString QtDragQLabel::convertUrlToNativeFilePath(const QUrl& urlStylePath) const
{
    return QDir::toNativeSeparators(urlStylePath.toLocalFile());
}

void QtDragQLabel::dragEnterEvent(QDragEnterEvent * event){
    cout <<"Drag Enter"<<endl; 
    if (event->mimeData()->hasUrls()) {
        event->accept(); 
    } else {
        event->ignore(); 
    }
}

void QtDragQLabel::dropEvent(QDropEvent * event) {
    cout <<"Drop Event"<<endl; 

    //const QMimeData *mimeData = event->mimeData();
    //QList<QUrl> urlList = mimeData->urls();
    QList<QUrl>urlList;
    for (auto url : event->mimeData()->urls()) {
        urlList.append(url.toLocalFile());
    }

    for (int i=0;i<urlList.size();i++) {
        qDebug() << urlList.at(i).path();
    }

   
    QString image_path = "d:" + urlList.at(0).path();
    qDebug()<<image_path;

    cout <<"local 8bit -> "<<image_path.toLocal8Bit().constData()<<endl; 

    FILE * fp = fopen("d:/drag_test.txt", "w"); 
    fprintf(fp, "%s\n", image_path.toStdString().c_str());
    fclose(fp);

    QString currentPath = QDir::currentPath(); 
    qDebug()<<"Current Path -> "<< currentPath; 
    
    //qDebug()<<"disk name -> "<<convertUrlToNativeFilePath(urlList.at(0));



    emit ( dragMsg(image_path) );
}




