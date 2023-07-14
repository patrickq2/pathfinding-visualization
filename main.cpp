#include "cell.h"
#include "sfWindow.h"


int main() {

    sfWindow userWindow;
    while (!userWindow.exit()) {
        userWindow.update();
        userWindow.draw();
    }
    return 0;
}