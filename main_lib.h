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
    int dd;   // μέρα
    int mm;   // μήνας
    int yyyy; // έτος
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
    int trip_type;      // 1=Deck,2=Air,3=Cabin
    float total_cost;
    char status[15];    // "Ekkremei" ή "Exoflithike"
} BookedTrip;

#endif