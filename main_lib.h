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
    int dd;
    int mm;
    int yyyy;
} Date;

typedef struct {
    char username[30];
    char password[30];
    int age;
    char card_number[17];
    int university_student;
} User;

typedef struct {
    char booking_id[50];
    char username[30];
    char dep_date[15];
    char ret_date[15];
    int trip_type;
    float total_cost;
    char status[15];
} BookedTrip;

#endif