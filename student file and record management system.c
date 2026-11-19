#include <stdio.h>

struct Student {
    int id;
    char name[50];
    float mark;
};

int main() {
    struct Student s;
    FILE *file;
    int choice, searchId, found;

    do {
        printf("\n--- Student Record System ---\n");
        printf("1. Add student\n");
        printf("2. View all students\n");
        printf("3. Search student by ID\n");
        printf("4. Delete student by ID\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            file = fopen("students.txt", "a");

            if (file == NULL) {
                printf("Could not open file.\n");
                continue;
            }

            printf("Enter student ID: ");
            scanf("%d", &s.id);

            printf("Enter student name (one word): ");
            scanf("%49s", s.name);

            printf("Enter mark: ");
            scanf("%f", &s.mark);

            fprintf(file, "%d %s %.2f\n", s.id, s.name, s.mark);
            fclose(file);

            printf("Student record saved.\n");
        }

        else if (choice == 2) {
            file = fopen("students.txt", "r");

            if (file == NULL) {
                printf("No records found yet.\n");
                continue;
            }

            printf("\nID\tName\tMark\n");
            while (fscanf(file, "%d %49s %f",
                          &s.id, s.name, &s.mark) == 3) {
                printf("%d\t%s\t%.2f\n", s.id, s.name, s.mark);
            }

            fclose(file);
        }

        else if (choice == 3) {
            file = fopen("students.txt", "r");

            if (file == NULL) {
                printf("No records found yet.\n");
                continue;
            }

            printf("Enter ID to search: ");
            scanf("%d", &searchId);
            found = 0;

            while (fscanf(file, "%d %49s %f",
                          &s.id, s.name, &s.mark) == 3) {
                if (s.id == searchId) {
                    printf("Found: ID=%d, Name=%s, Mark=%.2f\n",
                           s.id, s.name, s.mark);
                    found = 1;
                    break;
                }
            }

            if (!found) {
                printf("Student not found.\n");
            }

            fclose(file);
        }

        else if (choice == 4) {
            FILE *tempFile;
            int deleted = 0;

            file = fopen("students.txt", "r");
            tempFile = fopen("temp.txt", "w");

            if (file == NULL || tempFile == NULL) {
                printf("Could not open files.\n");
                if (file != NULL) fclose(file);
                if (tempFile != NULL) fclose(tempFile);
                continue;
            }

            printf("Enter ID to delete: ");
            scanf("%d", &searchId);

            while (fscanf(file, "%d %49s %f",
                          &s.id, s.name, &s.mark) == 3) {
                if (s.id == searchId) {
                    deleted = 1;
                } else {
                    fprintf(tempFile, "%d %s %.2f\n",
                            s.id, s.name, s.mark);
                }
            }

            fclose(file);
            fclose(tempFile);

            remove("students.txt");
            rename("temp.txt", "students.txt");

            if (deleted) {
                printf("Student record deleted.\n");
            } else {
                printf("Student ID not found.\n");
            }
        }

        else if (choice != 0) {
            printf("Invalid choice. Try again.\n");
        }

    } while (choice != 0);

    printf("Program ended.\n");
    return 0;
}