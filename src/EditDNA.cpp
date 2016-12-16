#include "EditDNA.hpp"

#include <QPushButton>
#include <QTextStream>
#include <QFileDialog>
#include <QAction>
#include <QFile>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QValidator>
#include <QScrollArea>
#include <QDesktopWidget>
#include <QMessageBox>

EditDNAwindow::EditDNAwindow(): EditAbstract()
{
    this->setWindowTitle("Edit DNA");

    QDesktopWidget screen;
	this->setMinimumWidth(screen.width()*0.6);
	this->setMinimumHeight(screen.height()*0.6);

    QScrollArea *scroll = new QScrollArea(this);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

	QPushButton *refresh = new QPushButton(tr("Resize"));
	mRLine = new QLineEdit();
	QLabel *label = new QLabel(tr("Set Fields (number comprised between 0 & 30) : "));
    QObject::connect(refresh, SIGNAL(clicked()), this, SLOT(refresh(void)));
	QObject::connect(mRLine, SIGNAL(returnPressed()), this, SLOT(refresh(void)));
	mRLine->setValidator(new QIntValidator(1, 30));
    QHBoxLayout *resizeLayout = new QHBoxLayout();
    resizeLayout->addWidget(label);
	resizeLayout->addWidget(mRLine);
    resizeLayout->addWidget(refresh);

	QLabel *label2 = new QLabel(tr("Add Field (No Loss) : "));
	mALine = new QLineEdit();
	QPushButton *Add = new QPushButton(tr("Add"));
	QObject::connect(Add, SIGNAL(clicked()), this, SLOT(add()));
	QObject::connect(mALine, SIGNAL(returnPressed()), this, SLOT(add()));
	mALine->setValidator(new QIntValidator(1, 30));
	QHBoxLayout *addingLayout = new QHBoxLayout();
	addingLayout->addWidget(label2);
	addingLayout->addWidget(mALine);
	addingLayout->addWidget(Add);

	QPushButton *rem = new QPushButton(tr("Remove"));
	mReLine = new QLineEdit();
	QLabel *label3 = new QLabel(tr("Choose Field to Delete (Enter Field Number)"));
	QObject::connect(rem, SIGNAL(clicked()), this, SLOT(remove()));
	QObject::connect(mReLine, SIGNAL(returnPressed()), this, SLOT(remove()));
	mReLine->setValidator(new QIntValidator(1, 30));
	QHBoxLayout *removeLayout = new QHBoxLayout();
	removeLayout->addWidget(label3);
	removeLayout->addWidget(mReLine);
	removeLayout->addWidget(rem);

    mTextLayout = new QVBoxLayout();
    mTextLayout->addLayout(resizeLayout);
	mTextLayout->addLayout(addingLayout);
	mTextLayout->addLayout(removeLayout);

    QWidget *viewport = new QWidget();
    scroll->setWidget(viewport);
    scroll->setWidgetResizable(true);
    viewport->setLayout(mTextLayout);
    QHBoxLayout *scrollLayout = new QHBoxLayout();
    scrollLayout->addWidget(scroll);
    QWidget *view = new QWidget(this);
    view->setLayout(scrollLayout);
    this->setCentralWidget(view);
    resize(1);
}

void EditDNAwindow::reset(void)
{
    for (const auto& h: mHeaders) {
        delete h;
    }
    for (const auto& d: mDNAs) {
        delete d;
    }
    mHeaders.resize(0);
    mDNAs.resize(0);
}

void EditDNAwindow::setLayout(void)
{
    for (size_t i(0); i < mHeaders.size(); ++i) {
        mTextLayout->addWidget(mHeaders[i]);
        mTextLayout->addWidget(mDNAs[i]);
    }
}

void EditDNAwindow::open(void)
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Select A File"), mPath);
    if (!filename.isEmpty()) {
        QFile read(filename);
        if (read.open(QIODevice::ReadOnly)) {
            reset();
            QTextStream in(&read);
            char test;
            in >> test;
            if (test != '>' && test != '<') {
                mHeaders.push_back(new QLineEdit(tr("No Header !")));
                mDNAs.push_back(new QTextEdit());
            } else {
                QString word;
                in >> word;
                mHeaders.push_back(new QLineEdit(word));
                mDNAs.push_back(new QTextEdit());
            }
            while (!in.atEnd()) {
                char c;
                in >> c;
                if (c == '>' || c == '<') {
                    QString word;
                    in >> word;
                    mHeaders.push_back(new QLineEdit(word));
                    mDNAs.push_back(new QTextEdit());
                } else {
                    mDNAs.back()->insertPlainText(QString(c));
                }
            }
            read.close();
            setLayout();
        }
    }
}

void EditDNAwindow::save(void)
{
    if (!mSavePath.isEmpty()) {
        QFile write(mSavePath);
        if (write.open(QIODevice::WriteOnly)) {
            QTextStream out(&write);
            for (size_t i(0); i < mHeaders.size(); ++i) {
				if (!mHeaders[i]->text().isEmpty()) {
					out << ">" << mHeaders[i]->text() << '\n';
				} else {
					out << ">Header" << i << '\n';
				}
				out << mDNAs[i]->toPlainText() << '\n';
            }
        }
    } else {
        saveAs();
    }
}

void EditDNAwindow::saveAs(void)
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save As..."), mPath);
    if (!filename.isEmpty()) {
        QFile write(filename);
        if (write.open(QIODevice::WriteOnly)) {
            mSavePath = filename;
            QTextStream out(&write);
            for (size_t i(0); i < mHeaders.size(); ++i) {
				if (!mHeaders[i]->text().isEmpty()) {
					out << ">" << mHeaders[i]->text() << '\n';
				} else {
					out << ">Header" << i << '\n';
				}
                out << mDNAs[i]->toPlainText() << '\n';
            }
            write.close();
        }
    }
}

void EditDNAwindow::refresh(void)
{
    bool ok(false);
	int size = mRLine->text().toInt(&ok);
    if (ok) {
        resize(size);
    }
}

void EditDNAwindow::add(void)
{
	bool ok(false);
	size_t size = mALine->text().toInt(&ok);
	if (ok) {
		if (mHeaders.size()+size >= 30) {
			int init = mHeaders.size();
			for (size_t i(init); i < 30; ++i) {
				mHeaders.push_back(new QLineEdit());
				mDNAs.push_back(new QTextEdit());
			}
		} else {
			for (size_t i(0); i < size; ++i) {
				mHeaders.push_back(new QLineEdit());
				mDNAs.push_back(new QTextEdit());
			}
		}
	}
	setLayout();
}

void EditDNAwindow::remove(void)
{
	bool ok(false);
	size_t toRem = mReLine->text().toInt(&ok);
	if (ok) {
		if (toRem > mHeaders.size() or toRem == 0) {
			QMessageBox::information(this, "Remove", "There is no such field\n You wanted to delete field : " + mReLine->text() + "\n");
		} else {
			std::vector<QString> h(mHeaders.size());
			std::vector<QString> d(mDNAs.size());
			for (size_t i(0); i < h.size(); ++i) {
				h[i] = mHeaders[i]->text();
				d[i] = mDNAs[i]->toPlainText();
			}
			reset();
			--toRem;
			h.erase(h.begin()+toRem);
			d.erase(d.begin()+toRem);
			resize(h.size());
			for(size_t i(0); i < h.size(); ++i) {
				mHeaders[i]->setText(std::move(h[i]));
				mDNAs[i]->insertPlainText(std::move(d[i]));
			}
		}
		setLayout();
	}
}

void EditDNAwindow::resize(size_t const& size)
{
    reset();
    mHeaders.resize(size);
    mDNAs.resize(size);
    for (size_t i(0); i < size; ++i) {
        mHeaders[i] = new QLineEdit();
        mDNAs[i] = new QTextEdit();
        mTextLayout->addWidget(mHeaders[i]);
        mTextLayout->addWidget(mDNAs[i]);
    }
    setLayout();
}
