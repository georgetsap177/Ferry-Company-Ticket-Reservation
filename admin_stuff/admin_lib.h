#ifndef ADMIN_LIB_H
#define ADMIN_LIB_H
#include "../main_lib.h"

// Έλεγχος αν υπάρχει username
int username_exists(User users[], int count, char *uname);

// Δημιουργία νέου χρήστη 
void create_new_client(User users[], int *count);

// Αλλαγή κωδικού χρήστη
void change_client_password(User users[], int count, char *username, char *new_password);

#endif