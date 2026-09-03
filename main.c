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

void inventoryManagement(void);

void addProduct(void);
void displayProducts(void);
void searchProduct(void);
void updateProduct(void);
void deleteProduct(void);
void sortProducts(void);
void lowStockReport(void);
void inventoryValueReport(void);

void readString(char text[], int size);
float readNonNegativeFloat(void);

void loadSampleProducts(void);

int main(void)
{
    int choice;

    displayWelcomeScreen();
    loadSampleProducts();

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
        printf("4. Low Stock Report\n");
        printf("5. Inventory Management\n");
        printf("6. Back to Main Menu\n");
        printf("----------------------------------------\n");
        printf("Enter your choice: ");

        choice = readInteger();

        switch (choice)
        {
            case 1:
                printf("\nNew sale module will be connected soon.\n");
                break;

            case 2:
                searchProduct();
                break;

            case 3:
                displayProducts();
                break;

            case 4:
                lowStockReport();
                break;

            case 5:
                inventoryManagement();
                break;

            case 6:
                printf("\nReturning to main menu...\n");
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }

    } while (choice != 6);
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

// Reads a complete line of text safely from the user.
void readString(char text[], int size)
{
    if (fgets(text, size, stdin) != NULL)
    {
        text[strcspn(text, "\n")] = '\0';
    }
}

// Reads a non-negative decimal value from the user.
float readNonNegativeFloat(void)
{
    float value;

    while (scanf("%f", &value) != 1 || value < 0)
    {
        while (getchar() != '\n')
        {
            /* Clear invalid input */
        }

        printf("Invalid value. Please enter a non-negative number: ");
    }

    while (getchar() != '\n')
    {
        /* Clear remaining input */
    }

    return value;
}

void addProduct(void)
{
    Product newProduct;

    if (productCount >= MAX_PRODUCTS)
    {
        printf("\nInventory is full. Cannot add another product.\n");
        return;
    }

    printf("\n========== ADD PRODUCT ==========\n");

    printf("Product ID: ");
    newProduct.id = readInteger();

    printf("Product name: ");
    readString(newProduct.name, sizeof(newProduct.name));

    printf("Category: ");
    readString(newProduct.category, sizeof(newProduct.category));

    printf("Retail price: ");
    newProduct.retailPrice = readNonNegativeFloat();

    printf("Wholesale price: ");
    newProduct.wholesalePrice = readNonNegativeFloat();

    while (newProduct.wholesalePrice > newProduct.retailPrice)
    {
        printf("Wholesale price cannot exceed retail price.\n");
        printf("Enter wholesale price again: ");
        newProduct.wholesalePrice = readNonNegativeFloat();
    }

    printf("Quantity: ");
    newProduct.quantity = readInteger();

    while (newProduct.quantity < 0)
    {
        printf("Quantity cannot be negative. Enter again: ");
        newProduct.quantity = readInteger();
    }

    printf("Reorder level: ");
    newProduct.reorderLevel = readInteger();

    while (newProduct.reorderLevel < 0)
    {
        printf("Reorder level cannot be negative. Enter again: ");
        newProduct.reorderLevel = readInteger();
    }

    products[productCount] = newProduct;
    productCount++;

    printf("\nProduct added successfully.\n");
}

// Displays every product currently stored in the inventory.
void displayProducts(void)
{
    int i;

    if (productCount == 0)
    {
        printf("\nNo products are currently available.\n");
        return;
    }

    printf("\n==================== PRODUCT INVENTORY ====================\n");

    for (i = 0; i < productCount; i++)
    {
        printf("\nID: %d\n", products[i].id);
        printf("Name: %s\n", products[i].name);
        printf("Category: %s\n", products[i].category);
        printf("Retail Price: %.2f\n", products[i].retailPrice);
        printf("Wholesale Price: %.2f\n", products[i].wholesalePrice);
        printf("Quantity: %d\n", products[i].quantity);
        printf("Reorder Level: %d\n", products[i].reorderLevel);
        printf("----------------------------------------\n");
    }

    printf("Total products: %d\n", productCount);
}

// Searches for a product using its ID or name.
void searchProduct(void)
{
    int choice;
    int id;
    int i;
    int found = 0;
    char name[50];

    if (productCount == 0)
    {
        printf("\nNo products are available to search.\n");
        return;
    }

    printf("\n========== SEARCH PRODUCT ==========\n");
    printf("1. Search by ID\n");
    printf("2. Search by Name\n");
    printf("Enter choice: ");

    choice = readInteger();

    if (choice == 1)
    {
        printf("Enter product ID: ");
        id = readInteger();

        for (i = 0; i < productCount; i++)
        {
            if (products[i].id == id)
            {
                printf("\nProduct found: %s\n", products[i].name);
                printf("Category: %s\n", products[i].category);
                printf("Retail Price: %.2f\n", products[i].retailPrice);
                printf("Wholesale Price: %.2f\n", products[i].wholesalePrice);
                printf("Quantity: %d\n", products[i].quantity);
                found = 1;
                break;
            }
        }
    }
    else if (choice == 2)
    {
        printf("Enter product name: ");
        readString(name, sizeof(name));

        for (i = 0; i < productCount; i++)
        {
            if (strcmp(products[i].name, name) == 0)
            {
                printf("\nProduct found: %s\n", products[i].name);
                printf("ID: %d\n", products[i].id);
                printf("Category: %s\n", products[i].category);
                printf("Retail Price: %.2f\n", products[i].retailPrice);
                printf("Wholesale Price: %.2f\n", products[i].wholesalePrice);
                printf("Quantity: %d\n", products[i].quantity);
                found = 1;
                break;
            }
        }
    }
    else
    {
        printf("\nInvalid search option.\n");
        return;
    }

    if (!found)
    {
        printf("\nProduct not found.\n");
    }
}

// Updates the information of an existing product.
void updateProduct(void)
{
    int id;
    int i;
    int found = 0;

    printf("\nEnter product ID to update: ");
    id = readInteger();

    for (i = 0; i < productCount; i++)
    {
        if (products[i].id == id)
        {
            printf("New product name: ");
            readString(products[i].name, sizeof(products[i].name));

            printf("New category: ");
            readString(products[i].category, sizeof(products[i].category));

            printf("New retail price: ");
            products[i].retailPrice = readNonNegativeFloat();

            printf("New wholesale price: ");
            products[i].wholesalePrice = readNonNegativeFloat();

            while (products[i].wholesalePrice > products[i].retailPrice)
            {
                printf("Wholesale price cannot exceed retail price.\n");
                printf("Enter wholesale price again: ");
                products[i].wholesalePrice = readNonNegativeFloat();
            }

            printf("New quantity: ");
            products[i].quantity = readInteger();

            while (products[i].quantity < 0)
            {
                printf("Quantity cannot be negative. Enter again: ");
                products[i].quantity = readInteger();
            }

            printf("New reorder level: ");
            products[i].reorderLevel = readInteger();

            found = 1;
            printf("\nProduct updated successfully.\n");
            break;
        }
    }

    if (!found)
    {
        printf("\nProduct ID not found.\n");
    }
}

// Deletes a product and shifts later records to fill the gap.
void deleteProduct(void)
{
    int id;
    int i;
    int found = 0;

    printf("\nEnter product ID to delete: ");
    id = readInteger();

    for (i = 0; i < productCount; i++)
    {
        if (products[i].id == id)
        {
            for (int j = i; j < productCount - 1; j++)
            {
                products[j] = products[j + 1];
            }

            productCount--;
            found = 1;

            printf("\nProduct deleted successfully.\n");
            break;
        }
    }

    if (!found)
    {
        printf("\nProduct ID not found.\n");
    }
}

// Sorts products by ID, name, price, or quantity.
void sortProducts(void)
{
    int choice;
    int i;
    int j;
    int minIndex;
    Product temp;

    if (productCount < 2)
    {
        printf("\nNot enough products to sort.\n");
        return;
    }

    printf("\n========== SORT PRODUCTS ==========\n");
    printf("1. Product ID\n");
    printf("2. Product Name\n");
    printf("3. Retail Price\n");
    printf("4. Quantity\n");
    printf("Enter choice: ");

    choice = readInteger();

    for (i = 0; i < productCount - 1; i++)
    {
        minIndex = i;

        for (j = i + 1; j < productCount; j++)
        {
            if ((choice == 1 && products[j].id < products[minIndex].id) ||
                (choice == 2 && strcmp(products[j].name, products[minIndex].name) < 0) ||
                (choice == 3 && products[j].retailPrice < products[minIndex].retailPrice) ||
                (choice == 4 && products[j].quantity < products[minIndex].quantity))
            {
                minIndex = j;
            }
        }

        temp = products[i];
        products[i] = products[minIndex];
        products[minIndex] = temp;
    }

    if (choice >= 1 && choice <= 4)
    {
        printf("\nProducts sorted successfully.\n");
    }
    else
    {
        printf("\nInvalid sorting option.\n");
    }
}

// Displays products whose stock has reached the reorder level.
void lowStockReport(void)
{
    int i;
    int found = 0;

    printf("\n========== LOW STOCK REPORT ==========\n");

    for (i = 0; i < productCount; i++)
    {
        if (products[i].quantity <= products[i].reorderLevel)
        {
            printf("ID: %d | %s | Quantity: %d | Reorder Level: %d\n",
                   products[i].id,
                   products[i].name,
                   products[i].quantity,
                   products[i].reorderLevel);

            found = 1;
        }
    }

    if (!found)
    {
        printf("No products currently require restocking.\n");
    }
}

// Calculates the total retail value of all inventory.
void inventoryValueReport(void)
{
    int i;
    float total = 0.0f;

    for (i = 0; i < productCount; i++)
    {
        total += products[i].retailPrice * products[i].quantity;
    }

    printf("\n========== INVENTORY VALUE ==========\n");
    printf("Total inventory value: %.2f\n", total);
}

void inventoryManagement(void)
{
    int choice;

    do
    {
        printf("\n");
        printf("========================================\n");
        printf("         INVENTORY MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add Product\n");
        printf("2. Display Products\n");
        printf("3. Search Product\n");
        printf("4. Update Product\n");
        printf("5. Delete Product\n");
        printf("6. Sort Products\n");
        printf("7. Low Stock Report\n");
        printf("8. Inventory Value\n");
        printf("9. Back\n");
        printf("----------------------------------------\n");
        printf("Enter your choice: ");

        choice = readInteger();

        switch (choice)
        {
            case 1:
                addProduct();
                break;

            case 2:
                displayProducts();
                break;

            case 3:
                searchProduct();
                break;

            case 4:
                updateProduct();
                break;

            case 5:
                deleteProduct();
                break;

            case 6:
                sortProducts();
                break;

            case 7:
                lowStockReport();
                break;

            case 8:
                inventoryValueReport();
                break;

            case 9:
                printf("\nReturning to previous menu...\n");
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }

    } while (choice != 9);
}

void loadSampleProducts(void)
{
    Product sampleProducts[] =
    {
        {101, "Miniket Rice 5kg", "Groceries", 680.0f, 620.0f, 25, 10},
        {102, "Fresh Milk 1L", "Dairy", 100.0f, 90.0f, 15, 10},
        {103, "Coca Cola 2L", "Beverages", 180.0f, 165.0f, 30, 10},
        {104, "Shampoo 400ml", "Personal Care", 450.0f, 400.0f, 12, 5},
        {105, "Dishwashing Liquid", "Cleaning", 220.0f, 195.0f, 8, 10},
        {106, "Ballpoint Pen Pack", "Stationery", 120.0f, 100.0f, 20, 5},
        {107, "Frying Pan", "Kitchen", 850.0f, 760.0f, 7, 5},
        {108, "Baby Diapers Pack", "Baby Care", 1250.0f, 1120.0f, 9, 5}
    };

    int sampleCount = sizeof(sampleProducts) / sizeof(sampleProducts[0]);

    for (int i = 0; i < sampleCount; i++)
    {
        products[i] = sampleProducts[i];
    }

    productCount = sampleCount;
}