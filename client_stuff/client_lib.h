#ifndef CLIENT_LIB_H
#define CLIENT_LIB_H

#include "../main_lib.h"

// USERS
int check_login(User users[], int count, char *username, char *password);

// CLIENT MENU
void client_login(User *u, Route routes[], int rcount, BookedTrip trips[], int *tcount);
void view_routes(Route routes[], int rcount);

// BOOKING
void book_trip(User u, Route routes[], int rcount, BookedTrip trips[], int *tcount);
int is_valid_date_format(char *str);
int is_return_after_departure(char *dep, char *ret);
void payment(User u, BookedTrip trips[], int total);
void confirmed_trips(User u, BookedTrip trips[], int total);

// HELPERS
void generate_trip_id(char *date, char *code, char *user, char *id);
Date make_date(char *str);
int compare_trips(char *d1, char *d2);

#endif