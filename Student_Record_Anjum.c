#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Student {
    int id;
    char name[50];
    float gpa;
};

struct Student MIT[100]; //Temporary RAM storage array for 100 students
int count = 0;

/*
 ====Manual struct add for testing=================

 MIT[0].id = 1001;
 strcpy(MIT[0].name, "test1");
 MIT[0].gpa = 2.1;

 MIT[1].id = 1002;
 strcpy(MIT[1].name, "test2");
 MIT[1].gpa = 2.2;

 count = 2; // important: update number of stored students
 // ================================================
*/

void clearInput() {
    while (getchar() != '\n');
}

int isValidName(const char *name) {
    for (int i = 0; name[i] != '\0'; i++) {
        if (!isalpha(name[i]))
            return 0;
    }
    return 1;
}

void addStudent() {
    struct Student temp;
    char input[50];

    printf("\n(Type 'exit' to cancel)\n");

    while (1) {
        printf("Enter ID: ");
        scanf("%49s", input);
        if (strcmp(input, "exit") == 0) return;
        if (sscanf(input, "%d", &temp.id) == 1)
            break;
        printf("Invalid ID!\n");
    }

    while (1) {
        printf("Enter name: ");
        scanf("%49s", temp.name);
        if (strcmp(temp.name, "exit") == 0) return;
        if (isValidName(temp.name))
            break;
        printf("Invalid name.\n");
    }

    while (1) {
        printf("Enter GPA (0.0 - 4.0): ");
        scanf("%49s", input);
        if (strcmp(input, "exit") == 0) return;
        if (sscanf(input, "%f", &temp.gpa) == 1 &&
            temp.gpa >= 0.0 && temp.gpa <= 4.0)
            break;
        printf("Invalid GPA.\n");
    }

    MIT[count] = temp;
    count++;

    printf("Student added.\n");
}

void saveToFile() {
    FILE *file = fopen("students.txt", "w");
    if (!file) {
        printf("Error saving file.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d %s %.2f\n",
                MIT[i].id, MIT[i].name, MIT[i].gpa);
    }

    fclose(file);
    printf("Saved %d records.\n", count);
}

void loadFromFile() {
    FILE *file = fopen("students.txt", "r");
    if (!file) {
        printf("No file found.\n");
        return;
    }

    count = 0;

    while (fscanf(file, "%d %49s %f",
                  &MIT[count].id,
                  MIT[count].name,
                  &MIT[count].gpa) == 3) {
        count++;
    }

    fclose(file);
    printf("Loaded %d students.\n", count);
}

void displayAll() {
    if (count == 0) {
        printf("No students stored.\n");
        return;
    }

    printf("\n--- Student List ---\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%s\t%.2f\n",
               MIT[i].id, MIT[i].name, MIT[i].gpa);
    }

    printf("\nPress enter to return...");
    clearInput();
    getchar();
}

void searchByID() {
    int id;
    printf("Enter ID: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (MIT[i].id == id) {
            printf("Found: %d %s %.2f\n",
                   MIT[i].id, MIT[i].name, MIT[i].gpa);
            return;
        }
    }

    printf("Not found.\n");
}

void searchMenu() {
    int c;
    do {
        printf("\n=== Search Menu ===\n");
        printf("1. Search by ID\n");
        printf("2. Back\n");
        printf("Enter choice: ");
        scanf("%d", &c);

        switch (c) {
            case 1: searchByID(); break;
            case 2: return;
            default: printf("Invalid.\n");
        }
    } while (1);
}

int main() {
    int choice;

    do {
        printf(" __  __ ___ _____ \n");
        printf("|  \\/  |_ _|_   _| Maldives Institute of Technology\n");
        printf("| |\\/| || |  | |   Empowering Future Engineers through Innovation & Skill.  \n");
        printf("|_|  |_|___| |_|  \n");
        printf("\n=== Students Records Manager ===\n");
        printf("1. Add Student\n");
        printf("2. Display All\n");
        printf("3. Search\n");
        printf("4. Load File\n");
        printf("5. Save File\n");
        printf("6. Exit\n");
        printf("Enter choice: ");

        while (scanf("%d", &choice) != 1) {
            clearInput();
            printf("Invalid. Try again: ");
        }

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayAll(); break;
            case 3: searchMenu(); break;
            case 4: loadFromFile(); break;
            case 5: saveToFile(); break;
            case 6:
                printf("Save before exiting? (y/n): ");
                clearInput();
                char x = getchar();
                if (x == 'y' || x == 'Y') saveToFile();
                printf("Goodbye.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 6);

    return 0;
}
