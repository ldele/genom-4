#include <QApplication>
#include <QDesktopWidget>

#include "MainWindow.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
	w.move(QApplication::desktop()->screen()->rect().center() - w.rect().center());
    w.show();
    return app.exec();
}
