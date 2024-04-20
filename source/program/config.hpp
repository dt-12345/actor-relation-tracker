#pragma once

// these first three are from another thing I was trying and aren't used in this specific mod
// this first one hooks the WorldManagerModule's baseproc to print Link's current WorldMgr position
static constexpr int s_baseproc[] = {
    0x00b22a34,
    0x00af225c,
    0x00b56d34,
    0x00ae0848,
    0x00aef4b4,
    0x00b36920
};

// this one hooks AutoSaveMgr's calc function to print Link's current save position
static constexpr int s_calc[] = {
    0x00c2e288,
    0x00c2f074,
    0x00c19d90,
    0x00c26e8c,
    0x00b76848,
    0x00c2cbd0
};

// this one hooks the PlayerRef component calc function to print the Player actor's position
static constexpr int s_poshook[] = {
    0x009632b8,
    0x007eb780,
    0x007393dc,
    0x0081b924,
    0x00950e28,
    0x009e558c
};

// hooks engine::actor::ActorMgr::addActorRelation
static constexpr int s_addhook[] = {
    0x023c72a0,
    0x00dc9360,
    0x00dc13f0,
    0x00d9fc2c,
    0x00dbe8c8,
    0x00d8b0ec
};

// hooks engine::actor::ActorMgr::resolveActorRelation
static constexpr int s_removehook[] = {
    0x00ab8610,
    0x008a6c80,
    0x008082d8,
    0x008b6e90,
    0x008b8b8c,
    0x008eee60
};