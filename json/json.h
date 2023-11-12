#include <QJsonDocument>
#include <QJsonObject>

bool getJsonObjectFromFile(const QString &fileName, QJsonObject &josnObject);
bool setJsonObjectToFile(const QString &fileName, const QJsonObject &jsonObject);
