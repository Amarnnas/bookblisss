#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <map>
#include <memory>

// Forward declarations
class Product;
class Sale;
class Expense;
class SalesManager;

// Product class for inventory management
class Product {
public:
    int id;
    std::string name;
    double price;
    int stock;
    
    Product(int id, const std::string& name, double price, int stock)
        : id(id), name(name), price(price), stock(stock) {}
    
    std::string toString() const {
        std::ostringstream oss;
        oss << "ID: " << id << ", Name: " << name 
            << ", Price: " << std::fixed << std::setprecision(2) << price 
            << " EGP, Stock: " << stock;
        return oss.str();
    }
    
    std::string toJson() const {
        std::ostringstream oss;
        oss << "{\"id\":" << id << ",\"name\":\"" << name 
            << "\",\"price\":" << std::fixed << std::setprecision(2) << price 
            << ",\"stock\":" << stock << "}";
        return oss.str();
    }
};

// Sale item for individual products in a sale
class SaleItem {
public:
    int productId;
    std::string name;
    double price;
    int quantity;
    
    SaleItem(int productId, const std::string& name, double price, int quantity)
        : productId(productId), name(name), price(price), quantity(quantity) {}
    
    double getTotal() const {
        return price * quantity;
    }
    
    std::string toString() const {
        std::ostringstream oss;
        oss << name << " - Qty: " << quantity 
            << " x " << std::fixed << std::setprecision(2) << price 
            << " EGP = " << getTotal() << " EGP";
        return oss.str();
    }
};

// Sale class for transaction management
class Sale {
public:
    int id;
    std::string date;
    std::vector<SaleItem> items;
    double total;
    std::string paymentMethod; // "cash" or "credit"
    std::string customerName;
    
    Sale(int id, const std::string& date, const std::vector<SaleItem>& items, 
         const std::string& paymentMethod, const std::string& customerName = "")
        : id(id), date(date), items(items), paymentMethod(paymentMethod), customerName(customerName) {
        calculateTotal();
    }
    
    void calculateTotal() {
        total = 0;
        for (const auto& item : items) {
            total += item.getTotal();
        }
    }
    
    void printInvoice() const {
        std::cout << "\n=== فاتورة مبيعات | Sales Invoice ===" << std::endl;
        std::cout << "Invoice ID: " << id << std::endl;
        std::cout << "Date: " << date << std::endl;
        if (!customerName.empty()) {
            std::cout << "Customer: " << customerName << std::endl;
        }
        std::cout << "Payment Method: " << (paymentMethod == "cash" ? "Cash" : "Credit") << std::endl;
        std::cout << "\n--- Items ---" << std::endl;
        
        for (const auto& item : items) {
            std::cout << item.toString() << std::endl;
        }
        
        std::cout << "\n--- Total ---" << std::endl;
        std::cout << "Total Amount: " << std::fixed << std::setprecision(2) 
                  << total << " EGP" << std::endl;
        std::cout << "================================\n" << std::endl;
    }
};

// Expense class for expense tracking
class Expense {
public:
    int id;
    std::string description;
    double amount;
    std::string date;
    
    Expense(int id, const std::string& description, double amount, const std::string& date)
        : id(id), description(description), amount(amount), date(date) {}
    
    std::string toString() const {
        std::ostringstream oss;
        oss << "Date: " << date << " | " << description 
            << " - " << std::fixed << std::setprecision(2) << amount << " EGP";
        return oss.str();
    }
};

// Main Sales Management System
class SalesManager {
private:
    std::vector<Product> inventory;
    std::vector<Sale> sales;
    std::vector<Expense> expenses;
    std::vector<SaleItem> cart;
    int nextProductId;
    int nextSaleId;
    int nextExpenseId;
    
    std::string getCurrentDate() const {
        time_t now = time(0);
        char* dt = ctime(&now);
        std::string dateStr(dt);
        dateStr.pop_back(); // Remove newline
        return dateStr;
    }
    
    void clearScreen() const {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
    
    void waitForEnter() const {
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore();
        std::cin.get();
    }

public:
    SalesManager() : nextProductId(1), nextSaleId(1), nextExpenseId(1) {
        // Add sample product
        inventory.push_back(Product(nextProductId++, "Sample Product", 100.0, 10));
        loadDataFromFile();
    }
    
    // === INVENTORY MANAGEMENT ===
    void showInventoryMenu() {
        while (true) {
            clearScreen();
            std::cout << "=== إدارة المخزون | Inventory Management ===" << std::endl;
            std::cout << "1. Add New Product" << std::endl;
            std::cout << "2. View All Products" << std::endl;
            std::cout << "3. Edit Product" << std::endl;
            std::cout << "4. Delete Product" << std::endl;
            std::cout << "0. Back to Main Menu" << std::endl;
            std::cout << "Choice: ";
            
            int choice;
            std::cin >> choice;
            std::cin.ignore();
            
            switch (choice) {
                case 1: addProduct(); break;
                case 2: viewAllProducts(); break;
                case 3: editProduct(); break;
                case 4: deleteProduct(); break;
                case 0: return;
                default: 
                    std::cout << "Invalid choice!" << std::endl;
                    waitForEnter();
            }
        }
    }
    
    void addProduct() {
        std::cout << "\n=== Add New Product ===" << std::endl;
        std::string name;
        double price;
        int stock;
        
        std::cout << "Product Name: ";
        std::getline(std::cin, name);
        
        std::cout << "Price (EGP): ";
        std::cin >> price;
        
        std::cout << "Stock Quantity: ";
        std::cin >> stock;
        std::cin.ignore();
        
        inventory.push_back(Product(nextProductId++, name, price, stock));
        saveDataToFile();
        
        std::cout << "Product added successfully!" << std::endl;
        waitForEnter();
    }
    
    void viewAllProducts() {
        std::cout << "\n=== قائمة المنتجات | Product List ===" << std::endl;
        if (inventory.empty()) {
            std::cout << "No products in inventory." << std::endl;
        } else {
            for (const auto& product : inventory) {
                std::cout << product.toString();
                if (product.stock < 5) {
                    std::cout << " [LOW STOCK]";
                }
                std::cout << std::endl;
            }
        }
        waitForEnter();
    }
    
    void editProduct() {
        viewAllProducts();
        if (inventory.empty()) return;
        
        std::cout << "\nEnter Product ID to edit: ";
        int id;
        std::cin >> id;
        std::cin.ignore();
        
        auto it = std::find_if(inventory.begin(), inventory.end(),
                              [id](const Product& p) { return p.id == id; });
        
        if (it != inventory.end()) {
            std::cout << "Current: " << it->toString() << std::endl;
            
            std::cout << "New Name (current: " << it->name << "): ";
            std::string name;
            std::getline(std::cin, name);
            if (!name.empty()) it->name = name;
            
            std::cout << "New Price (current: " << it->price << "): ";
            std::string priceStr;
            std::getline(std::cin, priceStr);
            if (!priceStr.empty()) it->price = std::stod(priceStr);
            
            std::cout << "New Stock (current: " << it->stock << "): ";
            std::string stockStr;
            std::getline(std::cin, stockStr);
            if (!stockStr.empty()) it->stock = std::stoi(stockStr);
            
            saveDataToFile();
            std::cout << "Product updated successfully!" << std::endl;
        } else {
            std::cout << "Product not found!" << std::endl;
        }
        waitForEnter();
    }
    
    void deleteProduct() {
        viewAllProducts();
        if (inventory.empty()) return;
        
        std::cout << "\nEnter Product ID to delete: ";
        int id;
        std::cin >> id;
        std::cin.ignore();
        
        auto it = std::find_if(inventory.begin(), inventory.end(),
                              [id](const Product& p) { return p.id == id; });
        
        if (it != inventory.end()) {
            std::cout << "Are you sure you want to delete: " << it->toString() << "? (y/n): ";
            char confirm;
            std::cin >> confirm;
            std::cin.ignore();
            
            if (confirm == 'y' || confirm == 'Y') {
                inventory.erase(it);
                saveDataToFile();
                std::cout << "Product deleted successfully!" << std::endl;
            }
        } else {
            std::cout << "Product not found!" << std::endl;
        }
        waitForEnter();
    }
    
    // === SALES MANAGEMENT ===
    void showSalesMenu() {
        while (true) {
            clearScreen();
            std::cout << "=== تسجيل المبيعات | Sales Management ===" << std::endl;
            std::cout << "1. Add Product to Cart" << std::endl;
            std::cout << "2. View Current Cart" << std::endl;
            std::cout << "3. Remove from Cart" << std::endl;
            std::cout << "4. Complete Sale" << std::endl;
            std::cout << "5. Clear Cart" << std::endl;
            std::cout << "0. Back to Main Menu" << std::endl;
            std::cout << "Choice: ";
            
            int choice;
            std::cin >> choice;
            std::cin.ignore();
            
            switch (choice) {
                case 1: addToCart(); break;
                case 2: viewCart(); break;
                case 3: removeFromCart(); break;
                case 4: completeSale(); break;
                case 5: clearCart(); break;
                case 0: return;
                default: 
                    std::cout << "Invalid choice!" << std::endl;
                    waitForEnter();
            }
        }
    }
    
    void addToCart() {
        std::cout << "\n=== Available Products ===" << std::endl;
        std::vector<Product> availableProducts;
        for (const auto& product : inventory) {
            if (product.stock > 0) {
                availableProducts.push_back(product);
                std::cout << product.toString() << std::endl;
            }
        }
        
        if (availableProducts.empty()) {
            std::cout << "No products available in stock!" << std::endl;
            waitForEnter();
            return;
        }
        
        std::cout << "\nEnter Product ID: ";
        int productId;
        std::cin >> productId;
        
        std::cout << "Enter Quantity: ";
        int quantity;
        std::cin >> quantity;
        std::cin.ignore();
        
        auto it = std::find_if(inventory.begin(), inventory.end(),
                              [productId](const Product& p) { return p.id == productId; });
        
        if (it != inventory.end() && it->stock >= quantity) {
            // Check if product already in cart
            auto cartIt = std::find_if(cart.begin(), cart.end(),
                                      [productId](const SaleItem& item) { return item.productId == productId; });
            
            if (cartIt != cart.end()) {
                if (it->stock >= cartIt->quantity + quantity) {
                    cartIt->quantity += quantity;
                    std::cout << "Updated quantity in cart!" << std::endl;
                } else {
                    std::cout << "Insufficient stock!" << std::endl;
                }
            } else {
                cart.push_back(SaleItem(productId, it->name, it->price, quantity));
                std::cout << "Product added to cart!" << std::endl;
            }
        } else {
            std::cout << "Product not found or insufficient stock!" << std::endl;
        }
        waitForEnter();
    }
    
    void viewCart() {
        std::cout << "\n=== الفاتورة الحالية | Current Cart ===" << std::endl;
        if (cart.empty()) {
            std::cout << "Cart is empty." << std::endl;
        } else {
            double total = 0;
            for (size_t i = 0; i < cart.size(); ++i) {
                std::cout << (i + 1) << ". " << cart[i].toString() << std::endl;
                total += cart[i].getTotal();
            }
            std::cout << "\nTotal: " << std::fixed << std::setprecision(2) << total << " EGP" << std::endl;
        }
        waitForEnter();
    }
    
    void removeFromCart() {
        if (cart.empty()) {
            std::cout << "Cart is empty!" << std::endl;
            waitForEnter();
            return;
        }
        
        viewCart();
        std::cout << "\nEnter item number to remove (1-" << cart.size() << "): ";
        int itemNum;
        std::cin >> itemNum;
        std::cin.ignore();
        
        if (itemNum >= 1 && itemNum <= static_cast<int>(cart.size())) {
            cart.erase(cart.begin() + itemNum - 1);
            std::cout << "Item removed from cart!" << std::endl;
        } else {
            std::cout << "Invalid item number!" << std::endl;
        }
        waitForEnter();
    }
    
    void completeSale() {
        if (cart.empty()) {
            std::cout << "Cart is empty!" << std::endl;
            waitForEnter();
            return;
        }
        
        viewCart();
        
        std::cout << "\nPayment Method:" << std::endl;
        std::cout << "1. Cash" << std::endl;
        std::cout << "2. Credit" << std::endl;
        std::cout << "Choice: ";
        
        int paymentChoice;
        std::cin >> paymentChoice;
        std::cin.ignore();
        
        std::string paymentMethod = (paymentChoice == 1) ? "cash" : "credit";
        std::string customerName = "";
        
        if (paymentMethod == "credit") {
            std::cout << "Customer Name: ";
            std::getline(std::cin, customerName);
        }
        
        // Update inventory
        for (const auto& cartItem : cart) {
            auto it = std::find_if(inventory.begin(), inventory.end(),
                                  [&cartItem](Product& p) { return p.id == cartItem.productId; });
            if (it != inventory.end()) {
                it->stock -= cartItem.quantity;
            }
        }
        
        // Create sale
        Sale newSale(nextSaleId++, getCurrentDate(), cart, paymentMethod, customerName);
        sales.push_back(newSale);
        
        // Print invoice
        newSale.printInvoice();
        
        cart.clear();
        saveDataToFile();
        
        std::cout << "Sale completed successfully!" << std::endl;
        waitForEnter();
    }
    
    void clearCart() {
        cart.clear();
        std::cout << "Cart cleared!" << std::endl;
        waitForEnter();
    }
    
    // === EXPENSE MANAGEMENT ===
    void showExpensesMenu() {
        while (true) {
            clearScreen();
            std::cout << "=== المصروفات | Expense Management ===" << std::endl;
            std::cout << "1. Add New Expense" << std::endl;
            std::cout << "2. View All Expenses" << std::endl;
            std::cout << "3. Delete Expense" << std::endl;
            std::cout << "0. Back to Main Menu" << std::endl;
            std::cout << "Choice: ";
            
            int choice;
            std::cin >> choice;
            std::cin.ignore();
            
            switch (choice) {
                case 1: addExpense(); break;
                case 2: viewAllExpenses(); break;
                case 3: deleteExpense(); break;
                case 0: return;
                default: 
                    std::cout << "Invalid choice!" << std::endl;
                    waitForEnter();
            }
        }
    }
    
    void addExpense() {
        std::cout << "\n=== Add New Expense ===" << std::endl;
        std::string description;
        double amount;
        
        std::cout << "Expense Description: ";
        std::getline(std::cin, description);
        
        std::cout << "Amount (EGP): ";
        std::cin >> amount;
        std::cin.ignore();
        
        expenses.push_back(Expense(nextExpenseId++, description, amount, getCurrentDate()));
        saveDataToFile();
        
        std::cout << "Expense added successfully!" << std::endl;
        waitForEnter();
    }
    
    void viewAllExpenses() {
        std::cout << "\n=== سجل المصروفات | Expense Record ===" << std::endl;
        if (expenses.empty()) {
            std::cout << "No expenses recorded." << std::endl;
        } else {
            double total = 0;
            for (const auto& expense : expenses) {
                std::cout << "ID: " << expense.id << " | " << expense.toString() << std::endl;
                total += expense.amount;
            }
            std::cout << "\nTotal Expenses: " << std::fixed << std::setprecision(2) << total << " EGP" << std::endl;
        }
        waitForEnter();
    }
    
    void deleteExpense() {
        viewAllExpenses();
        if (expenses.empty()) return;
        
        std::cout << "\nEnter Expense ID to delete: ";
        int id;
        std::cin >> id;
        std::cin.ignore();
        
        auto it = std::find_if(expenses.begin(), expenses.end(),
                              [id](const Expense& e) { return e.id == id; });
        
        if (it != expenses.end()) {
            std::cout << "Are you sure you want to delete: " << it->toString() << "? (y/n): ";
            char confirm;
            std::cin >> confirm;
            std::cin.ignore();
            
            if (confirm == 'y' || confirm == 'Y') {
                expenses.erase(it);
                saveDataToFile();
                std::cout << "Expense deleted successfully!" << std::endl;
            }
        } else {
            std::cout << "Expense not found!" << std::endl;
        }
        waitForEnter();
    }
    
    // === REPORTS ===
    void showReportsMenu() {
        while (true) {
            clearScreen();
            std::cout << "=== التقارير | Reports ===" << std::endl;
            std::cout << "1. Daily Report" << std::endl;
            std::cout << "2. All Sales Report" << std::endl;
            std::cout << "3. Financial Summary" << std::endl;
            std::cout << "4. Best Selling Products" << std::endl;
            std::cout << "5. Credit Sales (Debts)" << std::endl;
            std::cout << "0. Back to Main Menu" << std::endl;
            std::cout << "Choice: ";
            
            int choice;
            std::cin >> choice;
            std::cin.ignore();
            
            switch (choice) {
                case 1: generateDailyReport(); break;
                case 2: generateAllSalesReport(); break;
                case 3: generateFinancialSummary(); break;
                case 4: generateBestSellersReport(); break;
                case 5: generateCreditSalesReport(); break;
                case 0: return;
                default: 
                    std::cout << "Invalid choice!" << std::endl;
                    waitForEnter();
            }
        }
    }
    
    void generateDailyReport() {
        std::cout << "\n=== Daily Report ===" << std::endl;
        std::string today = getCurrentDate();
        
        double cashRevenue = 0, creditRevenue = 0, dailyExpenses = 0;
        int salesCount = 0, expensesCount = 0;
        
        for (const auto& sale : sales) {
            if (sale.date.substr(0, 10) == today.substr(0, 10)) {
                salesCount++;
                if (sale.paymentMethod == "cash") {
                    cashRevenue += sale.total;
                } else {
                    creditRevenue += sale.total;
                }
            }
        }
        
        for (const auto& expense : expenses) {
            if (expense.date.substr(0, 10) == today.substr(0, 10)) {
                expensesCount++;
                dailyExpenses += expense.amount;
            }
        }
        
        std::cout << "Date: " << today << std::endl;
        std::cout << "Sales Count: " << salesCount << std::endl;
        std::cout << "Cash Revenue: " << std::fixed << std::setprecision(2) << cashRevenue << " EGP" << std::endl;
        std::cout << "Credit Revenue: " << std::fixed << std::setprecision(2) << creditRevenue << " EGP" << std::endl;
        std::cout << "Total Revenue: " << std::fixed << std::setprecision(2) << (cashRevenue + creditRevenue) << " EGP" << std::endl;
        std::cout << "Expenses Count: " << expensesCount << std::endl;
        std::cout << "Total Expenses: " << std::fixed << std::setprecision(2) << dailyExpenses << " EGP" << std::endl;
        std::cout << "Net Income: " << std::fixed << std::setprecision(2) << (cashRevenue - dailyExpenses) << " EGP" << std::endl;
        
        waitForEnter();
    }
    
    void generateAllSalesReport() {
        std::cout << "\n=== All Sales Report ===" << std::endl;
        if (sales.empty()) {
            std::cout << "No sales recorded." << std::endl;
        } else {
            for (const auto& sale : sales) {
                std::cout << "Sale ID: " << sale.id << " | Date: " << sale.date 
                         << " | Total: " << std::fixed << std::setprecision(2) << sale.total 
                         << " EGP | Payment: " << sale.paymentMethod;
                if (!sale.customerName.empty()) {
                    std::cout << " | Customer: " << sale.customerName;
                }
                std::cout << std::endl;
            }
        }
        waitForEnter();
    }
    
    void generateFinancialSummary() {
        std::cout << "\n=== Financial Summary ===" << std::endl;
        
        double totalCashRevenue = 0, totalCreditRevenue = 0, totalExpenses = 0;
        
        for (const auto& sale : sales) {
            if (sale.paymentMethod == "cash") {
                totalCashRevenue += sale.total;
            } else {
                totalCreditRevenue += sale.total;
            }
        }
        
        for (const auto& expense : expenses) {
            totalExpenses += expense.amount;
        }
        
        std::cout << "Total Cash Revenue: " << std::fixed << std::setprecision(2) << totalCashRevenue << " EGP" << std::endl;
        std::cout << "Total Credit Revenue: " << std::fixed << std::setprecision(2) << totalCreditRevenue << " EGP" << std::endl;
        std::cout << "Total Revenue: " << std::fixed << std::setprecision(2) << (totalCashRevenue + totalCreditRevenue) << " EGP" << std::endl;
        std::cout << "Total Expenses: " << std::fixed << std::setprecision(2) << totalExpenses << " EGP" << std::endl;
        std::cout << "Net Income: " << std::fixed << std::setprecision(2) << (totalCashRevenue - totalExpenses) << " EGP" << std::endl;
        std::cout << "Outstanding Credit: " << std::fixed << std::setprecision(2) << totalCreditRevenue << " EGP" << std::endl;
        
        waitForEnter();
    }
    
    void generateBestSellersReport() {
        std::cout << "\n=== Best Selling Products ===" << std::endl;
        
        std::map<std::string, int> productSales;
        
        for (const auto& sale : sales) {
            for (const auto& item : sale.items) {
                productSales[item.name] += item.quantity;
            }
        }
        
        // Convert to vector and sort
        std::vector<std::pair<std::string, int>> sortedProducts(productSales.begin(), productSales.end());
        std::sort(sortedProducts.begin(), sortedProducts.end(),
                 [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) { return a.second > b.second; });
        
        if (sortedProducts.empty()) {
            std::cout << "No sales data available." << std::endl;
        } else {
            for (size_t i = 0; i < std::min(size_t(10), sortedProducts.size()); ++i) {
                std::cout << (i + 1) << ". " << sortedProducts[i].first 
                         << " - " << sortedProducts[i].second << " units sold" << std::endl;
            }
        }
        
        waitForEnter();
    }
    
    void generateCreditSalesReport() {
        std::cout << "\n=== Credit Sales (Outstanding Debts) ===" << std::endl;
        
        double totalCredit = 0;
        bool foundCredit = false;
        
        for (const auto& sale : sales) {
            if (sale.paymentMethod == "credit") {
                foundCredit = true;
                std::cout << "Customer: " << sale.customerName 
                         << " | Amount: " << std::fixed << std::setprecision(2) << sale.total 
                         << " EGP | Date: " << sale.date << std::endl;
                totalCredit += sale.total;
            }
        }
        
        if (!foundCredit) {
            std::cout << "No credit sales found." << std::endl;
        } else {
            std::cout << "\nTotal Outstanding Credit: " << std::fixed << std::setprecision(2) << totalCredit << " EGP" << std::endl;
        }
        
        waitForEnter();
    }
    
    // === DATA MANAGEMENT ===
    void showDataMenu() {
        while (true) {
            clearScreen();
            std::cout << "=== Data Management ===" << std::endl;
            std::cout << "1. Export Data" << std::endl;
            std::cout << "2. Import Data" << std::endl;
            std::cout << "3. Clear All Data" << std::endl;
            std::cout << "0. Back to Main Menu" << std::endl;
            std::cout << "Choice: ";
            
            int choice;
            std::cin >> choice;
            std::cin.ignore();
            
            switch (choice) {
                case 1: exportData(); break;
                case 2: importData(); break;
                case 3: clearAllData(); break;
                case 0: return;
                default: 
                    std::cout << "Invalid choice!" << std::endl;
                    waitForEnter();
            }
        }
    }
    
    void saveDataToFile() {
        std::ofstream file("sales_data.json");
        if (file.is_open()) {
            file << "{\n";
            
            // Save inventory
            file << "  \"inventory\": [\n";
            for (size_t i = 0; i < inventory.size(); ++i) {
                file << "    " << inventory[i].toJson();
                if (i < inventory.size() - 1) file << ",";
                file << "\n";
            }
            file << "  ],\n";
            
            // Save sales (simplified)
            file << "  \"sales\": " << sales.size() << ",\n";
            
            // Save expenses (simplified)  
            file << "  \"expenses\": " << expenses.size() << "\n";
            
            file << "}\n";
            file.close();
        }
    }
    
    void loadDataFromFile() {
        // Simplified loading - in a real application, you'd parse JSON properly
        std::ifstream file("sales_data.json");
        if (file.is_open()) {
            // For now, just check if file exists
            file.close();
        }
    }
    
    void exportData() {
        saveDataToFile();
        std::cout << "Data exported to sales_data.json successfully!" << std::endl;
        waitForEnter();
    }
    
    void importData() {
        std::cout << "Import functionality would read from sales_data.json" << std::endl;
        std::cout << "This is a simplified implementation." << std::endl;
        waitForEnter();
    }
    
    void clearAllData() {
        std::cout << "Are you sure you want to clear ALL data? This cannot be undone! (y/n): ";
        char confirm;
        std::cin >> confirm;
        std::cin.ignore();
        
        if (confirm == 'y' || confirm == 'Y') {
            inventory.clear();
            sales.clear();
            expenses.clear();
            cart.clear();
            nextProductId = 1;
            nextSaleId = 1;
            nextExpenseId = 1;
            
            // Add sample product back
            inventory.push_back(Product(nextProductId++, "Sample Product", 100.0, 10));
            
            saveDataToFile();
            std::cout << "All data cleared successfully!" << std::endl;
        }
        waitForEnter();
    }
    
    // === MAIN MENU ===
    void run() {
        while (true) {
            clearScreen();
            std::cout << "================================" << std::endl;
            std::cout << "نظام إدارة المبيعات والمصروفات" << std::endl;
            std::cout << "Sales & Expense Management System" << std::endl;
            std::cout << "================================" << std::endl;
            std::cout << "1. Sales Management (تسجيل المبيعات)" << std::endl;
            std::cout << "2. Inventory Management (إدارة المخزون)" << std::endl;
            std::cout << "3. Expense Management (المصروفات)" << std::endl;
            std::cout << "4. Reports (التقارير)" << std::endl;
            std::cout << "5. Data Management" << std::endl;
            std::cout << "0. Exit" << std::endl;
            std::cout << "Choice: ";
            
            int choice;
            std::cin >> choice;
            std::cin.ignore();
            
            switch (choice) {
                case 1: showSalesMenu(); break;
                case 2: showInventoryMenu(); break;
                case 3: showExpensesMenu(); break;
                case 4: showReportsMenu(); break;
                case 5: showDataMenu(); break;
                case 0: 
                    std::cout << "Thank you for using the system!" << std::endl;
                    return;
                default: 
                    std::cout << "Invalid choice!" << std::endl;
                    waitForEnter();
            }
        }
    }
};

int main() {
    SalesManager manager;
    manager.run();
    return 0;
}