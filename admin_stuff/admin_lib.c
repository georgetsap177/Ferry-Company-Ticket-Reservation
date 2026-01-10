#include <stdio.h>
#include <string.h>

#include "admin_lib.h"
#include "../main_lib.h"

// Έλεγχος ύπαρξης username 
int username_exists(User users[], int count, char *uname){
    int exists = 0;
    int i = 0;
    while(i < count && exists == 0){
        if(strcmp(users[i].username, uname) == 0){
            exists = 1;
        }
        i++;
    }
    return exists;
}

//  Δημιουργία νέου χρήστη 
void create_new_client(User users[], int *count){
    if(*count >= 30){
        printf("Δεν υπάρχει χώρος για νέο χρήστη\n");
        return;
    }

    User u;
    int valid = 0;

    // Ηλικία
    while(valid == 0){
        printf("Ηλικία (>=18): ");
        scanf("%d", &u.age);
        if(u.age >= 18){
            valid = 1;
        } 
        else {
            printf("Η ηλικία πρέπει να είναι >= 18\n");
        }
    }

    // Αριθμός κάρτας 

    valid = 0;
    while(valid == 0){
        printf("Αριθμός κάρτας (16 ψηφία): ");
        scanf("%s", u.card_number);
        if(strlen(u.card_number) == 16){
            valid = 1;
        }
        else{
            printf("Λάθος μήκος αριθμού κάρτας\n");
        }
    }

    // Φοιτητής 

    valid = 0;
    while(valid == 0){
        printf("Φοιτητής (0/1): ");
        scanf("%d", &u.university_student);

        if(u.university_student == 0 || u.university_student == 1){
            valid = 1;
        } 
        else{
            printf("Πρέπει να εισάγετε 0 ή 1\n");
        }
    }

    // Username 
    valid = 0;

    while(valid == 0){
        printf("Username: ");
        scanf("%s", u.username);
        if(username_exists(users, *count, u.username)){
            printf("Το username υπάρχει ήδη\n");
        } 
        else {
            valid = 1;
        }
    }

    // Password 
    valid = 0;

    while(valid == 0){
        printf("Password (7 χαρακτήρες): ");
        scanf("%s", u.password);
        if(strlen(u.password) == 7){
            valid = 1;
        } 
        else {
            printf("Το password πρέπει να έχει 7 χαρακτήρες\n");
        }
    }

    users[*count] = u;
    (*count)++;
    printf("Ο χρήστης %s δημιουργήθηκε επιτυχώς!\n", u.username);
}

// Αλλαγή κωδικού για admin 
void change_client_password(User users[], int count, char *username, char *new_password){
    if(count == 0){
        printf("Δεν υπάρχουν καταχωρημένοι χρήστες.\n");
        return;
    }

    char uname[30];
    printf("Username to change: ");
    scanf("%29s", uname);

    // Άμεσος έλεγχος αν υπάρχει ο χρήστης
    int user_index = -1;
    for(int i=0; i<count; i++){
        if(strcmp(users[i].username, uname) == 0){
            user_index = i;
            break;
        }
    }

    if(user_index == -1){
        printf("Σφάλμα: το username '%s' δεν υπάρχει.\n", uname);
        return;  // επιστροφή αμέσως
    }

    // Ζητάμε νέο password μόνο αν ο χρήστης υπάρχει
    char newpass[30];
    int attempts = 0;
    while(attempts < 3){
        printf("New password (7 chars): ");
        scanf("%29s", newpass);
        if(strlen(newpass) == 7){
            strcpy(users[user_index].password, newpass);
            printf("Ο κωδικός άλλαξε επιτυχώς!\n");
            return;
        } 
        else {
            attempts++;
            printf("Λάθος μήκος κωδικού (%d/3)\n", attempts);
        }
    }

    printf("Αποτυχία αλλαγής κωδικού. Επιστροφή στο menu.\n");
}