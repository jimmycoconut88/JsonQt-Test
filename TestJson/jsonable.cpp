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
        if (json.contains("menu") && json["menu"].isArray()) {  //Find if an Array item named menu exist
            QJsonArray menuArr = json["menu"].toArray();        //Convert it to a JSONArray obj to use easily
            menu.clear();                                       //Clear memory
            menu.reserve(menuArr.size());                       //alocate the needed space for the array
        for(int i = 0; i < menuArr.size(); ++i){                //For loop to run through all of Jsonarray obj
            jsonable temp;                                      //set a temporary storing variable
               QJsonObject obj = menuArr[i].toObject();         //transfer an Array element into a Json obj
            if (obj.contains("name") && obj["name"].isString())
                temp.name = obj["name"].toString();             //use the sotring variable to store an element of the Json Obj, remember to declare the correct elements and variable type
            if (obj.contains("description") && obj["description"].isString())
                temp.description = obj["description"].toString();
            if (obj.contains("category") && obj["category"].isString())
                temp.category = obj["category"].toString();
            if (obj.contains("price") && obj["price"].isDouble())
                temp.price = obj["price"].toDouble();


            if (obj.contains("quantity") && obj["quantity"].isArray()) {    //it is also possible to look for array element within an element
                QJsonArray Jquantity = obj["quantity"].toArray();           //Convert the obj array element into Json array
                temp.quantity.clear();
                temp.quantity.reserve(Jquantity.size());
                for (int j = 0; j < Jquantity.size(); ++j) {                //For loop running thru the json array
                    QJsonObject q = Jquantity[j].toObject();                // store an array element into a Json obj (remember to convert to is object)
                    int quanObject = q["quantity"].toInt();                 //Similar to the process above extract the Json Obj element u want
                    temp.quantity.push_back(quanObject);                    //Store the info
                }
            }
            menu.push_back(temp);                                           //Store the temporary obj into ur using variable
        }
    }
}
void jsonable::write(QJsonObject &json) const {

    QJsonArray menuArr;                                         //Declare a json array obj to store elements
    for (const jsonable &items : menu) {                        //for loop to run through ur variable list that also store the list elements into items
        QJsonObject temp;                                       //Declare temporary Json Obj to store wanted elements
        temp["name"] = items.name;                              //Proceed to declare the elements name and store its data
        temp["description"] = items.description;
        temp["category"] = items.category;
        temp["price"] = items.price;
        QJsonArray quanArr;                                     //For an array within array case, Declare another json array obj
        for(const int &iter : items.quantity){                  //similar discipline as the above for loop this time store in a variable with ur wanted type named iter
            QJsonObject qtemp;
            qtemp["quantity"] = iter;
            quanArr.append(qtemp);                              //Push the array element into Json Array object
        }
        temp["quantity"] = quanArr;                             //Store the entire json array object as an element
        menuArr.append(temp);                                   //Push the array element into Json Array object
    }
    json["menu"] = menuArr;                                     //Finally Store the entire Big array object into a json object to pass it into the file.
}
