// This Project Made by @RrQ_Owner

#include "RrQxHook.hpp"
#define TARGET_LIB_NAME oxorany("libil2cpp.so")

typedef void (*tLoginBypass)(void* instance);
tLoginBypass oLoginBypass = nullptr;

void LoginBypass_Hook(void* instance) {
    if (!instance)return;

    _BYTE* loginFlag = (_BYTE*)((uintptr_t)instance + 0x10);
    *loginFlag = 1;

    time_t now = time(NULL);   
}

void* RrQxthread(void*) {

	while (!get_lib_base(TARGET_LIB_NAME)) {
        sleep(1);
    }
    
    // Use Patch if you want or use Hook if you want, choice is yours.
    
    // Class : public class PlayCoreEventHandler : MonoBehaviour
    
    RrQ_Patch(TARGET_LIB_NAME, "0x3358098", "00 00 80 D2 C0 03 5F D6"); // public static void HandleEvent(Action action) { }
    
    //RrQ_Hook(TARGET_LIB_NAME, "0x3358098", (void*)LoginBypass_Hook, (void**)&oLoginBypass); // public static void HandleEvent(Action action) { }
    
    return nullptr;
}

__attribute__((constructor)) void _init() {
pthread_t thread;
pthread_create(&thread, 0, RrQxthread, 0);
}

// Smooth and optimise Project