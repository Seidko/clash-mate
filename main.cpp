//go:build ignore
#include <qguiapplication.h>
#include <qquickview.h>
#include <qurl.h>
#include "libclash.h"

int main(int argc, char* argv[]) {
    auto app = new QGuiApplication(argc, argv);
    app->setApplicationDisplayName("clash mate");

    auto view = new QQuickView();
    view->setSource(QUrl("res/main.qml"));
    view->setResizeMode(QQuickView::SizeRootObjectToView);
    view->show();
	app->exec();
    
}