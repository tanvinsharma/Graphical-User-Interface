#ifndef RECIPEDIALOG_H
#define RECIPEDIALOG_H

#include <QDialog>

namespace Ui {
class recipedialog;
}

class recipedialog : public QDialog
{
    Q_OBJECT

public:
    explicit recipedialog(QWidget *parent = nullptr);
    ~recipedialog();

private:
    Ui::recipedialog *ui;
};

#endif // RECIPEDIALOG_H
