#ifndef JSONABLE_H
#define JSONABLE_H

#include <QObject>
#include<QVector>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include<QFile>
class jsonable : public QObject
{
    Q_OBJECT
public:
    /**
     * Basic constructor.
     * @param parent Pointer to parent QObject, if any.
     */
    jsonable(QObject *parent = nullptr);

    /**
     * Copy constructor.
     * @param _stall Source object.
     * @param parent Pointer to parent QObject, if any.
     */
    jsonable(const jsonable &_stall, QObject *parent = nullptr);

      jsonable &operator=(const jsonable & _other);
    QVector<int> quantity;
    QString name, description, category;
    double price;
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
signals:

};
extern QVector<jsonable> menu;
#endif // JSONABLE_H
