#include <stdio.h>
#include <string.h>
#include "main_lib.h"
#include "client_stuff/client_lib.h"

User users[30];
int user_count = 0;

void View_Routes(Route routes[], int size);

int main() {
    Route routes[] = {
        {"Kos", "KOS", 60, 80, 120, 100},
        {"Rodos", "RHO", 80, 100, 140, 100},
        {"Kalymnos", "KAL", 60, 80, 120, 100}
        // ... ypoloipa dromologia ...
    };

    int size = sizeof(routes) / sizeof(routes[0]);
    View_Routes(routes, size);

    create_new_clients(users, &user_count);

    if (user_count > 0) {
        book_trip(users[user_count - 1].university_student);
    }

    return 0;
}

void View_Routes(Route routes[], int size) {
    printf("\n%-15s %-5s %-10s %-10s %-10s %-10s\n", "Port", "Code", "Deck", "Air", "Cabin", "Car");
    for (int i = 0; i < size; i++) {
        printf("%-15s %-5s %-10d %-10d %-10d %-10d\n", 
               routes[i].name, routes[i].code, routes[i].deck, 
               routes[i].air, routes[i].cabin, routes[i].car);
    }
}


// do {
//     printf("Dwse hlikia: ");
//     scanf("%d", &User[i].age);
//     if (User[i].age < 18) {
//         printf("Prepei na eisai toulaxiston 18 xronwn\n");
//     }
// } while (User[i].age < 18);

// do {
//     printf("Dwste password: ");
//     scanf("%s", int plx);

//     int length = 0;
//     while (plx[length] != '\0') {
//         length++;
//     }

//     if (length != 7) {
//         printf("Dwse ksana ton kwdiko\n", length);
//     }
// } while (length != 7);

// for (int i = 0; i <= 7; i++) {
//     User[user_count].password[i] = plx[i];
// }


