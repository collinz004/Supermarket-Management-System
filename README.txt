UNI MART - SUPERMARKET MANAGEMENT SYSTEM
CSE115L Final Project - Summer 2026

Name: Sadman Saleheen
ID  : 2421733043
Project: Supermarket Management System

1. PROJECT OVERVIEW

UNI MART is a console-based supermarket management system written in C.
The program is mainly for staff use in a physical store. Staff can manage
the products and make transactions for customers at the store.

There are two staff roles: Employee and Manager. The system also supports
regular and wholesale customers. Wholesale customers use the wholesale price
of products and receive a 10% discount on the subtotal.

2. HOW TO COMPILE

gcc -Wall -Wextra -std=c11 main.c -o uni_mart

3. HOW TO RUN

Windows:
.\uni_mart

The following files should be in the same folder:
products.txt
users.txt
transactions.txt

4. SAMPLE LOGIN ACCOUNTS

Employee:
Username: rahim
Password: 1234

Employee:
Username: karim
Password: 1234

Manager:
Username: manager
Password: admin123

5. REQUIREMENTS R1-R8

R1 - Struct and array:
The program uses Product, User, TransactionItem, and Transaction structs.
Products are stored in an array with space for 200 records, with
productCount keeping track of the records currently in use.

R2 - Menu loop:
The program has a main menu and separate staff, inventory, and transaction
menus. The menus continue until the user chooses to exit or log out.

R3 - Five distinct operations:
The program can add, display, search, update, delete, and sort products.
It also has low-stock and inventory-value reports, transaction processing,
and transaction history.

R4 - Real logic:
The program calculates transaction subtotals and totals, chooses retail or
wholesale prices, applies the wholesale discount, checks available stock,
and calculates the total value of the inventory.

R5 - Search and sort:
Products can be searched using their ID or name. The product list can be
sorted by ID, name, retail price, or quantity. The sorting is done manually
using selection sort rather than a library sorting function.

R6 - Saving and loading:
Product, staff, and transaction data are loaded from text files when the
program starts. The data is saved when changes are made and when the
program exits. If a data file is missing, the program reports it and starts
with empty data instead of crashing.

R7 - Input validation:
The program checks invalid numeric input, invalid menu choices, negative
quantities, duplicate product IDs, unavailable products, insufficient stock,
invalid customer types, and invalid sale confirmations.

R8 - Functions:
The program is divided into separate functions for input, login, inventory,
transactions, reports, and file handling. main mainly controls the program
flow instead of containing all of the logic.

6. PROJECT FILES

main.c              - C source code
products.txt        - sample product data
users.txt           - sample staff accounts
transactions.txt    - sample transaction history
README.txt          - project information
TESTING.txt         - testing record
REFLECTION.txt      - project reflection

7. UNFINISHED WORK

No required R1-R8 feature is unfinished in the code.
