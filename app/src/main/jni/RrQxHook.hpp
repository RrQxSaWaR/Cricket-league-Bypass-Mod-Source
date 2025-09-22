// This Project Completely Based on Dobbyhook & I didn't use any kittymemory, Substrate, A64 or mshook.

#include <jni.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
#include <sys/mman.h>
#include <list>
#include <pthread.h>
#include <thread>
#include <fstream>
#include <iostream>
#include <dlfcn.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <time.h>

#include "include.hpp"
#include "Dobby/dobby.hpp"

std::vector<uint8_t> hex_to_bytes(const char* hexStr) {
    std::vector<uint8_t> bytes;
    std::istringstream stream(hexStr);
    std::string byteStr;

    while (stream >> byteStr) {
        bytes.push_back(static_cast<uint8_t>(strtoul(byteStr.c_str(), nullptr, 16)));
    }

    return bytes;
}

uintptr_t get_lib_base(const char* libName) {
    FILE* fp = fopen("/proc/self/maps", "r");
    if (!fp) return 0;

    char line[512];
    uintptr_t base = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, libName)) {
            sscanf(line, "%lx-%*lx", &base);
            break;
        }
    }

    fclose(fp);
    return base;
}

void RrQ_Patch(const char* libName, const char* offsetStr, const char* hexBytesStr) {
    uintptr_t base = get_lib_base(libName);
    if (!base) {
        return;
    }

    uintptr_t offset = strtoul(offsetStr, nullptr, 0);
    void* target = (void*)(base + offset);

    std::vector<uint8_t> patch = hex_to_bytes(hexBytesStr);
    if (patch.empty()) {
        return;
    }

    size_t pageSize = sysconf(_SC_PAGESIZE);
    uintptr_t pageStart = (uintptr_t)target & ~(pageSize - 1);
    mprotect((void*)pageStart, pageSize, PROT_READ | PROT_WRITE | PROT_EXEC);

    memcpy(target, patch.data(), patch.size());
}

void RrQ_Hook(const char* libName, const char* offsetStr, void* hookFunc, void** origFuncPtr) {
    uintptr_t base = get_lib_base(libName);
    if (!base) {
        return;
    }

    uintptr_t offset = strtoul(offsetStr, nullptr, 0);
    void* target = (void*)(base + offset);

    if (DobbyHook(target, hookFunc, origFuncPtr) != 0) {
        return;
    }
}

// This Hook Made by @RrQ_Owner
