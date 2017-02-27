#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define OK "OK\n"
#define IGNORED "IGNORED\n"

struct DiseaseDescription {
    char *description;
    int referenceCounter;
};

typedef struct DiseaseDescription DiseaseDescription;

struct Disease {
    DiseaseDescription *diseaseDescription;
    int number;
};

typedef struct Disease Disease;

struct DiseaseNode;

typedef struct DiseaseNode *DiseaseList;

struct DiseaseNode {
    Disease *disease;
    DiseaseList next;
};

struct Patient {
    char *name;
    DiseaseList diseaseHistory;
};

typedef struct Patient Patient;

struct PatientNode;

typedef struct PatientNode *PatientList;

struct PatientNode {
    Patient *patient;
    PatientList next;
};

static int storagedDesriptions = 0;
static PatientList patientList = NULL;


static Patient *createNewPatient(char *patientName) {
    Patient *newPatient = malloc(sizeof *newPatient);

    newPatient->name = patientName;
    newPatient->diseaseHistory = NULL;

    return newPatient;
}

static void addNewPatientToPatientList(Patient *newPatient) {
    PatientList newPatientNode = malloc(sizeof *newPatientNode);

    newPatientNode->patient = newPatient;
    newPatientNode->next = patientList;

    patientList = newPatientNode;
}

static DiseaseDescription *createNewDiseaseDesription(char *description) {
    DiseaseDescription *newDescription = malloc(sizeof *newDescription);

    newDescription->description = description;
    newDescription->referenceCounter = 1;

    storagedDesriptions += 1;

    return newDescription;
}

static Disease *createNewDiseaseWithNewDescription(char *description,
    int number) {
    Disease *newDisease = malloc(sizeof *newDisease);

    newDisease->diseaseDescription = createNewDiseaseDesription(description);
    newDisease->number = number;

    return newDisease;
}

static Disease *createNewDiseaseWithExistingDesription(DiseaseDescription
        *diseaseDescription, int number) {
    Disease *newDisease = malloc(sizeof *newDisease);

    newDisease->diseaseDescription = diseaseDescription;
    newDisease->number = number;

    diseaseDescription->referenceCounter += 1;

    return newDisease;
}

static void addNewDiseaseToDiseaseList(DiseaseList *diseaseList,
        Disease *disease) {
    DiseaseList newDiseaseNode = malloc(sizeof *newDiseaseNode);

    newDiseaseNode->disease = disease;
    newDiseaseNode->next = *diseaseList;

    *diseaseList = newDiseaseNode;
}

static Patient *findPatientOnAList(char *patientName) {
    PatientList currentPatientNode = patientList;

    while (currentPatientNode != NULL) {
        if (!strcmp(patientName, currentPatientNode->patient->name)) {
            return currentPatientNode->patient;
        }

        currentPatientNode = currentPatientNode->next;
    }
    /* NULL means that patient has not been found on a list */
    return NULL;
}

static Disease *findDiseaseOnAList(int diseaseNumber, DiseaseList diseaseList) {
    while (diseaseList != NULL
            && diseaseList->disease->number >= diseaseNumber) {
        if (diseaseList->disease->number == diseaseNumber) {
            return diseaseList->disease;
        }
        diseaseList = diseaseList->next;
    }
    /* NULL means that disease has not been found on a list */
    return NULL;
}

void newDiseaseEnterDescription(char *patientName, char *diseaseDescription) {
    Patient *currentPatient = findPatientOnAList(patientName);
    Disease *newDisease;
    int diseaseNumber;

    if (currentPatient == NULL) {
        currentPatient = createNewPatient(patientName);
        addNewPatientToPatientList(currentPatient);
    }
    else {
        /* @patientName will not be used to create new patient,
        therefore it has to be freed */
        free(patientName);
    }

    if (currentPatient->diseaseHistory == NULL) {
        diseaseNumber = 1;
    }
    else {
        diseaseNumber = currentPatient->diseaseHistory->disease->number + 1;
    }

    newDisease = createNewDiseaseWithNewDescription(
            diseaseDescription,
            diseaseNumber
    );

    addNewDiseaseToDiseaseList(&currentPatient->diseaseHistory, newDisease);

    printf(OK);
}

void newDiseaseCopyDescription(char *patientName1, char *patientName2) {
    Patient *currentPatient = findPatientOnAList(patientName1);
    Patient *patientWithDescriptionToCopy
            = findPatientOnAList(patientName2);

    if (patientWithDescriptionToCopy == NULL ||
        patientWithDescriptionToCopy->diseaseHistory == NULL) {
        /* @patientName will not be used to create new patient,
        therefore it has to be freed */
        free(patientName1);

        printf(IGNORED);
    }
    else {
        Disease *newDisease;
        int diseaseNumber;
        if (currentPatient == NULL) {
            currentPatient = createNewPatient(patientName1);
            addNewPatientToPatientList(currentPatient);
        }
        else {
            free(patientName1);
        }

        if (currentPatient->diseaseHistory == NULL) {
            diseaseNumber = 1;
        }
        else {
            diseaseNumber = currentPatient->diseaseHistory->disease->number + 1;
        }

        newDisease = createNewDiseaseWithExistingDesription(
                patientWithDescriptionToCopy->
                        diseaseHistory->disease->diseaseDescription,
                diseaseNumber
        );

        addNewDiseaseToDiseaseList(&currentPatient->diseaseHistory, newDisease);

        printf(OK);
    }
}

static void removeDiseaseDesription(DiseaseDescription *diseaseDescription) {
    if (diseaseDescription != NULL) {
        if (diseaseDescription->referenceCounter == 1) {
            assert(diseaseDescription->description != NULL);

            free(diseaseDescription->description);
            free(diseaseDescription);

            storagedDesriptions -= 1;
        }
        else {
            diseaseDescription->referenceCounter -= 1;
        }
    }
}

void changeDescription(char *patientName, int diseaseNumber,
        char *diseaseDescription) {
    Patient *currentPatient = findPatientOnAList(patientName);

    if (currentPatient == NULL) {
        /* @diseaseDescription will not be used to create new description,
        therefore it has to be freed */
        free(diseaseDescription);

        printf(IGNORED);
    }
    else {
        Disease *currentDisease = findDiseaseOnAList(
                diseaseNumber,
                currentPatient->diseaseHistory
        );

        if (currentDisease == NULL) {
            /* @diseaseDescription will not be used to create new description,
            therefore it has to be freed */
            free(diseaseDescription);

            printf(IGNORED);
        }
        else {
            removeDiseaseDesription(currentDisease->diseaseDescription);
            currentDisease->diseaseDescription = createNewDiseaseDesription(
                    diseaseDescription
            );

            printf(OK);
        }
    }
}

void printDescription(char *patientName, int diseaseNumber) {
    Patient *currentPatient = findPatientOnAList(patientName);

    if (currentPatient == NULL) {
        printf(IGNORED);
    }
    else {
        Disease *currentDisease = findDiseaseOnAList(
                diseaseNumber,
                currentPatient->diseaseHistory
        );

        if (currentDisease == NULL) {
            printf(IGNORED);
        }
        else {
            printf("%s\n", currentDisease->diseaseDescription->description);
        }
    }
}

static void removeDiseaseList(DiseaseList *diseaseList) {
    while (*diseaseList != NULL) {
        DiseaseList currentDiseaseNode;
        currentDiseaseNode = *diseaseList;

        *diseaseList = (*diseaseList)->next;

        assert(currentDiseaseNode->disease != NULL);
        assert(currentDiseaseNode->disease->diseaseDescription != NULL);

        removeDiseaseDesription(
                currentDiseaseNode->disease->diseaseDescription
        );

        free(currentDiseaseNode->disease);
        free(currentDiseaseNode);
    }
}

void deletePatientData(char *patientName) {
    Patient *currentPatient = findPatientOnAList(patientName);

    if (currentPatient == NULL) {
        printf(IGNORED);
    }
    else {
        removeDiseaseList(&currentPatient->diseaseHistory);

        printf(OK);
    }
}

void removePatientList(void) {
    while (patientList != NULL) {
        PatientList currentPatientNode = patientList;

        patientList = patientList->next;

        removeDiseaseList(&currentPatientNode->patient->diseaseHistory);

        free(currentPatientNode->patient->name);
        free(currentPatientNode->patient);
        free(currentPatientNode);
    }
}

void printNumberOfStoragedDescriptions(void) {
    fprintf(stderr, "DESCRIPTIONS: %d\n", storagedDesriptions);
}
