#include "bridge.hpp"
#ifndef bridge
#define bridge
extern "C" void receive(void *ptr, char *name, char *payload);

GoBridge::GoBridge(void *bus, QQuickView *view): bus(bus), view(view) {};

GoBridge::~GoBridge() {};

Q_INVOKABLE void GoBridge::ChannelSend(QString event, QJsonDocument payload) {
        receive(this->bus, event.toLocal8Bit().data(), payload.toJson().data());
    }
Q_INVOKABLE void GoBridge::Receive(char *event, char *payload) {
    emit channelReceive(QString::fromUtf8(event), QJsonDocument::fromJson(payload));
}
#endif