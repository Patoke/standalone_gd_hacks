#pragma once
#include "../helpers/memory.hpp"

#define CREATE_TOGGLE(var_name, key)										\
	var_name();																\
	if(!did_toggle && GetAsyncKeyState(key)) {								\
		toggles.var_name = !toggles.var_name;								\
		printf("%s: %s\n", #var_name, toggles.##var_name## ? "on" : "off");	\
		did_toggle = true;													\
	}																		\
	else if(!GetAsyncKeyState(key) && did_toggle)							\
		did_toggle = false;													\

extern c_memory gd_memory;

struct s_hacks {

	s_hacks() {
		while (gd_memory.get_process_id() == 0) {
			gd_memory = c_memory("GeometryDash.exe");

			if (gd_memory.get_process_id() != 0) {
				break;
			}

			printf("waiting for gd..\n");

			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}

		printf("gd process found!\n");

		gd_base = gd_memory.get_module_handle("GeometryDash.exe");
	}

	// utils
	void do_toggles() {
		static bool did_toggle = false;
		static bool once = false;

		if (!once) {

			printf("	noclip bind: Middle mouse button (noclip lol)\n");
			printf("	unlock all bind: F1 (unlocks all icons and colors)\n");
			printf("	free chests: F2 (all chests for free, also bypass key chests)\n");
			printf("	free shop: F3 (all items on all shops for free)\n");
			printf("	shop bypass: F4 (lets you go into the diamonds and mechanic shop)\n");

			once = true;
		}
		
		CREATE_TOGGLE(noclip, VK_MBUTTON);
		CREATE_TOGGLE(unlockall, VK_F1);
		CREATE_TOGGLE(free_chests, VK_F2);
		CREATE_TOGGLE(free_shop, VK_F3);
		CREATE_TOGGLE(shop_bypass, VK_F4);
	}

	uintptr_t gd_base;

	// hack functions
	void noclip();
	void unlockall();
	void free_chests();
	void free_shop();
	void shop_bypass();

	// bind toggles
	struct {

		bool noclip = false;
		bool unlockall = false;
		bool free_chests = false;
		bool free_shop = false;
		bool shop_bypass = false;

	} toggles;
};