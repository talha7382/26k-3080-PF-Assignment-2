#include <stdio.h>
#include <string.h>
 
void registerMember(char name[], int *studentID, int *memberType) {
    printf("\nEnter your name\n");
    scanf(" %49[^\n]", name);
 
    printf("Enter student ID: ");
    scanf("%d", studentID);
 
    do {
        printf("membership type? (1 = Student, 2 = Faculty): ");
        scanf("%d", memberType);
        if (*memberType != 1 && *memberType != 2)
            printf("Invalid membership type. Try again.\n");
    } while (*memberType != 1 && *memberType != 2);
}
 
void displayBooks(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks) {
    printf("\n%-6s %-20s %s\n", "ID", "Title", "Copies");
    for(int i = 0; i < totalBooks; i++)
        printf("%-6d %-20s %d\n", bookIDs[i], bookTitles[i], availableCopies[i]);
}
 
void displayMenu() {
    printf("\n\nEnter 1 to register, 2 to display books, 3 to borrow a book, 4 to return a book,"
        "5 to display your record or 6 to Exit.\n");
}
 
void borrowBook(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks,
                int borrowedBookIDs[], int *borrowedCount, int memberType) {
    int id, days, index = -1;
 
    if (*borrowedCount >= 3) {
        printf("you cannot borrow more books.\n");
        return;
    }
 
    printf("enter book ID: ");
    scanf("%d", &id);
    printf("ener number of days you want to keep the book: ");
    scanf("%d", &days);
 
    if (days <= 0) {
        printf("number of days must be positive.\n");
        return;
    }
 
    for (int i = 0; i < totalBooks; i++) {
        if (bookIDs[i] == id)
            index = i;
    }
 
    if (index == -1) {
        printf("Invalid book ID.\n");
        return;
    }
    if (availableCopies[index] == 0) {
        printf("copies of %s are not available right now.\n", bookTitles[index]);
        return;
    }
 
    int allowedDays = (memberType) ? 14 : 30;
    if (days > allowedDays)
        printf("you areonly allowed %d days, extra days will be fined.\n", allowedDays);
 
    borrowedBookIDs[*borrowedCount] = id;
    (*borrowedCount)++;
    availableCopies[index]--;
    printf("You borrowed %s.\n", bookTitles[index]);
}
 
float returnBook(int bookIDs[], int availableCopies[], int totalBooks, int borrowedBookIDs[],
                 int *borrowedCount, int memberType, float *totalFine) {
    int id, days, pos = -1;
    float fine = 0, finePayable = 0;
    char code[20];
 
    if (!*borrowedCount) {
        printf("You have not borrowed any books.\n");
        return 0;
    }
 
    printf("Enter book ID to return: ");
    scanf("%d", &id);
    printf("Enter the number of days the book was kept: ");
    scanf("%d", &days);
 
    if (days <= 0) {
        printf("Number of days must be positive.\n");
        return 0;
    }
 
    for (int i = 0; i < *borrowedCount; i++) {
        if (borrowedBookIDs[i] == id)
            pos = i;
    }
    if (pos == -1) {
        printf("You have not borrowed the book with ID %d.\n", id);
        return 0;
    }
 
    for (int i = 0; i < totalBooks; i++) {
        if (bookIDs[i] == id)
            availableCopies[i]++;
    }
 
    int allowedDays = (memberType == 1) ? 14 : 30;
    int rate = (memberType == 1) ? 20 : 10;
 
    if (days > allowedDays)
        fine = (days - allowedDays) * rate;
 
    *totalFine = *totalFine + fine;
    finePayable = fine;
 
    if (fine > 0) {
        printf("The book is late. Fine is Rs. %.2f\n", fine);
        printf("Enter membership code (enter any other text to skip): ");
        scanf("%19s", code);
        if (strcmp(code, "LIB2026") == 0) {
            finePayable = fine / 2;
            printf("Code is correct, 50%% waiver applied. Fine to pay is Rs. %.2f\n", finePayable);
        }
        else
            printf("Wrong code, no waiver.\n");
    } 
    else
        printf("Book returned on time, no fine.\n");
 
    for (int i = pos; i < *borrowedCount - 1; i++)
        borrowedBookIDs[i] = borrowedBookIDs[i + 1];

    borrowedBookIDs[*borrowedCount - 1] = 0;
    (*borrowedCount)--;
 
    return finePayable;
}
 
void displayMemberRecord(char name[], int studentID, int memberType, int borrowedBookIDs[], int borrowedCount, float totalFine, float fineAfterWaiver) {
    printf("\nName: %s\n", name);
    printf("Student ID: %d\n", studentID);
    if (memberType == 1)
        printf("membership type: Student\n");
    else
        printf("membership type: Faculty\n");
 
    printf("borrowed books: ");
    if (borrowedCount == 0)
        printf("None");
    for (int i = 0; i < borrowedCount; i++)
        printf("%d ", borrowedBookIDs[i]);
    printf("\n");
 
    printf("total fine: Rs. %.2f\n", totalFine);
    printf("Final fine after waiver: Rs. %.2f\n", fineAfterWaiver);
}
 
int main() {
    int bookIDs[4] = {101, 102, 103, 104};
    char bookTitles[4][50] = {
        "Programming in C",
        "Data Structures",
        "Database Systems",
        "Computer Networks"
    };
 
    int availableCopies[4] = {5, 3, 0, 4};
    int totalBooks = 4;
    char name[50];
    int studentID, memberType;
    int registered = 0;
 
    int borrowedBookIDs[3] = {0};
    int borrowedCount = 0;
    float totalFine = 0, fineAfterWaiver = 0;
 
    int choice = 0;
    do {
        displayMenu();
        scanf("%d", &choice);
 
        switch (choice) {
            case 1:
                registerMember(name, &studentID, &memberType);
                registered = 1;
                break;
            case 2:
                displayBooks(bookIDs, bookTitles, availableCopies, totalBooks);
                break;
            case 3:
                if (registered == 0)
                    printf("Please register first.\n");
                else
                    borrowBook(bookIDs, bookTitles, availableCopies, totalBooks, borrowedBookIDs, &borrowedCount, memberType);
                break;
            case 4:
                if (registered == 0)
                    printf("Please register first.\n");
                else
                    fineAfterWaiver += returnBook(bookIDs, availableCopies, totalBooks, borrowedBookIDs, &borrowedCount, memberType, &totalFine);
                break;
            case 5:
                if (registered == 0)
                    printf("Please register first.\n");
                else
                    displayMemberRecord(name, studentID, memberType, borrowedBookIDs, borrowedCount, totalFine, fineAfterWaiver);
                break;
            case 6:
                break;
            default:
                printf("Invalid. Try again");
                break;
        }
 
    } while (choice != 6);
}
