#include "hacks.hpp"

void s_hacks::noclip() {
	static bool did_toggle{};

	if (toggles.noclip != did_toggle) {
		if (toggles.noclip) {
			// write rel jmp to skip destroyPlayer
			// E9 9C 07 00
			uint8_t noclip_write[] = { 0xE9, 0x9C, 0x07, 0x00 };
			gd_memory.write(gd_base + 0x2E0AD9, noclip_write, sizeof(noclip_write));
		}
		else {
			// rewrite the old jnz check
			// 0F 85 9B 07
			uint8_t noclip_write[] = { 0x0F, 0x85, 0x9B, 0x07 };
			gd_memory.write(gd_base + 0x2E0AD9, noclip_write, sizeof(noclip_write));
		}
	}

	did_toggle = toggles.noclip;
}