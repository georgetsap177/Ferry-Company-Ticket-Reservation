#include <stdio.h>
#include <string.h>
#include "main_lib.h"
#include "client_stuff/client_lib.h"
#include "admin_stuff/admin_lib.h"

#define MAX_LOGIN_ATTEMPTS 3
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "admin123"

int main() {
    User users[30] = {0};
    BookedTrip trips[50] = {0};
    int users_count = 0, trips_count = 0;

    Route routes[] = {
        {"Kos", "KOS", 60, 80, 120, 100},
        {"Rodos", "RHO", 80, 100, 140, 100},
        {"Kalymnos", "KAL", 60, 80, 120, 100},
        {"Patmos", "PAT", 55, 75, 115, 100},
        {"Astypalaia", "AST", 50, 70, 110, 100},
        {"Kasos", "KAS", 65, 85, 125, 100},
        {"Kastelorizo", "KST", 100, 120, 160, 120},
        {"Leros", "LER", 60, 80, 120, 100},
        {"Karpathos", "KAR", 70, 90, 130, 100},
        {"Symi", "SYM", 80, 100, 140, 120},
        {"Xalki", "XAL", 70, 90, 130, 100},
        {"Tilos", "TIL", 75, 95, 135, 100},
        {"Pserimos", "PSE", 60, 80, 120, 100}
    };
    int routes_count = 13;

    int main_choice = 0;

    while(main_choice != 2){
        printf("\n--- Main Menu ---\n");
        printf("1. Login\n");
        printf("2. Exit\n");
        printf("Choice: ");
        scanf("%d", &main_choice);

        if(main_choice == 1){
            int login_attempts = 0;
            int logged_in = 0;

            while(login_attempts < MAX_LOGIN_ATTEMPTS && logged_in == 0){
                char uname[30], pass[30];

                printf("\nUsername: ");
                scanf("%s", uname);
                printf("Password: ");
                scanf("%s", pass);

                // Ελεγχος αν έχουμε admin login 
                if(strcmp(uname, ADMIN_USERNAME) == 0 && strcmp(pass, ADMIN_PASSWORD) == 0){
                    int admin_choice = 0;

                    while(admin_choice != 3){
                        printf("\n--- Administration Dashboard ---\n");
                        printf("1. Create new client\n");
                        printf("2. Change client password\n");
                        printf("3. Logout\n");
                        printf("Choice: ");
                        if(scanf("%d", &admin_choice) != 1){
                            while(getchar() != '\n'){
                                printf("Λάθος εισαγωγή\n");
                                admin_choice = 0;
                            }
                        }

                        if(admin_choice == 1){
                            create_new_client(users, &users_count);
                        }
                        else if(admin_choice == 2){
                            char target[30], newpass[30];

                            printf("Username to change: ");
                            scanf("%s", target);

                            // Άμεσος έλεγχος ύπαρξης username
                            if(!username_exists(users, users_count, target)){
                                printf("Το username '%s' δεν υπάρχει.\n", target);
                            } 
                            else {
                                int valid_pass = 0;
                                while(valid_pass == 0){
                                    printf("New password (7 chars): ");
                                    scanf("%s", newpass);
                                    if(strlen(newpass) == 7){
                                        change_client_password(users, users_count, target, newpass);
                                        valid_pass = 1;
                                    } 
                                    else {
                                        printf("Λάθος μήκος κωδικού\n");
                                    }
                                }
                            }
                        }
                        else if(admin_choice == 3){
                            printf("Logging out from admin...\n");
                        }
                        else{
                            printf("Λάθος επιλογή\n");
                        }
                    }

                    logged_in = 1; // Admin έχει ολοκληρώσει
                }

                // Client login 
                if(logged_in == 0){
                    int idx = check_login(users, users_count, uname, pass);
                    if(idx != -1){
                        printf("Ο client συνδέθηκε\n");
                        client_login(&users[idx], routes, routes_count, trips, &trips_count);
                        logged_in = 1;                        
                    }
                }

                // Login failed 
                if(logged_in == 0){
                    login_attempts++;
                    printf("Λάθος στοιχεία! Προσπάθεια %d/%d\n", login_attempts, MAX_LOGIN_ATTEMPTS);
                    if(login_attempts >= MAX_LOGIN_ATTEMPTS){
                        printf("Ξεπεράσατε τις 3 προσπάθειες. Επιστροφή στο αρχικό menu.\n");
                    }
                }
            }
        }
        else if(main_choice == 2){
            printf("Exiting...\n");
        }
        else{
            printf("Λάθος επιλογή\n");
        }
    }

    return 0;
}