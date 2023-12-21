#include "hacks.hpp"

void s_hacks::unlockall() {
	static bool did_toggle{};

	if (toggles.unlockall != did_toggle) {
		if (toggles.unlockall) {
			// force isIconUnlocked to skip all first checks and jump straight to mov al, 1 (always return true)
			// 90 90
			uint8_t unlockall_write1[] = { 0x90, 0x90,
										   0x83, 0xFE, 0x05, // these bytes are to save a write call
										   0x90, 0x90 };
			gd_memory.write(gd_base + 0x1201A5, unlockall_write1, sizeof(unlockall_write1));

			// force isColorUnlocked to always succeed at jge (always return true)
			// 90 90
			uint8_t unlockall_write2[] = { 0x90, 0x90 };
			gd_memory.write(gd_base + 0x1206A6, unlockall_write2, sizeof(unlockall_write2));
		}
		else {
			// rewrite the old jge checks
			// 75 0C
			// 83 FE 05
			// 7D 13
			uint8_t unlockall_write1[] = { 0x75, 0x0C,
										   0x83, 0xFE, 0x05, // these bytes are to save a write call
										   0x7D, 0x13 };

			gd_memory.write(gd_base + 0x1201A5, unlockall_write1, sizeof(unlockall_write1));

			// 7D 04
			uint8_t unlockall_write2[] = { 0x7D, 0x04 };
			gd_memory.write(gd_base + 0x1206A6, unlockall_write2, sizeof(unlockall_write2));
		}
	}

	did_toggle = toggles.unlockall;
}