#include "client_task.h"
#include <iostream>

void Client_task::run() {
    for (int i = 0; i < requests_to_send; ++i) {
        buffer.enqueue(Data(name, "data"));
    }
    std::cout << "CLIENT DONE\n";
}
