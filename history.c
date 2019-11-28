/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include "history.h"
#include "player.h"
#include "score.h"
#include "combat.h"
#include "guilda.h"
#include "monsters.h"

int resposta;
int contador = 0;
int opcao;
int repetir;
int espada;
int goblins;
int tocha;
int carisma;
int choice;

int number_of_locations;
location locations[400];

quest quests[] = {
    {3, "Enquanto você estava em sua casa ela foi atacada, faça uma escolha.", 0, 50},
    {4, "Seu mestre quer ensiná-lo, faça sua escolha do que você deseja.", 0, 50},
    {8, "Para completar, preciso que aperfeiçoe sua concentração.", 0, 300},
    {9, "Sinta, se torne perceptivo!.", 0, 200},
    {7, "Para completar esse teste, é preciso passar um tempo na floresta aperfeiçoando suas técnicas de percepção.", 0, 200},
    {6, "Após você completar todas as missões, a sua última missão é cortar essa pedra.", 0, 100},
};

void execute_quest()
{
    int i = 0;
    int quests_available = 0;
    int resposta;
    while (quests[i].description != NULL)
    {
        if (quests[i].quest_id == player_remember.location)
        {
            if (quests[i].in_quest == 0)
            {
                quests_available++;
                printf("Nesse local há uma quest disponível\n");
                printf("Deseja realizar?\n1.Sim\n2.Não");
                scanf("%d", &resposta);
                if (resposta == 1)
                {
                    quests_available_p(i);
                }
            }
            else
            {
                printf("Você já completou essa missão, aguarde um pouco!!");
            }
        }
        i++;
    }
    if (quests_available == 0)
    {
        printf("Não tem nenhuma quest disponível nesse local, ou você já completou, espere um pouco para refaze-la");
    }
}

void quests_available_p(int i)
{
    int reposta;
    if (quests[i].quest_id == 3)
    {
        printf(RED "%s", quests[i].description);
        printf("1. Se esconder\n2. Tentar ajudar sua irmã");
        scanf("%d", &resposta);
        switch (reposta)
        {
        case 1:
            printf("Você se esconde enquanto, sua irmã é dizimada pelos monstros");
            quests[i].in_quest = 1;
            player_remember.xp = player_remember.xp + quests[i].exp;
            printf(BLU "Você ganhou %d de experiência\n", quests[i].exp);
            break;
        case 2:
            printf("Sua irmã prefere a sua vida do que a dela e te arremessa em um porão, enquanto você assiste tudo.");
            quests[i].in_quest = 1;
            player_remember.xp = player_remember.xp + quests[i].exp;
            printf(BLU "Você ganhou %d de experiência\n", quests[i].exp);
        default:
            printf("Não há tempo para brincadeiras, você foi jogado no porão.");
            quests[i].in_quest = 1;
            player_remember.xp = player_remember.xp + quests[i].exp;
            printf(BLU "Você ganhou %d de experiência\n", quests[i].exp);
            break;
        }
    }
    else if (quests[i].quest_id == 4)
    {
        printf(RED "%s", quests[i].description);
        printf("1. Seguir o caminho da vingança\n2. Se tornar forte para proteger as pessoas");
        scanf("%d", &resposta);
        switch (reposta)
        {
        case 1:
            printf("Você escolheu o caminho da vingança, sua jornada será sozinha e fria\n");
            quests[i].in_quest = 1;
            player_remember.str = player_remember.str + 10;
            player_remember.xp = player_remember.xp + quests[i].exp;
            printf(BLU "Seu ódio se tornou em força, sua força atual é: %d", player_remember.str);
            printf(BLU "Você ganhou %d de experiência\n", quests[i].exp);
            break;
        case 2:
            printf("Você escolheu o caminho para proteger as pessoas, um herói louvável.\n");
            quests[i].in_quest = 1;
            player_remember.itellect = player_remember.itellect + 10;
            player_remember.xp = player_remember.xp + quests[i].exp;
            printf(BLU "Você sua inteligência atual é: %d", player_remember.itellect);
            printf(BLU "Você ganhou %d de experiência\n", quests[i].exp);
        default:
            printf("Não há tempo para brincadeiras.");
            quests[i].in_quest = 1;
            player_remember.sort = player_remember.sort + 10;
            player_remember.xp = player_remember.xp + quests[i].exp;
            printf(YEL "Por sorte seu mestre te aceitou, ele vai te dar um jeito, sua sorte atual é: %d\n", player_remember.sort);
            printf(BLU "Você ganhou %d de experiência\n", quests[i].exp);
            break;
        }
    }
    else if (quests[i].quest_id == 6)
    {
        char resposta = 3;
        int j;
        if (quests[0].in_quest == 1 && quests[1].in_quest == 1 &&
            quests[2].in_quest == 1 && quests[3].in_quest == 1 && quests[4].in_quest == 1)
        {
            do
            {
                j++;
                printf(RED "%s", quests[i].description);
                printf("Existe apenas 4 tentativas.\n");
                printf("Digite a tag da habilidade que deseja usar para cortar a pedra:\n");
                execute_list_spells();
                scanf(" %c", &resposta);
                switch (resposta)
                {
                case 'PK':
                    if (player_remember.energy > 0 && player_remember.mana > 0)
                    {
                        printf("Você desfere um golpe fatal, e corta a pedra ao meio.");
                        player_remember.xp = player_remember.xp + quests[i].exp;
                        printf(BLU "Você ganhou %d de experiência\n", quests[i].exp);
                        quests[i].in_quest = 1;
                        i = 4;
                    }
                    else
                    {
                        printf("Você não tem mana ou energia suficiente");
                    }
                    break;

                default:
                    printf("Você errou.");
                    break;
                }

            } while (j != 4);
        }
        else
        {
            printf("Complete todas as missões para participar dessa!");
        }
    }
    else if (quests[i].quest_id == 7)
    {
        char resposta = 3;
        int j;
        do
        {
            j++;
            printf(RED "%s", quests[i].description);
            printf("Existe apenas 4 tentativas.\n");
            printf("Digite a tag da habilidade que deseja usar para sobreviver à floresta:\n");
            execute_list_spells();
            scanf(" %c", &resposta);
            switch (resposta)
            {
            case 'F':
                if (player_remember.energy > 0 && player_remember.mana > 0)
                {
                    printf("Utiliza sua força para sair de armadilhas.");
                    player_remember.xp = player_remember.xp + quests[i].exp;
                    printf(BLU "Você ganhou %d de experiência\n", quests[i].exp);
                    quests[i].in_quest = 1;
                    i = 4;
                }
                else
                {
                    printf("Você não tem mana ou energia suficiente");
                }
                break;

            case 'OO':
                if (player_remember.energy > 0 && player_remember.mana > 0)
                {
                    printf("Utiliza seu sentido de olfato para sentir as armadilhas.");
                    player_remember.xp = player_remember.xp + quests[i].exp;
                    printf(BLU "Você ganhou %d de experiência\n", quests[i].exp);
                    quests[i].in_quest = 1;
                    i = 4;
                }
                else
                {
                    printf("Você não tem mana ou energia suficiente");
                }
                break;

            default:
                printf("Você errou.");
                break;
            }

        } while (j != 4);
    }
    else if (quests[i].quest_id == 8)
    {
        char resposta = 3;
        int j;
        do
        {
            j++;
            printf(RED "%s", quests[i].description);
            printf("Existe apenas 4 tentativas.\n");
            printf("Digite a tag da habilidade que deseja usar para sobreviver à floresta:\n");
            execute_list_spells();
            scanf(" %c", &resposta);
            switch (resposta)
            {
            case 'CO':
                if (player_remember.energy > 0 && player_remember.mana > 0)
                {
                    printf("Utiliza sua concentração para se manter vivo e respirando em um ar rarefeito.");
                    player_remember.xp = player_remember.xp + quests[i].exp;
                    printf(BLU "Você ganhou %d de experiência\n", quests[i].exp);
                    quests[i].in_quest = 1;
                    i = 4;
                }
                else
                {
                    printf("Você não tem mana ou energia suficiente");
                }
                break;

            case 'ME':
                if (player_remember.energy > 0 && player_remember.mana > 0)
                {
                    printf("Utiliza sua meditação para se concentrar e manter sua energia no frio.");
                    player_remember.xp = player_remember.xp + quests[i].exp;
                    printf(BLU "Você ganhou %d de experiência\n", quests[i].exp);
                    quests[i].in_quest = 1;
                    i = 4;
                }
                else
                {
                    printf("Você não tem mana ou energia suficiente");
                }
                break;

            default:
                printf("Você errou.");
                break;
            }

        } while (j != 4);
    }
    else if (quests[i].quest_id == 9)
    {
        char resposta = 3;
        int j;
        do
        {
            j++;
            printf(RED "%s", quests[i].description);
            printf("Existe apenas 4 tentativas.\n");
            printf("Digite a tag da habilidade que deseja usar para sobreviver à floresta:\n");
            execute_list_spells();
            scanf(" %c", &resposta);
            switch (resposta)
            {
            case 'F':
                if (player_remember.energy > 0 && player_remember.mana > 0)
                {
                    printf("Utiliza sua força para sair de armadilhas.");
                    player_remember.xp = player_remember.xp + quests[i].exp;
                    printf(BLU "Você ganhou %d de experiência\n", quests[i].exp);
                    i = 4;
                }
                else
                {
                    printf("Você não tem mana ou energia suficiente");
                }
                break;

            case 'OO':
                if (player_remember.energy > 0 && player_remember.mana > 0)
                {
                    printf("Utiliza seu sentido de olfato para sentir as armadilhas.");
                    player_remember.xp = player_remember.xp + quests[i].exp;
                    printf(BLU "Você ganhou %d de experiência\n", quests[i].exp);
                    i = 4;
                }
                else
                {
                    printf("Você não tem mana ou energia suficiente");
                }
                break;

            default:
                printf("Você errou.");
                break;
            }

        } while (j != 4);
    }
}

void execute_look(const char *noun)
{
    int monsters_near = 0;

    if (noun != NULL && strcasecmp(noun, "SELF") == 0)
    {
        look_self();
    }
    else if (noun == NULL || strcasecmp(noun, "AROUND") == 0)
    {
        printf(LMAG "\n%s :\n" RESET, locations[player_remember.location].tag);
        printf("    %s\n", locations[player_remember.location].description);
        print_exits(player_remember.location);
        printf("\n" RESET);
        for (int i = 0; i < numero_de_monstros; i++)
        {
            if (player_remember.location == monsters[i].location && monsters[i].health > 0)
            {
                if (monsters_near == 0)
                {
                    printf(YEL "Alguns monstros apareceram: %s", monsters[i].name);

                    monsters_near++;
                }
                else if (monsters_near > 0)
                {
                    printf(", ");
                    printf("%s", monsters[i].name);

                    monsters_near++;
                }
            }
        }
        if (monsters_near > 0)
        {
            printf(" nas proximidades.\n" RESET);
        }
    }
    else
    {
        if (look_monsters(noun) == 0)
        {

            return;
        }
        printf("Não existe nenhum %s aqui.\n", noun);
    }

    return;
}

int load_locations()
{
    FILE *file = NULL;

    int i = 0;
    char buffer[500];
    char tok[500];

    file = fopen("LOCATION/locations.dat", "r");

    if (file == NULL)
    {
        printf("ERROR - Couldn't load locations.dat.\n");
        pause();
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        if (strstr(buffer, "#") != NULL)
        {
            continue;
        }
        else
        {
            strcpy(tok, strtok(buffer, "\n"));
            locations[i].room_id = atoi(tok);
            //printf("room_id: %d\n", locations[i].room_id);
            fgets(buffer, sizeof(buffer), file);
            strcpy(tok, strtok(buffer, "\n"));
            locations[i].tag = malloc(strlen(tok) + 1);
            strcpy(locations[i].tag, tok);
            //printf("Tag: %s\n", locations[i].tag);
            fgets(buffer, sizeof(buffer), file);
            strcpy(tok, strtok(buffer, "\n"));
            locations[i].tag_prolog = malloc(strlen(tok) + 1);
            strcpy(locations[i].tag_prolog, tok);
            //printf("Tag prolog: %s\n", locations[i].tag_prolog)
            fgets(buffer, sizeof(buffer), file);
            strcpy(tok, strtok(buffer, "\n"));
            locations[i].description = malloc(strlen(tok) + 1);
            strcpy(locations[i].description, tok);
            //printf("Description: %s\n", locations[i].description);
            fgets(buffer, sizeof(buffer), file);
            strcpy(tok, strtok(buffer, ","));
            locations[i].north = atoi(tok);
            strcpy(tok, strtok(NULL, ","));
            locations[i].south = atoi(tok);
            strcpy(tok, strtok(NULL, ","));
            locations[i].east = atoi(tok);
            strcpy(tok, strtok(NULL, ","));
            locations[i].west = atoi(tok);
            strcpy(tok, strtok(NULL, ","));
            locations[i].up = atoi(tok);
            strcpy(tok, strtok(NULL, "\n"));
            locations[i].down = atoi(tok);
            //printf("movement: %d,%d,%d,%d,%d,%d\n", locations[i].north,locations[i].south,
            //  locations[i].east,locations[i].west,locations[i].up,locations[i].down);
            i++;
        }
    }
    fclose(file);

    number_of_locations = i;
    printf("Locais carregados...\n");

    return 0;
}
//
//void print_exit(const char *tag) {
//    int i = 0;
//    load_locations(tag);
//    printf("a historia é : %s", locations[i].description);
//}

void move_player(int direction)
{
    int i = 0;

    while (direction != locations[i].room_id)
    {
        i++;
    }
    printf("Caminhando para %s\n\n", locations[i].tag);
    player_remember.location = i;
    execute_look("around");

    return;
}

void load_history(const char *name)
{
    char dir[30];
    strcpy(dir, "./HISTORY/");
    FILE *file;
    file = fopen(strcat(dir, name), "r");

    if (file == NULL)
    {
        printf("Não foi possível abrir!");
        getchar();
        exit(0);
    }
    char historia[300];
    while (fgets(historia, 300, file) != NULL)
    {
        printf("%s", historia);
        printf("\n");
    }

    fclose(file);
}

// void player_location()
// {
//     if (player.location == 1)
//     {
//         caverna_stage_1();
//     }
//     else if (player.location == 2)
//     {
//         caverna_stage_2();
//     }
//     else if (player.location == 3)
//     {
//         caverna_stage_3();
//     }
//     else
//     {
//         printf("Do you not save.");
//     }
// }

// void pause()
// {
//     printf("Press enter for continue...\n");
//     getch();
//     //    getchar();
// }
// void getch()
// {
//     printf(" ");
//     system("read tecla");
//     printf("\n");
// }

void execute_show_exits()
{
    printf(LCYN "Obvious Exits:\n" WHT);
    if (locations[player_remember.location].north > 0)
    {
        printf("  NORTH - %s\n", locations[locations[player_remember.location].north].tag);
    }
    if (locations[player_remember.location].south > 0)
    {
        printf("  SOUTH - %s\n", locations[locations[player_remember.location].south].tag);
    }
    if (locations[player_remember.location].east > 0)
    {
        printf("  EAST  - %s\n", locations[locations[player_remember.location].east].tag);
    }
    if (locations[player_remember.location].west > 0)
    {
        printf("  WEST  - %s\n", locations[locations[player_remember.location].west].tag);
    }
    if (locations[player_remember.location].up > 0)
    {
        printf("  UP    - %s\n", locations[locations[player_remember.location].up].tag);
    }
    if (locations[player_remember.location].down > 0)
    {
        printf("  DOWN  - %s\n", locations[locations[player_remember.location].down].tag);
    }
    printf(RESET);

    return;
}

void print_exits(int loc)
{
    int number_of_exits = 0;
    char exits[6][10];
    int north = 0;
    int south = 0;
    int east = 0;
    int west = 0;
    int up = 0;
    int down = 0;

    if (locations[loc].north > 0)
    {
        number_of_exits++;
    }
    if (locations[loc].south > 0)
    {
        number_of_exits++;
    }
    if (locations[loc].east > 0)
    {
        number_of_exits++;
    }
    if (locations[loc].west > 0)
    {
        number_of_exits++;
    }
    if (locations[loc].up > 0)
    {
        number_of_exits++;
    }
    if (locations[loc].down > 0)
    {
        number_of_exits++;
    }

    for (int i = 0; i < number_of_exits; i++)
    {
        if (locations[loc].north > 0 && north == 0)
        {
            strcpy(exits[i], "north");
            north = 1;
        }
        else if (locations[loc].south > 0 && south == 0)
        {
            strcpy(exits[i], "south");
            south = 1;
        }
        else if (locations[loc].east > 0 && east == 0)
        {
            strcpy(exits[i], "east");
            east = 1;
        }
        else if (locations[loc].west > 0 && west == 0)
        {
            strcpy(exits[i], "west");
            west = 1;
        }
        else if (locations[loc].up > 0 && up == 0)
        {
            strcpy(exits[i], "up");
            up = 1;
        }
        else if (locations[loc].down > 0 && down == 0)
        {
            strcpy(exits[i], "down");
            down = 1;
        }
    }

    printf(LGRN "Exits: ");
    if (number_of_exits == 1)
    {
        printf("%s." RESET, exits[0]);
    }
    else if (number_of_exits == 2)
    {
        printf("%s and %s." RESET, exits[0], exits[1]);
    }
    else if (number_of_exits == 3)
    {
        printf("%s, %s and %s." RESET, exits[0], exits[1], exits[2]);
    }
    else if (number_of_exits == 4)
    {
        printf("%s, %s, %s and %s." RESET, exits[0], exits[1], exits[2], exits[3]);
    }
    else if (number_of_exits == 5)
    {
        printf("%s, %s, %s, %s and %s." RESET, exits[0], exits[1], exits[2], exits[3], exits[4]);
    }

    return;
}

/*
void menu()
//Função do menu inicial do jogo
{
    int resposta;
    printf("\t                                 \n");
    printf("\t                                \n");
    printf("\t           ``.                   \n");
    printf("\t          .+++''#+               \n");
    printf("\t         .,  .`;+#               \n");
    printf("\t         ,`++++++,               \n");
    printf("\t        .  +++++#                \n");
    printf("\t       .  `#+`+#+#               \n");
    printf("\t      .    .+,,'#+##:            \n");
    printf("\t     .      ```+;+####`          \n");
    printf("\t  ````       `;++;####++,        \n");
    printf("\t   `````        ++:'++#+,++++    \n");
    printf("\t  ``   `````   ;'#:++'+#++++++   \n");
    printf("\t `.        ``..` ''++##++++++++  \n");
    printf("\t `             ``...,++'+++++++  \n");
    printf("\t               ++':`.`#+'++++++# \n");
    printf("\t            `++++#+#.,'++'+++++#`\n");
    printf("\t           ;+++++##+': `+'++++###\n");
    printf("\t          '++++'  #+++   ' ,++###\n");
    printf("\t          +++#     ##++  +    ###\n");
    printf("\t          ++#+#`    +++        +#\n");
    printf("\t            `;+'`    +++       :#\n");
    printf("\t               +:    `#+        `\n");
    printf("\t               .#     ,+#        \n");
    printf("\t                :      ,##       \n");
    printf("\t                        +#       \n");
    printf("\t                         #'      \n");
    printf("\t                         ''      \n");
    printf("\t                          '      \n");
    printf("\t                         .+      \n");
    printf("\t                         +#      \n");
    printf("\t                                \n");
    printf("\tAdventurous: The Begginning\n");
    printf("\n");
    pause();
    //iniciando o diálogo com o personagem

    //printf("---------------------------------------------------------------------------------------------------------------\n");

    //printf("                                 ---------------------------------- \n");
    printf("\t1: Start \n");
    printf("\t2: Continue\n");
    printf("\t3: Close  \n");
    //printf("---------------------------------- \n");
    scanf("%d", &resposta);
    switch (resposta)
    // switch para escolher entre iniciar um novo jogo, continuar um antigo ou sair.
    {
    case 1:
        load_history("Beginning.txt");
        pause();
        intro();
        break;
    case 2:
        // simulação de jogos salvos para continuar
        load_player("Specialist Goon");
        pause();
        player_location();
        break;

    case 3:
        // usuário saiu do jogo
        printf("\n Game closed \n");
        return 0;
        break;

    default:
        printf("\n invalid option \n ");
        break;
    }
}

void intro()
{
    load_history("Introduction.txt");
    scanf("%d", &resposta);
    switch (resposta)
    {
    case 1:
        load_history("Option.txt");
        carisma + 10;
        break;
    case 2:
        load_history("OptionTwo.txt");
        break;
    default:
        load_history("Default.txt");
        carisma - 20;
        break;
    }
    pause();
    load_history("Continuation.txt");
    scanf("%d", &resposta);
    switch (resposta)
    {
    case 1:
        load_history("Answer.txt");
        carisma + 20;
        break;
    case 2:
        load_history("AnswerTwo.txt");
        break;
    default:
        load_history("AnswerDafault.txt");
        carisma - 10;
        choice - 1;
        break;
    }
    pause();
    load_history("Follow.txt");
    pause();
    caverna_stage_1();
}

void caverna_stage_1()
{
    player.location = 1;
    save_player("Specialist Goon");
    repetir = 0;
    do
    {
        load_history("Cave.txt");
        scanf("%d", &resposta);
        switch (resposta)
        {
        case 1:
            load_history("CaveOne.txt");
            repetir = 0;
            break;

        case 2:
            load_history("CaveTwo.txt");
            repetir = 1;
            break;
        default:
            load_history("CaveDefault.txt");
            choice - 1;
            break;
        }
    } while (repetir != 1);
    pause();

    repetir = 0;
    do
    {
        load_history("Tools.txt");
        scanf("%d", &resposta);
        switch (resposta)
        {
        case 1:
            fight_stage_1();
            repetir = 1;
            break;

        case 2:
            guilda_menu();
            repetir = 3;
            break;

        default:
            init_traps();
            repetir = 3;
            break;
        }
    } while (repetir != 1);
    pause();

    repetir = 0;
    do
    {
        load_history("Decision.txt");
        scanf("%d", &resposta);
        switch (resposta)
        {
        case 1:
            load_history("DecisionOne.txt");
            repetir = 1;
            break;

        case 2:
            load_history("DecisionTwo.txt");
            scanf("%d", &resposta);
            if (resposta == 1)
            {
                espada = 1;
            }
            else
            {
                espada = 0;
            }
            printf("You return to the fork\n");
            repetir = 0;
            break;

        case 3:
            load_history("DecisionThree.txt");
            scanf("%d", &resposta);
            if (resposta == 1)
            {
                load_history("Information.txt");
            }
            else
            {
            }
            printf("You return to the two inputs\n");
            repetir = 3;
            break;
        default:
            init_traps();
            repetir = 4;
            choice - 1;
            break;
        }
    } while (repetir != 1);

    pause();

    repetir = 0;
    do
    {
        load_history("Unwinding.txt");
        scanf("%d", &resposta);
        switch (resposta)
        {
        case 1:
            if (tocha = 0)
            {
                printf("\n");
                printf("There is no torch near you.");
                break;
            }
            else
            {
                printf("\n");
                load_history("Torch.txt");
                printf("\n");
                goblins = +6;
                repetir = 0;
                tocha = 0;
                break;
            }

        case 2:
            printf("\n");
            load_history("UnwindingThree.txt");
            repetir = 1;
            break;
        default:
            printf("\n");
            load_history("UnwindingDefault.txt");
            repetir = 4;
            break;
        }
    } while (repetir != 1);

    pause();
    repetir = 0;
    do
    {
        scanf("%d", &resposta);
        switch (resposta)
        {
            //printf("\n");
            load_history("Time.txt");
        case 1:
            printf("\n");
            load_history("TimeOne.txt");
            printf("\n");
            printf("You return to the guild with the survivors.\n");
            repetir = 1;
            break;

        case 2:
            printf("\n");
            load_history("TimeTwo.txt");
            fight_stage_2();
            printf("You return to the guild with the survivors.\n");
            repetir = 1;
            break;
        default:
            init_traps();
            break;
        }
    } while (repetir != 1);

    caverna_stage_2();
}

void caverna_stage_2()
{
    repetir = 0;
    player.location = 2;
    save_player("Specialist Goon");
    guilda_menu();
    do
    {
        scanf("%d", &resposta);
        switch (resposta)
        {

            printf("Após retornar para guilda salvando as aventureiras sobreviventes, Claire a sacerdotisa decide te seguir, para salvar a esposa do aldeão\n");
            printf("Coming back from where they stopped, you meet again with goblins, prepared\n");
            printf("What do you want to do now?\n");
            printf("1: Fight\n");
            printf("2: Return to the guild\n");
        case 1:
            fight_stage_2();
            break;

        case 2:
            guilda_menu();
            break;

        default:
            init_traps();
            break;
        }
    } while (repetir != 1);
    repetir = 0;
    do
    {
        printf("After the battle at a turning point, you start walking again to proceed into the cave\n");
        printf("Until you reach a part with 3 paths to follow\n");
        printf("The one of the left very dark, the one of the silent half, and the one of the right with a totem again");
        printf("Which path to take?");
        printf("1: Left\n2:Mid\n3: Right");
        scanf("%d", &resposta);
        switch (resposta)
        {
        case 1:
            printf("The path is too dark, you end up falling into a trap");
            init_traps();
            repetir = 3;
            break;
        case 2:
            printf("You took a path that leads to a darker place.");
            repetir = 1;
            break;
        case 3:
            printf("You fell into a monster trap!");
            fight_stage_2();
            repetir = 3;
            break;
        default:
            printf("You went the wrong way, you end up stepping into a trap.");
            init_traps();
            break;
        }
    } while (repetir != 1);
    caverna_stage_3();
}

void caverna_stage_3()
{
    player.location = 3;
    save_player("Specialist Goon");
    repetir = 0;
    scanf("%d", &resposta);
    do
    {
        printf("\nYou finally arrive on the last stage, do you want to recover in the guild??");
        printf("1: Yes\n2: No");
        switch (resposta)
        {
        case 1:
            guilda_menu();
            repetir = 1;
            break;
        case 2:
            repetir = 2;
            break;
        default:
            init_traps();
            break;
        }
    } while (repetir != 2);

    printf("Você ouve um som vindo do fundo da caverna, parece ser um monstro épico.\n");
    printf("Finalmente você se encontra com o último monstro");
    //Chamada de método monsterinitboss
    init_monster_boss();
}
*/
