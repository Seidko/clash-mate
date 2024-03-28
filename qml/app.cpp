#include <QtWidgets/QApplication>
#include <QtGui/QFont>
#include <QtGui/QIcon>
#include <QtCore/QString>
#include <QtCore/QByteArray>
#include <QtCore/QList>

extern "C" {
void *NewApplication(int argc, char **argv) {
    return new QApplication(argc, argv);
}

void SetAttribute(long long attribute, bool on) {
    QApplication::setAttribute(Qt::ApplicationAttribute(attribute), on);
}

void SetFont(char *family, int pointSize, int weight, bool italic) {
    QFont font = QFont(QString(family), pointSize, weight, italic);
    QApplication::setFont(font);
}

void SetQuitOnLastWindowClosed(bool quit) {
    QApplication::setQuitOnLastWindowClosed(quit);
}

void SetApplicationDisplayName(char* name) {
	QApplication::setApplicationDisplayName(QString(name));
}

void SetWindowIcon(char* fileName) {
    QIcon icon = QIcon(QString(fileName));
    QApplication::setWindowIcon(icon);
}

void SetApplicationName(char* name) {
    QApplication::setApplicationName(QString(name));
}

void SetApplicationVersion(char* version) {
    QApplication::setApplicationVersion(QString(version));
}

void SetOrganizationName(char* name) {
    QApplication::setOrganizationName(QString(name));
}

void SetOrganizationDomain(char* domain) {
    QApplication::setOrganizationDomain(QString(domain));
}

int Exec() {
    return QApplication::exec();
}
}