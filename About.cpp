#include <QtWidgets> 
#include <QtGui> 
#include <QtCore> 

#include "About.h"

AboutWindow::AboutWindow() 
: QDialog() 
{
    this->initUi();
}


void AboutWindow::initUi() {
    this->setWindowTitle("关于软件"); 
    this->setFixedSize(800,600);

    helpTipsBrowser = new QTextBrowser(); 
    QString helpTxt = tr("<p><b>[软件许可]</b></p>\
        <p> - 本程序可供个人、企业、学校、政府机关等自由场合任意安装和使用.</p>\
        <p> - 凡使用本程序个人、企业、学校、政府机关等，即视为自动接受使用须知中全部条款.</p>\
        <p><b>[使用须知]</b></p>\
        <p> - 本程序受著作权法和软件保护法的保护，除保护法条款中允许或非限制的范围以外，任何人对本程序进行的逆向工程、反编译、重新组装都将被视为违法.</p>\
        <p> - 除任何人所在国法律条款中允许或非限制的范围以外，任何使用本程序行为都将被视为违法.</p>\
        <p> - 本程序未经著作权人许可绝对禁止用于其他商业用途.</p>\
        <p> - 本程序著作权归 文方俊 个人所有.</p>\
        ");

    helpTipsBrowser->setText(helpTxt);
    helpTipsBrowser->setReadOnly(true); 
    
    QVBoxLayout *vbox = new QVBoxLayout; 
    vbox->addWidget(helpTipsBrowser, 1); 
    this->setLayout(vbox);

    //this->layout()->addWidget(helpTipsBrowser); 

}