#ifndef QT_FILE_PATH_OP_STACK_H 
#define QT_FILE_PATH_OP_STACK_H

#include <QtCore/QStandardPaths>
#include <QCoreApplication>

QString getDesktopPath() {
    return QStandardPaths::writableLocation(QStandardPaths::DesktopLocation); 
}

QString getAppPath() {
    return QCoreApplication::applicationDirPath() ;
}

QString resourcePath(QString path) {
    return QFileInfo(path).canonicalPath() ; 
}

#endif 

