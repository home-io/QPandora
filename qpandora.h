#ifndef QPANDORA_H
#define QPANDORA_H

#include <QWidget>
#include <QSplashScreen>
#include <QMainWindow>
#include <QProcess>
#include <QInputDialog>
#include <QSettings>
#include <QDir>
#include <QVariant>
#include <QStyle>
#include <QStyleFactory>
#include <QStringList>
#include <QPoint>
#include <QMouseEvent>

#include <QBitmap>
#include <QPixmap>
#include <QTransform>
#include <QIcon>


namespace Ui {
class QPandora;
class QProcess;
}

class QPandora : public QWidget
{
    Q_OBJECT

public:
    explicit QPandora(QWidget *parent = 0);
    ~QPandora();
    QProcess *process;
    void getPASS();
    void getUSR();
    QString passw;
    QString usrname;
    QString constatus;
    QString station;
    QString oldstring;
    QSettings settings;
    QString songstat;
    void ButtonMagic();

    QIcon iconPlayUP;
    QIcon iconPlayDOWN;

    QIcon iconSkipUP;
    QIcon iconSkipDOWN;
    QIcon iconLoveUP;
    QIcon iconChangeUP;
    QIcon iconBanUP;
    QIcon iconQuitUP;

    QIcon iconTitle;

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    QPoint dragPosition;
private:
    void loadSettings();
    void saveSettings();
    void UpdateConnectStatus();
    void doPlay();
    void doPause();
    void doNext();
    void doLove();
    void doBan();
    void doTimeOut();
    void doInfo();
    void doConnect();
    void doDConnect();
    void doChangeStation();
    void doCreateStation();

protected:


private slots:
    void appendedText();
    void exitProgram();
    void on_btnPlay_clicked();
    void on_btnSkip_clicked();
    void on_btnChange_clicked();
    void on_btnTdown_clicked();
    void on_btnTup_clicked();
    void on_btnKill_clicked();
    void on_btnExit_clicked();
    void on_btnUPdown_clicked();

private:
    Ui::QPandora *ui;
    QPoint offset;
    bool moving;
};

#endif // QPANDORA_H
