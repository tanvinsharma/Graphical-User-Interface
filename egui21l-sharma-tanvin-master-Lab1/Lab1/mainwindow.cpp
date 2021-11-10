#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addRecipe.h"
#include "globalvar.h"
#include "editRecipe.h"
#include "recipeList.h"

#include<QJsonParseError>
#include<QFile>
#include<QJsonDocument>
#include<QStringListModel>
#include<QAbstractItemView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    refresh();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Function to refrest windo

void MainWindow::refresh()
{
    QFile inFile("/users/tanvinsharma/Downloads/Lab1-2/recipes.json");
    inFile.open(QIODevice::ReadOnly|QIODevice::Text);
    QByteArray data = inFile.readAll();
    inFile.close();
    QJsonParseError errorPtr;
    QJsonDocument doc = QJsonDocument::fromJson(data, &errorPtr);
    rootObj = doc.object();

    QStringList recipeList = rootObj.keys();
    QStringListModel *model = new QStringListModel();
    model->setStringList(recipeList);
    ui->listRecipe->setModel(model);
    //reset edit trigger to avoid problems
    ui->listRecipe->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

// Function for periodic refresh

void MainWindow::refresh_timer()
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(refresh()));
    timer->start(5000);

}

// Function to open button of addRecipe

void MainWindow::on_btnAdd_clicked()
{
    addRecipe* dlg = new addRecipe(this);
    dlg->show();
    refresh_timer();
}

// Function to open button of editRecipe

void MainWindow::on_btnEdit_clicked()
{
    QModelIndex edit_index = ui->listRecipe->currentIndex();
    QString edit_itemText = edit_index.data(Qt::DisplayRole).toString();
    currentItem = edit_itemText;

    editRecipe* dlg = new editRecipe(this);
    dlg->show();
    refresh_timer();
}

// Function to delete the currently selected item

void MainWindow::on_btnDel_clicked()
{
    QModelIndex del_index = ui->listRecipe->currentIndex();
    QString itemText = del_index.data(Qt::DisplayRole).toString();

    //remove item from rootObj
    rootObj.remove(itemText);

    //rewrite changes
    QJsonDocument JsonDocument;
    JsonDocument.setObject(rootObj);
    QFile file("/users/tanvinsharma/Downloads/Lab1-2/recipes.json");
    file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    file.write(JsonDocument.toJson());
    file.close();

    refresh();
}

// Function for the grocery/recipe list button

void MainWindow::on_btnGrocery_clicked()
{
    recipeList* dlg = new recipeList(this);
    dlg->show();
    refresh_timer();
}
