#ifndef ADDRECIPE_H
#define ADDRECIPE_H

#include <QDialog>
#include <QJsonObject>
#include "mainwindow.h"
#include "globalvar.h"

namespace Ui {
class addRecipe;
}

class addRecipe : public QDialog
{
    Q_OBJECT

public:
    explicit addRecipe(QWidget *parent = nullptr);
    ~addRecipe();
    QJsonObject ingred;

protected:
    void closeEvent(QCloseEvent *event) override { //closeEvent when dialog closed
            if (event->spontaneous()) {
                timer->stop();
            }
        }

private slots:
    void on_btnItemAdd_clicked();
    void on_btnOK_accepted();

private:
    Ui::addRecipe *ui;
};

#endif // ADDRECIPE_H
