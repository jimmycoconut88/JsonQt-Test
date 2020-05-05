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
            if (json.contains("name") && json["name"].isString())
                temp.name = json["name"].toString();
            if (json.contains("description") && json["description"].isString())
                temp.description = json["description"].toString();
            if (json.contains("category") && json["category"].isString())
                temp.category = json["category"].toString();
            if (json.contains("price") && json["price"].isDouble())
                temp.price = json["price"].toDouble();
            if (json.contains("quantity") && json["quantity"].isArray()) {
                QJsonArray Jquantity = json["quantity"].toArray();
                quantity.clear();
                quantity.reserve(Jquantity.size());
                for (int i = 0; i < Jquantity.size(); ++i) {
                    int quanObject = Jquantity[i].toInt();
                    quantity.push_back(quanObject);
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
        for(const int &iter : quantity){
            QJsonObject qtemp;
            qtemp["quantity"] = iter;
            quanArr.append(qtemp);
        }
        temp["quantity"] = quanArr;
        menuArr.append(temp);
    }
    json["menu"] = menuArr;
}
