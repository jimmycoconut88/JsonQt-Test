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






    jsonable test;

    QFile loadFile(QStringLiteral("menu.json"));
   if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }
    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    test.read(loadDoc.object());
    loadFile.close();





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




    QFile saveFile(QStringLiteral("menu.json"));
    QJsonObject gameObject;
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }
    test.write(gameObject);
    QJsonDocument saveDoc(gameObject);
    saveFile.write(saveDoc.toJson());
    saveFile.close();




    return app.exec();
}
