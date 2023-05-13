
#include <QtWidgets/QDialog> 
#include <QtWidgets/QTextBrowser>


class AboutWindow : public QDialog  
{
    public: 
    AboutWindow(); 

    void initUi(); 

    private: 
    QTextBrowser * helpTipsBrowser;

}; 