/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   player.h
 * Author: tadeu
 *
 * Created on April 4, 2019, 3:34 PM
 */

#ifndef PLAYER_H
#define PLAYER_H

typedef struct
{
    char *name;     //  nome
    int level;      // lvl do personagem
    int health;     // vida atual
    int max_health; // vida maxima
    int damage;     // dano
    int magic;      //dano magico
    int location;   // location number in the locations array
    int gold;       // gold (dinheiro)
    int armor;      // armadura atual
    int max_armor;  //armadura maxima
    int in_combat;
    int mana;
    int max_mana;
    int energy;
    int max_energy;
    int defence;
    int str;
    int itellect;
    int dex;
    int sort;
    int points;
    int xp;
    int auxDamage;
} character;

typedef struct {
  int level;
  char *name;
  char *tag;
  char *description;
  int damage;
  int healing;
  int energy;
  int mana;
  int number;
  int max_number;
} spell;

typedef struct
{
    char form[20];  //nome
    int durability; //resistencia da arma
    int damage;     // dano da arma
} arma;

typedef struct
{
    char type[20];     //nome da armadilha
    int damage_health; // dano na vida
    int damage_armor;  // dano na armadura
} armadilha;

typedef struct
{
    //atributos de preços para os objetos na guilda
    int sword_price;
    int potion_price;
} guilda;

extern void look_self();
extern void look_self_ant();
extern void allocate_stats(int points);
extern void execute_list_spells();
extern void execute_training(const char *noun);
void fortitude_to_health(int points);
void intellect_to_damage(int points);
void strength_to_damage(int points);
void dexterity_to_defence(int points);
void str_to_health(int points);
void luk_to_critical(int points);
extern character player_remember;
extern character player;
extern spell spells[];
extern arma arms;

#define xp_to_level 200

#endif /* PLAYER_H */
