/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   history.h
 * Author: tadeu
 *
 * Created on April 7, 2019, 7:47 PM
 */
#include "guilda.h"
extern int load_locations();
//extern void print_exit(const char *tag);
extern void load_history(const char *name);
//extern void pause();
extern void move_player(int direction);
//extern void player_location();
extern void getch();
extern void menu();
extern void execute_show_exits();
extern void execute_look(const char *noun);
extern void execute_quest();
void quests_available_p(int i);
void print_exits(int loc);
#ifndef HISTORY_H
#define HISTORY_H

typedef struct {
  int room_id;
  char *description;
  char *tag;
  char *tag_prolog;
  int north;
  int south;
  int east;
  int west;
  int up;
  int down;
} location;

typedef struct
{
  int quest_id;
  char *description;
  int in_quest;
  int exp;
} quest;


extern location locations[];

#endif /* HISTORY_H */

#define RED   "\x1B[31m"
#define LRED  "\x1B[91m"
#define GRN   "\x1B[32m"
#define LGRN  "\x1B[92m"
#define YEL   "\x1B[33m"
#define LYEL  "\x1B[93m"
#define BLU   "\x1B[34m"
#define LBLU  "\x1B[94m"
#define MAG   "\x1B[35m"
#define LMAG  "\x1B[95m"
#define CYN   "\x1B[36m"
#define LCYN  "\x1B[96m"
#define WHT   "\x1B[37m"
#define LWHT  "\x1B[97m"
#define RESET "\x1B[0m"