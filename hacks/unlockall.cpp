#include "hacks.hpp"

void s_hacks::unlockall() {
	static bool did_toggle{};

	if (toggles.unlockall != did_toggle) {
		if (toggles.unlockall) {
			// force isIconUnlocked to always succeed at second jge (always return true)
			// 90 90
			uint8_t unlockall_write1[] = { 0x90, 0x90 };
			gd_memory.write(gd_base + 0x1201AA, unlockall_write1, sizeof(unlockall_write1));

			// force isColorUnlocked to always succeed at second jge (always return true)
			// 90 90
			uint8_t unlockall_write2[] = { 0x90, 0x90 };
			gd_memory.write(gd_base + 0x1206A6, unlockall_write2, sizeof(unlockall_write2));
		}
		else {
			// rewrite the old jge checks
			// 7D 13
			uint8_t unlockall_write1[] = { 0x7D, 0x13 };
			gd_memory.write(gd_base + 0x1201AA, unlockall_write1, sizeof(unlockall_write1));

			// 7D 04
			uint8_t unlockall_write2[] = { 0x7D, 0x04 };
			gd_memory.write(gd_base + 0x1206A6, unlockall_write2, sizeof(unlockall_write2));
		}
	}

	did_toggle = toggles.unlockall;
}