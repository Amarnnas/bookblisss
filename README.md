# Sales & Expense Management System (C++)

نظام إدارة المبيعات والمصروفات - C++ Console Application

A comprehensive sales and expense management system converted from HTML/JavaScript to C++. This console application provides the same functionality as the original web-based system with a text-based interface.

## Features

### 🛒 Sales Management (تسجيل المبيعات)
- Add products to shopping cart
- View current cart with totals
- Remove items from cart
- Complete sales with cash or credit payment
- Generate and print invoices
- Customer name tracking for credit sales

### 📦 Inventory Management (إدارة المخزون)
- Add new products with name, price, and stock quantity
- View all products with low stock warnings
- Edit existing product information
- Delete products from inventory
- Automatic stock updates after sales

### 💰 Expense Management (المصروفات)
- Record new expenses with description and amount
- View all recorded expenses
- Delete expense records
- Track total expenses

### 📊 Reports (التقارير)
- Daily sales and expense reports
- Complete sales history
- Financial summary (revenue, expenses, net income)
- Best-selling products analysis
- Credit sales tracking (outstanding debts)

### 💾 Data Management
- Automatic data persistence to JSON file
- Export/import functionality
- Clear all data option
- Sample data initialization

## Requirements

- C++11 compatible compiler (GCC, Clang, MSVC)
- CMake 3.10 or higher (optional, for building)

## Building the Application

### Method 1: Using CMake (Recommended)

```bash
# Create build directory
mkdir build
cd build

# Generate build files
cmake ..

# Build the application
cmake --build .

# Run the application
./bin/sales_system  # Linux/Mac
.\bin\sales_system.exe  # Windows
```

### Method 2: Direct Compilation

```bash
# Using GCC/Clang
g++ -std=c++11 -Wall -Wextra -o sales_system main.cpp

# Using MSVC (Windows)
cl /EHsc main.cpp /Fe:sales_system.exe

# Run the application
./sales_system  # Linux/Mac
.\sales_system.exe  # Windows
```

## Usage

1. **Start the Application**: Run the compiled executable
2. **Navigation**: Use the numbered menu options to navigate between sections
3. **Data Entry**: Follow the prompts to enter product information, sales data, or expenses
4. **Reports**: Access various reports from the Reports menu
5. **Data Persistence**: All data is automatically saved to `sales_data.json`

### Menu Structure

```
Main Menu
├── 1. Sales Management
│   ├── Add Product to Cart
│   ├── View Current Cart
│   ├── Remove from Cart
│   ├── Complete Sale
│   └── Clear Cart
├── 2. Inventory Management
│   ├── Add New Product
│   ├── View All Products
│   ├── Edit Product
│   └── Delete Product
├── 3. Expense Management
│   ├── Add New Expense
│   ├── View All Expenses
│   └── Delete Expense
├── 4. Reports
│   ├── Daily Report
│   ├── All Sales Report
│   ├── Financial Summary
│   ├── Best Selling Products
│   └── Credit Sales (Debts)
└── 5. Data Management
    ├── Export Data
    ├── Import Data
    └── Clear All Data
```

## Sample Workflow

1. **Setup Inventory**:
   - Go to Inventory Management
   - Add your products with prices and stock quantities

2. **Make a Sale**:
   - Go to Sales Management
   - Add products to cart
   - Complete the sale (cash or credit)
   - Print invoice

3. **Record Expenses**:
   - Go to Expense Management
   - Add business expenses

4. **View Reports**:
   - Check daily, weekly, or custom period reports
   - Monitor best-selling products
   - Track outstanding credit sales

## Data Storage

- **File**: `sales_data.json` (created automatically)
- **Format**: JSON format for easy backup and portability
- **Location**: Same directory as the executable

## Features Comparison with Original HTML Version

| Feature | HTML Version | C++ Version | Status |
|---------|-------------|-------------|--------|
| Sales Management | ✅ | ✅ | Complete |
| Inventory Management | ✅ | ✅ | Complete |
| Expense Tracking | ✅ | ✅ | Complete |
| Reports | ✅ | ✅ | Complete |
| Data Persistence | localStorage | JSON file | Complete |
| Invoice Printing | Browser print | Console output | Adapted |
| Multi-language UI | Arabic/English | Arabic/English | Complete |
| Date/Time tracking | ✅ | ✅ | Complete |

## Technical Details

- **Language**: C++11
- **Architecture**: Object-oriented design with separate classes for Product, Sale, Expense, and SalesManager
- **Data Storage**: JSON-like text format for cross-platform compatibility
- **Memory Management**: Automatic memory management using STL containers
- **Platform Support**: Cross-platform (Windows, Linux, macOS)

## Troubleshooting

### Build Issues
- Ensure you have a C++11 compatible compiler
- Check that CMake is properly installed
- Verify file permissions for the build directory

### Runtime Issues
- Check file permissions for data storage
- Ensure the application has write access to the current directory
- Clear the `sales_data.json` file if data corruption occurs

## Contributing

This is a direct conversion of the HTML-based sales management system. The application maintains the same functionality and user interface patterns as the original web application.

## License

This project maintains the same license terms as the original HTML version.

## Arabic Interface Notes

The application supports Arabic text in the console interface. For best results:
- Use a terminal that supports UTF-8 encoding
- On Windows, use Windows Terminal or PowerShell with UTF-8 support
- On Linux/Mac, most modern terminals support Arabic text display

---

**نظام إدارة المبيعات والمصروفات - النسخة المكتبية**

تم تحويل النظام من تطبيق ويب إلى تطبيق سطح مكتب مع الحفاظ على جميع الخصائص والوظائف الأساسية.