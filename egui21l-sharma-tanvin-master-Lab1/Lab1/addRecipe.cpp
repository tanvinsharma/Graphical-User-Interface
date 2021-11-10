#include "addRecipe.h"
#include "ui_addRecipe.h"
#include "globalvar.h"
#include "mainwindow.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QMessageBox>
#include <QStringListModel>
#include <QListWidget>

addRecipe::addRecipe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addRecipe)
{
    ui->setupUi(this);
}

addRecipe::~addRecipe()
{
    delete ui;
}

// Function to add recipe

void addRecipe::on_btnItemAdd_clicked()
{
    // check to see if all fields are filled
    if(ui->itemName->text().isEmpty()||ui->itemAmount->text().isEmpty()||ui->itemAmount->text().isEmpty()){
        QMessageBox::warning(this,"Error","ALL FIELDS NOT FILLED!");

    }else{
        QString item_amt;
        item_amt =ui->itemAmount->text() +" "+ui->itemUnit->text();

        QString item_name;
        item_name = ui->itemName->text();

        //add item name and item amount + unit into ingred QJsonObject defined in header file
        ingred.insert(item_name,item_amt);
        //clear fields
        ui->itemName->clear();
        ui->itemAmount->clear();
        ui->itemUnit->clear();
        //display on gui
        ui->listIng->addItem(item_name + ": " + item_amt);
    }
}

// Function for OK button to write to the JSON

void addRecipe::on_btnOK_accepted()
{
    if(ui->nameText->text().isEmpty()||ui->recipeText->toPlainText().isEmpty()){
        QMessageBox::warning(this,"Error","ALL FIELDS NOT FILLED!");

    }else{
        QString name = ui->nameText->text();
        QString recipe= ui->recipeText->toPlainText();

        // Forming JSON object to be added
        QJsonArray ArrayRecipe = QJsonArray::fromStringList(recipe.split('\n'));

        ingred.insert("recipe",ArrayRecipe);

        rootObj.insert(name,ingred);

        ui->nameText->clear();
        ui->recipeText->clear();

        // Update JSON
        QJsonDocument JSONDoc;
        JSONDoc.setObject(rootObj);
        QFile file("/users/tanvinsharma/Downloads/Lab1-2/recipes.json");
        file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
        file.write(JSONDoc.toJson());
        file.close();

    }

}
