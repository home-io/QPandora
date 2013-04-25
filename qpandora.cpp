#include "qpandora.h"
#include "ui_qpandora.h"
#include <QtGui>


QPandora::QPandora(QWidget *parent) :
    QWidget(parent,Qt::FramelessWindowHint | Qt::WindowSystemMenuHint)
    ,ui(new Ui::QPandora)
{
    ui->setupUi(this);
    QCoreApplication::setOrganizationName("QtPandora");
    QCoreApplication::setOrganizationDomain("gminitv.no-ip.org");
    QCoreApplication::setApplicationName("QtPandora");
    process = new QProcess(this);
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(appendedText()));
    doConnect();

/*  do button magic  */
    ButtonMagic();

}
QPandora::~QPandora()
{
    delete ui;
}

void QPandora::ButtonMagic()
{
    QPixmap playmask(":/button_play_up.png");
    QPixmap skipmask(":/button_skip_up.png");
    QPixmap lovemask(":/button_love_up.png");
    QPixmap hatemask(":/button_hate_up.png");
    QPixmap changemask(":/button_change_up.png");
    QPixmap quitmask(":/button_quit_up.png");
    QPixmap titlemask(":/qpandora_title.png");
/*****************************************************************************************************************************/
    playmask = playmask.scaled(50,50,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    skipmask = skipmask.scaled(50,50,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    lovemask = lovemask.scaled(50,50,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    hatemask = hatemask.scaled(50,50,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    changemask = changemask.scaled(125,50,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    quitmask = quitmask.scaled(50,50,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    titlemask = titlemask.scaled(150,50,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
/*****************************************************************************************************************************/
    ui->btnPlay->setMask(playmask.mask());
    ui->btnSkip->setMask(skipmask.mask());
    ui->btnTup->setMask(lovemask.mask());
    ui->btnTdown->setMask(hatemask.mask());
    ui->btnChange->setMask(changemask.mask());
    ui->btnExit->setMask(quitmask.mask());
    ui->qpandora_title->setMask(titlemask.mask());
/*****************************************************************************************************************************/
    iconPlayUP.addFile(QString::fromUtf8(":/button_play_up.png"), QSize(), QIcon::Normal, QIcon::Off);
    iconSkipUP.addFile(QString::fromUtf8(":/button_skip_up.png"), QSize(), QIcon::Normal, QIcon::Off);
    iconLoveUP.addFile(QString::fromUtf8(":/button_love_up.png"), QSize(), QIcon::Normal, QIcon::Off);
    iconBanUP.addFile(QString::fromUtf8(":/button_hate_up.png"), QSize(), QIcon::Normal, QIcon::Off);
    iconChangeUP.addFile(QString::fromUtf8(":/button_change_up.png"), QSize(), QIcon::Normal, QIcon::Off);
    iconQuitUP.addFile(QString::fromUtf8(":/button_quit_up.png"), QSize(), QIcon::Normal, QIcon::Off);
    iconTitle.addFile(QString::fromUtf8(":/qpandora_title.png"), QSize(), QIcon::Normal, QIcon::Off);
/*****************************************************************************************************************************/
    ui->btnPlay->setIcon(iconPlayUP);
    ui->btnSkip->setIcon(iconSkipUP);
    ui->btnTup->setIcon(iconLoveUP);
    ui->btnTdown->setIcon(iconBanUP);
    ui->btnChange->setIcon(iconChangeUP);
    ui->btnExit->setIcon(iconQuitUP);
    ui->qpandora_title->setIcon(iconTitle);
/*****************************************************************************************************************************/
    ui->btnPlay->setIconSize(QSize(50, 50));
    ui->btnSkip->setIconSize(QSize(50, 50));
    ui->btnTup->setIconSize(QSize(50, 50));
    ui->btnTdown->setIconSize(QSize(50, 50));
    ui->btnChange->setIconSize(QSize(125, 50));
    ui->btnExit->setIconSize(QSize(50, 50));
    ui->qpandora_title->setIconSize(QSize(150, 50));
}

void QPandora::UpdateConnectStatus()
{
    /****************************************************************
    Check to see if our process is running and then store its state
    as a publicly declared QString to be used throughout our appli-
    -cation to determine running status.
    *****************************************************************/
        if(process->state()==QProcess::Running)
            {
                constatus = "Running";
            }
        else
            {
                constatus = "Not Running";
            }

}
void QPandora::loadSettings()
{

}
void QPandora::saveSettings()
{

}
void QPandora::doPlay()
{
    UpdateConnectStatus();
    if(constatus == "Running")
    {
        if(songstat == "playing")
        {
            songstat = "stopped";
        }
    }
    else
    {
      songstat = "playing";

        /*if(ui->btnPlay->text() == "")
            {
                ui->btnPlay->setText("");
            }
        else
            {
                ui->btnPlay->setText("");
            }
            */
    }
    process->write("p");
    process->write("\n");
}
void QPandora::doPause()
{

}
void QPandora::doNext()
{
    if(constatus == "Running")
        {
              if(songstat == "playing")
                  {
        process->write("n");
        process->write("\n");
                  }
        }
    process->write("n");
    process->write("\n");
    /*
    else show msg song not playing
    */
}
void QPandora::doLove()
{
    UpdateConnectStatus();
    if(constatus == "Running")
        {
        process->write("+");
        process->write("\n");
        }
}
void QPandora::doBan()
{
    UpdateConnectStatus();
    if(constatus == "Running")
        {
        process->write(qPrintable("-"));
        process->write("\n");
        }
}
void QPandora::doTimeOut()
{
    UpdateConnectStatus();
    if(constatus == "Running")
        {
        process->write("t");
        process->write("\n");
        }
}
void QPandora::doInfo()
{

}
void QPandora::exitProgram()
{
    /* Add do while loop */
    /****************************************************************
    To ensure the program "pianobar" , which our process has started,
    doesn't continue running after we've exited we can simply send our
    process the "q" character. This is the command pianobar expects
    when a user wishes to terminate it from memory.
    *****************************************************************/
    UpdateConnectStatus();
    if(constatus == "Running")
    {
    process->write("q");
    /*writing "\n" to the process input is synonymous
    to a user hitting the enter key while typing on
    a terminal*/
    process->write("\n");
    }
    else
        {
        exit(0);
        }

}
void QPandora::appendedText()
{
    QString pdata = process->readAll();
  if(pdata != oldstring)
    {
        pdata = pdata.mid(4);
        ui->txtFeed->append(qPrintable(pdata));
   /*ui->textEdit->append(process->readAll());*/
        oldstring = pdata;
    }

}
void QPandora::doConnect()
{

    /*declare a QString to hold our user commands to
      be sent to our process*/
    QString str_command;
    /*
    process = new QProcess(this);
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(appendedText()));
    */
    ui->txtFeed->clear();
    str_command = "pianobar";
    /*start our process "bin/bash" and send it the name of our
      application we will be controlling from this front end GUI*/
    process->start("/bin/bash", QStringList() << "-c" << QString(str_command));
    /*create QSettings object named settings, request user
      password, pass Pandora login information to pianobar*/
    UpdateConnectStatus();
    getUSR();
/****              process->write(qPrintable(settings.value("account/email").toString()));                   ***/
    process->write(qPrintable(usrname));
    process->write("\n");
    getPASS();
    process->write(qPrintable(passw));
    process->write("\n");
    doChangeStation();
}
void QPandora::doDConnect()
{
    process->write("q");
    process->write("\n");
    UpdateConnectStatus();
}
void QPandora::doCreateStation()
{

}
void QPandora::doChangeStation()
{

    if(songstat!="playing")
     {
        process->write("s");
        process->write("\n");
     }
        process->write("s ");
        process->write("\n");
        bool ok;
        QString text = QInputDialog::getText(this, ("QInputDialog::getText"),
                                             ("Station:"), QLineEdit::Normal,
                                             "number", &ok);
        if (ok && !text.isEmpty())
            station = text;
        process->write(qPrintable(station));
        process->write("\n");
        ui->btnPlay->setText("");
        songstat = "playing";

}
void QPandora::getUSR()
{
    /****************************************************************
        This function displays a dialog box to our user requesting
        the users password.
    *****************************************************************/
        /*create a boolean variable to check if user clicks ok*/
        bool ok;
        /*create a string to store user input from dialog and
          set the dialog box's type, title, and initial text*/
        QString text = QInputDialog::getText(this, ("QInputDialog::getText"),
                                             ("Email:"), QLineEdit::Normal,
                                             "Email", &ok);
        /*if user clicks ok then store user input as standard
          printable text using qPrintable(QString);*/
        if (ok && !text.isEmpty())
            usrname = qPrintable(text);
        /*passw is declared as a public variable in mainwindow.h*/
}
void QPandora::getPASS()
{
    /****************************************************************
        This function displays a dialog box to our user requesting
        the users password.
    *****************************************************************/
        /*create a boolean variable to check if user clicks ok*/
        bool ok;
        /*create a string to store user input from dialog and
          set the dialog box's type, title, and initial text*/
        QString text = QInputDialog::getText(this, ("QInputDialog::getText"),
                                             ("Password:"), QLineEdit::Normal,
                                             "password", &ok);
        /*if user clicks ok then store user input as standard
          printable text using qPrintable(QString);*/
        if (ok && !text.isEmpty())
            passw = qPrintable(text);
        /*passw is declared as a public variable in mainwindow.h*/
}

void QPandora::on_btnPlay_clicked()
{
    doPlay();
}

void QPandora::on_btnSkip_clicked()
{
    doNext();
}

void QPandora::on_btnChange_clicked()
{
    doChangeStation();
}

void QPandora::on_btnTup_clicked()
{
    doLove();
}

void QPandora::on_btnTdown_clicked()
{
    doTimeOut();
}

void QPandora::on_btnKill_clicked()
{
    doBan();
}

void QPandora::on_btnExit_clicked()
{
    exitProgram();
}

void QPandora::on_btnUPdown_clicked()
{
    /*implement roll up minimal view just btns*/
}



void QPandora::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void QPandora::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}

