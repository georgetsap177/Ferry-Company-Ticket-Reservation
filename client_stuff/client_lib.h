#ifndef CLIENT_LIB_H
#define CLIENT_LIB_H

#include "../main_lib.h"

// users
void Create_new_client(User users[], int *count);
int check_login(User users[], int count, char *username, char *password);
int username_exists(User users[], int count, char *uname);

// client_menu
void client_login(User *u, Route routes[], int rcount, BookedTrip trips[], int *tcount);

// booking
void book_trip(User u, Route routes[], int rcount, BookedTrip trips[], int *tcount);

void payment(User u, BookedTrip trips[], int total);
void confirmed_trips(User u, BookedTrip trips[], int total);

// helpers
void generate_trip_id(char *date, char *code, char *user, char *id);
int compare_trips(char *d1, char *d2);

#endif