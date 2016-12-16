#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include "Window.hpp"

namespace Ui
{
    class window;
}

class MainWindow: public QMainWindow
{
Q_OBJECT
public:
    explicit MainWindow();
signals:
    void exit();
public slots:
    void quit(void);
    void openDoc(void);
private:
    void closeEvent(QCloseEvent*);
    void setMenu(void);
private:
    Ui::window *mCWidget;
};

#endif // MAINWINDOW_HPP
