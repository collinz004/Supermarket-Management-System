#include <stdio.h>
#include <string.h>
#include <time.h>

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

#define ORDER_PENDING 1
#define ORDER_CONFIRMED 2
#define ORDER_PREPARING 3
#define ORDER_OUT_FOR_DELIVERY 4
#define ORDER_DELIVERED 5
#define ORDER_CANCELLED 6

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

int findProductById(int id);
void addToCart(Transaction *cart);
void viewCart(Transaction *cart);
void onlineCheckout(Transaction *cart);

void calculateTransactionTotal(Transaction *transaction);
void saveTransaction(Transaction *transaction);

void loadSampleUsers(void);

int authenticateUser(char username[], char password[]);
void staffMenu(int userIndex);
void viewOrders(void);
void updateOrderStatus(void);

void startInStoreSale(void);
void addItemToTransaction(Transaction *sale);
void completeInStoreSale(Transaction *sale);

int main(void)
{
    int choice;

    displayWelcomeScreen();
    loadSampleProducts();
    loadSampleUsers();

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

int findProductById(int id)
{
    for (int i = 0; i < productCount; i++)
    {
        if (products[i].id == id)
        {
            return i;
        }
    }

    return -1;
}

void onlineShopping(void)
{
    Transaction cart = {0};
    int choice;

    cart.type = TYPE_ONLINE;
    cart.customerType = CUSTOMER_REGULAR;
    cart.itemCount = 0;

    do
    {
        printf("\n========== ONLINE SHOPPING ==========\n");
        printf("1. Browse Products\n");
        printf("2. Search Product\n");
        printf("3. Add Product to Cart\n");
        printf("4. View Cart\n");
        printf("5. Checkout\n");
        printf("6. Back\n");
        printf("=====================================\n");

        choice = readInteger();

        switch (choice)
        {
            case 1:
                displayProducts();
                break;

            case 2:
                searchProduct();
                break;

            case 3:
                addToCart(&cart);
                break;

            case 4:
                viewCart(&cart);
                break;

            case 5:
                onlineCheckout(&cart);
                break;

            case 6:
                printf("Returning to main menu...\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 6);
}

void addToCart(Transaction *cart)
{
    int id;
    int quantity;
    int index;

    if (cart->itemCount >= MAX_ITEMS_PER_TRANSACTION)
    {
        printf("Cart is full.\n");
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

    printf("Product: %s\n", products[index].name);
    printf("Available stock: %d\n", products[index].quantity);

    printf("Enter quantity: ");
    quantity = readInteger();

    if (quantity <= 0)
    {
        printf("Quantity must be greater than zero.\n");
        return;
    }

    if (quantity > products[index].quantity)
    {
        printf("Insufficient stock.\n");
        return;
    }

    cart->items[cart->itemCount].productId = id;
    cart->items[cart->itemCount].quantity = quantity;
    cart->items[cart->itemCount].unitPrice = products[index].retailPrice;
    cart->items[cart->itemCount].subtotal =
        quantity * products[index].retailPrice;

    cart->itemCount++;

    printf("%s added to cart.\n", products[index].name);
}

void viewCart(Transaction *cart)
{
    float total = 0.0f;

    if (cart->itemCount == 0)
    {
        printf("\nYour cart is empty.\n");
        return;
    }

    printf("\n=============== CART ===============\n");
    printf("%-8s %-25s %-8s %-12s\n",
           "ID", "Product", "Qty", "Subtotal");

    for (int i = 0; i < cart->itemCount; i++)
    {
        int index = findProductById(cart->items[i].productId);

        if (index != -1)
        {
            printf("%-8d %-25s %-8d %-12.2f\n",
                   products[index].id,
                   products[index].name,
                   cart->items[i].quantity,
                   cart->items[i].subtotal);

            total += cart->items[i].subtotal;
        }
    }

    printf("------------------------------------\n");
    printf("Cart Total: %.2f\n", total);
}

void onlineCheckout(Transaction *cart)
{
    Transaction order = {0};
    char address[100];
    int customerType;

    if (cart->itemCount == 0)
    {
        printf("\nYour cart is empty. Add products first.\n");
        return;
    }

    printf("\n============== CHECKOUT ==============\n");

    viewCart(cart);

    printf("\nCustomer Type:\n");
    printf("1. Regular Customer\n");
    printf("2. Wholesale Customer\n");
    printf("Enter choice: ");
    customerType = readInteger();

    if (customerType != CUSTOMER_REGULAR &&
        customerType != CUSTOMER_WHOLESALE)
    {
        printf("Invalid customer type.\n");
        return;
    }

    printf("Enter delivery address: ");
    readString(address, sizeof(address));

    order.type = TYPE_ONLINE;
    order.customerType = customerType;
    order.itemCount = cart->itemCount;
    order.deliveryCharge = 60.0f;
    order.status = ORDER_PENDING;

    strcpy(order.deliveryAddress, address);

    for (int i = 0; i < cart->itemCount; i++)
    {
        order.items[i] = cart->items[i];
    }

    calculateTransactionTotal(&order);

    printf("\n============= ORDER SUMMARY =============\n");
    printf("Subtotal:        %.2f\n", order.subtotal);
    printf("Discount:       -%.2f\n", order.discount);
    printf("Delivery Charge:  %.2f\n", order.deliveryCharge);
    printf("------------------------------------------\n");
    printf("Total:           %.2f\n", order.total);

    printf("\nConfirm order? (1 = Yes, 2 = No): ");
    
    if (readInteger() != 1)
    {
        printf("Order cancelled.\n");
        return;
    }

    /*
     * Deduct inventory only after successful confirmation.
     */
    for (int i = 0; i < order.itemCount; i++)
    {
        int index = findProductById(order.items[i].productId);

        if (index != -1)
        {
            products[index].quantity -= order.items[i].quantity;
        }
    }

    time_t currentTime = time(NULL);
    struct tm *localTime = localtime(&currentTime);

    if (localTime != NULL)
    {
        strftime(order.date, sizeof(order.date),
                 "%Y-%m-%d", localTime);
    }

    saveTransaction(&order);

    cart->itemCount = 0;
}

void calculateTransactionTotal(Transaction *transaction)
{
    transaction->subtotal = 0.0f;

    for (int i = 0; i < transaction->itemCount; i++)
    {
        transaction->subtotal += transaction->items[i].subtotal;
    }

    if (transaction->customerType == CUSTOMER_WHOLESALE)
    {
        transaction->discount = transaction->subtotal * 0.10f;
    }
    else
    {
        transaction->discount = 0.0f;
    }

    transaction->total =
        transaction->subtotal
        - transaction->discount
        + transaction->deliveryCharge;
}

void saveTransaction(Transaction *transaction)
{
    if (transactionCount >= MAX_TRANSACTIONS)
    {
        printf("Transaction storage is full.\n");
        return;
    }

    transaction->transactionId = transactionCount + 1;

    transactions[transactionCount] = *transaction;
    transactionCount++;

    if (transaction->type == TYPE_ONLINE)
{
    printf("\nOrder placed successfully!\n");
    printf("Order ID: %d\n", transaction->transactionId);
}
else
{
    printf("\nSale recorded successfully!\n");
    printf("Transaction ID: %d\n", transaction->transactionId);
}
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
                startInStoreSale();
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

void loadSampleUsers(void)
{
    User sampleUsers[] =
    {
        {1, "Rahim Ahmed", "rahim", "1234", ROLE_EMPLOYEE},
        {2, "Karim Hasan", "karim", "1234", ROLE_EMPLOYEE},
        {3, "Manager", "manager", "admin123", ROLE_MANAGER}
    };

    int sampleCount = sizeof(sampleUsers) / sizeof(sampleUsers[0]);

    for (int i = 0; i < sampleCount; i++)
    {
        users[i] = sampleUsers[i];
    }

    userCount = sampleCount;
}

int authenticateUser(char username[], char password[])
{
    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0)
        {
            return i;
        }
    }

    return -1;
}

void staffLogin(void)
{
    char username[30];
    char password[30];
    int userIndex;

    printf("\n============== STAFF LOGIN ==============\n");

    printf("Username: ");
    readString(username, sizeof(username));

    printf("Password: ");
    readString(password, sizeof(password));

    userIndex = authenticateUser(username, password);

    if (userIndex == -1)
    {
        printf("\nInvalid username or password.\n");
        return;
    }

    printf("\nLogin successful. Welcome, %s!\n",
           users[userIndex].name);

    staffMenu(userIndex);
}

void staffMenu(int userIndex)
{
    int choice;

    do
    {
        printf("\n============= STAFF MENU =============\n");
        printf("Logged in as: %s\n", users[userIndex].name);
        printf("Role: %s\n",
               users[userIndex].role == ROLE_MANAGER
               ? "Manager" : "Employee");

        printf("\n1. View Products\n");
        printf("2. Search Product\n");
        printf("3. View Online Orders\n");
        printf("4. Update Order Status\n");
        printf("5. Inventory Management\n");

        if (users[userIndex].role == ROLE_MANAGER)
        {
            printf("6. Reports\n");
            printf("7. Logout\n");
        }
        else
        {
            printf("6. Logout\n");
        }

        printf("Enter choice: ");
        choice = readInteger();

        if (users[userIndex].role == ROLE_MANAGER)
        {
            switch (choice)
            {
                case 1:
                    displayProducts();
                    break;

                case 2:
                    searchProduct();
                    break;

                case 3:
                    viewOrders();
                    break;

                case 4:
                    updateOrderStatus();
                    break;

                case 5:
                    inventoryManagement();
                    break;

                case 6:
                    printf("\nReports will be available soon.\n");
                    break;

                case 7:
                    printf("Logging out...\n");
                    break;

                default:
                    printf("Invalid choice.\n");
            }
        }
        else
        {
            switch (choice)
            {
                case 1:
                    displayProducts();
                    break;

                case 2:
                    searchProduct();
                    break;

                case 3:
                    viewOrders();
                    break;

                case 4:
                    updateOrderStatus();
                    break;

                case 5:
                    inventoryManagement();
                    break;

                case 6:
                    printf("Logging out...\n");
                    break;

                default:
                    printf("Invalid choice.\n");
            }
        }

    } while ((users[userIndex].role == ROLE_MANAGER && choice != 7) ||
             (users[userIndex].role == ROLE_EMPLOYEE && choice != 6));
}

void viewOrders(void)
{
    if (transactionCount == 0)
    {
        printf("\nNo orders have been placed yet.\n");
        return;
    }

    printf("\n================ ONLINE ORDERS ================\n");

    for (int i = 0; i < transactionCount; i++)
    {
        if (transactions[i].type == TYPE_ONLINE)
        {
            printf("\nOrder ID: %d\n",
                   transactions[i].transactionId);

            printf("Date: %s\n",
                   transactions[i].date);

            printf("Customer Type: %s\n",
                   transactions[i].customerType == CUSTOMER_WHOLESALE
                   ? "Wholesale" : "Regular");

            printf("Total: %.2f\n",
                   transactions[i].total);

            printf("Address: %s\n",
                   transactions[i].deliveryAddress);

            printf("Status: ");

            switch (transactions[i].status)
            {
                case ORDER_PENDING:
                    printf("Pending\n");
                    break;

                case ORDER_CONFIRMED:
                    printf("Confirmed\n");
                    break;

                case ORDER_PREPARING:
                    printf("Preparing\n");
                    break;

                case ORDER_OUT_FOR_DELIVERY:
                    printf("Out for Delivery\n");
                    break;

                case ORDER_DELIVERED:
                    printf("Delivered\n");
                    break;

                case ORDER_CANCELLED:
                    printf("Cancelled\n");
                    break;
            }

            printf("-----------------------------------------------\n");
        }
    }
}

void updateOrderStatus(void)
{
    int orderId;
    int status;
    int index = -1;

    printf("\nEnter Order ID: ");
    orderId = readInteger();

    for (int i = 0; i < transactionCount; i++)
    {
        if (transactions[i].transactionId == orderId &&
            transactions[i].type == TYPE_ONLINE)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        printf("Online order not found.\n");
        return;
    }

    printf("\nCurrent Status: ");

    switch (transactions[index].status)
    {
        case ORDER_PENDING:
            printf("Pending\n");
            break;

        case ORDER_CONFIRMED:
            printf("Confirmed\n");
            break;

        case ORDER_PREPARING:
            printf("Preparing\n");
            break;

        case ORDER_OUT_FOR_DELIVERY:
            printf("Out for Delivery\n");
            break;

        case ORDER_DELIVERED:
            printf("Delivered\n");
            break;

        case ORDER_CANCELLED:
            printf("Cancelled\n");
            break;
    }

    printf("\n1. Pending\n");
    printf("2. Confirmed\n");
    printf("3. Preparing\n");
    printf("4. Out for Delivery\n");
    printf("5. Delivered\n");
    printf("6. Cancelled\n");

    printf("Enter new status: ");
    status = readInteger();

    if (status < ORDER_PENDING || status > ORDER_CANCELLED)
    {
        printf("Invalid status.\n");
        return;
    }

    transactions[index].status = status;

    printf("Order status updated successfully.\n");
}

void startInStoreSale(void)
{
    Transaction sale = {0};
    int choice;

    sale.type = TYPE_IN_STORE;
    sale.customerType = CUSTOMER_REGULAR;
    sale.deliveryCharge = 0.0f;

    do
    {
        printf("\n=========== NEW SALE ===========\n");
        printf("1. Add Product\n");
        printf("2. View Current Sale\n");
        printf("3. Select Customer Type\n");
        printf("4. Complete Sale\n");
        printf("5. Cancel Sale\n");
        printf("Enter choice: ");

        choice = readInteger();

        switch (choice)
        {
            case 1:
                addItemToTransaction(&sale);
                break;

            case 2:
                viewCart(&sale);
                break;

            case 3:
                printf("\n1. Regular Customer\n");
                printf("2. Wholesale Customer\n");
                printf("Enter choice: ");

                sale.customerType = readInteger();

                if (sale.customerType != CUSTOMER_REGULAR &&
                    sale.customerType != CUSTOMER_WHOLESALE)
                {
                    printf("Invalid customer type.\n");
                    sale.customerType = CUSTOMER_REGULAR;
                }

                break;

            case 4:
                completeInStoreSale(&sale);
                return;

            case 5:
                printf("Sale cancelled.\n");
                return;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 5);
}

void addItemToTransaction(Transaction *sale)
{
    int id;
    int quantity;
    int index;

    if (sale->itemCount >= MAX_ITEMS_PER_TRANSACTION)
    {
        printf("Maximum number of items reached.\n");
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

    printf("Product: %s\n", products[index].name);
    printf("Available stock: %d\n", products[index].quantity);

    printf("Quantity: ");
    quantity = readInteger();

    if (quantity <= 0)
    {
        printf("Quantity must be greater than zero.\n");
        return;
    }

    if (quantity > products[index].quantity)
    {
        printf("Insufficient stock.\n");
        return;
    }

    sale->items[sale->itemCount].productId = id;
    sale->items[sale->itemCount].quantity = quantity;
    sale->items[sale->itemCount].unitPrice =
        products[index].retailPrice;

    sale->items[sale->itemCount].subtotal =
        quantity * products[index].retailPrice;

    sale->itemCount++;

    printf("Product added to sale.\n");
}

void completeInStoreSale(Transaction *sale)
{
    if (sale->itemCount == 0)
    {
        printf("\nNo products have been added.\n");
        return;
    }

    calculateTransactionTotal(sale);

    printf("\n============= SALE SUMMARY =============\n");
    viewCart(sale);

    printf("Subtotal: %.2f\n", sale->subtotal);
    printf("Discount: %.2f\n", sale->discount);
    printf("Total: %.2f\n", sale->total);

    printf("\nConfirm sale? (1 = Yes, 2 = No): ");

    if (readInteger() != 1)
    {
        printf("Sale cancelled.\n");
        return;
    }

    for (int i = 0; i < sale->itemCount; i++)
    {
        int index = findProductById(sale->items[i].productId);

        if (index != -1)
        {
            products[index].quantity -=
                sale->items[i].quantity;
        }
    }

    time_t currentTime = time(NULL);
    struct tm *localTime = localtime(&currentTime);

    if (localTime != NULL)
    {
        strftime(sale->date, sizeof(sale->date),
                 "%Y-%m-%d", localTime);
    }

    saveTransaction(sale);

    printf("\nSale completed successfully!\n");
}

