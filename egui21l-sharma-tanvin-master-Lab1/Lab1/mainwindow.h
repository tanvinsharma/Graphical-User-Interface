#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void refresh();
    void refresh_timer();
    void on_btnAdd_clicked();
    void on_btnGrocery_clicked();
    void on_btnEdit_clicked();
    void on_btnDel_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
