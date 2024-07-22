#ifndef InterfaceController_H
#define InterfaceController_H
#include "h/config.h"
#include "controller/communicationController.h"
#include <QTimer>
#include <QMainWindow>
#include <QListWidgetItem>

#include "ui_teachBox.h"

class InterfaceController:public QObject
{
    /* 用到信号槽即需要此宏定义 */
    Q_OBJECT
    friend class MainWindow;
    friend class CommunicationController;
private:
    Ui::MainWindow *ui;
    ReferenceManager *referenceManager;

public:
    ~InterfaceController();
    InterfaceController(const Config &config, ReferenceManager *referenceManager, Ui::MainWindow *ui, QWidget *parent = nullptr);
    InterfaceController()= delete;
    InterfaceController(const InterfaceController &) = delete;
    void operator=(const InterfaceController &) = delete;

    // 交互处理逻辑
    void functionPageSwitching(QListWidgetItem *current, QListWidgetItem *previous, CommunicationController *communicationController);
    void setIPandPort(bool checked, CommunicationController *communicationController);
    void changeVelocity(VelocityType velocityType, bool isPlus, CommunicationController *communicationController);
    void changeMoveGoal(int index, bool checked, Space space);
    void teachPosition(int index, Space teachSpace);

private slots:

};
#endif

