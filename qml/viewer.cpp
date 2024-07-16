#include <QtCore/QUrl>
#include <QtCore/QJsonDocument>
#include <QtCore/QObject>
#include <QtCore/QMetaObject>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlContext>
#include "bridge.hpp"


extern "C" {
void ReceiveEvent(void *ptr, char *event, char *payload) {
    GoBridge *bridge = static_cast<GoBridge*>(ptr);
    bridge->Receive(event, payload);
}

// void ConnectBridge(void *bridgePtr, void *viewerPtr) {
//     GoBridge *bridge = static_cast<GoBridge*>(bridgePtr);
//     QQuickView *view = static_cast<QQuickView*>(viewerPtr);
//     QObject::destroyed();
//     view->rootContext()->connect(bridge->sender);
// }

void **NewViewer(uintptr_t bus, char *source) {
    auto view = new QQuickView((QWindow*)bus);
    if (source) {
        QMetaObject::invokeMethod(view, "setSource", Q_ARG(QUrl, QUrl(source)));
    }
    GoBridge *bridge = new GoBridge((void*)bus, view);
    // view->rootContext()->setContextProperty(QString("GoBridge"), bridge);
    void **ptr = (void **)malloc(2 * sizeof(size_t));
    ptr[0] = view;
    ptr[1] = bridge;
    return ptr;
}

void SetSource(void* ptr, char* url) {
    QQuickView *view = static_cast<QQuickView*>(ptr);
    view->setSource(QUrl(url));
    // QMetaObject::invokeMethod(view, "setSource", Q_ARG(QUrl, QUrl(url)));
}

void SetSourceFromQml(void *ptr, char *qml) {
    QUrl dataurl(QByteArray(qml).toPercentEncoding().prepend("data:,"));
    QQuickView *view = static_cast<QQuickView*>(ptr);
    QMetaObject::invokeMethod(view, "setSource", Q_ARG(QUrl, dataurl));
}

void SetResizeMode(void* ptr, int resizeMode) {
    QQuickView *view = static_cast<QQuickView*>(ptr);
    view->setResizeMode(QQuickView::ResizeMode(resizeMode));
}

void SetHeight(void* ptr, int height) {
    QQuickView *view = static_cast<QQuickView*>(ptr);
    view->setHeight(height);
}

void SetWidth(void* ptr, int width) {
    QQuickView *view = static_cast<QQuickView*>(ptr);
    view->setWidth(width);
}

void Show(void* ptr) {
    QQuickView *view = static_cast<QQuickView*>(ptr);
    view->show();
}

void Reload(void* ptr) {
    QQuickView *view = static_cast<QQuickView*>(ptr);
    view->engine()->clearComponentCache();
    QUrl url = view->source();
    QMetaObject::invokeMethod(view, "setSource", Q_ARG(QUrl, url));
}
}
