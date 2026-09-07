#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_PRODUCTS 200
#define MAX_USERS 20
#define MAX_TRANSACTIONS 1000
#define MAX_ITEMS 20

#define NAME_SIZE 50
#define CATEGORY_SIZE 30
#define USERNAME_SIZE 30
#define PASSWORD_SIZE 30
#define DATE_SIZE 11
#define INPUT_SIZE 100
#define LINE_SIZE 300

#define ROLE_EMPLOYEE 1
#define ROLE_MANAGER 2

#define CUSTOMER_REGULAR 1
#define CUSTOMER_WHOLESALE 2
#define WHOLESALE_DISCOUNT 0.10f

#define PRODUCTS_FILE "products.txt"
#define USERS_FILE "users.txt"
#define TRANSACTIONS_FILE "transactions.txt"

typedef struct
{
    int id;
    char name[NAME_SIZE];
    char category[CATEGORY_SIZE];
    float retailPrice;
    float wholesalePrice;
    int quantity;
    int reorderLevel;
} Product;

typedef struct
{
    int id;
    char name[NAME_SIZE];
    char username[USERNAME_SIZE];
    char password[PASSWORD_SIZE];
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
    char date[DATE_SIZE];
    int customerType;
    int employeeId;
    TransactionItem items[MAX_ITEMS];
    int itemCount;
    float subtotal;
    float discount;
    float total;
} Transaction;

Product products[MAX_PRODUCTS];
User users[MAX_USERS];
Transaction transactions[MAX_TRANSACTIONS];

int productCount = 0;
int userCount = 0;
int transactionCount = 0;

int readInteger(void);
float readNonNegativeFloat(void);
void readString(char text[], int size);
void clearInputLine(void);

void displayWelcomeScreen(void);
void showMainMenu(void);
int findProductById(int id);
void staffLogin(void);
void staffMenu(int userIndex);

void inventoryManagement(int role);
void readProductFields(Product *product);
void addProduct(void);
void displayProducts(void);
void printProduct(Product product);
void searchProduct(void);
void updateProduct(void);
void deleteProduct(void);
void sortProducts(void);
int comesBefore(Product first, Product second, int choice);
void lowStockReport(void);
void inventoryValueReport(void);

void startTransaction(int employeeId);
int selectCustomerType(void);
void addTransactionItem(Transaction *transaction);
void viewTransaction(Transaction *transaction);
void calculateTransactionTotal(Transaction *transaction);
void completeTransaction(Transaction *transaction);
int transactionStockAvailable(Transaction *transaction);
int confirmSale(void);
void transactionHistory(void);

void saveProducts(void);
void saveUsers(void);
void saveTransactions(void);
void loadProducts(void);
void loadUsers(void);
void loadTransactions(void);
void loadAllData(void);
void saveAllData(void);
/* Runs the UNI MART program until the user exits. */
int main(void)
{
    int choice;
    displayWelcomeScreen();
    loadAllData();
    do
    {
        showMainMenu();
        choice = readInteger();
        switch (choice)
        {
            case 1: staffLogin(); break;
            case 2: printf("\nThank you for using UNI MART!\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }
    }
    while (choice != 2);
    saveAllData();
    return 0;
}

/* Clears characters left after an oversized text input. */
void clearInputLine(void)
{
    int character;
    while ((character = getchar()) != '\n' && character != EOF)
    {
    }
}

/* Reads a valid integer from the keyboard. */
int readInteger(void)
{
    char input[INPUT_SIZE];
    char extra;
    int value;
    while (1)
    {
        if (fgets(input, sizeof(input), stdin) == NULL)
            return 0;
        if (sscanf(input, "%d %c", &value, &extra) == 1)
            return value;
        printf("Invalid input. Please enter a number: ");
    }
}

/* Reads a valid non-negative decimal value. */
float readNonNegativeFloat(void)
{
    char input[INPUT_SIZE];
    char extra;
    float value;
    while (1)
    {
        if (fgets(input, sizeof(input), stdin) == NULL)
            return 0.0f;
        if (sscanf(input, "%f %c", &value, &extra) == 1 &&
            value >= 0.0f)
            return value;
        printf("Invalid value. Enter a non-negative number: ");
    }
}

/* Reads text safely and removes the newline. */
void readString(char text[], int size)
{
    int length;
    if (fgets(text, size, stdin) == NULL)
    {
        text[0] = '\0';
        return;
    }
    length = (int)strlen(text);
    if (length > 0 && text[length - 1] == '\n')
        text[length - 1] = '\0';
    else
        clearInputLine();
}

/* Displays the UNI MART welcome banner. */
void displayWelcomeScreen(void)
{
    printf("\n==================================================\n");
    printf("                    UNI MART\n");
    printf("             SUPERMARKET MANAGEMENT\n");
    printf("                     SYSTEM\n");
    printf("==================================================\n");
}

/* Displays the main menu. */
void showMainMenu(void)
{
    printf("\n================ MAIN MENU ================\n");
    printf("1. Staff Login\n");
    printf("2. Exit\n");
    printf("-------------------------------------------\n");
    printf("Enter choice: ");
}

/* Finds a product by ID and returns its index. */
int findProductById(int id)
{
    int i;
    for (i = 0; i < productCount; i++)
        if (products[i].id == id)
            return i;
    return -1;
}

/* Handles staff authentication. */
void staffLogin(void)
{
    char username[USERNAME_SIZE];
    char password[PASSWORD_SIZE];
    int userIndex;
    printf("\n=============== STAFF LOGIN ===============\n");
    printf("Username: ");
    readString(username, sizeof(username));
    printf("Password: ");
    readString(password, sizeof(password));
    userIndex = -1;
    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0)
        {
            userIndex = i;
            break;
        }
    }

    if (userIndex == -1)
    {
        printf("Invalid username or password.\n");
        return;
    }

    printf("Login successful. Welcome, %s!\n", users[userIndex].name);
    staffMenu(userIndex);
}

/* Displays features available to the logged-in staff member. */
void staffMenu(int userIndex)
{
    int choice;
    int manager = users[userIndex].role == ROLE_MANAGER;
    do
    {
        printf("\n================ STAFF MENU ================\n");
        printf("Logged in: %s (%s)\n", users[userIndex].name, manager ? "Manager" : "Employee");
        printf("1. New Transaction\n2. View Products\n3. Search Product\n4. Inventory Management\n5. Low Stock Report\n");
        if (manager) printf("6. Inventory Value\n7. Transaction History\n8. Logout\n");
        else printf("6. Logout\n");
        printf("Enter choice: ");
        choice = readInteger();
        switch (choice)
        {
            case 1: startTransaction(users[userIndex].id); break;
            case 2: displayProducts(); break;
            case 3: searchProduct(); break;
            case 4: inventoryManagement(users[userIndex].role); break;
            case 5: lowStockReport(); break;
            case 6:
                if (manager) inventoryValueReport();
                else printf("Logging out...\n");
                break;
            case 7:
                if (manager) transactionHistory();
                else printf("Invalid choice.\n");
                break;
            case 8:
                if (manager) printf("Logging out...\n");
                else printf("Invalid choice.\n");
                break;
            default: printf("Invalid choice.\n");
        }
    }
    while ((manager && choice != 8) || (!manager && choice != 6));
}

/* Displays inventory management operations. */
void inventoryManagement(int role)
{
    int choice;
    int manager = role == ROLE_MANAGER;
    do
    {
        printf("\n============ INVENTORY MANAGEMENT ============\n");
        printf("1. Add Product\n2. Display Products\n3. Search Product\n4. Update Product\n");
        printf("5. Delete Product\n6. Sort Products\n7. Low Stock Report\n");
        if (manager) printf("8. Inventory Value\n9. Back\n");
        else printf("8. Back\n");
        printf("Enter choice: ");
        choice = readInteger();
        switch (choice)
        {
            case 1: addProduct(); break;
            case 2: displayProducts(); break;
            case 3: searchProduct(); break;
            case 4: updateProduct(); break;
            case 5: deleteProduct(); break;
            case 6: sortProducts(); break;
            case 7: lowStockReport(); break;
            case 8: if (manager) inventoryValueReport(); break;
            case 9: if (!manager) printf("Invalid choice.\n"); break;
            default: printf("Invalid choice.\n");
        }
    }
    while ((manager && choice != 9) || (!manager && choice != 8));
}

/* Reads the editable fields of a product from the user. */
void readProductFields(Product *product)
{
    printf("Product name: ");
    readString(product->name, sizeof(product->name));
    printf("Category: ");
    readString(product->category, sizeof(product->category));
    printf("Retail price: ");
    product->retailPrice = readNonNegativeFloat();
    printf("Wholesale price: ");
    product->wholesalePrice = readNonNegativeFloat();
    while (product->wholesalePrice > product->retailPrice)
    {
        printf("Wholesale price cannot exceed retail price.\n");
        printf("Enter wholesale price again: ");
        product->wholesalePrice = readNonNegativeFloat();
    }

    printf("Quantity: ");
    product->quantity = readInteger();
    while (product->quantity < 0)
    {
        printf("Quantity cannot be negative. Enter again: ");
        product->quantity = readInteger();
    }

    printf("Reorder level: ");
    product->reorderLevel = readInteger();
    while (product->reorderLevel < 0)
    {
        printf("Reorder level cannot be negative. Enter again: ");
        product->reorderLevel = readInteger();
    }
}

/* Adds a product to the inventory. */
void addProduct(void)
{
    Product product;
    if (productCount >= MAX_PRODUCTS)
    {
        printf("Inventory is full.\n");
        return;
    }

    printf("\n=============== ADD PRODUCT ===============\n");
    printf("Product ID: ");
    product.id = readInteger();
    if (product.id <= 0 || findProductById(product.id) != -1)
    {
        printf("Invalid or duplicate product ID.\n");
        return;
    }
    readProductFields(&product);
    products[productCount++] = product;
    saveProducts();
    printf("Product added successfully.\n");
}

/* Displays all products in the inventory. */
void displayProducts(void)
{
    int i;
    if (productCount == 0)
    {
        printf("\nNo products available.\n");
        return;
    }

    printf("\n================ PRODUCT LIST ================\n");
    printf("%-5s %-24s %-16s %-10s %-10s %-7s\n",
           "ID", "Name", "Category", "Retail", "Wholesale", "Stock");
    for (i = 0; i < productCount; i++)
        printf("%-5d %-24s %-16s %-10.2f %-10.2f %-7d\n",
               products[i].id, products[i].name, products[i].category,
               products[i].retailPrice, products[i].wholesalePrice,
               products[i].quantity);
}

/* Prints one product's complete details. */
void printProduct(Product product)
{
    printf("\nID: %d\n", product.id);
    printf("Name: %s\n", product.name);
    printf("Category: %s\n", product.category);
    printf("Retail price: %.2f\n", product.retailPrice);
    printf("Wholesale price: %.2f\n", product.wholesalePrice);
    printf("Stock: %d\n", product.quantity);
    printf("Reorder level: %d\n", product.reorderLevel);
}

/* Searches for a product by ID or name. */
void searchProduct(void)
{
    int choice, id, index, i;
    char name[NAME_SIZE];
    if (productCount == 0)
    {
        printf("No products available.\n");
        return;
    }
    printf("\n=============== SEARCH PRODUCT ===============\n1. Search by ID\n2. Search by Name\n");
    printf("Enter choice: ");
    choice = readInteger();
    if (choice == 1)
    {
        printf("Enter product ID: ");
        id = readInteger();
        index = findProductById(id);
        if (index == -1) printf("Product not found.\n");
        else printProduct(products[index]);
        return;
    }
    if (choice == 2)
    {
        printf("Enter product name: ");
        readString(name, sizeof(name));
        for (i = 0; i < productCount; i++)
        {
            if (strcmp(products[i].name, name) == 0)
            {
                printProduct(products[i]);
                return;
            }
        }
        printf("Product not found.\n");
        return;
    }
    printf("Invalid search option.\n");
}
/* Updates an existing product. */
void updateProduct(void)
{
    int id;
    int index;
    printf("\nEnter product ID to update: ");
    id = readInteger();
    index = findProductById(id);
    if (index == -1)
    {
        printf("Product not found.\n");
        return;
    }
    readProductFields(&products[index]);
    saveProducts();
    printf("Product updated successfully.\n");
}

/* Deletes a product from the inventory. */
void deleteProduct(void)
{
    int id;
    int index;
    int i;
    printf("\nEnter product ID to delete: ");
    id = readInteger();
    index = findProductById(id);
    if (index == -1)
    {
        printf("Product not found.\n");
        return;
    }

    for (i = index; i < productCount - 1; i++)
        products[i] = products[i + 1];
    productCount--;
    saveProducts();
    printf("Product deleted successfully.\n");
}

/* Compares two products for the selected sort field. */
int comesBefore(Product first, Product second, int choice)
{
    if (choice == 1)
        return first.id < second.id;
    if (choice == 2)
        return strcmp(first.name, second.name) < 0;
    if (choice == 3)
        return first.retailPrice < second.retailPrice;
    return first.quantity < second.quantity;
}

/* Sorts the product array using selection sort. */
void sortProducts(void)
{
    int choice;
    int i;
    int j;
    int selected;
    Product temp;
    if (productCount < 2)
    {
        printf("Not enough products to sort.\n");
        return;
    }

    printf("\n================ SORT PRODUCTS ================\n");
    printf("1. Product ID\n2. Product Name\n");
    printf("3. Retail Price\n4. Quantity\n");
    printf("Enter choice: ");
    choice = readInteger();
    if (choice < 1 || choice > 4)
    {
        printf("Invalid sorting option.\n");
        return;
    }

    for (i = 0; i < productCount - 1; i++)
    {
        selected = i;
        for (j = i + 1; j < productCount; j++)
            if (comesBefore(products[j], products[selected], choice))
                selected = j;
        temp = products[i];
        products[i] = products[selected];
        products[selected] = temp;
    }
    saveProducts();
    printf("Products sorted successfully.\n");
}

/* Displays products that are at or below reorder level. */
void lowStockReport(void)
{
    int i;
    int found = 0;
    printf("\n=============== LOW STOCK REPORT ===============\n");
    for (i = 0; i < productCount; i++)
    {
        if (products[i].quantity <= products[i].reorderLevel)
        {
            printf("ID: %d | %s | Stock: %d | Reorder: %d\n",
                   products[i].id, products[i].name,
                   products[i].quantity, products[i].reorderLevel);
            found = 1;
        }
    }

    if (!found)
        printf("No products currently require restocking.\n");
}

/* Calculates and displays the total inventory value. */
void inventoryValueReport(void)
{
    int i;
    float total = 0.0f;
    for (i = 0; i < productCount; i++)
        total += products[i].retailPrice * products[i].quantity;
    printf("\n=============== INVENTORY VALUE ===============\n");
    printf("Total inventory value: %.2f\n", total);
}

/* Starts a new customer sale. */
void startTransaction(int employeeId)
{
    Transaction transaction = {0};
    int choice;
    transaction.transactionId = transactionCount + 1;
    transaction.employeeId = employeeId;
    transaction.customerType = selectCustomerType();
    time_t currentTime = time(NULL);
    struct tm *localTime = localtime(&currentTime);
    if (localTime != NULL)
        strftime(transaction.date, DATE_SIZE, "%Y-%m-%d", localTime);
    do
    {
        printf("\n================ NEW SALE ================\n");
        printf("1. Add Product\n2. View Sale\n");
        printf("3. Complete Sale\n4. Cancel\n");
        printf("Enter choice: ");
        choice = readInteger();
        switch (choice)
        {
            case 1: addTransactionItem(&transaction); break;
            case 2: viewTransaction(&transaction); break;
            case 3: completeTransaction(&transaction); return;
            case 4: printf("Sale cancelled.\n"); return;
            default: printf("Invalid choice.\n");
        }
    }
    while (choice != 4);
}

/* Gets and validates the customer type for a sale. */
int selectCustomerType(void)
{
    int choice;
    printf("\n1. Regular Customer\n2. Wholesale Customer\n");
    printf("Enter choice: ");
    choice = readInteger();
    while (choice != CUSTOMER_REGULAR &&
           choice != CUSTOMER_WHOLESALE)
    {
        printf("Invalid choice. Enter 1 or 2: ");
        choice = readInteger();
    }
    return choice;
}

/* Adds one product line to the current sale. */
void addTransactionItem(Transaction *transaction)
{
    int id, quantity, index;
    float price;
    if (transaction->itemCount >= MAX_ITEMS)
    {
        printf("Maximum items reached.\n");
        return;
    }
    printf("Enter product ID: ");
    id = readInteger();
    index = findProductById(id);
    if (index == -1)
    {
        printf("Product not found.\n");
        return;
    }
    for (int i = 0; i < transaction->itemCount; i++)
        if (transaction->items[i].productId == id)
        {
            printf("Product already added to this sale.\n");
            return;
        }
    printf("Product: %s\nStock: %d\n", products[index].name, products[index].quantity);
    printf("Quantity: ");
    quantity = readInteger();
    if (quantity <= 0 || quantity > products[index].quantity)
    {
        printf("Invalid quantity or insufficient stock.\n");
        return;
    }
    price = products[index].retailPrice;
    if (transaction->customerType == CUSTOMER_WHOLESALE)
        price = products[index].wholesalePrice;
    transaction->items[transaction->itemCount++] =
        (TransactionItem){id, quantity, price, quantity * price};
    printf("Product added to sale.\n");
}

/* Displays the current sale and its calculated total. */
void viewTransaction(Transaction *transaction)
{
    int i;
    int index;
    if (transaction->itemCount == 0)
    {
        printf("\nNo products in this sale.\n");
        return;
    }

    printf("\n=============== CURRENT SALE ===============\n");
    for (i = 0; i < transaction->itemCount; i++)
    {
        index = findProductById(transaction->items[i].productId);
        if (index != -1)
            printf("%d. %s x%d = %.2f\n",
                   transaction->items[i].productId,
                   products[index].name,
                   transaction->items[i].quantity,
                   transaction->items[i].subtotal);
    }
    calculateTransactionTotal(transaction);
    printf("Subtotal: %.2f\n", transaction->subtotal);
    printf("Discount: %.2f\n", transaction->discount);
    printf("Total: %.2f\n", transaction->total);
}

/* Calculates subtotal, wholesale discount, and total. */
void calculateTransactionTotal(Transaction *transaction)
{
    int i;
    transaction->subtotal = 0.0f;
    for (i = 0; i < transaction->itemCount; i++)
        transaction->subtotal += transaction->items[i].subtotal;
    if (transaction->customerType == CUSTOMER_WHOLESALE)
        transaction->discount =
            transaction->subtotal * WHOLESALE_DISCOUNT;
    else
        transaction->discount = 0.0f;
    transaction->total =
        transaction->subtotal - transaction->discount;
}

/* Checks that all items still have enough stock to complete a sale. */
int transactionStockAvailable(Transaction *transaction)
{
    for (int i = 0; i < transaction->itemCount; i++)
    {
        int index = findProductById(transaction->items[i].productId);
        if (index == -1 || transaction->items[i].quantity > products[index].quantity)
            return 0;
    }
    return 1;
}

/* Gets a valid yes-or-no confirmation for a sale. */
int confirmSale(void)
{
    int choice;
    do
    {
        printf("\nConfirm sale? (1 = Yes, 2 = No): ");
        choice = readInteger();
        if (choice != 1 && choice != 2) printf("Invalid choice. Enter 1 or 2.\n");
    }
    while (choice != 1 && choice != 2);
    return choice == 1;
}

/* Confirms a sale, updates stock, and records the transaction. */
void completeTransaction(Transaction *transaction)
{
    if (transaction->itemCount == 0)
    {
        printf("Cannot complete an empty sale.\n");
        return;
    }
    viewTransaction(transaction);
    if (!confirmSale())
    {
        printf("Sale cancelled. Stock was not changed.\n");
        return;
    }
    if (transactionCount >= MAX_TRANSACTIONS)
    {
        printf("Transaction storage is full.\n");
        return;
    }
    if (!transactionStockAvailable(transaction))
    {
        printf("Stock changed. Sale could not be completed.\n");
        return;
    }
    for (int i = 0; i < transaction->itemCount; i++)
    {
        int index = findProductById(transaction->items[i].productId);
        products[index].quantity -= transaction->items[i].quantity;
    }
    transactions[transactionCount++] = *transaction;
    saveProducts();
    saveTransactions();
    printf("Sale completed successfully.\nTransaction ID: %d\n", transaction->transactionId);
}

/* Displays saved transaction history for the manager. */
void transactionHistory(void)
{
    if (transactionCount == 0)
    {
        printf("\nNo transaction history available.\n");
        return;
    }
    printf("\n=============== TRANSACTION HISTORY ===============\n");
    for (int i = 0; i < transactionCount; i++)
        printf("ID: %d | Date: %s | %s | Employee: %d | Total: %.2f\n",
               transactions[i].transactionId, transactions[i].date,
               transactions[i].customerType == CUSTOMER_WHOLESALE ? "Wholesale" : "Regular",
               transactions[i].employeeId, transactions[i].total);
}

/* Saves product records to the product file. */
void saveProducts(void)
{
    FILE *file;
    int i;
    file = fopen(PRODUCTS_FILE, "w");
    if (file == NULL)
    {
        printf("Could not save product data.\n");
        return;
    }
    for (i = 0; i < productCount; i++)
        fprintf(file, "%d|%s|%s|%.2f|%.2f|%d|%d\n",
                products[i].id, products[i].name, products[i].category,
                products[i].retailPrice, products[i].wholesalePrice,
                products[i].quantity, products[i].reorderLevel);
    fclose(file);
}
/* Saves staff records to the user file. */
void saveUsers(void)
{
    FILE *file;
    int i;
    file = fopen(USERS_FILE, "w");
    if (file == NULL)
    {
        printf("Could not save staff data.\n");
        return;
    }
    for (i = 0; i < userCount; i++)
        fprintf(file, "%d|%s|%s|%s|%d\n",
                users[i].id, users[i].name,
                users[i].username, users[i].password,
                users[i].role);
    fclose(file);
}
/* Saves transactions and their item records. */
void saveTransactions(void)
{
    FILE *file;
    int i;
    int j;
    file = fopen(TRANSACTIONS_FILE, "w");
    if (file == NULL)
    {
        printf("Could not save transaction data.\n");
        return;
    }

    for (i = 0; i < transactionCount; i++)
    {
        fprintf(file, "T|%d|%s|%d|%d|%.2f|%.2f|%.2f|%d\n",
                transactions[i].transactionId,
                transactions[i].date,
                transactions[i].customerType,
                transactions[i].employeeId,
                transactions[i].subtotal,
                transactions[i].discount,
                transactions[i].total,
                transactions[i].itemCount);
        for (j = 0; j < transactions[i].itemCount; j++)
            fprintf(file, "I|%d|%d|%.2f|%.2f\n",
                    transactions[i].items[j].productId,
                    transactions[i].items[j].quantity,
                    transactions[i].items[j].unitPrice,
                    transactions[i].items[j].subtotal);
    }
    fclose(file);
}

/* Loads product records from the product file. */
void loadProducts(void)
{
    FILE *file;
    char line[LINE_SIZE];
    Product product;
    file = fopen(PRODUCTS_FILE, "r");
    if (file == NULL)
    {
        printf("Product file not found. Starting empty.\n");
        return;
    }
    while (productCount < MAX_PRODUCTS &&
           fgets(line, sizeof(line), file) != NULL)
    {
        if (sscanf(line, "%d|%49[^|]|%29[^|]|%f|%f|%d|%d",
                   &product.id, product.name, product.category,
                   &product.retailPrice, &product.wholesalePrice,
                   &product.quantity, &product.reorderLevel) == 7)
            products[productCount++] = product;
    }
    fclose(file);
}

/* Loads staff records from the user file. */
void loadUsers(void)
{
    FILE *file;
    char line[LINE_SIZE];
    User user;
    file = fopen(USERS_FILE, "r");
    if (file == NULL)
    {
        printf("Staff file not found. Starting empty.\n");
        return;
    }
    while (userCount < MAX_USERS &&
           fgets(line, sizeof(line), file) != NULL)
    {
        if (sscanf(line, "%d|%49[^|]|%29[^|]|%29[^|]|%d",
                   &user.id, user.name, user.username,
                   user.password, &user.role) == 5)
            users[userCount++] = user;
    }
    fclose(file);
}

/* Loads transactions and their item records. */
void loadTransactions(void)
{
    FILE *file;
    char line[LINE_SIZE];
    Transaction transaction;
    TransactionItem item;
    int i;
    file = fopen(TRANSACTIONS_FILE, "r");
    if (file == NULL)
    {
        printf("Transaction file not found. Starting empty.\n");
        return;
    }
    while (transactionCount < MAX_TRANSACTIONS && fgets(line, sizeof(line), file) != NULL)
    {
        if (sscanf(line, "T|%d|%10[^|]|%d|%d|%f|%f|%f|%d",
                   &transaction.transactionId, transaction.date,
                   &transaction.customerType, &transaction.employeeId,
                   &transaction.subtotal, &transaction.discount,
                   &transaction.total, &transaction.itemCount) != 8)
            continue;
        if (transaction.transactionId <= 0 ||
            (transaction.customerType != CUSTOMER_REGULAR && transaction.customerType != CUSTOMER_WHOLESALE) || transaction.itemCount < 0 || transaction.itemCount > MAX_ITEMS)
            continue;
        for (i = 0; i < transaction.itemCount; i++)
        {
            if (fgets(line, sizeof(line), file) == NULL ||
                sscanf(line, "I|%d|%d|%f|%f", &item.productId, &item.quantity,
                       &item.unitPrice, &item.subtotal) != 4 ||
                item.productId <= 0 || item.quantity <= 0 || item.unitPrice < 0.0f)
                break;
            transaction.items[i] = item;
        }
        if (i == transaction.itemCount)
            transactions[transactionCount++] = transaction;
    }
    fclose(file);
}

/* Loads all saved data at program startup. */
void loadAllData(void)
{
    loadProducts();
    loadUsers();
    loadTransactions();
    printf("\nLoaded %d products.\n", productCount);
    printf("Loaded %d staff members.\n", userCount);
    printf("Loaded %d transactions.\n", transactionCount);
}

/* Saves all data before the program exits. */
void saveAllData(void)
{
    saveProducts();
    saveUsers();
    saveTransactions();
}

