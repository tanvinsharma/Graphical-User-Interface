#include "recipedialog.h"
#include "ui_recipedialog.h"
#include "globalvar.h"

#include<QStringListModel>

recipedialog::recipedialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::recipedialog)
{
    ui->setupUi(this);

    //sets the listmodel to show the recipe list
    QStringListModel *model = new QStringListModel();
    model->setStringList(FinalRecipeList);
    ui->recipeList->setModel(model);
    ui->recipeList->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

recipedialog::~recipedialog()
{
    delete ui;
}
