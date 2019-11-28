/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: tadeu
 *
 * Created on April 4, 2019, 2:10 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include "player.h"
#include "monsters.h"
#include "score.h"
#include "combat.h"
#include "history.h"
#include "guilda.h"
#include <jni.h>
#include <HsFFI.h>
#ifdef __GLASGOW_HASKELL__
#include "Ataque_stub.h"
extern void __stginit_Ataque(void);
#endif

/*
 * 
 */
//save_player("Specialist Goon");
//load_player("Specialist Goon");
//printf("vida = %d", player.health);
static char input[20];

JNIEnv *create_vm(JavaVM **jvm)
{
    JNIEnv *env;
    JavaVMInitArgs args;
    JavaVMOption options;
    args.version = JNI_VERSION_1_6;
    args.nOptions = 1;
    options.optionString = "-Djava.class.path=./:./java_files/jars/jpl.jar";
    args.options = &options;
    args.ignoreUnrecognized = 0;
    int rv;
    rv = JNI_CreateJavaVM(jvm, (void **)&env, &args);
    if (rv < 0 || !env)
        printf("Unable to Launch JVM %d\n", rv);
    else
        printf("Launched JVM! :)\n");
    return env;
}

void invoke_class(JNIEnv *env, char resposta[20])
{
    //char resposta[20];
    //scanf("%s", resposta);
    jclass hello_world_class;
    jmethodID smfnMethod;
    jstring StringArg = NULL;
    hello_world_class = (*env)->FindClass(env, "ConsultOracle");
    smfnMethod = (*env)->GetStaticMethodID(env, hello_world_class, "consultOracle", "(Ljava/lang/String;)V");
    StringArg = (*env)->NewStringUTF(env, resposta);
    if (smfnMethod != NULL)
    {
        (*env)->CallStaticVoidMethod(env, hello_world_class, smfnMethod, StringArg);
    }
}

void combat(int argc, char **argv, const char *noun)
{
    int j;
    hs_init(&argc, &argv);
#ifdef __GLASGOW_HASKELL__
    hs_add_root(__stginit_Ataque);
#endif
    if (noun == NULL)
    {
        for (int i = 0; i < numero_de_monstros; i++)
        {
            if (monsters[i].location == player_remember.location && monsters[i].health > 0)
            {

                int dano, escolha, hitChance, critChance, concentracaoN, meditacaoN;
                bool rLvl = false, playerL = true, monstroL = true, concentracao = false, meditacao = false;

                printf("                     Se prepare para o combate...\n");
                do
                {
                    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------");
                    execute_list_spells();
                    do
                    {
                        printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------");
                        printf("Seleciona um Ataque : ");
                        scanf("%d", &escolha);

                        dano = 0;

                        if (spells[escolha - 1].level <= player_remember.level)
                        {
                            rLvl = true;
                            if (spells[escolha].number <= 0)
                            {
                                rLvl = false;
                                printf("Você já usou demais este ataque\n");
                            }
                        }
                        else
                        {
                            printf("Selecione um ataque valido\n");
                        }
                    } while (rLvl != true);

                    srand(time(NULL));
                    hitChance = rand() % 100;

                    srand(time(NULL));
                    critChance = rand() % 20;

                    if (dexHitChance(player_remember.dex, hitChance) == true)
                    {
                        spells[escolha - 1].number = spells[escolha - 1].number - 1;
                        switch (escolha)
                        {
                        case 1:
                            dano = atkBasico(player_remember.damage, player_remember.str);
                            break;

                        case 2:
                            dano = 0;
                            printf("Informações do monstro :\n");
                            printf(LCYN "Nome: %-18s Level: %d    Vida maxima: %d   Dano: %d \n" RESET, monsters[i].name,
                                   monsters[i].level,
                                   monsters[i].max_health,
                                   monsters[i].damage);
                            break;

                        case 3:
                            printf("Voce esta concentrado e seu dano aumentado\n");
                            dano = 0;
                            concentracao = true;
                            concentracaoN = 3;
                            break;

                        case 4:
                            printf("Voce medita e seu corpo suportara mais dano por um tempo\n");
                            dano = 0;
                            meditacao = true;
                            player_remember.health = meditarF(player_remember.health);
                            meditacaoN = 3;

                        case 5:
                            dano = corteGir(player_remember.damage, player_remember.str);
                            break;

                        case 6:
                            dano = fireBall(player_remember.magic, player_remember.itellect);
                            break;

                        case 7:
                            dano = 0;
                            printf("Voce cura suas feridas com magia\n");
                            player_remember.health = heal(player_remember.health, player_remember.itellect);
                            break;

                        case 8:
                            dano = tempAco(player_remember.damage, player_remember.str);
                            break;

                        case 9:
                            dano = comArc(player_remember.magic, player_remember.itellect);
                            break;

                        case 10:
                            dano = posKamai(player_remember.damage, player_remember.str);
                            break;
                        }
                    }
                    else
                    {
                        dano = 0;
                        printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------");
                        printf("O ataque errou\n");
                        printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------");
                    }

                    if (concentracao == true)
                    {
                        dano = concentracaoF(dano);
                        concentracaoN = concentracaoN - 1;
                        if (concentracaoN == 0)
                        {
                            concentracao == false;
                            printf("Sua concentracao volta ao normal");
                        }
                    }

                    if (meditacao == true)
                    {
                        meditacaoN = meditacaoN - 1;
                        if (meditacaoN == 0)
                        {
                            player_remember.health = player_remember.health - 100;
                            printf("O efeito de sua meditacao terminou");
                        }
                    }

                    dano = criticoDamage(dano, critChance);
                    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------");
                    printf("Voce causa %d de dano\n", dano);
                    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------");

                    monsters[i].health = sub_defence(monsters[i].health, monsters[i].armor, dano, 0);

                    if (monsters[i].health <= 0)
                    {
                        monstroL = false;
                        printf("O monstro esta morto, boa luta");
                    }

                    else
                    {
                        printf("Resta %d de vida do monstro\n", monsters[i].health);
                        printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------");
                    }

                    //turno do monstro--------------------------------------------------

                    if (monstroL == true)
                    {
                        printf("O monstro te ataca causando %d de dano", monsters[i].damage);
                        printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------");
                        player_remember.health = sub_defence(player_remember.health, player_remember.armor, monsters[i].damage, player_remember.defence);
                        printf("Resta %d de sua vida e %d de sua armadura\n", player_remember.health, player_remember.armor);
                    }

                    if (player_remember.health <= 0)
                    {
                        monstroL = false;
                        printf("Voce pereceu em combate, infelizmente hoje nao foi seu dia");
                    }

                } while (monstroL != false || playerL != false);
            }
            else
            {
                printf("não existe monstros nesse local\n");
            }
        }
    }
}

void consult_oracle(char consult[20])
{
    JavaVM *jvm;
    JNIEnv *env;
    env = create_vm(&jvm);
    if (env == NULL)
        return 1;
    invoke_class(env, consult);
}

static int get_input()
{
    show_prompt();
    return fgets(input, sizeof(input), stdin) != NULL;
}

static int parse_input(int argc, char **argv)
{
    char *verb = strtok(input, " \n"); // Break the input string down into 2 tokens
    char *noun = strtok(NULL, "\n");
    //    char consult[20];
    // if statements to run commands based on input verb
    if (verb != NULL)
    {
        if (strcasecmp(verb, "QUIT") == 0)
        {
            if (player_remember.location > 15)
            {
                printf("Você está em uma posição com monstros.\n");
            }
            else
            {
                printf("Saindo do jogo...\n");
                sleep(1);
                return 0;
            }
        }
        else if (strcasecmp(verb, "CLEAR") == 0)
        {
            clear_screen();
        }
        /* Commands for singe letter directions */
        else if (strcasecmp(verb, "N") == 0 &&
                 locations[player_remember.location].north > 0)
        {
            move_player(locations[player_remember.location].north);
        }
        else if (strcasecmp(verb, "S") == 0 &&
                 locations[player_remember.location].south > 0)
        {
            move_player(locations[player_remember.location].south);
        }
        else if (strcasecmp(verb, "E") == 0 &&
                 locations[player_remember.location].east > 0)
        {
            move_player(locations[player_remember.location].east);
        }
        else if (strcasecmp(verb, "W") == 0 &&
                 locations[player_remember.location].west > 0)
        {
            move_player(locations[player_remember.location].west);
        }
        else if (strcasecmp(verb, "U") == 0 &&
                 locations[player_remember.location].up > 0)
        {
            move_player(locations[player_remember.location].up);
        }
        else if (strcasecmp(verb, "D") == 0 &&
                 locations[player_remember.location].down > 0)
        {
            move_player(locations[player_remember.location].down);
        }
        else if (strcasecmp(verb, "CONSULT") == 0)
        {
            consult_oracle(locations[player_remember.location].tag_prolog);
        }
        else if (strcasecmp(verb, "SPELLS") == 0)
        {
            execute_list_spells();
        }
        else if (strcasecmp(verb, "QUEST") == 0)
        {
            execute_quest();
        }
        else if (strcasecmp(verb, "STATS") == 0)
        {
            look_self_ant();
        }
        else if (strcasecmp(verb, "EXITS") == 0)
        {
            execute_show_exits();
        }
        else if (strcasecmp(verb, "TRAIN") == 0)
        {
            execute_training(noun);
        }
        else if (strcasecmp(verb, "LOOK") == 0)
        {
            execute_look(noun);
        }
        else if (strcasecmp(verb, "ATTACK") == 0 || strcasecmp(verb, "A") == 0)
        {
            combat(argc, argv, noun);
        }
        else
        {
            printf("Eu não reconheço esse comando: %s.\n", verb);
        }
    }
    return 1;
}

int main(int argc, char **argv)
{

    init_demons();
    load_locations();
    clear_screen();
    printf("\n Bem-Vindo");
    execute_look("around");

    while (get_input() && parse_input(argc, argv))
        ;
    hs_exit();
    printf("\nObrigado por jogar!\n");

    return 0;
}
