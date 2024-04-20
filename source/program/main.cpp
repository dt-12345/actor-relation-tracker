#include "lib.hpp"

#include "nn/util/util_snprintf.hpp"
#include "nn.hpp"
#include "simpleio.h"
#include "utils.hpp"
#include "config.hpp"
#include "hooks.hpp"
#include "binaryoffsethelper.h"

extern "C" void exl_main(void* x0, void* x1) {

    char buf[500];

    /* Setup hooking enviroment */
    exl::hook::Initialize();

    PRINT("Getting app version...");
    int version = InitializeAppVersion();
    if (version == 0xffffffff || version > 5) {
        PRINT("Error getting version");
        return;
    }
    PRINT("Version index %d", version);

    PRINT("Hooking functions...");
    Add::InstallAtOffset(s_addhook[version]);
    Remove::InstallAtOffset(s_removehook[version]);
    PRINT("Hook successful");
    
    PRINT("Disclaimer: CameraXLinkControl being added to either PlayerCamera or EventCamera will be ignored to avoid spam");

    return;
}

extern "C" NORETURN void exl_exception_entry() {
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}