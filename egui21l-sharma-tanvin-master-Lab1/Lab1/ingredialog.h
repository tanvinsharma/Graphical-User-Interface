#ifndef INGREDIALOG_H
#define INGREDIALOG_H

#include <QDialog>

namespace Ui {
class ingredialog;
}

class ingredialog : public QDialog
{
    Q_OBJECT

public:
    explicit ingredialog(QWidget *parent = nullptr);
    ~ingredialog();

private:
    Ui::ingredialog *ui;
};

#endif // INGREDIALOG_H
