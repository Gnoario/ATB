/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   monsters.h
 * Author: tadeu
 *
 * Created on April 4, 2019, 3:33 PM
 */
#include "player.h"
#include "score.h"

extern void init_monsters();
extern void init_monsters_lvl_2();
extern void init_monster_boss();
extern void init_traps();
extern int look_monsters();
extern void respawn_monster(int m);
extern void init_demons();
void check_for_duplicate(int current, int low, int high);


#ifndef MONSTERS_H
#define MONSTERS_H
extern character monsters[];
extern armadilha armadilhas[];
#define numero_de_monstros 20
#define numero_de_armadilhas 1

#endif /* MONSTERS_H */

