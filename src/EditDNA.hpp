#ifndef EDITDNA_H
#define EDITDNA_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QVBoxLayout>

#include <vector>
#include "EditAbstract.hpp"

class EditDNAwindow: public EditAbstract
{
Q_OBJECT
public:
    EditDNAwindow();
    virtual void open(void) override;
    virtual void saveAs(void) override;
    virtual void save(void) override;
    virtual void refresh(void) override;
	virtual void add(void) override;
	virtual void remove(void) override;
private:
    void reset(void);
    void setLayout(void);
    void resize(size_t const&);
private:
    std::vector<QLineEdit*> mHeaders;
    std::vector<QTextEdit*> mDNAs;

	QLineEdit *mRLine;
	QLineEdit *mALine;
	QLineEdit *mReLine;
    QVBoxLayout *mTextLayout;

    QString mSavePath;
};

#endif // EDITDNA_H
