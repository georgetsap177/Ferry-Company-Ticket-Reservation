#include <stdio.h>
#include <string.h>
#include "client_lib.h"

// DATE COMPARISON

Date make_date(char *str){
    Date d;

    d.dd = (str[0] - '0') * 10 + (str[1] - '0');
    d.mm = (str[3] - '0') * 10 + (str[4] - '0');
    d.yyyy = (str[6] - '0') * 1000 +(str[7] - '0') * 100 +(str[8] - '0') * 10 +(str[9] - '0');

    return d;
}

int compare_trips(char *d1, char *d2){
    Date a = make_date(d1);
    Date b = make_date(d2);
    int result = 0;

    if (a.yyyy < b.yyyy){
        result = -1;
    }
    else if (a.yyyy > b.yyyy){
        result = 1;
    }
    else {
        if (a.mm < b.mm){
            result = -1;
        }
        else if (a.mm > b.mm){
            result = 1;
        }
        else {
            if (a.dd < b.dd){
                result = -1;
            }
            else if (a.dd > b.dd){
                result = 1;
            }
        }
    }

    return result;
}

// USERS

int username_exists(User users[], int count, char *uname){
    for (int i = 0; i < count; i++){
        if (strcmp(users[i].username, uname) == 0){
            return 1;
            return 0;
        }
    }
}

void Create_new_client(User users[], int *count){
    User u;

    if (*count >= 30){
        printf("Den yparxei xwros\n");
        return;
    }

    do{
        printf("Hlikia (>=18): ");
        scanf("%d", &u.age);
    }while (u.age < 18);

    do{
        printf("Arithmos kartas (16 psifia): ");
        scanf("%s", u.card_number);
    }while (strlen(u.card_number) != 16);

    do{
        printf("Foithths (0/1): ");
        scanf("%d", &u.university_student);
    }while (u.university_student != 0 && u.university_student != 1);

    do{
        printf("Username: ");
        scanf("%s", u.username);
    }while (username_exists(users, *count, u.username));

    do{
        printf("Password (7 xarakthres): ");
        scanf("%s", u.password);
    }while (strlen(u.password) != 7);

    users[*count] = u;
    (*count)++;

    printf("Eggrafh epityxhs!\n");
}

// LOGIN 

int check_login(User users[], int count, char *username, char *password){
    for (int i = 0; i < count; i++){
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0){
            return i;
            return -1;
        }
    }
}

// ID 

void generate_trip_id(char *date, char *code, char *user, char *id){
    char clean[15];
    int k = 0;

    for (int i = 0; date[i] != '\0'; i++){
        if (date[i] != '/'){
            clean[k++] = date[i];
            clean[k] = '\0';
        }
    }

    strcpy(id, clean);
    strcat(id, code);
    strcat(id, "-");
    strcat(id, user);
}

// BOOKING

void book_trip(User u, Route routes[], int rcount, BookedTrip trips[], int *tcount){
    if (*tcount >= 50){
        printf("Megistos arithmos taxidiwn\n");
        return;
    }

    int seat, car, back;
    int index = -1;
    float base, total;
    char dep[15], ret[15] = "-", code[10];

    printf("Hmeromhnia anaxwrhshs: ");
    scanf("%s", dep);

    while (index == -1){
        printf("Kwdikos limaniou: ");
        scanf("%s", code);

        for (int i = 0; i < rcount; i++){
            if (strcmp(routes[i].code, code) == 0){
                index = i;
                if (index == -1){
                    printf("Lathos kwdikos\n");
                }
            }
        }
    }

    printf("Thesh (1-Deck 2-Air 3-Cabin): ");
    scanf("%d", &seat);

    if (seat == 1){
        base = routes[index].deck;
    }
    else if (seat == 2){
        base = routes[index].air;
    }
    else{
        base = routes[index].cabin;
    }

    total = base;

    printf("Aftokinhto (0/1): ");
    scanf("%d", &car);
    if (car){
        total = total + routes[index].car;
    }

    printf("Epistrofh (0/1): ");
    scanf("%d", &back);
    if (back){
        printf("Hmeromhnia epistrofhs: ");
        scanf("%s", ret);
        total = total + base * 0.75;
    }

    if (u.university_student){
        total = total / 2;
    }

    strcpy(trips[*tcount].username, u.username);
    strcpy(trips[*tcount].dep_date, dep);
    strcpy(trips[*tcount].ret_date, ret);
    strcpy(trips[*tcount].status, "Ekkremei");
    trips[*tcount].trip_type = back;
    trips[*tcount].total_cost = total;

    generate_trip_id(dep, routes[index].code,u.username, trips[*tcount].booking_id);

    printf("ID: %s | Kostos: %.2f\n",trips[*tcount].booking_id, total);

    (*tcount)++;
}

// PAYMENT 

void payment(User u, BookedTrip trips[], int total){
    char id[50];
    int found = 0;

    for (int i = 0; i < total; i++){
        if (strcmp(trips[i].username, u.username) == 0 && strcmp(trips[i].status, "Ekkremei") == 0) {
            printf("%s | %.2f\n",trips[i].booking_id, trips[i].total_cost);
            found = 1;
        }
    }
    if (!found){
        printf("Den yparxoun krathseis\n");
        return;
    }

    printf("Dwse ID: ");
    scanf("%s", id);

    for (int i = 0; i < total; i++){
        if (strcmp(trips[i].booking_id, id) == 0){
            strcpy(trips[i].status, "Exoflithike");
        }
    }
}

// CONFIRMED 

void confirmed_trips(User u, BookedTrip trips[], int total){
    BookedTrip temp[50];
    int count = 0;
    char order[10];

    for (int i = 0; i < total; i++){
        if (strcmp(trips[i].username, u.username) == 0 && strcmp(trips[i].status, "Exoflithike") == 0){
            temp[count++] = trips[i];
            if (count == 0) {
                printf("Den yparxoun exoflhmenes\n");
                return;
            }
        }
    }

    printf("Seira (LOW/HIGH): ");
    scanf("%s", order);

    for (int i = 0; i < count - 1; i++){
        for (int j = 0; j < count - 1; j++) {
            int cmp = compare_trips(temp[j].dep_date,temp[j + 1].dep_date);
            if ((strcmp(order, "LOW") == 0 && cmp > 0) || (strcmp(order, "HIGH") == 0 && cmp < 0)) {
                BookedTrip t = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = t;
            }
        }
    }

    for (int i = 0; i < count; i++){
        printf("%s | %.2f\n",temp[i].booking_id, temp[i].total_cost);
    }
}

// CLIENT MENU

void client_login(User *u, Route routes[], int rcount, BookedTrip trips[], int *tcount){
    int choice = 0;

    while (choice != 4) {
        printf("\n--- MENU (%s) ---\n", u->username);
        printf("1.Book\n2.Payment\n3.Confirmed\n4.Logout\n");
        scanf("%d", &choice);

        if (choice == 1){
            book_trip(*u, routes, rcount, trips, tcount);
        }
        else if (choice == 2){
            payment(*u, trips, *tcount);
        }
        else if (choice == 3){
            confirmed_trips(*u, trips, *tcount);
        }
    }
}

