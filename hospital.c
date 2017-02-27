#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "structure.h"
#include "parse.h"

#define ERROR "ERROR\n"
#define STDERROR_PARAMETER "-v"

static bool checkProgramParameters(int argc, char *argv[]) {
    if (argc >= 2) {
        if (argc == 2 && !strcmp(argv[1], STDERROR_PARAMETER)) {
            return true;
        }
        else {
            fprintf(stderr, ERROR);
            exit(1);
        }
    }
    else {
        return false;
    }
}

int main(int argc, char *argv[]) {
    int character;
    int functionName;
    bool printNumberOfDescriptions = checkProgramParameters(argc, argv);

    while ((character = getchar()) != EOF) {
        ungetc(character, stdin);
        functionName = readFunctionName();

        readFunctionParametersAndRun(functionName, printNumberOfDescriptions);
    }

    removePatientList();
    return 0;
}
