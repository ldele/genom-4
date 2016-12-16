#include "EditPWM.hpp"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QValidator>

#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>

#include <QFile>
#include <QTextStream>

#include <iostream>

EditPWMwindow::EditPWMwindow() :EditAbstract()
{
    this->setWindowTitle("Edit PWM");

    QScrollArea *scroll = new QScrollArea(this);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    mViewport = new QWidget(this);
    scroll->setWidget(mViewport);
    scroll->setWidgetResizable(true);

    mLayout = new QVBoxLayout(mViewport);
    mViewport->setLayout(mLayout);

    QDesktopWidget screen;
    this->setMinimumHeight(screen.height()*0.5);
    this->setMinimumWidth(screen.width()*0.5);

    mEntryLayout = new QGridLayout();
    QLabel *A = new QLabel("A");
    QLabel *C = new QLabel("C");
    QLabel *G = new QLabel("G");
    QLabel *T = new QLabel("T");
    A->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    C->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    G->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    T->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    mEntryLayout->addWidget(A, 0, 1);
    mEntryLayout->addWidget(C, 0, 2);
    mEntryLayout->addWidget(G, 0, 3);
    mEntryLayout->addWidget(T, 0, 4);
    mEntryLayout->setColumnStretch(0, 0);

    QHBoxLayout *resizeLayout = new QHBoxLayout();
    QLabel *mSizeLabel = new QLabel(tr("Enter PWM size (comprised between 0 & 100)"));
    mEnterSize = new QLineEdit();
	QPushButton *refresh = new QPushButton(tr("Resize"));
    QObject::connect(refresh, SIGNAL(clicked()), this, SLOT(refresh(void)));
    QObject::connect(mEnterSize, SIGNAL(returnPressed()), this, SLOT(refresh(void)));
    resizeLayout->addWidget(mSizeLabel);
    resizeLayout->addWidget(mEnterSize);
	mEnterSize->setValidator(new QIntValidator(1, 100));
    resizeLayout->addWidget(refresh);

	QHBoxLayout *addingLayout = new QHBoxLayout();
	QLabel *addLabel = new QLabel(tr("Add Field(s) : "));
	mAddLine = new QLineEdit();
	mAddLine->setValidator(new QIntValidator(1, 100));
	QPushButton *adding = new QPushButton(tr("Add"));
	QObject::connect(adding, SIGNAL(clicked()), this, SLOT(add()));
	QObject::connect(mAddLine, SIGNAL(returnPressed()), this, SLOT(add(void)));
	addingLayout->addWidget(addLabel);
	addingLayout->addWidget(mAddLine);
	addingLayout->addWidget(adding);

	QHBoxLayout *removeLayout = new QHBoxLayout();
	QLabel *remLabel = new QLabel(tr("Remove Field (enter field number) : "));
	mRemLine = new QLineEdit();
	mRemLine->setValidator(new QIntValidator(1, 100));
	QPushButton *removing = new QPushButton(tr("Remove"));
	QObject::connect(removing, SIGNAL(clicked()), this, SLOT(remove()));
	QObject::connect(mRemLine, SIGNAL(returnPressed()), this, SLOT(remove(void)));
	removeLayout->addWidget(remLabel);
	removeLayout->addWidget(mRemLine);
	removeLayout->addWidget(removing);

    mLayout->addLayout(resizeLayout);
	mLayout->addLayout(addingLayout);
	mLayout->addLayout(removeLayout);
    resize(7);
    mLayout->addLayout(mEntryLayout);

    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addWidget(scroll);
    QWidget *mainWindow = new QWidget();
    mainWindow->setLayout(mainLayout);
    this->setCentralWidget(mainWindow);
}

void EditPWMwindow::resize(size_t const& size)
{
    for (const auto& line: mPWMentryLines) {
        delete line;
    }
    for (const auto& number: mLineNumbers) {
        delete number;
    }
	mLineNumbers.resize(size);
    mPWMentryLines.resize(size*4);
	for (size_t i(0); i < mLineNumbers.size(); ++i) {
		mLineNumbers[i] = new QLabel(QString::number(i+1) + ".");
		mEntryLayout->addWidget(mLineNumbers[i], i+1, 0);
	}
    for (size_t i(0); i < mPWMentryLines.size(); ++i) {
        mPWMentryLines[i] = new QLineEdit();
        mPWMentryLines[i]->setValidator(new QDoubleValidator(this));
        mEntryLayout->addWidget(mPWMentryLines[i], (i+4)/4, i%4 + 1);
    }
    mViewport->adjustSize();
    mLayout->insertStretch( -1, -1 );
}

void EditPWMwindow::refresh(void)
{
    bool ok(false);
    int size = mEnterSize->text().toInt(&ok, 10);
    if (ok) {
        resize(size);
	} else {
		resize(mLineNumbers.size());
	}
}

void EditPWMwindow::saveAs(void)
{
    QString filename = QFileDialog::getSaveFileName(0, "Save File As...", mPath);
    if (!filename.isEmpty()) {
        mSavePath = filename;
        QFile write(filename);
        if (write.open(QIODevice::WriteOnly)) {
            QTextStream out(&write);
            for (size_t i(0); i < mPWMentryLines.size(); ++i) {
                bool ok(false);
                double score = mPWMentryLines[i]->text().toDouble(&ok);
                if (ok) {
                    out << score << '\t';
                    if (i != 0 && i%4 == 0) {
                        out << '\n';
                    }
                }
            }
            write.close();
        }
    }
}

void EditPWMwindow::save(void)
{
    if (!mSavePath.isEmpty()) {
        QFile write(mPath);
        if (write.open(QIODevice::WriteOnly)) {
            QTextStream out(&write);
            for (size_t i(0); i < mPWMentryLines.size(); ++i) {
                bool ok(false);
                double score = mPWMentryLines[i]->text().toDouble(&ok);
                if (ok) {
                    out << score << '\t';
                    if (i != 0 && i%4 == 0) {
                        out << '\n';
                    }
                }
            }
            write.close();
        }
    } else {
        saveAs();
    }
}

void EditPWMwindow::open(void)
{
    QString filename = QFileDialog::getOpenFileName(0, "Select A File", mPath);
    if (!filename.isEmpty()) {
        QFile read(filename);
        if (read.open(QIODevice::ReadOnly)) {
            mPath = filename;
            std::vector<QString> scores;
            QTextStream in(&read);
            while (!in.atEnd()) {
                QString score;
                in >> score;
                if (in.status() != QTextStream::Ok) break;
                scores.push_back(score);
            }
            read.close();
            if (scores.size()%4 != 0) {
                resize((scores.size()/4) + 1);
            } else {
                resize(scores.size()/4);
            }
            for (size_t i(0); i < scores.size(); ++i) {
                mPWMentryLines[i]->setText(scores[i]);
            }
        }
    }
}

void EditPWMwindow::add(void)
{
	bool ok(false);
	size_t size = mAddLine->text().toInt(&ok);
	if (ok) {
		int init = mLineNumbers.size();
		if (mLineNumbers.size()+size >= 100) {
			for (size_t i(init); i < 100; ++i) {
				mLineNumbers.push_back(new QLabel(QString::number(i+1) + "."));
				mEntryLayout->addWidget(mLineNumbers.back(), i+1, 0);
				for (size_t j(0); j < 4; ++j) {
					mPWMentryLines.push_back(new QLineEdit());
					mPWMentryLines.back()->setValidator(new QDoubleValidator(this));
					mEntryLayout->addWidget(mPWMentryLines.back(), i+1, j+1);
				}
			}
		} else {
			for (size_t i(0); i < size; ++i) {
				mLineNumbers.push_back(new QLabel(QString::number(init+1+i) + "."));
				mEntryLayout->addWidget(mLineNumbers.back(), init+i+1, 0);
				for (size_t j(0); j < 4; ++j) {
					mPWMentryLines.push_back(new QLineEdit());
					mPWMentryLines.back()->setValidator(new QDoubleValidator(this));
					mEntryLayout->addWidget(mPWMentryLines.back(), i+init+1, j+1);
				}
			}
		}
		mViewport->adjustSize();
		mLayout->insertStretch( -1, -1 );
	}
}

void EditPWMwindow::remove(void)
{
	bool ok(false);
	size_t toRem = mRemLine->text().toInt(&ok);
	if (ok) {
		if (toRem > mLineNumbers.size() or toRem == 0) {
			QMessageBox::information(this, "Remove", "There is no such field/n You wanted to delete field : " + mRemLine->text() + "\n");
		} else {
			std::vector<QString> data(mPWMentryLines.size());
			for (size_t i(0); i < mPWMentryLines.size(); ++i) {
				if (!mPWMentryLines[i]->text().isEmpty()) {
					data[i] = std::move(mPWMentryLines[i]->text());
				} else {
					data[i] = "";
				}
			}
			data.erase(data.begin() + (toRem-1)*4, data.begin()+ (toRem-1)*4+4);
			resize(mLineNumbers.size()-1);
			for (size_t i(0); i < mPWMentryLines.size(); ++i) {
				mPWMentryLines[i]->setText(data[i]);
			}
		}
	}
}

void EditPWMwindow::setLayout()
{
	mEntryLayout = new QGridLayout();
	for (size_t i(0); i < mLineNumbers.size(); ++i) {
		mEntryLayout->addWidget(mLineNumbers[i], i+1, 0);
		for (size_t j(1); j < 5; ++i) {
			mEntryLayout->addWidget(mPWMentryLines[4*i+j], i+1, j);
		}
	}
}
