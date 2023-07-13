#include "cell.h"
#include "sfWindow.h"
#include "graph.h"

int main() {

    sfWindow userWindow;
    while (!userWindow.exit()) {
        userWindow.update();
    }
    return 0;
}