
#include <QtWidgets> 
#include <QtGui> 
#include <QtCore> 
#include <QtCore/QStandardPaths> 

#include "mainwindow.h" 
#include "QtFilePathOpStack.h"


MainWindow::MainWindow() : QMainWindow() {
    this->initUi();
    
    QObject::connect(picLbl, &QtDragQLabel::dragMsg,
                     this, &MainWindow::updateDragMsg);
                    

    
} 

void MainWindow::updatePixMsg(QPixmap msg) {
    if (!msg.isNull()) {
        picLbl->setPixmap(msg);
    }
}

void MainWindow::updateDragMsg(QString msg){
    if (msg != this->imagePath) {
        this->imagePath = msg;
    } 
    picLbl->setPixmap(QPixmap::fromImage(QImage(this->imagePath)));
    this->statusBar()->showMessage(this->imagePath);
} 

void MainWindow::updateTabDoubleClickedMsg(int index) {
    if (isTabShrink) {
        tabWidget->setFixedHeight(28);
    } else {
        tabWidget->setFixedHeight(80);
    }
    isTabShrink = !isTabShrink; 
}

void MainWindow::initUi() {
    this->setWindowTitle(tr("图像处理助手"));
    this->setMinimumSize(1600,1000);
    this->setWindowIcon(QIcon(QDir::currentPath() + "/icons/main.ico"));

    tabWidget = new QTabWidget(); 
    tabWidget->setFixedHeight(80);
    tabWidget->setMaximumWidth(800);
    connect(tabWidget, &QTabWidget::tabBarDoubleClicked, this, &MainWindow::updateTabDoubleClickedMsg);

    QWidget *denoiseWidget = new QWidget(); 
    QWidget *enhanceWidget = new QWidget();
    QWidget *filterWidget = new QWidget();
    tabWidget->addTab(denoiseWidget, tr("图像去噪")); 
    tabWidget->addTab(enhanceWidget, tr("图像增强")); 
    tabWidget->addTab(filterWidget, tr("图像滤镜")); 

    // denoise widget 
    QLabel *bilateralLbl = new QLabel;
    bilateralLbl->setText(tr("双边滤波"));
    bilateralLbl->setFixedSize(100,30); 

    QLabel *num1Hint = new QLabel; 
    QLabel *num2Hint = new QLabel; 
    QLabel *num3Hint = new QLabel; 

    num1Hint->setText(tr("参数1:"));
    num1Hint->setFixedSize(60,30); 

    num2Hint->setText(tr("参数2:"));
    num2Hint->setFixedSize(60,30); 

    num3Hint->setText(tr("参数3:"));
    num3Hint->setFixedSize(60,30); 

    num1Edit = new QLineEdit;
    num2Edit = new QLineEdit;
    num3Edit = new QLineEdit;

    num1Edit->setFixedSize(100,30);
    num2Edit->setFixedSize(100,30);
    num3Edit->setFixedSize(100,30);

    QPushButton *bilateralBtn = new QPushButton(); 
    bilateralBtn->setText(tr("运行"));
    bilateralBtn->setFixedSize(80,30); 
    connect(bilateralBtn, &QPushButton::clicked, this, &MainWindow::updateBilateralExtraMsg);

    QHBoxLayout *hbox1 = new QHBoxLayout(); 
    QHBoxLayout *hbox2 = new QHBoxLayout(); 
    QHBoxLayout *hbox3 = new QHBoxLayout(); 
    QHBoxLayout *hbox4 = new QHBoxLayout(); 
    hbox1->setAlignment(Qt::AlignLeft); 
    hbox2->setAlignment(Qt::AlignLeft); 
    hbox3->setAlignment(Qt::AlignLeft); 
    hbox1->setSpacing(0); hbox2->setSpacing(0); hbox3->setSpacing(0); 
    hbox1->setContentsMargins(0,0,0,0); hbox2->setContentsMargins(0,0,0,0); hbox3->setContentsMargins(0,0,0,0); 

    hbox1->addWidget(num1Hint); 
    hbox1->addWidget(num1Edit); 
    hbox2->addWidget(num2Hint); 
    hbox2->addWidget(num2Edit); 
    hbox3->addWidget(num3Hint); 
    hbox3->addWidget(num3Edit); 

    QHBoxLayout *hbox = new QHBoxLayout(); 
    hbox->setSpacing(0); hbox->setContentsMargins(0,0,0,0);
    hbox->setAlignment(Qt::AlignLeft);
    hbox->addWidget(bilateralLbl);
    hbox->addLayout(hbox1);
    hbox->addLayout(hbox2);
    hbox->addLayout(hbox3);
    hbox->addWidget(bilateralBtn);

    denoiseWidget->setLayout(hbox); 




    picLbl = new QtDragQLabel();
    picLbl->setStyleSheet("border:1px solid black;");
    picLbl->setMinimumSize(this->rect().size()); 
    //picLbl->setText("测试文本"); 
    picLbl->setScaledContents(false);
    picLbl->setAlignment(Qt::AlignCenter);

    // 
    aboutwindow = new AboutWindow(); 

    // enhance worker 
    enhanceWorker = new ImageEnhanceWorker(); 
    QObject::connect(enhanceWorker, &ImageEnhanceWorker::pixMsg, this, &MainWindow::updatePixMsg); 
    enhanceWorker->start(); 

    // denoise worker 
    denoiseWorker = new ImageDenoiseWorker(); 
    QObject::connect(denoiseWorker, &ImageDenoiseWorker::pixMsg, this, &MainWindow::updatePixMsg);
    denoiseWorker->start(); 

    // filter worker 
    filterWorker = new ImageFilterWorker(); 
    QObject::connect(filterWorker, &ImageFilterWorker::pixMsg, this, &MainWindow::updatePixMsg);
    filterWorker->start();
    

    QHBoxLayout * hbox_1st = new QHBoxLayout(); 
    QHBoxLayout * hbox_2nd = new QHBoxLayout();
    QVBoxLayout * vbox_1st = new QVBoxLayout(); 
    hbox_1st->setSpacing(0); 
    vbox_1st->setSpacing(0); 
    hbox_1st->setContentsMargins(0,0,0,0); 
    vbox_1st->setContentsMargins(0,0,0,0); 

    hbox_2nd->setAlignment(Qt::AlignLeft);

    hbox_2nd->addWidget(tabWidget);
    hbox_1st->addWidget(picLbl, 1); 

    QWidget * widget = new QWidget() ; 
    this->setCentralWidget(widget); 
    widget->setLayout(vbox_1st); 
    this->centralWidget()->setContentsMargins(0,0,0,0); 

    // create menus 
    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    
    
    vbox_1st->addWidget(topFiller); 
    vbox_1st->addLayout(hbox_2nd, 1); 
    vbox_1st->addLayout(hbox_1st, 1); 
    vbox_1st->addWidget(bottomFiller);

    createActions();
    createMenus();

}


void MainWindow::createActions() {
    QString currentPath = QDir::currentPath(); 
    
    openAct = new QAction(tr("打开")); 
    openAct->setIcon(QIcon(currentPath + "/icons/open.ico"));
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("打开图片"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);

    saveAct = new QAction(tr("保存")); 
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("保存图片"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);

    closeAct = new QAction(tr("关闭")); 
    closeAct->setIcon(QIcon(currentPath + "/icons/close.ico"));
    closeAct->setShortcuts(QKeySequence::Close); 
    closeAct->setStatusTip(tr("关闭软件")); 
    connect(closeAct, &QAction::triggered, this, &MainWindow::close);

    aboutAct = new QAction(tr("关于")); 
    aboutAct->setShortcuts(QKeySequence::WhatsThis);
    aboutAct->setStatusTip(tr("关于图像处理助手"));
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

    // enhance action 
    enhanceXMethodAct = new QAction(tr("X方法")); 
    enhanceXMethodAct->setStatusTip(tr("X图像增强"));
    connect(enhanceXMethodAct, &QAction::triggered, this, &MainWindow::enhanceXMethod);

    // denoise action 
    denoiseXMethodAct = new QAction(tr("X方法")) ;
    denoiseXMethodAct->setStatusTip(tr("X图像去噪")); 
    connect(denoiseXMethodAct, &QAction::triggered, this, &MainWindow::denoiseXMethod);

    denoiseBilateralAct = new QAction(tr("双边滤波")); 
    connect(denoiseBilateralAct, &QAction::triggered, this, &MainWindow::denoiseBilateral);

    // filter action 
    filterReverseMethodAct = new QAction(tr("反色")); 
    connect(filterReverseMethodAct, &QAction::triggered, this, &MainWindow::filterReverseMethod);



    alignmentGroup = new QActionGroup(this);
    alignmentGroup->addAction(openAct);
    alignmentGroup->addAction(saveAct);
    alignmentGroup->addAction(closeAct);
    alignmentGroup->addAction(aboutAct);
    alignmentGroup->addAction(enhanceXMethodAct);
    alignmentGroup->addAction(denoiseXMethodAct);
    alignmentGroup->addAction(denoiseBilateralAct);
    alignmentGroup->addAction(filterReverseMethodAct);
    aboutAct->setChecked(true);


}

void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&文件"));
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
    fileMenu->addAction(closeAct);

    denoiseMenu = menuBar()->addMenu(tr("&去噪"));
    denoiseMenu->addAction(denoiseXMethodAct);
    denoiseMenu->addSeparator();
    denoiseMenu->addAction(denoiseBilateralAct); 
    denoiseMenu->addSeparator();


    enhanceMenu = menuBar()->addMenu(tr("&增强"));
    enhanceMenu->addAction(enhanceXMethodAct);
    enhanceMenu->addSeparator();


    filterMenu = menuBar()->addMenu(tr("&滤镜"));
    filterMenu->addAction(filterReverseMethodAct); 
    filterMenu->addSeparator(); 
    

    helpMenu = menuBar()->addMenu(tr("&关于"));
    helpMenu->addAction(aboutAct);
    helpMenu->addSeparator();
    helpMenu->addAction(aboutAct);
    helpMenu->addSeparator();

    

}


void MainWindow::updateBilateralExtraMsg() {
    /* 图像去噪Bilateral带参数方法 */
    const QPixmap *pixmap = picLbl->pixmap(); 
    if (0 == pixmap) return; 

    int d = num1Edit->text().toInt();
    double sigmaColor = num2Edit->text().toDouble(); 
    double sigmaSpace = num3Edit->text().toDouble(); 

    cv::Mat src = ImageFormatOpStack::GetInstance().QPixmap2Mat(*pixmap);
    cv::Mat dst; 
    denoiseWorker->ColorDenoisingBilateralExtraCpu(src,dst,d,sigmaColor,sigmaSpace);

    QPixmap pix = ImageFormatOpStack::GetInstance().Mat2QPixmap(dst); 
    picLbl->setPixmap(pix);
}


void MainWindow::open() {
    qDebug()<<"打开图片";
    QString desktop = getDesktopPath();  
    QString picPath = QFileDialog::getOpenFileName(this, "打开图片", desktop, "图片文件 (*.jpg *.jpeg *.png *.bmp *.jpeg);;PNG图片(*.png);;JPG图片(*.jpg);;BMP图片(*.bmp)");
    if (0 == picPath.length()){
        return;
    }
    
    picLbl->setPixmap(QPixmap::fromImage(QImage(picPath))); 
    statusBar()->showMessage(picPath);    
}

void MainWindow::save() {
    qDebug()<<"保存图片";
    const QPixmap *pix = picLbl->pixmap();
    if (0 == pix) return; 
    QString desktop = getDesktopPath() + "/untitled";    
    QString pixPath = QFileDialog::getSaveFileName(this, "保存图片", desktop, "图片文件 (*.jpg *.jpeg *.png *.bmp *.jpeg);;PNG图片(*.png);;JPG图片(*.jpg);;BMP图片(*.bmp)");
    (*pix).save(pixPath);
} 

void MainWindow::about() {
    qDebug()<<"关于软件";
    aboutwindow->exec();
}

void MainWindow::close() {
    qDebug()<<"关闭软件";
    QApplication::quit();
}


void MainWindow::enhanceXMethod() {
    /* 图像增强X方法 */
    const QPixmap *pixmap = picLbl->pixmap();
    if (0 == pixmap) return; 

    cv::Mat src = ImageFormatOpStack::GetInstance().QPixmap2Mat(*pixmap);
    cv::Mat dst; 
    
    enhanceWorker->setSrc(src); 
    enhanceWorker->setDst(dst); 
    enhanceWorker->setEnhanceMethod("X_METHOD");    
    enhanceWorker->runEnhanceTask();
}

void MainWindow::denoiseXMethod() {
    /* 图像去噪X方法 */
    const QPixmap *pixmap = picLbl->pixmap();
    if (0 == pixmap) return; 

    cv::Mat src = ImageFormatOpStack::GetInstance().QPixmap2Mat(*pixmap);
    cv::Mat dst; 

    denoiseWorker->setSrc(src); 
    denoiseWorker->setDst(dst); 
    denoiseWorker->setDenoiseMethod("X_METHOD");
    denoiseWorker->runDenoiseTask();
}

void MainWindow::denoiseBilateral() {
    /* 图像去噪Bilateral方法 */
    const QPixmap *pixmap = picLbl->pixmap(); 
    if (0 == pixmap) return; 

    cv::Mat src = ImageFormatOpStack::GetInstance().QPixmap2Mat(*pixmap);
    cv::Mat dst; 

    denoiseWorker->setSrc(src); 
    denoiseWorker->setDst(dst); 
    denoiseWorker->setDenoiseMethod("BILATERAL_METHOD");
    denoiseWorker->runDenoiseTask();
}

void MainWindow::filterReverseMethod() {
    /* 图像反色方法 */
    const QPixmap *pixmap = picLbl->pixmap(); 
    if (0 == pixmap) return; 

    cv::Mat src = ImageFormatOpStack::GetInstance().QPixmap2Mat(*pixmap);
    cv::Mat dst; 

    filterWorker->setSrc(src); 
    filterWorker->setDst(dst); 
    filterWorker->setFilterMethod("REVERSE_METHOD");
    filterWorker->runFilterTask();
}




