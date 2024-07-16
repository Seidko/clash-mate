#include <QtCore/QUrl>
#include <QtCore/QJsonDocument>
#include <QtCore/QObject>
#include <QtCore/QMetaObject>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlContext>

class GoBridge : public QObject
{
    Q_OBJECT
public:
    void *bus;
    QQuickView *view;
    explicit GoBridge(void *bus, QQuickView *view);
    virtual ~GoBridge();
    Q_INVOKABLE void ChannelSend(QString event, QJsonDocument payload);
    Q_INVOKABLE void Receive(char *event, char *payload);
signals:
    void channelReceive(QString event, QJsonDocument payload);
};
