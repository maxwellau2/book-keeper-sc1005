#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXBOOKS 5
#define LENGTH 30

struct Book
{
    int bookID;
    char title[40];
    char author[40];
    double price;
    int quantity;
};

// quicksort stuff
int compareBooks(const struct Book *a, const struct Book *b)
{
    // Special case: If bookID is 0, place it at the back
    if (a->bookID == 0 && b->bookID == 0) {
        return 0;
    } else if (a->bookID == 0) {
        return 1;
    } else if (b->bookID == 0) {
        return -1;
    }

    // Compare bookIDs for normal books
    return a->bookID - b->bookID;
}

// Quicksort partition function
int partition(struct Book books[], int low, int high)
{
    struct Book pivot = books[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (compareBooks(&books[j], &pivot) <= 0) {
            i++;
            struct Book temp = books[i];
            books[i] = books[j];
            books[j] = temp;
        }
    }

    struct Book temp = books[i + 1];
    books[i + 1] = books[high];
    books[high] = temp;

    return i + 1;
}

// Quicksort
void quickSort(struct Book books[], int low, int high)
{
    if (low < high) {
        int pivot = partition(books, low, high);
        quickSort(books, low, pivot - 1);
        quickSort(books, pivot + 1, high);
    }
}

// helper function to help me check books
void checkBook(struct Book book)
{
    printf("BookID: %d\n", book.bookID);
    printf("Book title: %s\n", book.title);
    printf("Author name: %s\n", book.author);
    printf("Book price: %.2f\n", book.price);
    printf("Quantity: %d\n", book.quantity);
}

void listBooks(struct Book books[])
{
    quickSort(books, 0, MAXBOOKS - 1);
    // first check if list is empty (i.e. first book id is 0)
    if(books[0].bookID == 0)
    {
        printf("The bookshop is empty\n");
        return;
    }
    // otherwise continue
    for(int i = 0; i < MAXBOOKS; i++)
    {
        if(books[i].bookID == 0) break;
        checkBook(books[i]);
    } 
    
}

void convertToUpper(char returnable[40], char sequence[40])
{
    // initialise the characters to contain converted characters
    int a; // placeholder for character
    // for each element in sequence, convert to upper and append to returnable
    for(int i=0; i < 40; i++)
    {
        if(sequence[i] == 0) break;
        a = toupper(sequence[i]);
        char c = (char)a;
        returnable[i] = c;
    }
    return;
}

int getLength(struct Book books[])
{
    for(int i = 0; i<LENGTH; i++)
    {
        if(books[i].bookID == 0) return i;
    }
    return -1;
}

int findBookidx(struct Book books[], char booktitle[LENGTH], char authorname[LENGTH])
{
    // get target author and title
    char UpperBookTitleTarget[LENGTH] = {0}, UpperAuthorNameTarget[LENGTH] = {0};
    // initialise placeholder strings
    char UpperBookTitlePlace[LENGTH] = {0}, UpperAuthorNamePlace[LENGTH] = {0};
    // convert targets to upper
    convertToUpper(UpperBookTitleTarget, booktitle);
    convertToUpper(UpperAuthorNameTarget, authorname);
        // printf("%s %s\n", UpperBookTitleTarget, UpperAuthorNameTarget);
    // iterate thru the list of books, and match its title and author
    for(int i=0; i<MAXBOOKS; i++)
    {
        memset(UpperBookTitlePlace,'\0', sizeof(UpperBookTitlePlace)); // reset placeholders to null
        memset(UpperAuthorNamePlace,'\0', sizeof(UpperAuthorNamePlace));
        convertToUpper(UpperBookTitlePlace, books[i].title);
        convertToUpper(UpperAuthorNamePlace, books[i].author);
        // printf("%s %s", books[i].title, books[i].author);
        // printf("%s %s\n", UpperBookTitlePlace, UpperAuthorNamePlace);
        if((strcmp(UpperAuthorNamePlace, UpperAuthorNameTarget) == 0)
            && (strcmp(UpperBookTitlePlace, UpperBookTitleTarget) == 0))
        {
            return i;
        }
    }
    return -1;
}

void findBook(struct Book books[])
{
    char targettitle[40] = {0};
    char targetauthor[40] = {0};
    int bookidx;
    printf("Enter the target book title:\n");
    getchar();
    gets(targettitle);
    printf("Enter the target author name:\n");
    // getchar();
    gets(targetauthor);
    bookidx = findBookidx(books, targettitle, targetauthor);
    if(bookidx == -1)
    {
        printf("The target book is not found\n");
        return;
    }
    else
    {
        printf("The target book is found\n");
        checkBook(books[bookidx]);
        return;
    }
    return;

}

int checkBookId(struct Book books[], int bookID)
{
    for(int i=0; i<MAXBOOKS; i++)
    {
        if(books[i].bookID == bookID) return 1;
    }
    return 0;
}

void addBook(struct Book books[])
{
    int bookid, quantity;
    double price;
    char booktitle[40] = {'\0'}, authorname[40] = {'\0'};
    printf("Enter bookID:\n");
    scanf("%d", &bookid);
    printf("Enter book title:\n");
    getchar();
    gets(booktitle);;
    printf("Enter author name:\n");
    // getchar();
    gets(authorname);;
    printf("Enter price:\n");
    scanf("%lf", &price);
    printf("Enter quantity:\n");
    scanf("%d", &quantity);
    // create new book
    struct Book newbook;
    strcpy(newbook.author, authorname);
    strcpy(newbook.title, booktitle);
    newbook.price = price;
    newbook.bookID = bookid;
    newbook.quantity = quantity;
    // check if store is full
    if (books[MAXBOOKS-1].bookID != 0)
    {
        printf("The bookshop is full! Unable to addBook()\n");
        return;
    }
    // check if book id exists
    if (checkBookId(books, newbook.bookID) != 0)
    {
        printf("The bookID has already existed! Unable to addBook()\n");
        return;
    }
    // assign new element
    books[getLength(books)] = newbook;
    printf("The book has been added successfully\n");
    quickSort(books, 0, MAXBOOKS - 1);
    return;
}

void removeBook(struct Book books[])
{
    char targettitle[40] = {0};
    char targetauthor[40] = {0};
    int bookidx;
    printf("Enter the target book title:\n");
    getchar();
    gets(targettitle);
    printf("Enter the target author name:\n");
    // getchar();
    gets(targetauthor);
    if(books[0].bookID == 0)
    {
        printf("The bookshop is empty\n");
        return;
    }
    bookidx = findBookidx(books, targettitle, targetauthor);
    if(bookidx != -1)
    {
        printf("The target book is removed\n");
        checkBook(books[bookidx]);
        // create empty book
        struct Book emptybook = {0};
        books[bookidx] = emptybook;
        quickSort(books, 0, MAXBOOKS - 1);
        return;
    }
    printf("The target book is not in the bookshop\n");
    return;
}

void updateBook(struct Book books[])
{
    char targettitle[40] = {0};
    char targetauthor[40] = {0};
    int bookidx, quantity;
    double price;
    printf("Enter the target book title:\n");
    getchar();
    gets(targettitle);
    printf("Enter the target author name:\n");
    // getchar();
    gets(targetauthor);
    bookidx = findBookidx(books, targettitle, targetauthor);
    if(bookidx == -1)
    {
        printf("The target book is not in the bookshop\n");
        return;
    }
    printf("Enter updated book price:\n");
    scanf("%lf", &price);
    printf("Enter updated quantity:\n");
    scanf("%d", &quantity);
    books[bookidx].quantity = quantity;
    books[bookidx].price = price;
    printf("The target book is updated\n");
    checkBook(books[bookidx]);
    return;
}

int main()
{
    int selection = 0, quit = 0;
    struct Book books[LENGTH] = {0}; // struct initialisation standard
    printf("NTU BOOKSHOP MANAGEMENT PROGRAM: \n");
    printf("1: listBooks()\n2: addBook()\n3: removeBook()\n4: findBook()\n5: updateBook()\n6: quit\n");
    while(!quit)
    {
        switch (selection)
        {
            case 0:
            {
                printf("Enter your choice:\n");
                scanf("%d", &selection);
                break;
            }
            case 1:
            {
                printf("listBooks():\n");
                listBooks(books);
                selection = 0;
                break;
            }
            case 2:
            {
                printf("addBook():\n");
                addBook(books);
                selection = 0;
                break;
            }
            case 3:
            {
                printf("removeBook():\n");
                removeBook(books);
                selection = 0;
                break;
            }
            case 4:
            {
                printf("findBook():\n");
                findBook(books);
                selection = 0;
                break;
            }
            case 5:
            {
                printf("updateBook():\n");
                updateBook(books);
                selection = 0;
                break;
            }
            case 6:
            {
                quit = 1;
                break;
            }
            default :
            {
                printf("enter a valid input\n");
                selection = 0;
                break;
            }
        }
    }
    return 0;
}
