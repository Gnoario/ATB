/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   misc.h
 * Author: tadeu
 *
 * Created on April 7, 2019, 7:07 PM
 */

#ifndef MISC_H
#define MISC_H

extern int randomize(int min, int max);
extern int save_player(const char *name);
extern int load_player(const char *name);
extern void show_prompt();
extern void clear_screen();
extern void remove_newline(char *str);

#endif /* MISC_H */

