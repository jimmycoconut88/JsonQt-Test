#include "jsonable.h"
QVector<jsonable> menu;
jsonable::jsonable(QObject *parent) : QObject(parent)
{
}


jsonable::jsonable(const jsonable& _json, QObject *parent)
{
    this->name = _json.name;
    this->price=_json.price;
    this->category = _json.category;
    this->description= _json.description;
    this->quantity = _json.quantity;

}

jsonable& jsonable::operator=(const jsonable &){
    return *this;
}

void jsonable::read(const QJsonObject &json){
        if (json.contains("menu") && json["menu"].isArray()) {
            QJsonArray menuArr = json["menu"].toArray();
            menu.clear();
            menu.reserve(menuArr.size());
        for(int i = 0; i < menuArr.size(); ++i){
            jsonable temp;
               QJsonObject obj = menuArr[i].toObject();
            if (obj.contains("name") && obj["name"].isString())
                temp.name = obj["name"].toString();
            if (obj.contains("description") && obj["description"].isString())
                temp.description = obj["description"].toString();
            if (obj.contains("category") && obj["category"].isString())
                temp.category = obj["category"].toString();
            if (obj.contains("price") && obj["price"].isDouble())
                temp.price = obj["price"].toDouble();


            if (obj.contains("quantity") && obj["quantity"].isArray()) {
                QJsonArray Jquantity = obj["quantity"].toArray();
                temp.quantity.clear();
                temp.quantity.reserve(Jquantity.size());
                for (int j = 0; j < Jquantity.size(); ++j) {
                    QJsonObject q = Jquantity[j].toObject();
                    int quanObject = q["quantity"].toInt();
                    temp.quantity.push_back(quanObject);
                }
            }
            menu.push_back(temp);
        }
    }
}
void jsonable::write(QJsonObject &json) const {

    QJsonArray menuArr;
    for (const jsonable &items : menu) {
        QJsonObject temp;
        temp["name"] = items.name;
        temp["description"] = items.description;
        temp["category"] = items.category;
        temp["price"] = items.price;
        QJsonArray quanArr;
        for(const int &iter : items.quantity){
            QJsonObject qtemp;
            qtemp["quantity"] = iter;
            quanArr.append(qtemp);
        }
        temp["quantity"] = quanArr;
        menuArr.append(temp);
    }
    json["menu"] = menuArr;
}
