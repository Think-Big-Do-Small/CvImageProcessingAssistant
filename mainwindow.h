#ifndef MAINWINDOW_H 
#define MAINWINDOW_H

#include <QMainWindow> 
#include <QtWidgets/QLabel>
#include <QtCore/QObject>
#include <QtWidgets/QActionGroup>
#include <QtWidgets/QLineEdit>

#include "QtDragWidgetOpStack.h"
#include "About.h"
#include "ImageEnhanceWorker.h"
#include "ImageDenoiseWorker.h"
#include "ImageFilterWorker.h"


class MainWindow : public QMainWindow 
{
    public:
    MainWindow(); 

    void initUi();

    private: 
    //QLabel * picLbl; 
    QTabWidget *tabWidget;
    QtDragQLabel * picLbl;
    QString imagePath;
    QLineEdit *num1Edit; 
    QLineEdit *num2Edit; 
    QLineEdit *num3Edit;
    bool isTabShrink;

    // About 
    AboutWindow * aboutwindow;
    
    ImageEnhanceWorker * enhanceWorker; 
    ImageDenoiseWorker * denoiseWorker; 
    ImageFilterWorker * filterWorker;
    

    public slots:
    void updateDragMsg(QString msg); 
    void updatePixMsg(QPixmap msg);
    void updateBilateralExtraMsg();
    void updateTabDoubleClickedMsg(int index);

    private slots:
    void open(); 
    void save(); 
    void about();
    void close();
    void enhanceXMethod();
    void denoiseXMethod();
    void denoiseBilateral(); 
    void filterReverseMethod(); 

    private:
    void createActions(); 
    void createMenus(); 

    QMenu * fileMenu; 
    QMenu * denoiseMenu; 
    QMenu * enhanceMenu; 
    QMenu * filterMenu; 
    QMenu * helpMenu; 
    QActionGroup *alignmentGroup;
    QAction *openAct; 
    QAction *saveAct; 
    QAction *aboutAct;
    QAction *closeAct;
    QAction *enhanceXMethodAct;
    QAction *denoiseXMethodAct;
    QAction *denoiseBilateralAct;
    QAction *filterReverseMethodAct; 

  

}; 

/* https://doc.qt.io/qt-5/all-examples.html */

#endif

