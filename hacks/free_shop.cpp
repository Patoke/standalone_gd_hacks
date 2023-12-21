#include "hacks.hpp"

void s_hacks::free_shop() {

	static bool did_toggle{};

	if (toggles.free_shop != did_toggle) {
		if (toggles.free_shop) {
			// remove GameStatsManager::setStat call from GameStatsManager::purchaseItem (don't lose money)
			// 90
			// 90
			// 90 90 90 90 90
			uint8_t free_shop_write1[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
			gd_memory.write(gd_base + 0x168223, free_shop_write1, sizeof(free_shop_write1));

			// skip GJShopLayer::showCantAffordMessage in GJShopLayer::onSelectItem
			uint8_t free_shop_write2[] = { 0xEB };
			gd_memory.write(gd_base + 0x216666, free_shop_write2, sizeof(free_shop_write2));

			// skip currency check in GameStatsManager::purchaseItem
			uint8_t free_shop_write3[] = { 0xEB };
			gd_memory.write(gd_base + 0x168205, free_shop_write3, sizeof(free_shop_write3));
		}
		else {
			// rewrite call back
			// 52
			// 50
			// E8 36 05 00 00
			uint8_t free_shop_write1[] = { 0x52, 0x50, 0xE8, 0x36, 0x05, 0x00, 0x00 };
			gd_memory.write(gd_base + 0x168223, free_shop_write1, sizeof(free_shop_write1));

			// rewrite jz conditional
			// 74
			uint8_t free_shop_write2[] = { 0x74 };
			gd_memory.write(gd_base + 0x216666, free_shop_write2, sizeof(free_shop_write2));

			// rewrite jge conditional
			// 7D
			uint8_t free_shop_write3[] = { 0x7D };
			gd_memory.write(gd_base + 0x168205, free_shop_write3, sizeof(free_shop_write3));
		}
	}

	did_toggle = toggles.free_shop;
}