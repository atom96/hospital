#ifndef STRUCTURE_H
#define STRUCTURE_H

int storagedDesriptions;

extern void newDiseaseEnterDescription (char *patientName, char *diseaseDescription);

extern void newDiseaseCopyDescription(char *patientName1, char *patientName2);

extern void changeDescription (char *patientName, int diseaseNumber, char *diseaseDescription);

extern void printDescription(char *patientName, int diseaseNumber);

extern void deletePatientData(char *patientName);

extern void removePatientList(void);

extern void printNumberOfStoragedDescriptions(void);

#endif /* STRUCTURE_H */
