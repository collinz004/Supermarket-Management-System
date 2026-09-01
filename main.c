#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 200
#define MAX_USERS 20
#define MAX_TRANSACTIONS 1000
#define MAX_ITEMS_PER_TRANSACTION 20

#define ROLE_EMPLOYEE 1
#define ROLE_MANAGER 2

#define TYPE_IN_STORE 1
#define TYPE_ONLINE 2

#define CUSTOMER_REGULAR 1
#define CUSTOMER_WHOLESALE 2

typedef struct
{
    int id;
    char name[50];
    char category[30];
    float retailPrice;
    float wholesalePrice;
    int quantity;
    int reorderLevel;
} Product;

Product products[MAX_PRODUCTS];
int productCount = 0;

typedef struct
{
    int id;
    char name[50];
    char username[30];
    char password[30];
    int role;
} User;

typedef struct
{
    int productId;
    int quantity;
    float unitPrice;
    float subtotal;
} TransactionItem;

typedef struct
{
    int transactionId;
    char date[11];
    int type;
    int customerType;
    int employeeId;

    TransactionItem items[MAX_ITEMS_PER_TRANSACTION];
    int itemCount;

    float subtotal;
    float discount;
    float deliveryCharge;
    float total;

    char deliveryAddress[100];
    int status;
} Transaction;

User users[MAX_USERS];
int userCount = 0;

Transaction transactions[MAX_TRANSACTIONS];
int transactionCount = 0;

void displayWelcomeScreen(void)
{
    printf("\n");
    printf("==================================================\n");
    printf("                  UNI MART\n");
    printf("          SUPERMARKET MANAGEMENT\n");
    printf("                  SYSTEM\n");
    printf("==================================================\n");
}

void showMainMenu(void)
{
    printf("\n");
    printf("--------------- MAIN MENU ---------------\n");
    printf("1. Shop Online\n");
    printf("2. In-Store Checkout\n");
    printf("3. Staff Login\n");
    printf("4. Exit\n");
    printf("------------------------------------------\n");
    printf("Enter your choice: ");
}

int readInteger(void)
{
    int value;

    while (scanf("%d", &value) != 1)
    {
        while (getchar() != '\n')
        {
            /* Clear invalid input */
        }

        printf("Invalid input. Please enter a number: ");
    }

    while (getchar() != '\n')
    {
        /* Clear remaining input */
    }

    return value;
}

void onlineShopping(void);
void inStoreCheckout(void);
void staffLogin(void);

int main(void)
{
    int choice;

    displayWelcomeScreen();

    do
    {
        showMainMenu();
        choice = readInteger();

        switch (choice)
        {
            case 1:
                onlineShopping();
                break;

            case 2:
                inStoreCheckout();
                break;

            case 3:
                staffLogin();
                break;

            case 4:
                printf("\nThank you for visiting UNI MART!\n");
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

void onlineShopping(void)
{
    int choice;

    do
    {
        printf("\n");
        printf("========================================\n");
        printf("            UNI MART ONLINE\n");
        printf("========================================\n");
        printf("1. Browse Products\n");
        printf("2. Search Products\n");
        printf("3. View Cart\n");
        printf("4. Checkout\n");
        printf("5. View My Orders\n");
        printf("6. Back to Main Menu\n");
        printf("----------------------------------------\n");
        printf("Enter your choice: ");

        choice = readInteger();

        switch (choice)
        {
            case 1:
                printf("\nBrowse Products selected.\n");
                break;

            case 2:
                printf("\nSearch Products selected.\n");
                break;

            case 3:
                printf("\nView Cart selected.\n");
                break;

            case 4:
                printf("\nCheckout selected.\n");
                break;

            case 5:
                printf("\nMy Orders selected.\n");
                break;

            case 6:
                printf("\nReturning to main menu...\n");
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }

    } while (choice != 6);
}

void inStoreCheckout(void)
{
    int choice;

    do
    {
        printf("\n");
        printf("========================================\n");
        printf("          IN-STORE CHECKOUT\n");
        printf("========================================\n");
        printf("1. Start New Sale\n");
        printf("2. Search Product\n");
        printf("3. View Products\n");
        printf("4. Low Stock Check\n");
        printf("5. Back to Main Menu\n");
        printf("----------------------------------------\n");
        printf("Enter your choice: ");

        choice = readInteger();

        switch (choice)
        {
            case 1:
                printf("\nNew sale selected.\n");
                break;

            case 2:
                printf("\nSearch Product selected.\n");
                break;

            case 3:
                printf("\nView Products selected.\n");
                break;

            case 4:
                printf("\nLow Stock Check selected.\n");
                break;

            case 5:
                printf("\nReturning to main menu...\n");
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }

    } while (choice != 5);
}

void staffLogin(void)
{
    char username[30];
    char password[30];

    printf("\n");
    printf("========================================\n");
    printf("               STAFF LOGIN\n");
    printf("========================================\n");

    printf("Username: ");
    fgets(username, sizeof(username), stdin);

    printf("Password: ");
    fgets(password, sizeof(password), stdin);

    printf("\nLogin system will be connected to user records.\n");
}