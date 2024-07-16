#include <stdint.h>

void **NewViewer(uintptr_t bus, char *source);
void SetSource(void* ptr, char* url);
void SetSourceFromQml(void *ptr, char *qml);
void SetResizeMode(void* ptr, int resizeMode);
void SetHeight(void* ptr, int height);
void SetWidth(void* ptr, int width);
void Show(void* ptr);
void Reload(void* ptr);
void *NewBridge(void *bus);
void ReceiveEvent(void *ptr, char *event, char *payload);
extern void receive(void *ptr, char *name, char *payload);