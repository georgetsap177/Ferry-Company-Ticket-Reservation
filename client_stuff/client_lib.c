#include <stdio.h>
#include "client_lib.h"

void create_new_clients(User *users, int *user_count) {
    int num_to_add;
    int xwros = 30 - *user_count;

    if (xwros == 0) {
        printf("\nDen yparxei xwros\n");
        return;
    }

    printf("\nPosous xrhstes thelete na eisagete; ");
    scanf("%d", &num_to_add);

    if (num_to_add > xwros) num_to_add = xwros;

    for (int i = 0; i < num_to_add; i++) {
        printf("\n--- Eggrafh Xrhsth %d ---\n", *user_count + 1);
        printf("Username: ");
        scanf("%s", users[*user_count].username);
        printf("Password: ");
        scanf("%s", users[*user_count].password);
        printf("Hlikia: ");
        scanf("%d", &users[*user_count].age);
        
        // SOS: Πρέπει να αποθηκεύσουμε αν είναι φοιτητής
        printf("Eisai foititis; (1=NAI, 0=OXI): ");
        scanf("%d", &users[*user_count].university_student);
        
        (*user_count)++;
    }
}

void book_trip(int is_student) {
    int dest_code, seat_type, has_car, is_round_trip;
    float cost_per_seat = 0, extra_car_cost = 0, first_cost = 0;
    float return_trip_cost = 0, total_cost = 0;
    char dep_date[15], ret_date[15];

    printf("\n--- KRATHSH EISITHRIOU ---\n");
    printf("Hmeromhnia anaxwrhshs (DD/MM/YYYY): ");
    scanf("%s", dep_date);

    printf("Kwdikos proorismou (1, 2, h 3): ");
    scanf("%d", &dest_code);
    while (dest_code < 1 || dest_code > 3) {
        printf("Lathos! Dose ksana (1-3): ");
        scanf("%d", &dest_code);
    }

    printf("Typos theshs (1:Katastroma, 2:Aeroporiko, 3:Kampina): ");
    scanf("%d", &seat_type);
    if (seat_type == 1) cost_per_seat = 25.0;
    else if (seat_type == 2) cost_per_seat = 40.0;
    else if (seat_type == 3) cost_per_seat = 70.0;
    
    printf("Metafora aftokinhtou; (1=NAI, 0=OXI): ");
    scanf("%d", &has_car);
    if (has_car == 1) extra_car_cost = 45.0;

    first_cost = cost_per_seat + extra_car_cost;

    printf("Taxidi me epistrofh; (1=NAI, 0=OXI): ");
    scanf("%d", &is_round_trip);

    if (is_round_trip == 1) {
        printf("Hmeromhnia epistrofhs: ");
        scanf("%s", ret_date);
        return_trip_cost = 0.75 * first_cost;
    }

    total_cost = first_cost + return_trip_cost;

    if (is_student == 1) {
        total_cost = total_cost / 2.0;
        printf("[Foititiki ekptosi 50%% efarmostike]\n");
    }

    printf("\n--- APOTELESMA KRATHSHS ---");
    printf("\nKostos metavashs: %.2f", first_cost);
    if (is_round_trip == 1) printf("\nKostos epistrofhs: %.2f", return_trip_cost);
    printf("\nSYNOLIKO KOSTOS: %.2f\n", total_cost);
}