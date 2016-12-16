#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include <QApplication>
#include <QCloseEvent>
#include <QProcess>
#include "MainWindow.hpp"

MainWindow::MainWindow(): QMainWindow()
{
    mCWidget = new Ui::window();
    this->setCentralWidget(mCWidget);
    setMenu();

    QObject::connect(this, SIGNAL(exit()), qApp, SLOT(quit()));
}

void MainWindow::setMenu(void)
{
    QMenu *File;
    File = menuBar()->addMenu("&File");
    QAction *quit = new QAction("&Quit", this);
    quit->setShortcut(tr("CTRL+Q"));
    QObject::connect(quit, SIGNAL(triggered()), this, SLOT(quit()));

    File->addActions({quit});
    this->addActions({quit});

    QMenu *Run;
    Run = menuBar()->addMenu("&Run");
    QAction *run = new QAction("&Run", this);
    run->setShortcut(tr("CTRL+R"));
    QObject::connect(run, SIGNAL(triggered()), mCWidget, SLOT(run()));

    Run->addActions({run});
    this->addActions({run});

    QMenu *Help;
    Help = menuBar()->addMenu("&Help");
    QAction *doc = new QAction("&Open Doxydoc", this);
    doc->setShortcut(tr("CTRL+D"));
    QObject::connect(doc, SIGNAL(triggered()), this, SLOT(openDoc()));

    Help->addActions({doc});
    this->addActions({doc});
}

void MainWindow::closeEvent (QCloseEvent *event)
{
    auto reply = QMessageBox::question( this, tr("Exit"), tr("Are you sure you want to exit ?"), QMessageBox::Cancel | QMessageBox::Yes);
    if (reply != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
    }
}

void MainWindow::quit(void)
{
    auto reply = QMessageBox::question( this, tr("Exit"), tr("Are you sure you want to exit ?"), QMessageBox::Cancel | QMessageBox::Yes);
    if (reply != QMessageBox::Yes) {
        emit exit();
    }
}

void MainWindow::openDoc(void)
{
    QProcess::startDetached("firefox https://www.google.ch/?hl=fr/");
}

