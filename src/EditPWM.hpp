#ifndef EDITPWMWINDOW_H
#define EDITPWMWINDOW_H

#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QDialog>
#include <QScrollArea>
#include <QGridLayout>

#include <vector>

#include "EditAbstract.hpp"
#include "PWM.hpp"

class EditPWMwindow: public EditAbstract
{
Q_OBJECT
public:
    EditPWMwindow();
    virtual void open(void) override;
    virtual void saveAs(void) override;
    virtual void save(void) override;
    virtual void refresh(void) override;
	virtual void add(void) override;
	virtual void remove(void) override;
private:
    void resize(size_t const&);
	void setLayout();

private:
    std::vector<QLineEdit*> mPWMentryLines;
    std::vector<QLabel*> mLineNumbers;
    QLineEdit *mEnterSize;
	QLineEdit *mAddLine;
	QLineEdit *mRemLine;
    QWidget *mViewport;

    QGridLayout *mEntryLayout;
    QVBoxLayout *mLayout;

    QString mSavePath;

    PWM mPWM;
};

#endif // EDITPWMWINDOW_H
