# UNI MART — Supermarket Management System

## 1. Project Overview

UNI MART is a C-based supermarket management system designed to simulate the operations of a large general supermarket.

The system supports both physical in-store purchases and online ordering for delivery. Both channels use the same inventory and transaction records.

The project is being developed individually for CSE 115L.

---

## 2. Development Constraints

- Programming language: C
- Compiler: GCC
- Standard C libraries only
- Struct-based data storage
- Array-based record storage
- Text-file persistence
- Menu-driven console interface
- Program must handle invalid input without crashing
- Code must remain understandable and explainable by the developer

---

## 3. User Types

### Customer

Customers do not require accounts.

Two customer types are supported:

1. Regular Customer
2. Wholesale Customer

Regular customers purchase using retail prices.

Wholesale customers receive the product-specific wholesale price.

### Employee

Employees can:

- Process in-store sales
- View products
- Search products
- Check inventory
- View low-stock information
- Manage online orders
- View relevant sales information

### Manager

Managers have all employee capabilities plus:

- Product management
- Employee management
- Sales reports
- Inventory reports
- Business statistics

---

## 4. Shopping Channels

### In-Store

A staff member processes a physical customer's purchase.

Workflow:

Customer purchase
→ Select products
→ Enter quantities
→ Validate stock
→ Calculate total
→ Apply pricing
→ Generate receipt
→ Deduct inventory
→ Record transaction

### Online

A customer can:

- Browse products
- Search products
- Add products to a cart
- Review the cart
- Choose customer type
- Enter delivery information
- Place an order
- Receive an order ID
- View order status

Online orders follow:

Pending
→ Confirmed
→ Preparing
→ Out for Delivery
→ Delivered

For simplicity, inventory is deducted immediately when an online order is successfully placed.

---

## 5. Product Information

Each product will contain:

- Product ID
- Product name
- Category
- Retail price
- Wholesale price
- Quantity
- Reorder level

The system will maintain an array capable of storing at least 100 products.

---

## 6. Inventory Operations

Planned operations:

- Add product
- Display products
- Search products
- Update product
- Delete product
- Sort products
- Check low-stock products
- Calculate total inventory value

---

## 7. Wholesale Pricing

Wholesale pricing is product-specific.

Each product has:

- Retail price
- Wholesale price

Regular customers use the retail price.

Wholesale customers use the wholesale price.

---

## 8. Transactions

The system will maintain transaction records for both:

- In-store purchases
- Online orders

Transaction information will include:

- Transaction ID
- Date
- Transaction type
- Customer type
- Employee ID where applicable
- Purchased items
- Quantities
- Unit prices
- Subtotals
- Discount/savings
- Delivery charge where applicable
- Final total
- Online order status where applicable

---

## 9. Reports

Planned reports include:

- Today's sales
- Sales by date
- Monthly sales
- Online vs in-store sales
- Sales by employee
- Top-selling products
- Low-stock products
- Total inventory value

Reports will be calculated from stored transaction and inventory data rather than hardcoded results.

---

## 10. Data Persistence

The system will store persistent information in text files.

Planned data files:

- products.txt
- users.txt
- transactions.txt

Sample data will be included with the final submission so the system contains meaningful information during demonstration.

---

## 11. Creative Feature Candidate

Smart Restock Recommendation.

The system may use recent sales information to estimate product demand and recommend when a product should be restocked.

This feature will only be implemented after the core system is stable.

---

## 12. Project Requirements Checklist

### Required

- [ ] R1 — Struct + at least 100 records
- [ ] R2 — Menu loop
- [ ] R3 — At least 5 operations
- [ ] R4 — Meaningful program logic
- [ ] R5 — Search + sorting
- [ ] R6 — File saving/loading
- [ ] R7 — Robust error handling
- [ ] R8 — At least 8 functions besides main

### Bonus

- [x] Git + GitHub development history
- [ ] Multiple .c files + header files + Makefile
- [ ] Creative feature

---

## 13. Development Principles

1. Build the core system before adding advanced features.
2. Test each major feature before moving forward.
3. Avoid unnecessary complexity.
4. Keep functions focused and reasonably short.
5. Use clear variable and function names.
6. Use constants for fixed limits.
7. Never copy another student's implementation.
8. Every part of the final program must be understandable and explainable by the developer.