#include "hacks.hpp"

void s_hacks::shop_bypass() {
	static bool did_toggle{};

	if (toggles.shop_bypass != did_toggle) {
		if (toggles.shop_bypass) {
			// bypass all alternative dialogs for all unlockable shops
			// EB 1D
			uint8_t shop_bypass_write[] = { 0xEB, 0x1D };
			// diamonds shop dialog SecretRewardsLayer::showDialogDiamond
			gd_memory.write(gd_base + 0x2F9A6C, shop_bypass_write, sizeof(shop_bypass_write));
			// mechanics dialog SecretRewardsLayer::showDialogMechanic
			gd_memory.write(gd_base + 0x2F90C0, shop_bypass_write, sizeof(shop_bypass_write));
			// potbors dialog SecretRewardsLayer::showDialog03
			gd_memory.write(gd_base + 0x2F86AC, shop_bypass_write, sizeof(shop_bypass_write));
			// scratchs dialog SecretRewardsLayer::showDialog01
			gd_memory.write(gd_base + 0x2F79C4, shop_bypass_write, sizeof(shop_bypass_write));
		}
		else {
			// rewrite the old jl checks
			// 0F 8C
			uint8_t shop_bypass_write[] = { 0x0F, 0x85 };
			// diamonds shop dialog
			gd_memory.write(gd_base + 0x2F9A6C, shop_bypass_write, sizeof(shop_bypass_write));
			// mechanics dialog
			gd_memory.write(gd_base + 0x2F90C0, shop_bypass_write, sizeof(shop_bypass_write));
			// potbors dialog
			gd_memory.write(gd_base + 0x2F86AC, shop_bypass_write, sizeof(shop_bypass_write));
			// scratchs dialog
			gd_memory.write(gd_base + 0x2F79C4, shop_bypass_write, sizeof(shop_bypass_write));
		}
	}

	did_toggle = toggles.shop_bypass;
}