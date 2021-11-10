#ifndef recipeList_H
#define recipeList_H

#include <QDialog>

namespace Ui {
class recipeList;
}

class recipeList : public QDialog
{
    Q_OBJECT

public:
    explicit recipeList(QWidget *parent = nullptr);
    ~recipeList();

private slots:
    void on_btnRecipe_clicked();

    void on_btnGrocery_clicked();

private:
    Ui::recipeList *ui;
};

#endif // recipeList_H
