#include <HsFFI.h>
#ifdef __GLASGOW_HASKELL__
#include "Safe_stub.h"
extern void __stginit_Safe(void);
#endif
#include <stdio.h>
#include "player.h"
#include "monsters.h"

int main(int argc, char *argv[])
{
    int i;
    int i2;
    int i3;
    hs_init(&argc, &argv);
#ifdef __GLASGOW_HASKELL__
    hs_add_root(__stginit_Safe);
#endif
    player_remember.health = sub_hs(player_remember.health, monsters[1].damage);
    player_remember.damage = actionValueLuck(player_remember.damage, player_remember.sort);
    // player_remember.damage = actionValueInt(player_remember.damage, player_remember.wis);
    // player_remember.damage = actionValueDex(player_remember.damage, player_remember.dex);
    printf("Vida: %d\n", player_remember.health);
    printf("Dano: %d: ", player_remember.damage);
    hs_exit();
    return 0;
}