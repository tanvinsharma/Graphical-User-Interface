#include "ingredialog.h"
#include "ui_ingredialog.h"
#include "globalvar.h"

ingredialog::ingredialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ingredialog)
{
    ui->setupUi(this);

    ui->ingreList->setPlainText(FinalIngred); //displays the ingredients
}

ingredialog::~ingredialog()
{
    delete ui;
}
