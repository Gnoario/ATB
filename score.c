/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include "score.h"
#include "player.h"
#include "history.h"


int randomize(int min, int max){
    srand(time(NULL));
    max = min + (rand() % max);
    return max;
    
}

int save_player(const char *name)
{
  char dir[30];
  strcpy(dir, "PLAYERS/");
  FILE *file = NULL;



  // open the file in write mode
  file = fopen(strcat(dir, name), "w+");

  // always check return values to see if it was opened okay
  if(file == NULL) {
    fprintf(stderr, "Error opening file for writing.\n");
    return 1;
  }

  fprintf(file, "%s\n", player.name);
  fprintf(file, "%d\n", player.level);
  fprintf(file, "%d\n", player.armor);
  fprintf(file, "%d\n", player.max_armor);
  /* give the player 1 vida after death before saving */
  if (player.health <= 0) { 
    player.health = 1;
  }
  fprintf(file, "%d\n", player.health);
  fprintf(file, "%d\n", player.max_health);
  fprintf(file, "%d\n", player.damage);
  fprintf(file, "%d\n", player.magic);
  fprintf(file, "%d\n", player.location);
  fprintf(file, "%d\n", player.gold);
  fprintf(file, "%d\n", player.defence);
  fprintf(file, "%d\n", player.str);
  fprintf(file, "%d\n", player.itellect);
  fprintf(file, "%d\n", player.dex);
  fprintf(file, "%d\n", player.sort);
  fprintf(file, "%d\n", player.points);  
  // never forget to close the file
  fclose(file);
  return 0;
}

int load_player(const char *name)
{
  FILE *file = NULL;
  char dir[30];

  strcpy(dir, "./dist/debug/Cygwin_1-Windows/PLAYERS/");

  char str[25];
  char tok[25];


  file = fopen(strcat(dir, name), "r");

  if (file == NULL) {
    printf("That user name does not exist.\n");
    return 1;
  }

  fgets(str, sizeof(str), file);
  strcpy(tok, strtok(str, "\n"));
  player.name = malloc(strlen(tok)+1);
  strcpy(player.name, tok);          
  fgets(str, sizeof(str), file);
  player.level = atoi(str);
  fgets(str, sizeof(str), file);
  player.armor = atoi(str);
  fgets(str, sizeof(str), file);
  player.health = atoi(str);
  fgets(str, sizeof(str), file);
  player.max_health = atoi(str);
  fgets(str, sizeof(str), file);
  player.damage = atoi(str);
  fgets(str, sizeof(str), file);
  strcpy(tok, strtok(str, "\n"));
  fgets(str, sizeof(str), file);
  player.location = atoi(str);
  fgets(str, sizeof(str), file);
  player.gold = atoi(str);
  fgets(str, sizeof(str), file);

  fclose(file);

  printf("\nWelcome back %s, the level %d\n", player.name, player.level);
  return 0;
}

void show_prompt()
{
  if (player.health < (player.max_health * 0.3)) {
    printf("\n[" LRED "%d" RESET "|%d]> ", player.health, player.energy);             // show health in red when below 30%
  }
  else {
    printf("\n[%d|%d]> ", player.health, player.energy);                              // Player prompt
  }
  fflush(stdout);                                            // flush the line buffer         

  return;
}

void clear_screen()
{
  printf("\e[1;1H\e[2J");

  return;
}

/* remove_newline() - removes the "\n" from the end of a string */
void remove_newline(char *s)
{
  if (strlen(s) > 1) {
    s[strlen(s) - 1] = '\0';
  }

  return;
}
