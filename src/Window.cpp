#include "Window.hpp"

#include<QFileDialog>
#include<QMessageBox>
#include<QDialog>
#include<QLayout>
#include<QDesktopWidget>
#include<QTextStream>
#include<QTextBrowser>
#include<QApplication>
#include<QValidator>
#include<QLabel>
#include<stdexcept>

using namespace Ui;

window::window()	:QWidget()
{
    setNames();
    this->move(0, 0);
    QDesktopWidget screen;
    this->resize(screen.width()*0.5, screen.height()*0.1);
    this->setMinimumWidth(screen.width()*0.5);

    QObject::connect(mDNAInitButton, SIGNAL(clicked()), this, SLOT(DNAButtonSlot()));
    QObject::connect(mPWMInitButton, SIGNAL(clicked()), this, SLOT(PWMButtonSlot()));
	QObject::connect(mOutInitButton, SIGNAL(clicked()), this, SLOT(OutButtonSlot()));
    QObject::connect(mShowOutputButton, SIGNAL(clicked()), this, SLOT(printOutput()));
    QObject::connect(mRunButton, SIGNAL(clicked()), this, SLOT(run()));
    QObject::connect(mEditPWMButton, SIGNAL(clicked()), this, SLOT(editPWM()));
    QObject::connect(mEditDNAButton, SIGNAL(clicked()), this, SLOT(editDNA()));
	QObject::connect(mOutLine, SIGNAL(textChanged(QString)), this, SLOT(SOBDisable()));
    mShowOutputButton->setEnabled(false);
    mOpenOutputCheckBox->setChecked(false);
	mWriteOutput->setChecked(true);

    createLayout();
}

QString const window::getOutputFile()
{
	return mOutLine->text();
}

void window::DNAButtonSlot(void)
{
	editLine(mDNALine, tr("Text files(*.fasta *.fa)"));
}

void window::PWMButtonSlot(void)
{
	editLine(mPWMLine, tr("Text files(*.mat)"));
}
void window::OutButtonSlot(void)
{
	QString selectedFilePath = QFileDialog::getSaveFileName(this, "Select file", mOutPath, tr("Text files(*.fasta *.fa)"));
	if (!selectedFilePath.isEmpty()) {
		QMessageBox::information( 0, "Info", "You selected :\n" + selectedFilePath);
		mOutLine->setText(selectedFilePath);
		mOutPath = selectedFilePath;
	}
}

void window::editPWM(void)
{
	mPWMeditWindow.move(QApplication::desktop()->screen()->rect().center() - mPWMeditWindow.rect().center());
	mPWMeditWindow.show();
}

void window::editDNA(void)
{
	mDNAeditWindow.move(QApplication::desktop()->screen()->rect().center() - mDNAeditWindow.rect().center());
    mDNAeditWindow.show();
}

void window::SOBDisable(void)
{
    mShowOutputButton->setEnabled(false);
}

void window::printOutput(void)
{
	QFile file(getOutputFile());
	if(!file.open(QIODevice::ReadOnly)) {
		QMessageBox::information(this, "error", file.errorString());
	} else {
		QTextBrowser *txt = new QTextBrowser();
		QTextStream in(&file);
		txt->setText(in.readAll());
		txt->setWindowTitle("Output");

		file.close();
		QDesktopWidget screen;
		txt->resize(screen.width()*0.4, screen.height()*0.7);
		txt->move(screen.rect().center() - txt->rect().center());
		txt->show();
	}
}

void window::run(void)
{
	if (mDNALine->text().isEmpty() || mPWMLine->text().isEmpty()) {
		QMessageBox::information(this, tr("Error"), tr("You need to specify DNA and PWM files !"));
    } else {
		try {
			if (mDefThrCheckBox->isChecked()) {
				bool ok(false);
				double thr = mThrLine->text().toDouble(&ok);
				if (ok) {
					mApp1.setThreshold(thr);
				}
			} else {
				mApp1.setThreshToDefault();
			}
			mApp1.setDNA(mDNALine->text().toStdString());
			mApp1.setPWM(mPWMLine->text().toStdString());
			mApp1.setOut(mOutLine->text().toStdString());
			mApp1.output();
			if (mOpenOutputCheckBox->isChecked()) {
				printOutput();
			} else {
				QMessageBox::information(this, tr("Good !"), tr("Output Available !"));
			}
			mShowOutputButton->setEnabled(true);
		} catch(std::runtime_error msg) {
			QMessageBox::information(this, tr("Error"), QString(msg.what()));
		}
    }
}

void window::setNames(void)
{
    this->setWindowTitle("genom-4");

    mShowOutputButton = new QPushButton("Show Output");
    mDNAInitButton = new QPushButton("DNA");
    mPWMInitButton = new QPushButton("PWM");
	mOutInitButton = new QPushButton("Output");
    mRunButton = new QPushButton("Run");
    mEditPWMButton = new QPushButton("edit PWM");
    mEditDNAButton = new QPushButton("edit DNA");

	mWriteOutput = new QCheckBox("Write Ouput in File");
	mDefThrCheckBox = new QCheckBox("Use Custum Threshold");
	mOpenOutputCheckBox = new QCheckBox("Run and Show Output");

    mDNALine = new QLineEdit("../InputFiles/promoters.fasta");
    mPWMLine = new QLineEdit("../InputFiles/DBP_PPM.mat");
	mOutLine = new QLineEdit("../OutputFiles/output.fasta");
	mThrLine = new QLineEdit("");
	QDoubleValidator *valid = new QDoubleValidator(this);
	mThrLine->setValidator(valid);

    mRunButton->setStyleSheet("background-color:#FF8C00");
}

void window::createLayout(void)
{
    QGridLayout *layout = new QGridLayout(this);
    QHBoxLayout *DNAlayout = new QHBoxLayout();
    QHBoxLayout *PWMlayout = new QHBoxLayout();
    QHBoxLayout *Outlayout = new QHBoxLayout();
	QHBoxLayout *Thrlayout = new QHBoxLayout();
    QHBoxLayout *CheckBlayout = new QHBoxLayout();

    DNAlayout->addWidget(mDNAInitButton);
    DNAlayout->addWidget(mDNALine);
    layout->addWidget(mEditDNAButton, 0, 1);

    PWMlayout->addWidget(mPWMInitButton);
    PWMlayout->addWidget(mPWMLine);
    layout->addWidget(mEditPWMButton, 1, 1);

	Outlayout->addWidget(mOutInitButton);
	Outlayout->addWidget(mOutLine);

	Thrlayout->addWidget(mDefThrCheckBox);
	Thrlayout->addWidget(mThrLine);

	//CheckBlayout->addWidget(mWriteOutput);
    CheckBlayout->addWidget(mOpenOutputCheckBox);

    layout->addLayout(DNAlayout, 0, 0);
    layout->addLayout(PWMlayout, 1, 0);
	layout->addLayout(Outlayout, 2, 0);
	layout->addLayout(Thrlayout, 3, 0);
	layout->addLayout(CheckBlayout, 4, 0);
	layout->addWidget(mRunButton, 4, 1);
	layout->addWidget(mShowOutputButton, 2, 1);
}

void window::editLine(QLineEdit* m_line, QString const& filter)
{
	QString selectedFilePath = QFileDialog::getOpenFileName(this, "Select file", mPath, filter);
    if (!selectedFilePath.isEmpty()) {
        QMessageBox::information( 0, "Info", "You selected :\n" + selectedFilePath);
        m_line->setText(selectedFilePath);
        mPath = selectedFilePath;
    }
}
