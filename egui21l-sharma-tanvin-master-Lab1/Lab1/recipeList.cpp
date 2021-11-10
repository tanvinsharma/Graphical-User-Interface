#include "recipeList.h"
#include "ui_recipeList.h"
#include "globalvar.h"

#include <string>
#include <QDebug>
#include <regex>
#include <QJsonObject>
#include <QJsonDocument>
#include <QStringListModel>
#include <QJsonArray>
#include <QJsonValue>
#include <QMap>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

recipeList::recipeList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::recipeList)
{
    ui->setupUi(this);
}

recipeList::~recipeList()
{
    delete ui;
}

// Function to get the Grocery list from the entered recipes
void recipeList::on_btnGrocery_clicked()
{
    QString name = ui->nameList->toPlainText();
    QStringList lst_name = name.split("\n");
    lst_name.sort();
    // Using a hash map (QMAP) to find the amount of a repeated recipe to calculate total amount of groceries needed
    QMap<QString,int> amt_map;
    for (int i = 0; i < lst_name.count(); i++){
        int count_val = lst_name.count(lst_name[i]);
        amt_map.insert(lst_name[i],count_val); //QMap contained recipe name and the number of times that recipe wants to be made
    }
    lst_name.removeDuplicates();
    QMap<QString,float> ing_map;
    for (int i = 0; i < lst_name.count(); i++ ){
        QJsonObject tempIngred = rootObj[lst_name[i]].toObject();
        QStringList tempIngredList = tempIngred.keys();
        // factor taken from the amt_map to know the total sum of groceries
        int factor = amt_map.value(lst_name[i]);
        int count_ing = tempIngred.keys().count();

        for(int i = 0; i < count_ing; i++){
            if(tempIngredList[i]!="recipe"){
                // Parsing json file
                QStringList tempList = tempIngred[tempIngredList[i]].toString().split(" ");
                tempList.removeAll("");

                QString sepString = tempIngredList[i]+"_"+tempList[1];
                float amount = tempList[0].toFloat();
                // calculating final amount using factor
                amount = amount * factor;

                //insert new amount into our hash table
                if(ing_map.contains(sepString)){
                    float newAmount = ing_map.value(sepString)+amount;
                    ing_map.insert(sepString,newAmount);
                }else{
                    ing_map.insert(sepString,amount);
                }
            }
        }
    }
    QString ingredients;
    QStringList mapList = ing_map.keys();

    for(int i = 0; i < mapList.count(); i++){
        QStringList sepList = mapList[i].split("_");
        QString amounts = QString::number(ing_map.value(mapList[i]));
        //add the final ingredients
        if(i==mapList.count()-1){
            ingredients += sepList[0]+": "+amounts+" "+sepList[1];
        }else{
            ingredients += sepList[0]+": "+amounts+" "+sepList[1]+"\n";
        }
    }
    FinalIngred = ingredients;

    ui->ingreList->setPlainText(FinalIngred);
}

// Function for getting the recipies for the entered food

void recipeList::on_btnRecipe_clicked()
{
    // clear
    FinalRecipeList.clear();

    //Parsing
    QString name = ui->nameList->toPlainText();
    QStringList lst_name = name.split("\n");

    lst_name.removeDuplicates();

    for(int i = 0; i < lst_name.count(); i++){
        if(rootObj.contains(lst_name[i])){

            //creat temporary object and array for recipe name and recipe
            QJsonObject temp_var = rootObj[lst_name[i]].toObject();
            QJsonArray temp_arr = temp_var["recipe"].toArray();

            QString names = lst_name[i];
            for (int i = 0; i < temp_arr.count(); i++){
                names += "\n-"+ temp_arr[i].toString();
            }
            if (!FinalRecipeList.contains(names)){
                FinalRecipeList.append(names);// add the names string to final recipe list
            }
        }
    }
    QStringListModel *model = new QStringListModel();
    model->setStringList(FinalRecipeList);
    ui->recList->setModel(model);
    ui->recList->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

