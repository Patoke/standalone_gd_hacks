#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <TlHelp32.h>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <chrono>
#include <thread>

class c_memory {
private:
	uintptr_t process_id{};
	HANDLE process_handle{};

public:
	[[nodiscard]] c_memory(const char* process_name) {
		PROCESSENTRY32 entry = { };
		entry.dwSize = sizeof(PROCESSENTRY32);

		const HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		while (Process32Next(snapshot, &entry)) {
			if (!strcmp(process_name, entry.szExeFile)) {
				process_id = entry.th32ProcessID;
				process_handle = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_READ | PROCESS_VM_OPERATION, FALSE, process_id);
				break;
			}
		}

		// Free handle
		if (snapshot)
			CloseHandle(snapshot);
	}

	// Destructor that frees the opened handle
	~c_memory() {
		if (process_handle)
			CloseHandle(process_handle);
	}

	// Returns the base address of a module by name
	[[nodiscard]] uintptr_t get_module_handle(const char* module_name) {
		MODULEENTRY32 entry = { };
		entry.dwSize = sizeof(MODULEENTRY32);

		const HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, process_id);

		uintptr_t result = 0;

		while (Module32Next(snapshot, &entry)) {
			if (!strcmp(module_name, entry.szModule)) {
				result = reinterpret_cast<uintptr_t>(entry.modBaseAddr);
				break;
			}
		}

		if (snapshot)
			CloseHandle(snapshot);

		return result;
	}

	// Read process memory
	template <typename T>
	[[nodiscard]] const T read(const uintptr_t address) {
		T value = { };
		ReadProcessMemory(process_handle, reinterpret_cast<const void*>(address), &value, sizeof(T), NULL);
		return value;
	}

	template <typename T>
	void write(const uintptr_t address, const T& value) {
		WriteProcessMemory(process_handle, reinterpret_cast<void*>(address), &value, sizeof(T), NULL);
	}

	void write(const uintptr_t address, const uint8_t* value, uint32_t size) {
		WriteProcessMemory(process_handle, reinterpret_cast<void*>(address), value, size, NULL);
	}

	[[nodiscard]] uintptr_t get_process_id() {
		return process_id;
	}
};