#include <QtGui/QGuiApplication>
#include <QtGui/QFont>
#include <QtGui/QIcon>
#include <QtCore/QString>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtQml/QQmlApplicationEngine>
#include "bridge.hpp"

extern "C" {
void *NewApplication(int argc, char **argv) {
    return new QGuiApplication(argc, argv);
}

void SetAttribute(long long attribute, bool on) {
    QGuiApplication::setAttribute(Qt::ApplicationAttribute(attribute), on);
}

void SetFont(char *family, int pointSize, int weight, bool italic) {
    QFont font = QFont(QString(family), pointSize, weight, italic);
    QGuiApplication::setFont(font);
}

void SetQuitOnLastWindowClosed(bool quit) {
    QGuiApplication::setQuitOnLastWindowClosed(quit);
}

void SetApplicationDisplayName(char* name) {
	QGuiApplication::setApplicationDisplayName(QString(name));
}

void SetWindowIcon(char* fileName) {
    QIcon icon = QIcon(QString(fileName));
    QGuiApplication::setWindowIcon(icon);
}

void SetApplicationName(char* name) {
    QGuiApplication::setApplicationName(QString(name));
}

void SetApplicationVersion(char* version) {
    QGuiApplication::setApplicationVersion(QString(version));
}

void SetOrganizationName(char* name) {
    QGuiApplication::setOrganizationName(QString(name));
}

void SetOrganizationDomain(char* domain) {
    QGuiApplication::setOrganizationDomain(QString(domain));
}

int Exec() {
    qmlRegisterType<GoBridge>("GoBridge", 1, 0, "GoBridge");
    return QGuiApplication::exec();
}
}