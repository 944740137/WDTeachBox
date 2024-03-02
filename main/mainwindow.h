#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "clientCom/clientCom.h"
#include <QMainWindow>
#include <QListWidgetItem>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ClientCom *clientCom;

    ~MainWindow();
    MainWindow(const QString &ipAddress_in, int port_in, QWidget *parent = nullptr);

    MainWindow() = delete;
    MainWindow(const MainWindow &) = delete;
    void operator=(const MainWindow &) = delete;

    //网络
    void resetNetConfigInterface();

private slots:

    //功能列表
    void on_fun_ListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    //网络
    void on_setNet_Btn_toggled(bool checked);

    //归控切换
    void on_ctr_ComboBox_activated(int index);
    void on_plan_ComboBox_activated(int index);

    //tmp
    void on_tmp_clicked();
    void on_tmp2_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
