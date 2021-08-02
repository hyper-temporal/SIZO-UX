#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWidgets/QApplication>
#include <QtQuick/QQuickView>
#include <QtCore/QDir>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlContext>


#include "Models/treemodel.h"
#include "Models/iomodel.h"
#include "dronde.h"
#include "ondestore.h"
#include "dsonde.h"
#include "drpotard.h"
#include "drfader.h"
#include "drxy.h"
#include "drenveloppe.h"
#include "PianoRoll/drgantt.h"
#include "drgraphe.h"

#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickWindow>
#include <QtGui/QImageReader>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QMimeDatabase>
#include <QtCore/QStandardPaths>
#include <QtCore/QUrl>

#include <QQuickView>



int main(int argc, char *argv[])
{

    qmlRegisterType<DrXY>("DrTools", 1, 0, "DrXY");
    qmlRegisterType<DrFader>("DrTools", 1, 0, "DrFader");
    qmlRegisterType<DrPotard>("DrTools", 1, 0, "DrPotard");
    qmlRegisterType<DrOnde1D>("DrTools", 1, 0, "DrOnde");
    qmlRegisterType<TreeModel>("DrTools", 1, 0, "TreeModel");
    qmlRegisterType<DrGanttOptim>("DrTools", 1, 0, "Enveloppe");
    qmlRegisterType<DrGantt>("DrTools", 1, 0, "Gantt");
    qmlRegisterType<DrGraphe>("DrTools", 1, 0, "Arbre");

    QApplication app(argc, argv);
    QQuickView viewer;
#ifdef Q_OS_WIN
    QString extraImportPath(QStringLiteral("%1/../../../../%2"));
#else
    QString extraImportPath(QStringLiteral("%1/../../../%2"));
#endif
    viewer.engine()->addImportPath(
                extraImportPath.arg(
                    QGuiApplication::applicationDirPath(),
                    QString::fromLatin1("qml")));
    QObject::connect(viewer.engine(), &QQmlEngine::quit, &viewer, &QWindow::close);
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    viewer.setMinimumSize({400,400});
    viewer.setColor(QColor("#404040"));

    std::string chses="./564.json";

    OndeStore dssmckr;
    QQmlContext *ctxt = viewer.rootContext();
    ctxt->setContextProperty("OndeStore", &dssmckr);
    viewer.setSource(QUrl("qrc:/QML/main.qml"));
    viewer.show();
    return app.exec();
}
