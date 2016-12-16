#ifndef WINDOW_H
#define WINDOW_H

#include<QWidget>
#include<QPushButton>
#include<QCheckBox>
#include<QLineEdit>

#include "EditPWM.hpp"
#include "EditDNA.hpp"
#include "Interface.hpp"

namespace Ui {

class ShowOutput;

class window: public QWidget
{
Q_OBJECT
public:
    explicit window();
	QString const getOutputFile();
public slots:
    void DNAButtonSlot(void);
    void PWMButtonSlot(void);
	void OutButtonSlot(void);

    void SOBDisable(void);
    void editPWM(void);
    void editDNA(void);
    void printOutput(void);
    void run(void);

private:
    void setNames(void);
    void createLayout(void);
	void editLine(QLineEdit*, QString const&);

private:
    QPushButton *mDNAInitButton;
    QPushButton *mPWMInitButton;
	QPushButton *mOutInitButton;
    QPushButton *mShowOutputButton;
    QPushButton *mRunButton;
    QPushButton *mEditPWMButton;
    QPushButton *mEditDNAButton;

	QCheckBox *mWriteOutput;
	QCheckBox *mDefThrCheckBox;
    QCheckBox *mOpenOutputCheckBox;

    QLineEdit *mDNALine;
    QLineEdit *mPWMLine;
	QLineEdit *mOutLine;
	QLineEdit *mThrLine;

    EditPWMwindow mPWMeditWindow;
    EditDNAwindow mDNAeditWindow;
    QString mPath = "../InputFiles";
	QString mOutPath = "../OutputFiles";

    Interface mApp1;
};

}

#endif // WINDOW_H
