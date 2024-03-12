#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controller/communicationController.h"
#include "controller/interfaceController.h"
#include "config.h"

#include <QMainWindow>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    InterfaceController *interfaceController;
    CommunicationController *communicationController;

public:
    ~MainWindow();
    MainWindow(const Config &config, Ui::MainWindow *ui, QWidget *parent = nullptr);
    MainWindow() = delete;
    MainWindow(const MainWindow &) = delete;
    void operator=(const MainWindow &) = delete;

private slots:
    // 功能表切换
    void on_fun_ListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    // ip端口设置按钮
    void on_setNet_Btn_toggled(bool checked);
    // 规控切换组合框
    void on_ctr_ComboBox_activated(int index);
    void on_plan_ComboBox_activated(int index);
    // 速度增减按钮
    void on_jogVel_Btn2_clicked();
    void on_jogVel_Btn1_clicked();
    void on_runVel_Btn_clicked();
    void on_runVel_Btn_2_clicked();
    // 功能按钮
    void on_backZero_Btn_clicked();
    void on_stop_Btn_clicked();

};
#endif // MAINWINDOW_H
