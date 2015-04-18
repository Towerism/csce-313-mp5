#include "client_task.h"

void Client_task::run() {
    for (int i = 0; i < requests_to_send; ++i) {
        buffer.enqueue(Data(name, ""));
    }
}
