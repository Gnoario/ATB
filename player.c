/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <unistd.h>
#include "player.h"
#include "history.h"
#include "score.h"

character player = {
    "Specialist Goon", //nome
    35,                //level
    100,               //vida
    100,               //vida maxima
    10,                //dano
    10,                //dano mágico
    0,                 //localização
    10,                //gold
    100,               //armadura
    100,               //armadura maxima
    0,                 //turnAttack
    100,               //mana
    100,               //mana maxima
    100,               //energia
    100,               //energia maxima
    0,                 //defesa
    0,                 //str
    0,                 //intel
    0,                 //dex
    0,                 //sort
    0,                 //pontos de habilidades
    0,                 //xp
    10,                //Dano auxiliar
};

character player_remember = {
    "Kozuma", //nome
    1,        //level
    100,      //vida
    100,      //vida maxima
    10,       //dano
    10,       //dano mágico
    1,        //localização
    10,       //gold
    100,      //armadura
    100,      //armadura maxima
    0,        //turnAttack
    100,      //mana
    100,      //mana maxima
    100,      //energia
    100,      //energia maxima
    0,        //defesa
    0,        //str
    0,        //intel
    0,        //dex
    0,        //sort
    0,        //pontos de habilidades
    0,        //xp
    0,        //Dano auxiliar
};

arma arms = {
    "Espada", //tipo
    20,       //resistencia
    20,       //dano
};

spell spells[] = {
    //Level//Nome//Tag//Descrição//Dano//Heal//Energia//Mana//Número disponivel de vezes//num_max
    {0, "Força", "F", "Ataques básicos.", 10, 0, 2, 0, 100, 100},
    {0, "Olfato", "OO", "Permite à você localizar armadilhas e inimigos no local.", 0, 0, 10, 0, 2, 2},
    {1, "Concentração", "CO", "Permite à você aumentar temporariamente o dano de suas habilidades e melhora sua respiração", 0, 10, 20, 10, 2, 2},
    {2, "Meditar", "ME", "Permite à você aumentar sua vida temporiariamente e sua energia", 0, 100, 20, 10, 2, 2},
    {3, "Corte Giratório", "CG", "Desfere um golpe giratório contra o inimigo", 30, 0, 5, 0, 10, 10},
    {3, "Bola de Fogo", "BF", "Desfere uma bola mágica de fogo no inimigo", 40, 0, 0, 5, 8, 8},
    {4, "Heal", "HH", "Habilidade de healar vida", 0, 10, 0, 10, 10, 10},
    {4, "Tempesta de Aço", "TA", "Desfere um golpe frontal de katana em pontos vitais.", 50, 10, 20, 10, 5, 5},
    {4, "Cometa Arcano", "CA", "Carrega uma poderosa magia sobre o inimigo.", 60, 0, 0, 30, 3, 3},
    {5, "Posição Kaimatachi", "PK", "Desfere um golpe com sua katana capaz de cortar até rochas", 200, 0, 40, 0, 1, 1},
};

void look_self()
{
    printf("\n    Nome : %-15s", player.name);
    printf("   Level : %-15d", player.level);
    printf("     Exp : %d\n", player.xp);
    printf("  Armadura : %-15d", player.armor);
    printf(" Defesa : %d\n", player.defence);
    printf("  Dano : %-15d", player.damage);
    printf("   Magia : %d\n", player.magic);
    printf("     Força : %-15d", player.str);
    printf("     Inteligência : %d\n", player.itellect);
    printf("     Destreza : %d\n", player.dex);
    printf("    Sorte : %d\n", player.str);
    printf("  Health : %d/%d\n", player.health, player.max_health);
    printf("  Energia : %d/%d\n", player.energy, player.max_energy);
    return;
}

void look_self_ant()
{
    printf("\n Nome : %-15s", player_remember.name);
    printf("   Level : %-15d", player_remember.level);
    printf("          Exp : %d\n", player_remember.xp);
    printf(" Defesa : %-15d", player_remember.defence);
    printf(" Dano : %-15d\n", player_remember.damage);
    printf(" Magia : %-15d", player_remember.magic);
    printf("  Força : %-15d", player_remember.str);
    printf(" Inteligência : %-15d\n", player_remember.itellect);
    printf(" Destreza : %-15d", player_remember.dex);
    printf(" Sorte : %-15d\n", player_remember.str);
    printf(" Health : %d/%d", player_remember.health, player_remember.max_health);
    printf("         Energia : %d/%d\n", player_remember.energy, player_remember.max_energy);
    return;
}

void allocate_stats(int points)
{
    char i[15];
    int s;
    int done = 0;

    do
    {
        look_self_ant();
        printf("\nVocê tem %d pontos para alocar em 4 atributos diferentes.\n", points);
        printf("Qual você gostaria de aprimorar?\n");
        printf("STR, INT, DEX, LUK, DONE quando terminar de alocar os pontos ou HELP para ajuda: ");
        while (fgets(i, sizeof(i), stdin) == NULL)
            ;
        remove_newline(i);
        if (strcasecmp(i, "STR") == 0)
        {
            printf("Muito bem vai alocar em força? [%d]", points);
            while (fgets(i, sizeof(i), stdin) == NULL)
                ;
            sscanf(i, "%d", &s);
            if (s == points)
            {
                player_remember.str = player_remember.str + points;
                strength_to_damage(s);
                str_to_health(s);
                points = 0;
            }
            else if (s < points)
            {
                player_remember.str = player_remember.str + s;
                strength_to_damage(s);
                str_to_health(s);
                points = points - s;
            }
            else if (s > points)
            {
                printf("Digite um número válido.\n");
            }
            else
            {
                player_remember.str = player_remember.str + points;
                strength_to_damage(points);
                str_to_health(points);
                points = 0;
            }
        }
        else if (strcasecmp(i, "INT") == 0)
        {
            printf("Muito bem gostaria de alocar em inteligência? [%d]", points);
            while (fgets(i, sizeof(i), stdin) == NULL)
                ;
            sscanf(i, "%d", &s);
            if (s == points)
            {
                player_remember.itellect = player_remember.itellect + points;
                intellect_to_damage(s);
                points = 0;
            }
            else if (s < points)
            {
                player_remember.itellect = player_remember.itellect + s;
                intellect_to_damage(s);
                points = points - s;
            }
            else if (s > points)
            {
                printf("Por favor digite um número válido.\n");
            }
            else
            {
                player_remember.itellect = player_remember.itellect + points;
                intellect_to_damage(points);
                points = 0;
            }
        }
        else if (strcasecmp(i, "DEX") == 0)
        {
            printf("Muito bem gostaria de alocar em destreza? [%d]", points);
            while (fgets(i, sizeof(i), stdin) == NULL)
                ;
            sscanf(i, "%d", &s);
            if (s == points)
            {
                player_remember.dex = player_remember.dex + points;
                dexterity_to_defence(points);
                points = 0;
            }
            else if (s < points)
            {
                player_remember.dex = player_remember.dex + s;
                dexterity_to_defence(s);
                points = points - s;
            }
            else if (s > points)
            {
                printf("Por favor digite um número válido.\n");
            }
            else
            {
                player_remember.dex = player_remember.dex + points;
                dexterity_to_defence(points);
                points = 0;
            }
            player_remember.armor = player_remember.dex / 2;
        }
        else if (strcasecmp(i, "LUK") == 0)
        {
            printf("Muito bem gostaria de alocar em sorte? [%d]", points);
            while (fgets(i, sizeof(i), stdin) == NULL)
                ;
            sscanf(i, "%d", &s);
            if (s == points)
            {
                player_remember.sort = player_remember.sort + points;
                luk_to_critical(s);
                points = 0;
            }
            else if (s < points)
            {
                player_remember.sort = player_remember.sort + s;
                luk_to_critical(s);
                points = points - s;
            }
            else if (s > points)
            {
                printf("Por favor digite um número válido.\n");
            }
            else
            {
                player_remember.sort = player_remember.sort + points;
                luk_to_critical(points);
                points = 0;
            }
        }
        else if (strcasecmp(i, "DONE") == 0)
        {
            player_remember.points = points;
            return;
        }
        else if (strcasecmp(i, "HELP") == 0)
        {
            printf("\n\nEsses atributos influênciam em seu personagem:\n");
            printf("  Força  - Incrementa dano para ataques a mão e aumento de vida.\n");
            printf("  Inteligência - Incrementa dano para ataques basiados em mágia.\n");
            printf("  Destreza - Incrementa uma chance melhor para acertar o ataque e defesa.\n");
            printf("  Sorte - Incrementa uma melhor chance de acerto crítico.\n\n");
        }
        else
        {
            printf("Por favor, faça uma escolha válida.\n");
        }
    } while (points > 0);
    player_remember.points = 0;
    look_self_ant();

    return;
}

void dexterity_to_defence(int points)
{
    player_remember.defence = player_remember.dex * 1;
    //return;
}

/* function to convert added fortitude to health */
void str_to_health(int points)
{
    player_remember.max_health = player_remember.max_health + points;
    player_remember.health = player_remember.max_health;

    // return;
}

/* function to convert added intellect to damage if applicable */
void intellect_to_damage(int points)
{
    player_remember.magic = player_remember.itellect / 2;

    //return;
}

/* function to convert added strength to damage if applicable */
void strength_to_damage(int points)
{
    player_remember.damage = player_remember.str / 2;

    //return;
}

void luk_to_critical(int points)
{
    player_remember.damage = randomize(0, player_remember.sort);
}

void execute_training(const char *noun)
{
    int next_level = player.level * (player.level * xp_to_level);

    if (player.location != 0)
    {
        printf("Você não está no ambiente de treinamento.\n");

        return;
    }

    printf(LCYN "Vou ajudar em seu treino %s:\n" RESET, player.name);
    if (noun == NULL)
    {
        if (player.xp >= next_level)
        {
            player.level++;
            player.points += 4;
            player.max_health += 4;
            player.health = player.max_health;
            printf(WHT "  Com seu treino você pôde subir de nível %d.\n", player.level);
            printf("  Você ganhou 4 de vida e 4 pontos de habilidade. Digite "
                   "TRAIN STATS"
                   " para alocar seus pontos.\n" RESET);
            for (int i = 0; spells[i].name != NULL; i++)
            {
                if (player.level == spells[i].level)
                {
                    printf(WHT "  Você aprendeu uma nova habilidade: %s\n" RESET, spells[i].name);

                    return;
                }
            }
        }
        else
        {
            printf(WHT "  Você precisa de %d xp para avançar ao próximo nível.\n" RESET, next_level - player.xp);
        }
    }
    else if (strcasecmp(noun, "STATS") == 0)
    {
        if (player.points > 0)
        {
            allocate_stats(player.points);
        }
        else
        {
            printf(WHT "  Você não tem pontos.\n" RESET);
        }
    }
    else
    {
        printf(WHT "  Deixe de brincadeiras, pare de desperdiçar meu tempo com esse %s, faça algo válido!\n" RESET, noun);
    }

    return;
}

void execute_list_spells()
{
    int i = 0;
    int spells_available = 0;

    while (spells[i].name != NULL)
    {
        if (spells[i].level <= player_remember.level)
        {
            spells_available++;
            printf(LCYN "Nome: %-18s Tag: %s    Custo de Energia: %d   Custo de Mana: %d %d/%d \n" RESET, spells[i].name,
                   spells[i].tag,
                   spells[i].energy,
                   spells[i].mana,
                   spells[i].number,
                   spells[i].max_number);
            printf(LCYN "Dano: %d Cura: %d \n" RESET, spells[i].damage, spells[i].healing);
            printf(WHT "  %s\n" RESET, spells[i].description);
        }
        i++;
    }
    if (spells_available == 0)
    {
        printf("Você ainda não tem especiais liberados.\n");
    }

    return;
}