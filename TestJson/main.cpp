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



    QFile loadFile(QStringLiteral("menu.json"));

    jsonable test;
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    test.read(loadDoc.object());

//    for(int i=0;i<10;i++){
//        test.name="Chicken wings";
//        test.price= 100.1;
//        test.description="Hello";
//        test.category="main dish";
//       for(int j=0;j<3;j++){
//            test.quantity.push_back(j*i);
//        }
//        menu.push_back(test);
//    }

    QFile saveFile(QStringLiteral("menu2.json"));
    QJsonObject gameObject;
    test.write(gameObject);
    QJsonDocument saveDoc(gameObject);
    saveFile.write(saveDoc.toJson());

    return app.exec();
}
