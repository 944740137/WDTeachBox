#include "referenceManager.h"
#include<QDebug>
ReferenceManager::~ReferenceManager()
{

}
ReferenceManager::ReferenceManager(Ui::MainWindow *ui, QWidget *parent):ui(ui)
{
    Q_UNUSED(parent);

    this->runPageNowJointPosition << ui->J1pos_Label2 << ui->J2pos_Label2<< ui->J3pos_Label2
              << ui->J4pos_Label2 << ui->J5pos_Label2 << ui->J6pos_Label2 << ui->J7pos_Label2;
    this->runPageNowCartesianPosition<< ui->C1pos_Label2 << ui->C2pos_Label2<< ui->C3pos_Label2
                                     << ui->C4pos_Label2 << ui->C5pos_Label2 << ui->C6pos_Label2;

    jointRunningQueueGroup.append({ui->J11_lineEdit, ui->J12_lineEdit, ui->J13_lineEdit,ui->J14_lineEdit,
                                   ui->J15_lineEdit,ui->J16_lineEdit,ui->J17_lineEdit});
    jointRunningQueueGroup.append({ui->J21_lineEdit, ui->J22_lineEdit, ui->J23_lineEdit,ui->J24_lineEdit,
                                   ui->J25_lineEdit,ui->J26_lineEdit,ui->J27_lineEdit});
    jointRunningQueueGroup.append({ui->J31_lineEdit, ui->J32_lineEdit, ui->J33_lineEdit,ui->J34_lineEdit,
                                   ui->J35_lineEdit,ui->J36_lineEdit,ui->J37_lineEdit});
    jointRunningQueueGroup.append({ui->J41_lineEdit, ui->J42_lineEdit, ui->J43_lineEdit,ui->J44_lineEdit,
                                   ui->J45_lineEdit,ui->J46_lineEdit,ui->J47_lineEdit});
    jointRunningQueueGroup.append({ui->J51_lineEdit, ui->J52_lineEdit, ui->J53_lineEdit,ui->J54_lineEdit,
                                   ui->J55_lineEdit,ui->J56_lineEdit,ui->J57_lineEdit});
    jointRunningQueueGroup.append({ui->J61_lineEdit, ui->J62_lineEdit, ui->J63_lineEdit,ui->J64_lineEdit,
                                   ui->J65_lineEdit,ui->J66_lineEdit,ui->J67_lineEdit});

    cartesianRunningQueueGroup.append({ui->C11_lineEdit, ui->C12_lineEdit, ui->C13_lineEdit,ui->C14_lineEdit,ui->C15_lineEdit,ui->C16_lineEdit});
    cartesianRunningQueueGroup.append({ui->C21_lineEdit, ui->C22_lineEdit, ui->C23_lineEdit,ui->C24_lineEdit,ui->C25_lineEdit,ui->C26_lineEdit});
    cartesianRunningQueueGroup.append({ui->C31_lineEdit, ui->C32_lineEdit, ui->C33_lineEdit,ui->C34_lineEdit,ui->C35_lineEdit,ui->C36_lineEdit});
    cartesianRunningQueueGroup.append({ui->C41_lineEdit, ui->C42_lineEdit, ui->C43_lineEdit,ui->C44_lineEdit,ui->C45_lineEdit,ui->C46_lineEdit});
    cartesianRunningQueueGroup.append({ui->C51_lineEdit, ui->C52_lineEdit, ui->C53_lineEdit,ui->C54_lineEdit,ui->C55_lineEdit,ui->C56_lineEdit});
    cartesianRunningQueueGroup.append({ui->C61_lineEdit, ui->C62_lineEdit, ui->C63_lineEdit,ui->C64_lineEdit,ui->C65_lineEdit,ui->C66_lineEdit});

    runPageChangeMoveGoal << ui->runQueue_enable_Btn13 << ui->runQueue_enable_Btn23<< ui->runQueue_enable_Btn33
                               << ui->runQueue_enable_Btn43 << ui->runQueue_enable_Btn53 << ui->runQueue_enable_Btn63;
}


