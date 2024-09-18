#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define FILE_NAME "books.dat"

typedef struct {
    char title[100];
    char author[100];
    float price;
    int quantity;
} Book;

// Function declarations
void addBook(Book books[], int *count);
void viewBooks(Book books[], int count);
void sellBook(Book books[], int count);
void searchBook(Book books[], int count);
void updateBook(Book books[], int count);
void saveBooks(Book books[], int count);
void loadBooks(Book books[], int *count);

int main() {
    Book books[MAX_BOOKS];
    int count = 0;
    int choice;

    // Load books from file at the start
    loadBooks(books, &count);

    do {
        printf("\nBookstore Menu:\n");
        printf("1. Add Book\n");
        printf("2. View Books\n");
        printf("3. Sell Book\n");
        printf("4. Search Book\n");
        printf("5. Update Book\n");
        printf("6. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook(books, &count);
                break;
            case 2:
                viewBooks(books, count);
                break;
            case 3:
                sellBook(books, count);
                break;
            case 4:
                searchBook(books, count);
                break;
            case 5:
                updateBook(books, count);
                break;
            case 6:
                saveBooks(books, count);
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}

void addBook(Book books[], int *count) {
    if (*count >= MAX_BOOKS) {
        printf("Bookstore is full, cannot add more books.\n");
        return;
    }

    printf("Enter book title: ");
    scanf(" %[^\n]", books[*count].title);
    printf("Enter book author: ");
    scanf(" %[^\n]", books[*count].author);
    printf("Enter book price: ");
    scanf("%f", &books[*count].price);
    printf("Enter book quantity: ");
    scanf("%d", &books[*count].quantity);

    (*count)++;
    printf("Book added successfully!\n");
}

void viewBooks(Book books[], int count) {
    if (count == 0) {
        printf("No books available.\n");
        return;
    }

    printf("\nAvailable Books:\n");
    for (int i = 0; i < count; i++) {
        printf("Title: %s, Author: %s, Price: %.2f, Quantity: %d\n",
               books[i].title, books[i].author, books[i].price, books[i].quantity);
    }
}

void sellBook(Book books[], int count) {
    char title[100];
    printf("Enter the title of the book to sell: ");
    scanf(" %[^\n]", title);

    for (int i = 0; i < count; i++) {
        if (strcmp(books[i].title, title) == 0) {
            if (books[i].quantity > 0) {
                books[i].quantity--;
                printf("Book sold successfully! Remaining quantity: %d\n", books[i].quantity);
            } else {
                printf("Sorry, this book is out of stock.\n");
            }
            return;
        }
    }
    printf("Book not found.\n");
}

void searchBook(Book books[], int count) {
    char title[100];
    printf("Enter the title of the book to search: ");
    scanf(" %[^\n]", title);

    for (int i = 0; i < count; i++) {
        if (strcmp(books[i].title, title) == 0) {
            printf("Found Book: Title: %s, Author: %s, Price: %.2f, Quantity: %d\n",
                   books[i].title, books[i].author, books[i].price, books[i].quantity);
            return;
        }
    }
    printf("Book not found.\n");
}

void updateBook(Book books[], int count) {
    char title[100];
    printf("Enter the title of the book to update: ");
    scanf(" %[^\n]", title);

    for (int i = 0; i < count; i++) {
        if (strcmp(books[i].title, title) == 0) {
            printf("Updating Book: %s\n", books[i].title);
            printf("Enter new author: ");
            scanf(" %[^\n]", books[i].author);
            printf("Enter new price: ");
            scanf("%f", &books[i].price);
            printf("Enter new quantity: ");
            scanf("%d", &books[i].quantity);
            printf("Book updated successfully!\n");
            return;
        }
    }
    printf("Book not found.\n");
}

void saveBooks(Book books[], int count) {
    FILE *file = fopen(FILE_NAME, "wb");
    if (file == NULL) {
        printf("Error opening file for saving.\n");
        return;
    }
    fwrite(books, sizeof(Book), count, file);
    fclose(file);
    printf("Books saved successfully!\n");
}

void loadBooks(Book books[], int *count) {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("No saved books found. Starting fresh.\n");
        *count = 0;
        return;
    }
    *count = fread(books, sizeof(Book), MAX_BOOKS, file);
    fclose(file);
    printf("%d books loaded successfully!\n", *count);
}