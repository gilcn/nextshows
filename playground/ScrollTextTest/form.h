#ifndef __FORM_H__
#define __FORM_H__

#include "ui_form.h"

#include <QtGui>

class Form : public QDialog
{
    Q_OBJECT

public:
    Form(QWidget *parent = 0);
    ~Form();

private:
    Ui::Form ui;
};

#endif // __FORM_H__
