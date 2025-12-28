#ifndef MAIN_LIB_H
#define MAIN_LIB_H

typedef struct {
    char name[30];
    char code[5];
    int deck;
    int air;
    int cabin;
    int car;
} Route;

typedef struct {
    char name[30];
    char surname[30];
    char password[30];
    char username[30];
    int age;
    long card_number;
    int university_student;
} User;


#endif