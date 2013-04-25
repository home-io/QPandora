#include <QApplication>
#include "qpandora.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPandora w;    
    QStyle *style=QStyleFactory::create("QtCurve");
    a.setStyle(style);
    QPixmap pixmap("/home/picuntu/QtProjects/QtPandora/splash.png");
    QSplashScreen splash(pixmap);
    splash.show();
    a.processEvents();
    splash.finish(&w);
    w.show();
    return a.exec();
}

void QSplashScreen::finish(QWidget *mainWin)
{
    if (mainWin) {
#if defined(Q_WS_X11)
        extern void qt_x11_wait_for_window_manager(QWidget *mainWin);
        qt_x11_wait_for_window_manager(mainWin);
#endif
    }
    close();
}
