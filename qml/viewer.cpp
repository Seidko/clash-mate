#include <QtCore/QUrl>
#include <QtCore/QMetaObject>
#include <QtQuick/QQuickView>

void *NewViewer() {
    return new QQuickView();
}

void *NewViewerWithSource(char *url) {
    return new QQuickView(QUrl(url));
}

void SetSource(void* ptr, char* url) {
    QQuickView *view = static_cast<QQuickView*>(ptr);
    QMetaObject::invokeMethod(view, "setSource", Q_ARG(QUrl, QUrl(QString(url))));
}
