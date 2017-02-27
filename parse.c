#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "structure.h"

#define MAX_SIZE 100000
#define NEW_DISEASE_ENTER_DESCRIPTION "NEW_DISEASE_ENTER_DESCRIPTION"
#define NEW_DISEASE_COPY_DESCRIPTION "NEW_DISEASE_COPY_DESCRIPTION"
#define CHANGE_DESCRIPTION "CHANGE_DESCRIPTION"
#define PRINT_DESCRIPTION "PRINT_DESCRIPTION"
#define DELETE_PATIENT_DATA "DELETE_PATIENT_DATA"
#define NEW_DISEASE_ENTER_DESCRIPTION_NUMBER 0
#define NEW_DISEASE_COPY_DESCRIPTION_NUMBER 1
#define CHANGE_DESCRIPTION_NUMBER 2
#define PRINT_DESCRIPTION_NUMBER 3
#define DELETE_PATIENT_DATA_NUMBER 4

static char stringBuffer[MAX_SIZE];

static void copyFromBuffer(char **stringToSave, int numberOfLetters) {
    int i;
    /* Size of a new string has to be @numberOfLetters + 1 because we have to
    add '\0' character at the end of the string */
    char *copiedString = malloc((numberOfLetters + 1) * sizeof *copiedString);

    for (i = 0; i < numberOfLetters; ++i) {
        copiedString[i] = stringBuffer[i];
    }

    copiedString[i] = '\0';

    *stringToSave = copiedString;
}

static char *readWordFromInput(void) {
    int i = 0;
    int currentElement;
    char *word;

    while ((currentElement = getchar()) != ' ' && currentElement != '\n') {
        stringBuffer[i] = currentElement;
        ++i;
    }

    copyFromBuffer(&word, i);

    return word;
}

static char *readSentenceFromInput(void) {
    int i = 0;
    int currentElement;
    char *sentence;

    while ((currentElement = getchar()) != '\n') {
        stringBuffer[i] = currentElement;
        ++i;
    }

    copyFromBuffer(&sentence, i);

    return sentence;
}

int readFunctionName(void) {
    char *functionName = readWordFromInput();

    if (!strcmp(functionName, NEW_DISEASE_ENTER_DESCRIPTION)) {
        free(functionName);

        return NEW_DISEASE_ENTER_DESCRIPTION_NUMBER;
    }
    else if (!strcmp(functionName, NEW_DISEASE_COPY_DESCRIPTION)) {
        free(functionName);

        return NEW_DISEASE_COPY_DESCRIPTION_NUMBER;
    }
    else if (!strcmp(functionName, CHANGE_DESCRIPTION)) {
        free(functionName);

        return CHANGE_DESCRIPTION_NUMBER;
    }
    else if (!strcmp(functionName, PRINT_DESCRIPTION)) {
        free(functionName);

        return PRINT_DESCRIPTION_NUMBER;
    }
    else if (!strcmp(functionName, DELETE_PATIENT_DATA)) {
        free(functionName);

        return DELETE_PATIENT_DATA_NUMBER;
    }
    else {
        assert(false);
    }
}

void readFunctionParametersAndRun(int functionNumber,
                                  bool printNumberOfDescriptions) {
    char *name, *name2, *description;
    int n;

    switch (functionNumber) {
        case NEW_DISEASE_ENTER_DESCRIPTION_NUMBER:
            name = readWordFromInput();
            description = readSentenceFromInput();

            newDiseaseEnterDescription(name, description);

            break;

        case NEW_DISEASE_COPY_DESCRIPTION_NUMBER:
            name = readWordFromInput();
            name2 = readWordFromInput();

            newDiseaseCopyDescription(name, name2);

            free(name2);

            break;

        case CHANGE_DESCRIPTION_NUMBER:
            name = readWordFromInput();

            scanf("%d", &n);
            getchar();

            description = readSentenceFromInput();

            changeDescription(name, n, description);

            free(name);

            break;

        case PRINT_DESCRIPTION_NUMBER:
            name = readWordFromInput();

            scanf("%d", &n);
            getchar();

            printDescription(name, n);

            free(name);

            break;

        case DELETE_PATIENT_DATA_NUMBER:
            name = readWordFromInput();

            deletePatientData(name);

            free(name);

            break;

        default:
            assert(false);
    }

    if (printNumberOfDescriptions) {
        printNumberOfStoragedDescriptions();
    }
}
