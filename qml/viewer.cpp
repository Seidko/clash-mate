#include <QtCore/QUrl>
#include <QtCore/QJsonDocument>
#include <QtCore/QObject>
#include <QtCore/QMetaObject>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlContext>
#include <cstdlib>

extern "C" void receive(void *ptr, char *name, char *payload);

class GoBridge : public QObject
{
    Q_OBJECT
public:
    void *bus;
    QQuickView *view;
    GoBridge(void *bus, QQuickView *view): bus(bus), view(view) {};
    virtual ~GoBridge() {};
    Q_INVOKABLE void Send(QString event, QJsonDocument payload) {
        receive(this->bus, event.toLocal8Bit().data(), payload.toJson().data());
    }
    Q_INVOKABLE void Receive(char *event, char *payload) {
        QMetaObject::invokeMethod(this, event, Q_ARG(QJsonDocument, QJsonDocument::fromJson(payload)));
    }
};

extern "C" {
// void *NewBridge(void *bus) {
//     return new GoBridge(bus);
// }

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

void **NewViewer(void *bus, char *source) {
    QQuickView *view = new QQuickView();
    if (source) {
        QMetaObject::invokeMethod(view, "setSource", Q_ARG(QUrl, QUrl(source)));
    }
    GoBridge *bridge = new GoBridge(bus, view);
    void **ptr = (void **)malloc(2 * sizeof(size_t));
    ptr[0] = view;
    ptr[1] = bridge;
    return ptr;
}

void SetSource(void* ptr, char* url) {
    QQuickView *view = static_cast<QQuickView*>(ptr);
    QMetaObject::invokeMethod(view, "setSource", Q_ARG(QUrl, QUrl(url)));
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
