#include "lib.hpp"
#include "utils.hpp"
#include "structs.hpp"
#include "types.h"
#include <string.h>

// this function actually exists in 1.0.0 but is inlined in later versions so I just recreated it for simplicity
// 0x71006fdc84 on 1.0.0
ActorBase * GetChild(ActorMgr& mgr, u32 index, ActorBase &parent) {
    u32 idx = index & 0xFFFF;
    if (mgr.count <= idx) {
        return mgr.array[0].child;
    }
    if (mgr.array[idx].parent == &parent) {
        return mgr.array[idx].child;
    }

    return nullptr;
}

// CameraXLinkControl appears to be added to PlayerCamera and EventCamera every frame so we ignore them so it's actually readable

HOOK_DEFINE_TRAMPOLINE(Add) {
    static u32 Callback(ActorMgr &actor_mgr, ActorBase &parent, ActorBase &child) {
        if (strcmp("CameraXLinkControl", child.name) && (strcmp("PlayerCamera", parent.name) || strcmp("EventCamera", parent.name))) {
            char buf[1024];
            u32 result = Orig(actor_mgr, parent, child);
            PRINT("%s child [%s] to parent [%s]", result ? "Successfully added" : "Failed to add", child.name, parent.name);
            if (parent.count > 0) {
                std::string children;
                children.reserve(1024);
                for (u32 i = 0; i < parent.count; ++i) {
                    ActorBase * child = GetChild(actor_mgr, (u32)parent.array[i], parent);
                    if (child != nullptr) {
                        children.append(child->name, strlen(child->name));
                        children.append(" ");
                    }
                }
                PRINT("%s now has %d relations: %s", parent.name, parent.count, children.c_str());
            }
            return result;
        }
        return Orig(actor_mgr, parent, child);;
    }
};

// I think the parent and child can sometimes be flipped in this function?
HOOK_DEFINE_TRAMPOLINE(Remove) {
    static u32 Callback(ActorMgr &actor_mgr, ActorBase &parent, ActorBase &child) {
        if (strcmp("CameraXLinkControl", child.name) && (strcmp("PlayerCamera", parent.name) || strcmp("EventCamera", parent.name))) {
            char buf[1024];
            u32 result = Orig(actor_mgr, parent, child);
            PRINT("%s child [%s] from parent [%s]", result ? "Successfully removed" : "Failed to remove", child.name, parent.name);
            if (parent.count > 0) {
                std::string children;
                children.reserve(1024);
                for (u32 i = 0; i < parent.count; ++i) {
                    ActorBase * child = GetChild(actor_mgr, (u32)parent.array[i], parent);
                    if (child != nullptr) {
                        children.append(child->name, strlen(child->name));
                        children.append(" ");
                    }
                }
                PRINT("%s now has %d relations: %s", parent.name, parent.count, children.c_str());
            }
            return result;
        }
        return Orig(actor_mgr, parent, child);;
    }
};