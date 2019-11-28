/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <pthread.h>
#include <unistd.h>
#include "player.h"
#include "monsters.h"
#include "score.h"

character types[] = {
    //Nome//Level//Vida//VidaMaxima//Dano//Danomagico//Localizacao//Gold//Armadura//MaxArmadura//turnAttack
    {"Goblin", 3, 20, 20, 6, 0, 0, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 15, 0},
    {"Orc", 5, 30, 30, 7, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 17, 0},
    {"Ogre", 6, 50, 50, 8, 0, 0, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 18, 0},
    {"Lord Goblin", 10, 60, 60, 9, 0, 0, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 20, 0},
    {"Goblin King", 15, 400, 400, 30, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 25, 0},
    {"Oni", 30, 300, 300, 40, 30, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 30, 0},
};

armadilha forms[] = {
    {"Veneno", 10, 0},
    {"Flechas", 5, 10},
    {"Gás", 15, 0},
    {"Armadilha terrestre", 5, 15}};

character monsters[numero_de_monstros];
armadilha armadilhas[numero_de_armadilhas];
pthread_t respawn[numero_de_monstros];
int monster_respawn_id[numero_de_monstros];

#define tipos_de_monstros (sizeof(types) / sizeof(*types))
#define tipos_de_armadilha (sizeof(forms) / sizeof(*forms))

void init_traps()
{
    for (int i = 0; i < numero_de_armadilhas; i++)
    {
        armadilhas[i] = forms[randomize(0, 4)];
        player.armor = armadilhas[i].damage_armor;
        player.health = armadilhas[i].damage_health;
        printf("Você pisou em uma armadilha infligindo %d de dano em sua vida e %d na armadura", armadilhas[i].damage_health, armadilhas[i].damage_armor);
        printf("Armadilha: %s", armadilhas[i].type);
    }
}

void init_monsters()
{
    for (int i = 0; i < 2; i++)
    { // inicializa random lvl 1 de monstros na zona inicial
        monsters[i] = types[randomize(0, 2)];
    }
}

void init_demons()
{
    for (int i = 0; i < 8; i++)
    { // initialize random lvl 1 monsters in start zone
        monsters[i] = types[1];
        monsters[i].location = 10;
    }

    for (int i = 0; i < 2; i++)
    { // random level 2 monsters for Dungeon
        monsters[i] = types[3];
        monsters[i].location = 11;
    }

    for (int i = 0; i < 5; i++)
    { // random level 2 monsters for Dungeon
        monsters[i] = types[5];
        monsters[i].location = 12;
    }

    for (int i = 0; i < numero_de_monstros; i++)
    { // Give monsters unique ID number
        monsters[i].in_combat = 100001 + i;
    }

    return;
}

void init_monsters_lvl_2()
{
    for (int i = 0; i < numero_de_monstros; i++)
    {
        monsters[i] = types[randomize(2, 3)];
    }
}

void init_monster_boss()
{
    for (int i = 0; i < numero_de_monstros; i++)
    { //lvl 3 final boss
        monsters[i] = types[4];
    }
}

int look_monsters()
{
    for (int i = 0; i < numero_de_monstros; i++)
    {
        printf("Level: %d Nome: %s.  ", monsters[i].level, monsters[i].name);
        printf("Vida: %d Dano: %d.  ", monsters[i].health, monsters[i].damage);
        if (player.health < monsters[i].health)
        {
            printf("Monstro lendário.\n");
            return 0;
        }
        else if ((player.health / 2) > monsters[i].health)
        {
            printf("Um pouco fraco.\n");
            return 0;
        }
        else
        {
            printf("Vale a pena tentar.\n");
            return 0;
        }
    }
    return 1;
}

void *respawn_wait(void *target)
{
    int i = *(int *)target;
    sleep(100000);
    monsters[i].health = monsters[i].max_health;
    pthread_exit(NULL);
    return NULL;
}

/* respawn_monster() function - respawns a killed monster after set time limit */
void respawn_monster(int m)
{
    monster_respawn_id[m] = m;

    if (monsters[m].health < 1)
    {
        pthread_create(&respawn[m], NULL, respawn_wait, &monster_respawn_id[m]);
    }
    return;
}

void check_for_duplicate(int current, int low, int high)
{
    int duplicate = 0;

    do
    {
        for (int x = 0; x < current; x++)
        {
            if (monsters[current].location == monsters[x].location)
            {
                duplicate++;
                monsters[current].location = randomize(low, high);
                break;
            }
        }
    } while (duplicate > 1);

    return;
}
