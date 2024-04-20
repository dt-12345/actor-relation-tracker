#pragma once

#include "types.h"

// technically only just IActor and not ActorBase but eh whatever
// GameActor inherits from ActorBase which inherits from IActor
// ActorBase is from the engine, GameActor is totk's extension of it
struct ActorBase {
    void * vtable;
    void * heap;
    s32 id;
    s32 pad;
    char * name;
    u8 morepad[0x1a0]; // I cannot be bothered to fill this all in lol
    u16 * array; // ring of actor relations, stores an index into ActorMgr's actor relation array
    u32 max;
    u32 offset;
    u32 count;
    // 29 on 1.0.0, 33 on 1.1.0+
    // fun fact, once you hit the limit, that's when things stop equipping when zuggle overloaded
    u16 relations[29];
};

struct ActorRelation {
    ActorBase * parent;
    ActorBase * child;
};

struct ActorMgr {
    u8 padding[0x2f0];
    u32 count;
    u32 pad;
    ActorRelation * array;
};