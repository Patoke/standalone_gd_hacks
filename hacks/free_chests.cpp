#include "hacks.hpp"

void s_hacks::free_chests() {

	static bool did_toggle{};

	if (toggles.free_chests != did_toggle) {
		if (toggles.free_chests) {
			// abuse first jle for each chest key cost to always return on first case and be always 0
			// all of these done in the following functions: (in order)
			//	GameStatsManager::unlockSecretChest
			//	GameStatsManager::recountSpecialStats
			//	SecretRewardsLayer::onSelectItem
			// (this is an inlined function, GameStatsManager::keyCostForSecretChest)
			// 90 90
			// B8 00
			uint8_t free_chests_write1[] = { 0x90, 0x90, 0xB8, 0x00 };
			gd_memory.write(gd_base + 0x17811B, free_chests_write1, sizeof(free_chests_write1));
			gd_memory.write(gd_base + 0x172E0D, free_chests_write1, sizeof(free_chests_write1));
			gd_memory.write(gd_base + 0x2F6DCE, free_chests_write1, sizeof(free_chests_write1));

			// write over the key check in SecretRewardsLayer::onSpecialItem
			// E9 5D 01 00
			uint8_t free_chests_write2[] = { 0xE9, 0x5D, 0x01, 0x00 };
			gd_memory.write(gd_base + 0x2F742A, free_chests_write2, sizeof(free_chests_write2));

			// write over the key check in SecretRewardsLayer::onSelectItem
			// E9 D7 01 00
			uint8_t free_chests_write3[] = { 0xE9, 0xD7, 0x01, 0x00 };
			gd_memory.write(gd_base + 0x2F6E18, free_chests_write3, sizeof(free_chests_write3));
		}
		else {
			// 7E 07
			// B8 64
			uint8_t free_chests_write1[] = { 0x7E, 0x07, 0xB8, 0x64 };
			gd_memory.write(gd_base + 0x17811B, free_chests_write1, sizeof(free_chests_write1));
			gd_memory.write(gd_base + 0x172E0D, free_chests_write1, sizeof(free_chests_write1));
			gd_memory.write(gd_base + 0x2F6DCE, free_chests_write1, sizeof(free_chests_write1));

			// 0F 8D 5C 01
			uint8_t free_chests_write2[] = { 0x0F, 0x8D, 0x5C, 0x01 };
			gd_memory.write(gd_base + 0x2F742A, free_chests_write2, sizeof(free_chests_write2));

			// 0F 8D D6 01
			uint8_t free_chests_write3[] = { 0x0F, 0x8D, 0xD6, 0x01 };
			gd_memory.write(gd_base + 0x2F6E18, free_chests_write3, sizeof(free_chests_write3));
		}
	}

	did_toggle = toggles.free_chests;
}