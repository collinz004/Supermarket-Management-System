# UNI MART — Supermarket Management System

## 1. Project Goal

UNI MART is a C-based supermarket management system for managing supermarket inventory and in-store customer transactions.

The project is developed individually for CSE 115L.

## 2. Main Features

### Staff System
- Employee and Manager login
- Role-based menu access

### Inventory Management
- Add products
- Display products
- Search products
- Update products
- Delete products
- Sort products
- Low-stock report
- Inventory value calculation

### In-Store Transactions
- Regular and wholesale customers
- Multiple products per transaction
- Retail and wholesale pricing
- 10% wholesale discount
- Stock validation and deduction
- Transaction receipt
- Transaction history for managers

## 3. Data Storage

The system uses structs and arrays to store records during execution.

Persistent data is stored in:

- `products.txt`
- `users.txt`
- `transactions.txt`

The program loads existing data at startup and saves updated data when exiting.

## 4. Development Approach

1. Build the inventory system.
2. Add staff login and role-based access.
3. Add in-store transaction processing.
4. Add file saving and loading.
5. Add validation, sorting, and reports.
6. Test the complete system with normal and invalid inputs.
7. Prepare the final documentation and submission.

## 5. Project Requirements

The final system includes:

- Struct-based data storage
- Array capacity for at least 100 products
- Menu-driven operation
- Multiple inventory and transaction operations
- Search and manual sorting
- File persistence
- Input validation
- More than 8 functions besides `main`

## 6. Development Notes

The project is maintained using Git and GitHub.

The implementation is kept within standard C and uses separate functions for individual tasks so that the code remains understandable and explainable.