#include <stdio.h>
#include <string.h>
#include "client_lib.h"

// DATE COMPARISON 
Date make_date(char *str){
    Date d;
    
    d.dd = (str[0]-'0')*10 + (str[1]-'0');
    d.mm = (str[3]-'0')*10 + (str[4]-'0');
    d.yyyy = (str[6]-'0')*1000 + (str[7]-'0')*100 + (str[8]-'0')*10 + (str[9]-'0');
    return d;
}

int compare_trips(char *d1, char *d2){
    Date date1 = make_date(d1);
    Date date2 = make_date(d2);

    if(date1.yyyy < date2.yyyy){
        return -1;
    }
    else if(date1.yyyy > date2.yyyy){
        return 1;
    }

    if(date1.mm < date2.mm){
        return -1;
    }
    else if(date1.mm > date2.mm){
        return 1;
    }

    if(date1.dd < date2.dd){
        return -1;
    }
    else if(date1.dd > date2.dd){
        return 1;
    }

    return 0; // οι ημερομηνίες είναι ίδιες
}

// LOGIN
int check_login(User users[], int count, char *username, char *password){
    for(int i=0;i<count;i++){
        if(strcmp(users[i].username,username)==0 && strcmp(users[i].password,password)==0){
            return i;
        }
    }
    return -1;
}

// ROUTES 
void view_routes(Route routes[], int rcount){
    int i;

    printf("\n-----------------------------------------------\n");
    printf("Νησί/Λιμάνι     Κωδικός  Κατάστρωμα  Αεροπορικού τύπου  Καμπίνα  Αυτοκίνητο\n");
    printf("-----------------------------------------------\n");

    for(i = 0; i < rcount; i++){
        printf("%-15s %-7s %-9d %-7d %-8d %-7d\n",
               routes[i].name,
               routes[i].code,
               routes[i].deck,
               routes[i].air,
               routes[i].cabin,
               routes[i].car);
    }
    printf("-----------------------------------------------\n");
}

// ID GENERATION 
void generate_trip_id(char *date, char *code, char *user, char *id){
    char clean[15];
    int k=0;

    for(int i=0; date[i]!='\0'; i++){
        if(date[i]!='/'){
            clean[k++]=date[i];
        }
    }

    clean[k]='\0';
    strcpy(id, clean);
    strcat(id, code); 
    strcat(id, "-"); 
    strcat(id, user);
}

// BOOKING
int is_valid_date_format(char *str){
    if(strlen(str) != 10) return 0;
    if(str[2] != '/' || str[5] != '/') return 0;
    for(int i = 0; i < 10; i++){
        if(i == 2 || i == 5) continue;
        if(str[i] < '0' || str[i] > '9') return 0;
    }
    return 1;
}

// Έλεγχος ότι ημερομηνία επιστροφής είναι μετά την αναχώρηση
int is_return_after_departure(char *dep, char *ret){
    Date d1 = make_date(dep);
    Date d2 = make_date(ret);

    if(d2.yyyy < d1.yyyy) return 0;
    if(d2.yyyy == d1.yyyy && d2.mm < d1.mm) return 0;
    if(d2.yyyy == d1.yyyy && d2.mm == d1.mm && d2.dd <= d1.dd) return 0;

    return 1;
}

void book_trip(User u, Route routes[], int rcount, BookedTrip trips[], int *tcount){
    if(*tcount >= 50) {
        printf("Megistos arithmos taxidiwn\n");
        return;
    }

    int seat, car, back;
    float base, total;
    char dep[15], ret[15] = "-", code[10];
    int dep_attempts = 0, port_attempts = 0, ret_attempts = 0;
    int dep_valid = 0, ret_valid = 0;
    int index = -1;

    // Ημερομηνία αναχώρησης 
    while(dep_attempts < 3 && dep_valid == 0){
        printf("Hmeromhnia anaxwrhshs (dd/mm/yyyy): ");
        scanf("%s", dep);
        if(is_valid_date_format(dep)){
            dep_valid = 1; // σωστή εισαγωγή
        } 
        else{
            dep_attempts++;
            printf("Λάθος μορφή ημερομηνίας (%d/3)\n", dep_attempts);
        }
    }
    if(dep_valid == 0){
        printf("Ξεπεράσατε τις 3 προσπάθειες. Επιστροφή στο menu.\n");
        return;
    }

    // Είσοδος κωδικού λιμανιού μέχρι 3 προσπάθειες 
    while(port_attempts < 3 && index == -1){
        printf("Kwdikos limaniou: ");
        scanf("%s", code);
        for(int i = 0; i < rcount; i++){
            if(strcmp(routes[i].code, code) == 0){
                index = i;
            }
        }
        if(index == -1){
            port_attempts++;
            printf("Λάθος κωδικός λιμανιού (%d/3)\n", port_attempts);
        }
    }
    if(index == -1){
        printf("Ξεπεράσατε τις 3 προσπάθειες. Επιστροφή στο menu.\n");
        return;
    }

    // Επιλογή θέσης επιβάτη μέχρι 3 προσπάθειες
    printf("Thesh (1-Deck 2-Air 3-Cabin): ");
    scanf("%d", &seat);

    if(seat == 1){
        base = routes[index].deck;
    }
    else if(seat == 2){
        base = routes[index].air;
    }
    else{ 
        base = routes[index].cabin;
    }

    total = base;

    // Επιλογή αν ο επιβάτης έχει αυτοκίνητο
    printf("Aftokinhto (0/1): ");
    scanf("%d", &car);
    if(car) total += routes[index].car;

    // Επιλογή αν ο επιβάτης κάνει ταξίδι με επιστροφή
    printf("Epistrofh (0/1): ");
    scanf("%d", &back);

    if(back == 1){
        while(ret_attempts < 3 && ret_valid == 0){
            printf("Hmeromhnia epistrofhs (dd/mm/yyyy): ");
            scanf("%s", ret);

            if(!is_valid_date_format(ret)){
                ret_attempts++;
                printf("Λάθος μορφή ημερομηνίας (%d/3)\n", ret_attempts);
            } 
            else if(!is_return_after_departure(dep, ret)){
                ret_attempts++;
                printf("Η ημερομηνία επιστροφής πρέπει να είναι μετά την αναχώρηση (%d/3)\n", ret_attempts);
            }
            else {
                ret_valid = 1; // σωστή ημερομηνία
            }
        }
        if(ret_valid == 0){
            printf("Ξεπεράσατε τις 3 προσπάθειες. Επιστροφή στο menu.\n");
            return;
        }
        total = total + base * 0.75;
    }

    // Έλεγχος αν είναι φοιτητικό για να γίνει έκτπωση
    if(u.university_student == 1){
        total /= 2;
    }

    // Αποθήκευση κράτησης 
    
    strcpy(trips[*tcount].username, u.username);
    strcpy(trips[*tcount].dep_date, dep);
    strcpy(trips[*tcount].ret_date, ret);
    strcpy(trips[*tcount].status, "Ekkremei");
    trips[*tcount].trip_type = back;
    trips[*tcount].total_cost = total;
    generate_trip_id(dep, routes[index].code, u.username, trips[*tcount].booking_id);

    printf("ID: %s | Kostos: %.2f\n", trips[*tcount].booking_id, total);
    (*tcount)++;
}

// PAYMENT 

void payment(User u, BookedTrip trips[], int total){
    char id[50];
    int found = 0, attempts = 0;

    for(int i = 0; i < total; i++){
        if(strcmp(trips[i].username, u.username) == 0 && strcmp(trips[i].status, "Ekkremei") == 0){
            printf("%s | %.2f\n", trips[i].booking_id, trips[i].total_cost);
            found = 1;
        }
    }

    if(!found){
        printf("Den yparxoun krathseis gia exoflhsh\n");
        return;
    }

    int valid = 0;
    while(valid == 0 && attempts < 3){
        printf("Dwse ID: ");
        scanf("%s", id);
        int i;
        for(i = 0; i < total; i++){
            if(strcmp(trips[i].booking_id, id) == 0 && strcmp(trips[i].status, "Ekkremei") == 0){
                strcpy(trips[i].status, "Exoflithike");
                printf("Kratise exoflhth!\n");
                valid = 1;
            }
        }
        if(!valid){
            attempts++;
            printf("Λάθος ID (%d/3)\n", attempts);
            if(attempts >= 3){
                printf("Ξεπεράσατε τις 3 προσπάθειες. Επιστροφή στο menu.\n");
            }
        }
    }
}

// CONFIRMED 

void confirmed_trips(User u, BookedTrip trips[], int total){
    BookedTrip temp[50];
    int count = 0;

    for(int i = 0; i < total; i++){
        if(strcmp(trips[i].username, u.username) == 0 && strcmp(trips[i].status, "Exoflithike") == 0){
            temp[count++] = trips[i];
        }
    }

    if(count == 0){
        printf("Den yparxoun exoflhmenes krathseis\n");
        return;
    }

    char order[10];
    int attempts = 0, valid = 0;
    while(!valid && attempts < 3){
        printf("Seira (LOW/HIGH): ");
        scanf("%s", order);
        if(strcmp(order, "LOW") == 0 || strcmp(order, "HIGH") == 0){
            valid = 1;
        } else {
            attempts++;
            printf("Λάθος εισαγωγή (%d/3)\n", attempts);
            if(attempts >= 3){
                printf("Ξεπεράσατε τις 3 προσπάθειες. Επιστροφή στο menu.\n");
            }
        }
    }

    // Ταξινόμηση εφόσον όλα τα προηγούμενα στοιχεία έχουν εισαχθεί σωστά
    if(valid){
        for(int i = 0; i < count - 1; i++){
            for(int j = 0; j < count - 1; j++){
                int cmp = compare_trips(temp[j].dep_date, temp[j+1].dep_date);
                if((strcmp(order,"LOW")==0 && cmp>0) || (strcmp(order,"HIGH")==0 && cmp<0)){
                    BookedTrip t = temp[j];
                    temp[j] = temp[j+1];
                    temp[j+1] = t;
                }
            }
        }
        // Εκτύπωση
        printf("\nID κράτησης | Κόστος\n");
        for(int i = 0; i < count; i++){
            printf("%s | %.2f\n", temp[i].booking_id, temp[i].total_cost);
        }
    }
}

// CLIENT MENU 

void client_login(User *u, Route routes[], int rcount, BookedTrip trips[], int *tcount){
    int choice=0;

    while(choice!=5){
        printf("\n--- Client Dashboard (%s) ---\n", u->username);
        printf("1. View routes\n");
        printf("2. Book trip\n");
        printf("3. Payment\n");
        printf("4. Confirmed trips\n");
        printf("5. Logout\n");
        scanf("%d",&choice);
        if(choice == 1){
            view_routes(routes, rcount);
        }
        if(choice==2){
            book_trip(*u,routes,rcount,trips,tcount);
        }
        else if(choice==3){
            payment(*u,trips,*tcount);
        }
        else if(choice==4){
            confirmed_trips(*u,trips,*tcount);
        }
    }
}

