#ifndef InterfaceController_H
#define InterfaceController_H
#include "config.h"

#include <QDebug>
#include <QTimer>
#include "ui_mainwindow.h"

class InterfaceController:public QObject
{
    /* 用到信号槽即需要此宏定义 */
    Q_OBJECT
    friend class MainWindow;

private:
    Ui::MainWindow *ui;

    QTimer *askPosTimer;

public:
    ~InterfaceController();
    InterfaceController(const Config &config, Ui::MainWindow *ui, QWidget *parent = nullptr);
    InterfaceController()= delete;
    InterfaceController(const InterfaceController &) = delete;
    void operator=(const InterfaceController &) = delete;

private slots:

};
#endif

