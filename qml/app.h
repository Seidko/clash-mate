#include <stdbool.h>

void *NewApplication(int argc, char **argv);

void SetAttribute(long long attr, bool on);

void SetFont(char *family, int size, int weight, bool italic);

void SetQuitOnLastWindowClosed(bool quit);

void SetApplicationDisplayName(char* name);

void SetWindowIcon(char* fileName);

void SetApplicationName(char* name);

void SetApplicationVersion(char* version);

void SetOrganizationName(char* name);

void SetOrganizationDomain(char* domain);

int Exec();