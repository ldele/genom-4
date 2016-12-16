#ifndef EDITABSTRACT_HPP
#define EDITABSTRACT_HPP

#include <QMainWindow>

class EditAbstract: public QMainWindow
{
Q_OBJECT
public:
    EditAbstract();
public slots:
    virtual void open(void) = 0;
    virtual void saveAs(void) = 0;
    virtual void save(void) = 0;
    virtual void refresh(void) = 0;
	virtual void add(void) = 0;
	virtual void remove(void) = 0;
protected:
    void setMenu(void);
    QString mPath = "../test/InputFiles";
};

#endif // EDITABSTRACT_HPP
