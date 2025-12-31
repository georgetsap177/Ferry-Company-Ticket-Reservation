#include <stdio.h>
#include "main_lib.h"
#include "client_stuff/client_lib.h"

int main(){
    User users[30];
    BookedTrip trips[50];
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

    int routes_count = 5;
    char uname[30], pass[30];
    int index;

    Create_new_client(users, &users_count);

    printf("Username: ");
    scanf("%s", uname);
    printf("Password: ");
    scanf("%s", pass);

    index = check_login(users, users_count, uname, pass);

    if (index == -1){
        printf("Lathos stoixeia\n");
    }
    else{
        client_login(&users[index], routes, routes_count,trips, &trips_count);
    }

    return 0;
}