
#include <QtWidgets/QLabel> 
//#include <QtCore/QObject>

class QtDragQLabel : public QLabel
{
    Q_OBJECT

    public: 
    QtDragQLabel(QLabel *parent = nullptr); 
    QString convertUrlToNativeFilePath(const QUrl& urlStylePath) const;

    signals: 
    void dragMsg(QString msg); 

    protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    //void dragMoveEvent(QDragMoveEvent *event) override;
    //void dragLeaveEvent(QDragLeaveEvent *event) override;


    
};

