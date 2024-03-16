#ifndef CONFIG_H
#define CONFIG_H
#include <QString>

#define  TeachBoxJsonPath "/home/wd/workSpace/WDcontroller/config/teachBox.json"
#define  TaskJsonPath "/home/wd/workSpace/WDcontroller/config/task.json"

struct Task
{
    double data[6][7] = {0}; //6*7
};

struct Config
{
    Config(const QString & ip_in, int port_in) : ip(ip_in), port(port_in) {}
    QString ip;
    int port;
};
enum VelocityType
{
    jogVelocity = 0,
    runVelocity = 1
};
enum PlanType
{
    joint = 0,
    cartesian = 1
};
enum RobotType
{
    panda = 0,
    ur = 1
};
#endif // CONFIG_H
