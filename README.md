# 🏪 UNI MART — Supermarket Management System

A console-based supermarket management system written in **C** for managing supermarket inventory and processing **in-store customer transactions**.

---

## ✨ Features

### 📦 Inventory Management

- Add new products
- Display all products
- Search products by ID or name
- Update product information
- Delete products
- Sort products by selected fields
- Check low-stock products
- Calculate total inventory value
- Supports up to **200 products**

### 🧾 In-Store Transactions

- Process physical customer purchases
- Add multiple products to a transaction
- Support Regular and Wholesale customers
- Product-specific wholesale pricing
- **10% wholesale discount** for wholesale customers
- Check product availability before completing a sale
- Deduct inventory only after transaction confirmation
- Generate transaction receipts
- Store transaction history

### 👥 Staff Roles

The system provides two staff roles with different access levels:

| Feature | Employee | Manager |
|:---|:---:|:---:|
| Process Transactions | ✅ | ✅ |
| View Products | ✅ | ✅ |
| Search Products | ✅ | ✅ |
| Manage Inventory | ✅ | ✅ |
| Low-Stock Report | ✅ | ✅ |
| Inventory Value | ❌ | ✅ |
| Transaction History | ❌ | ✅ |

---

## 💰 Customer Types

### Regular Customer

Regular customers purchase products using their **retail prices**.

### Wholesale Customer

Wholesale customers:

1. Use the product's **wholesale price**
2. Receive an additional **10% discount** on the subtotal

The wholesale price is stored separately for each product.

---

## 🔄 Transaction Workflow

```text
Select Customer Type
        ↓
Add Products
        ↓
Enter Quantities
        ↓
Check Stock
        ↓
Calculate Prices
        ↓
Apply Wholesale Discount
        ↓
Review Transaction
        ↓
Confirm Sale
        ↓
Deduct Stock
        ↓
Save Transaction