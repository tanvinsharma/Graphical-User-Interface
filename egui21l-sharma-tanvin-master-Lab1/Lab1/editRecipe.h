#ifndef EDITRECIPE_H
#define EDITRECIPE_H

#include <QDialog>
#include <QCloseEvent>
#include <QTimer>
#include "globalvar.h"


namespace Ui {
class editRecipe;
}

class editRecipe : public QDialog
{
    Q_OBJECT

public:
    explicit editRecipe(QWidget *parent = nullptr);
    ~editRecipe();
protected:
    void closeEvent(QCloseEvent *event) override { //closeEvent when dialog closed
            if (event->spontaneous()) {
                timer->stop();
            }
        }
private slots:
    void on_btnOK_accepted();

private:
    Ui::editRecipe *ui;
};

#endif // EDITRECIPE_H
