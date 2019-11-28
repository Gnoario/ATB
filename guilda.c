/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include "player.h"
#include "guilda.h"
#include "history.h"

guilda guild = {
    150, //Espada preço
    60, //Potion Preço
};

int resposta, reparo, reparoAux, saida = 0;

void guilda_menu() {

    menuGuilda();

    do {
        scanf("%d", &resposta);
        switch (resposta) {
            case 1: buyPot();
                espacamento();
                menuGuilda();
                break;

            case 2: buyWpn();
                espacamento();
                menuGuilda();
                break;

            case 3: repairArmor();
                espacamento();
                menuGuilda();
                break;

            case 4:
                break;

            default: printf("Opção Invalida\n");
                printf("\n");
                break;
        }
    } while (saida != 1);
    //player_location();
}

void menuGuilda(void) {
    printf("         ________________\n");
    printf("         ||            ||\n");
    printf("         ||   GUILDA   ||\n");
    printf("         ||____________||\n");
    printf("    __________________________\n");
    printf("    ||1-Comprar Poção       || \n");
    printf("    ||2-Comprar Espadas       || \n");
    printf("    ||3-Reparar Armadura    || \n");
    printf("    ||4-Saír da guilda      || \n");
    printf("    ||______________________|| \n");
    printf("\n");
}

void espacamento(void) {
    printf("\n");
    printf("\n");
    printf("\n");
}

void buyPot(void) {

    printf("\n");
    printf("Deseja comprar poções de vida ?\n");
    printf("\n");
    printf("   1-sim              2-nao    \n");
    scanf("%d", &resposta);
    if (resposta == 1) {

        if (player.gold >= guild.potion_price) {

            player.gold == player.gold - resposta;
            printf("\n");
            player.health = 100;
            printf("Aqui esta sua poção, obrigado pela preferencia\n");
            printf("\n");

        } else {

            printf("\n");
            printf("Desculpe mas voce nao tem gold suficiente\n");
            printf("\n");

        }
    }
}

void buyWpn(void) {

    printf("\n");
    printf("Deseja comprar novas espadas ?\n");
    printf("\n");
    printf("   1-sim              2-nao    \n");
    if (resposta == 1) {

        if (player.gold >= guild.sword_price) {

            player.gold == player.gold - guild.sword_price;
            printf("\n");
            printf("Aqui esta sua espada, obrigado pela preferencia\n");
            printf("\n");
            arms.durability += 20;
        } else {
            printf("\n");
            printf("Desculpe mas voce nao tem gold suficiente\n");
            printf("\n");
        }
    }
}

void repairArmor(void) {

    if (player.armor != player.max_armor) {
        reparo = 0;
        reparoAux = player.armor;
        while (reparoAux != player.max_armor) {
            reparoAux++;
            reparo++;
        }
        reparo == reparo * 2;
        printf("                              \n");
        printf("O Reparo custara %d gold\n", reparo);
        printf("\n");
        printf("Deseja reparar sua armadura ?\n");
        printf("1-sim               2-nao    \n");
        scanf("%d", &resposta);
        if (resposta == 1) {

            if (player.gold >= reparo) {

                player.gold == player.gold - reparo;
                player.armor == player.max_armor;
                printf("\n");
                printf("Sua armadura está pronta, obrigado pela preferencia\n");
                printf("\n");

            } else {

                printf("\n");
                printf("Desculpe mas voce nao tem gold suficiente\n");
                printf("\n");

            }
        }
    } else {
        printf("\n");
        printf("Sua armadura nao precisa de reparos, volte quando precisar de meus servicos\n");
        printf("\n");

    }
}




