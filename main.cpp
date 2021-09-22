#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "include/authhandler.h"
#include "include/todomodel.h"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    AuthHandler auth;
    auth.setAPIKey("AIzaSyCYebtMxuQsBGkjdi3MFR70g2TpQncmqoM");
    QString baseUrl = "http://localhost:8080/api";
    QString add_p = "/add_to_do";
    QString delete_p = "/delete_todo";
    QString update_p = "/update_todo";
    QString get_p = "/get_todos";

    ToDoModel model(baseUrl, add_p, delete_p, update_p, get_p);

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.rootContext()->setContextProperty("auth", &auth);
    engine.rootContext()->setContextProperty("todoModel", &model);

    engine.load(url);

    return app.exec();
}
