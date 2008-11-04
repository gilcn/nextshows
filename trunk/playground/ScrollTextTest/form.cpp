#include "form.h"


Form::Form(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);

    connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(close()));
} // ctor()


Form::~Form()
{
} // dtor()

