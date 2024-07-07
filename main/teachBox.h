#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controller/communicationController.h"
#include "controller/interfaceController.h"
#include "manager/referenceManager.h"
#include "h/config.h"

#include <QMainWindow>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class TeachBox : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    InterfaceController *interfaceController;
    CommunicationController *communicationController;
    ReferenceManager *referenceManager;

public:
    ~TeachBox();
    TeachBox(const Config &config, Ui::MainWindow *ui, QWidget *parent = nullptr);
    TeachBox() = delete;
    TeachBox(const TeachBox &) = delete;
    void operator=(const TeachBox &) = delete;

private slots:
    // 功能表切换
    void on_fun_ListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    // ip端口设置按钮
    void on_setNet_Btn_toggled(bool checked);
    // 规控切换组合框
    void on_ctr_ComboBox_activated(int index);
    void on_plan_ComboBox_activated(int index);
    void on_space_ComboBox_activated(int index);
    // 速度增减按钮
    void on_jogVel_Btn2_clicked();
    void on_jogVel_Btn1_clicked();
    void on_runVel_Btn_clicked();
    void on_runVel_Btn_2_clicked();
    // 运行页面：示教按钮
    void on_runQueue_enable_Btn11_clicked();
    void on_runQueue_enable_Btn21_clicked();
    void on_runQueue_enable_Btn31_clicked();
    void on_runQueue_enable_Btn41_clicked();
    void on_runQueue_enable_Btn51_clicked();
    void on_runQueue_enable_Btn61_clicked();
    // 运行页面：运行按钮
    void on_runQueue_enable_Btn12_clicked();
    void on_runQueue_enable_Btn22_clicked();
    void on_runQueue_enable_Btn32_clicked();
    void on_runQueue_enable_Btn42_clicked();
    void on_runQueue_enable_Btn52_clicked();
    void on_runQueue_enable_Btn62_clicked();
    // 运行页面：保存按钮
    void on_runQueue_enable_Btn13_toggled(bool checked);
    void on_runQueue_enable_Btn23_toggled(bool checked);
    void on_runQueue_enable_Btn33_toggled(bool checked);
    void on_runQueue_enable_Btn43_toggled(bool checked);
    void on_runQueue_enable_Btn53_toggled(bool checked);
    void on_runQueue_enable_Btn63_toggled(bool checked);
    // 功能按钮
    void on_backZero_Btn_clicked();
    void on_stop_Btn_clicked();
    //点动按钮
    void on_J1_Btn1_pressed();
    void on_J1_Btn2_pressed();
    void on_J2_Btn1_pressed();
    void on_J2_Btn2_pressed();
    void on_J3_Btn1_pressed();
    void on_J3_Btn2_pressed();
    void on_J4_Btn1_pressed();
    void on_J4_Btn2_pressed();
    void on_J5_Btn1_pressed();
    void on_J5_Btn2_pressed();
    void on_J6_Btn1_pressed();
    void on_J6_Btn2_pressed();
    void on_J7_Btn1_pressed();
    void on_J7_Btn2_pressed();

    void on_J1_Btn1_released();
    void on_J1_Btn2_released();
    void on_J2_Btn1_released();
    void on_J2_Btn2_released();
    void on_J3_Btn1_released();
    void on_J3_Btn2_released();
    void on_J4_Btn1_released();
    void on_J4_Btn2_released();
    void on_J5_Btn1_released();
    void on_J5_Btn2_released();
    void on_J6_Btn1_released();
    void on_J6_Btn2_released();
    void on_J7_Btn1_released();
    void on_J7_Btn2_released();

    void on_X_Btn1_pressed();
    void on_X_Btn2_pressed();
    void on_Y_Btn1_pressed();
    void on_Y_Btn2_pressed();
    void on_Z_Btn1_pressed();
    void on_Z_Btn2_pressed();
    void on_r_Btn1_pressed();
    void on_r_Btn2_pressed();
    void on_p_Btn1_pressed();
    void on_p_Btn2_pressed();
    void on_y_Btn1_pressed();
    void on_y_Btn2_pressed();

    void on_X_Btn1_released();
    void on_X_Btn2_released();
    void on_Y_Btn1_released();
    void on_Y_Btn2_released();
    void on_Z_Btn1_released();
    void on_Z_Btn2_released();
    void on_r_Btn1_released();
    void on_r_Btn2_released();
    void on_p_Btn1_released();
    void on_p_Btn2_released();
    void on_y_Btn1_released();
    void on_y_Btn2_released();
};
#endif // MAINWINDOW_H
