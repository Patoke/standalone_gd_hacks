#include "hacks/hacks.hpp"

c_memory gd_memory("GeometryDash.exe");

int main() {
    
    printf("Welcome to Patoke's standalone GD hacks!\n");

    s_hacks global_hacks{};

    while (true) {
    
        global_hacks.do_toggles();

        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

}