#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include<jsonable.h>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);


//////////////////////////////////////////////////////////////////////////////////////



    jsonable test;
////Loading save File process
    QFile loadFile(QStringLiteral("menu.json"));    //Load named file
   if (!loadFile.open(QIODevice::ReadOnly)) {       //Checking process watch the warning window to see notification
        qWarning("Couldn't open save file.");
        return false;
    }
    QByteArray saveData = loadFile.readAll();      //Read the file and save it into a temp var
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));   //Load the temp into a Json Document form in order to pass it as a JSON object
    test.read(loadDoc.object());                    //Use the read function
    loadFile.close();                               //Close the file
/////Loading save File process


/////Testing

//    for(int i=0;i<10;i++){
        test.name="Buffalo wings";
        test.price= 200;
        test.description="Not Hello";
        test.category="SIDE dish";
//       for(int j=0;j<3;j++){
//            test.quantity.push_back(j*i);
//        }
        menu.push_back(test);
//    }

/////Testing


    QFile saveFile(QStringLiteral("menu.json"));    //Get the file u want to save
    QJsonObject gameObject;                         //declare a Json OBJ var to store
    if (!saveFile.open(QIODevice::WriteOnly)) {     //check the file to see if its open
        qWarning("Couldn't open save file.");
        return false;
    }
    test.write(gameObject);                         //Use the Defined write function in order to store the data into the declared jsonObject
    QJsonDocument saveDoc(gameObject);              //Turns it into JsonDocument
    saveFile.write(saveDoc.toJson());               //write the Document into the file
    saveFile.close();                               //Close the file




    return app.exec();
}
