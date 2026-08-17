<<<<<<< HEAD
#include "LMS.h"
//#include "SFMLUI.h"
#include <iostream>

namespace sf {}
using namespace std;
using namespace sf;


static bool setupSystem(LMS& system) {
    if (!system.initialize()) {
        std::cout << "Failed to initialize data files.\n";
        return false;
    }
    if (!system.loadData()) {
        std::cout << "Failed to load data files.\n";
        return false;
    }
    return true;
}

/*static void launchApplication(HospitalSystem& system) {
#ifdef HMS_ENABLE_SFML  
    SFMLUI ui;
    ui.run(system);
#else
    system.run();
#endif
}*/   //For SFML, Stay Tuned

int main() {
    HospitalSystem system;
    if (!setupSystem(system)) {
        return 1;
    }
    launchApplication(system);
=======
#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
    


>>>>>>> 94e9b7a2f74ebe09b6fd888c20e8ab592196d9b3
    return 0;
}