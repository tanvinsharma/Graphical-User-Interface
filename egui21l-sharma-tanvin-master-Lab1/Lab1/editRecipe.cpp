#include "editRecipe.h"
#include "ui_editRecipe.h"
#include "globalvar.h"

#include <QStringList>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
#include <QCloseEvent>
#include <QJsonDocument>
#include <QMessageBox>
#include <QFile>

//Function for editing recipes
editRecipe::editRecipe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editRecipe)
{
    ui->setupUi(this);
    if(rootObj.contains(currentItem)){
        ui->nameText->setText(currentItem);

        QString temp; //create temporary string
        QJsonObject tempRecipe = rootObj[currentItem].toObject();
        QJsonArray arrayRecipe = tempRecipe["recipe"].toArray();

        // To go through json file to update data line by line
        for (int i = 0; i < arrayRecipe.count(); i++){
            if (i==arrayRecipe.count()-1){
                temp += arrayRecipe[i].toString();
            }else{
                temp += arrayRecipe[i].toString()+"\n";
            }

        }
        ui->recipeText->setPlainText(temp);

        QString ing;

        //getting data from json file
        QStringList listIngredients = tempRecipe.keys();

        for(int i = 0; i < listIngredients.count(); i++){
            if(listIngredients[i]!="recipe"){
                if (i == listIngredients.count()-1){
                    //add the data to temp string
                    ing += listIngredients[i]+": "+tempRecipe[listIngredients[i]].toString();
                }else{
                    ing += listIngredients[i]+": "+tempRecipe[listIngredients[i]].toString()+"\n";
                }

            }
        }
        //set the ingredients text with the data
        ui->ingredText->setPlainText(ing);
    }
}

editRecipe::~editRecipe()
{
    delete ui;
}

// Function for the OK button

void editRecipe::on_btnOK_accepted()
{
    QString editName = ui->nameText->text();
    QString editRecipe = ui->recipeText->toPlainText();

    QStringList listRecipeEdit = editRecipe.split("\n");
    QJsonArray arrayRecipeEdit = QJsonArray::fromStringList(listRecipeEdit);

    QJsonObject ingred;
    ingred.insert("recipe",arrayRecipeEdit);

    //get new ingredients list
    QString ingredEdit = ui->ingredText->toPlainText();
    QStringList listIngredEdit = ingredEdit.split("\n");

    QString name;
    QString amount;

    for (int i = 0; i < listIngredEdit.count(); i++){
        QRegularExpression nameRE;

        //using regex for getting the things we want
        nameRE.setPattern("[a-z]+");

        QRegularExpressionMatch nameSame = nameRE.match(listIngredEdit[i]);
        if (nameSame.hasMatch()){
            name = nameSame.captured(0);
        }
        QRegularExpression amountRE;
        //same logic for the regex used before
        amountRE.setPattern("[0-9]+[.]*[0-9]*[\\s]+[a-z]+");

        QRegularExpressionMatch amountSame = amountRE.match(listIngredEdit[i]);
        if (amountSame.hasMatch()){
            //update
            amount = amountSame.captured(0);

        }
        //add updated name and amount to JsonObject
        ingred.insert(name,amount);
    }

    if(rootObj.contains(editName)){
        //updates recipe and ingredients of that recipe name
        rootObj.insert(editName,ingred);
    }else{
        //creating temp with current data
        QString temp = currentItem;
        rootObj.remove(temp);
        rootObj.insert(editName,ingred);

    }
    //update JSON file
    QJsonDocument JsonDocument;
    JsonDocument.setObject(rootObj);
    QFile file("/users/tanvinsharma/Downloads/Lab1-2/recipes.json");
    file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    file.write(JsonDocument.toJson());
    file.close();
}
