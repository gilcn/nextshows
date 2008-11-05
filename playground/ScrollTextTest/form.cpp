#include "form.h"


Form::Form(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);

    connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(close()));

    ui.graphicsView->addCreditSection("Credits", 15);
    ui.graphicsView->addCredit("FR", "Gilles Chauvin", "gcnweb@gmail.com", "Author, main developper");
    ui.graphicsView->addCredit("FR", "Emmanuel Hamelet", "kh.starlifter@gmail.com", "Contributor");
    ui.graphicsView->addCreditSection("Releases prior to v3.0.0<br />(SuperKaramba widget)");
    ui.graphicsView->addCredit("FR", "Gilles Chauvin", "gcnweb@gmail.com","Author, main developper");
    ui.graphicsView->addCredit("FR", "Emmanuel Hamelet", "kh.starlifter@gmail.com","Ideas, testing, bug-hunting");
    ui.graphicsView->addCredit("ES", "Alexandre Vázquez", "", "Testing, bug-hunting");
    ui.graphicsView->addCredit("SE", "ge5239", "", "Ideas, testing, bug-hunting");
    ui.graphicsView->addCredit("FR", "Joachim Ionoff", "", "Ideas, testing, bug-hunting");
    ui.graphicsView->addCreditSection("Special thanks to");
    ui.graphicsView->addCredit("FR", "Jean-Baptiste Sannier", "http://jsannier.org/", "Qt help, tips & tricks");
    ui.graphicsView->addCredit("US", "Sebrioth", "http://www.tvrage.com/", "XML feeds providing");

    ui.graphicsView->startScrolling();
} // ctor()


Form::~Form()
{
} // dtor()

