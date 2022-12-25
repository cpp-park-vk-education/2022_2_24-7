#include "mythread.h"

void mythread::run() {
    _client->start();
    _context.run();
}
