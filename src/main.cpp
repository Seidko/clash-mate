//go:build ignore
#include <qaction.h>
#include <qicon.h>
#include <qmenu.h>
#include <qapplication.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qpalette.h>
#include <qqmlengine.h>
#include <qstring.h>
#include <qquickview.h>
#include <qsystemtrayicon.h>
#include <qfilesystemwatcher.h>
#include <qurl.h>
#include "libclash.h"

int main(int argc, char* argv[]) {
    auto app = new QApplication(argc, argv);
    app->setApplicationDisplayName("clash mate");
    app->setQuitOnLastWindowClosed(false);

    auto view = new QQuickView();
    view->setSource(QUrl("res/main.qml"));
    view->setResizeMode(QQuickView::SizeRootObjectToView);
    view->setColor(app->palette().color(QPalette::ColorRole::Window));

    QFileSystemWatcher qmlwatcher;
    qmlwatcher.addPath("./res");
    QObject::connect(&qmlwatcher, &QFileSystemWatcher::directoryChanged, [&]() {
        view->engine()->clearComponentCache();
        QUrl url = view->source();
        view->setSource(url);
    });
    
    auto tray = new QSystemTrayIcon(app);
    auto menu = new QMenu();
    auto quit = new QAction("Exit");
    auto show = new QAction("Show");
    QObject::connect(show, &QAction::triggered, [&] {
        view->show();
    });
    QObject::connect(quit, &QAction::triggered, [&] {
        app->quit();
    });
    QObject::connect(tray, &QSystemTrayIcon::activated, [=](QSystemTrayIcon::ActivationReason r){
        if(r == QSystemTrayIcon::ActivationReason::Trigger) emit show->triggered();
    });
    menu->addAction(show);
    menu->addSeparator();
    menu->addAction(quit);
    tray->setIcon(QIcon("res/test.png"));
    tray->setContextMenu(menu);

    Launch();

    view->show();
    tray->show();

	app->exec();
}