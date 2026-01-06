#include <stdio.h>
#include <string.h>

// Συναρτήσεις για τα dashboards
void adminDashboard() {
    int choice;

    printf("\n--- Administration Dashboard ---\n");
    printf("1. Προβολή χρηστών (dummy επιλογή)\n");
    printf("2. Επιστροφή στην Αρχική Οθόνη\n");
    printf("Επιλογή: ");
    scanf("%d", &choice);

    // Δεν υλοποιούμε κάτι παραπάνω, απλά επιστρέφουμε
    printf("Επιστροφή στην Αρχική Οθόνη...\n");
}

void clientDashboard() {
    int choice;

    printf("\n--- Client Dashboard ---\n");
    printf("1. Προβολή στοιχείων (dummy επιλογή)\n");
    printf("2. Επιστροφή στην Αρχική Οθόνη\n");
    printf("Επιλογή: ");
    scanf("%d", &choice);

    printf("Επιστροφή στην Αρχική Οθόνη...\n");
}

// Συνάρτηση Login
void login() {
    char username[30];
    char password[30];
    int tries = 0;

    // Επιτρέπονται μέχρι 3 προσπάθειες
    while (tries < 3) {
        printf("\n--- Login ---\n");
        printf("Username: ");
        scanf("%s", username);

        printf("Password: ");
        scanf("%s", password);

        // Έλεγχος για admin
        if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
            printf("\nΕπιτυχής σύνδεση Διαχειριστή!\n");
            adminDashboard();
            return;
        }

        // Έλεγχος για πελάτη (απλά ένα παράδειγμα χρήστη)
        if (strcmp(username, "client") == 0 && strcmp(password, "client123") == 0) {
            printf("\nΕπιτυχής σύνδεση Πελάτη!\n");
            clientDashboard();
            return;
        }

        // Αν φτάσει εδώ, είναι λάθος στοιχεία
        tries++;
        printf("\nΛάθος στοιχεία. Προσπάθεια %d από 3\n", tries);
    }

    // Μετά από 3 αποτυχημένες προσπάθειες
    printf("\n3 αποτυχημένες προσπάθειες. Επιστροφή στην Αρχική Οθόνη...\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n=== Αρχική Οθόνη Συστήματος ===\n");
        printf("1. Login\n");
        printf("2. Exit\n");
        printf("Επιλογή: ");
        scanf("%d", &choice);

        if (choice == 1) {
            login();
        }
        else if (choice == 2) {
            printf("\nΤερματισμός εφαρμογής...\n");
            break;
        }
        else {
            // Κλασικός έλεγχος λάθους επιλογής
            printf("\nΜη έγκυρη επιλογή. Προσπαθήστε ξανά.\n");
        }
    }

    return 0;
}