/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#include <stdio.h>
#include <string.h>
#include "types.h"

#define CODE_LENGTH 2

#ifdef STATIC_LIST
#include "static_list.h"
#endif
#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef TEST_LIST
#include "list/list.h"
#endif
void print_list(tList list) {
    tPosL pos;
    tItemL item;

    printf("(");
    if (!isEmptyList(list)) {
        pos = first(list);
        while (pos != LNULL) {
            item = getItem(pos, list);
            printf(" %s numVotes %d", item.partyName, item.numVotes);
            pos = next(pos, list);
        }
    }
    printf(")\n");
}

void newParty(tPartyName partyName, tList* list) {
    tItemL party;
    party.numVotes = 0;
    strcpy(party.partyName, partyName);
    tPosL pos;
    printf("%p", &list);
    insertItem(party, LNULL, list);
}

void processCommand(char command_number[CODE_LENGTH+1], char command, char param[NAME_LENGTH_LIMIT+1], tList* list) {

    switch(command) {
        case 'N': {
            printf("Read: %s %c %s.\n", command_number, command, param);
            newParty(param, list);
        }
        default: {
            break;
        }
    }

    print_list(*list);
}

void readTasks(char *filename, tList* list) {
    FILE *df;
    char command_number[CODE_LENGTH+1], command, param[NAME_LENGTH_LIMIT+1];

    df = fopen(filename, "r");
    if (df != NULL) {
        while (!feof(df)) {
            char format[16];
            sprintf(format, "%%%is %%c %%%is", CODE_LENGTH, NAME_LENGTH_LIMIT);
            fscanf(df,format, command_number, &command, param);
            processCommand(command_number, command, param, list);
        }
        fclose(df);
    } else {
        printf("Cannot open file %s.\n", filename);
    }
}

int main(int nargs, char **args) {
    tList list;
    char *file_name = "new.txt";
    if (nargs > 1) {
        file_name = args[1];
    } else {
        #ifdef INPUT_FILE
        file_name = INPUT_FILE;
        #endif
    }

    createEmptyList(&list);
    readTasks(file_name, &list);

    return 0;
}


