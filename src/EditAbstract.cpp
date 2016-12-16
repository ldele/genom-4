#include "EditAbstract.hpp"

#include <QMenuBar>
#include <QAction>

EditAbstract::EditAbstract() : QMainWindow()
{
    setMenu();
}

void EditAbstract::setMenu(void)
{
    QAction *open = new QAction("&Open File", this);
    QAction *save = new QAction("&Save", this);
    QAction *saveAs = new QAction("&Save As...", this);
    QAction *quit = new QAction("&Quit", this);

    QMenu *file;
    file = menuBar()->addMenu("&File");

    open->setShortcut(tr("CTRL+O"));
    save->setShortcut(tr("CTRL+S"));
    quit->setShortcut(tr("CTRL+Q"));

    QObject::connect(quit, SIGNAL(triggered()), this, SLOT(close()));
    QObject::connect(save, SIGNAL(triggered()), this, SLOT(save()));
    QObject::connect(saveAs, SIGNAL(triggered()), this, SLOT(saveAs()));
    QObject::connect(open, SIGNAL(triggered()), this, SLOT(open()));

    file->addActions({open, save, saveAs, quit});

	QAction *add = new QAction("&Add", this);
	QAction *remove = new QAction("&Remove", this);

	QMenu *edit;
	edit = menuBar()->addMenu("&Edit");

	add->setShortcut(tr("CTRL+M"));
	add->setShortcut(tr("CTRL+R"));

	QObject::connect(add, SIGNAL(triggered()), this, SLOT(add()));
	QObject::connect(remove, SIGNAL(triggered()), this, SLOT(remove()));

	edit->addActions({add, remove});
	this->addActions({open, save, saveAs, quit, remove, add});
}
