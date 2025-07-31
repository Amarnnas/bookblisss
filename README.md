# Sales & Expense Management System (C++)

**نظام إدارة المبيعات والمصروفات - C++ Console Application**

A comprehensive sales and expense management system converted from HTML/JavaScript to C++. This console application provides the same functionality as the original web-based system with a cross-platform text-based interface.

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![C++](https://img.shields.io/badge/C%2B%2B-11-blue.svg)
![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)

## 📋 Table of Contents
- [Features](#-features)
- [Requirements](#-requirements)
- [Installation](#-installation)
- [Building](#-building)
- [Usage](#-usage)
- [File Structure](#-file-structure)
- [Arabic Support](#-arabic-support)
- [Troubleshooting](#-troubleshooting)
- [Contributing](#-contributing)

## 🚀 Features

### 🛒 Sales Management (تسجيل المبيعات)
- **Shopping Cart System**: Add/remove products with quantity control
- **Real-time Calculations**: Automatic total calculation with tax support
- **Payment Methods**: Cash and credit payment options
- **Invoice Generation**: Professional invoice printing with unique IDs
- **Customer Tracking**: Customer name recording for credit sales
- **Stock Validation**: Automatic stock level checking before sales

### 📦 Inventory Management (إدارة المخزون)
- **Product Database**: Complete product information management
- **Stock Monitoring**: Real-time stock level tracking
- **Low Stock Alerts**: Automatic warnings for products below threshold
- **Bulk Operations**: Add, edit, delete multiple products
- **Price Management**: Flexible pricing with currency support (EGP)
- **Auto-ID Generation**: Unique product ID assignment

### 💰 Expense Management (المصروفات)
- **Expense Tracking**: Comprehensive expense recording system
- **Categorization**: Detailed expense descriptions and amounts
- **Date Stamping**: Automatic timestamp for all transactions
- **Expense Reports**: Total expense calculations and summaries
- **Delete Protection**: Confirmation dialogs for data safety

### 📊 Advanced Reports (التقارير)
- **Daily Reports**: Complete daily sales and expense analysis
- **Financial Summaries**: Revenue, expenses, and profit calculations
- **Sales Analytics**: Best-selling products and trends
- **Credit Management**: Outstanding debt tracking and customer reports
- **Custom Periods**: Flexible date range reporting
- **Export Ready**: Data formatted for external analysis

### 💾 Data Management
- **JSON Storage**: Human-readable data persistence
- **Auto-Save**: Automatic data backup after each operation
- **Export/Import**: Full data portability between systems
- **Data Integrity**: Validation and error checking
- **Backup Support**: Manual data export for safety

## 🔧 Requirements

### System Requirements
- **Operating System**: Windows 10+, Linux (Ubuntu 18.04+), macOS 10.14+
- **Memory**: Minimum 512MB RAM
- **Storage**: 50MB free disk space
- **Terminal**: UTF-8 compatible terminal (for Arabic text support)

### Development Requirements
- **C++ Compiler**: 
  - GCC 7.0+ (Linux/macOS)
  - Clang 6.0+ (macOS/Linux)
  - MSVC 2017+ (Windows)
  - MinGW-w64 8.0+ (Windows alternative)
- **CMake**: Version 3.10 or higher (optional but recommended)
- **Build Tools**: 
  - Make (Linux/macOS)
  - Ninja (optional, faster builds)
  - MSBuild (Windows with Visual Studio)

### Runtime Dependencies
- **Standard Libraries**: STL (included with C++ compiler)
- **No External Dependencies**: Self-contained application

## 📥 Installation

### Quick Start (Pre-compiled)
```bash
# Clone the repository
git clone <repository-url>
cd sales-management-system

# Make executable (Linux/macOS)
chmod +x sales_system

# Run the application
./sales_system
```

### From Source
```bash
# Clone the repository
git clone <repository-url>
cd sales-management-system

# Build using method 1 or 2 below
```

## 🔨 Building

### Method 1: Direct Compilation (Recommended for single file)

#### Linux/macOS:
```bash
# Standard build
g++ -std=c++11 -Wall -Wextra -o sales_system main.cpp

# Optimized build
g++ -std=c++11 -O3 -Wall -Wextra -o sales_system main.cpp

# Debug build
g++ -std=c++11 -g -Wall -Wextra -o sales_system main.cpp
```

#### Windows (MinGW):
```cmd
g++ -std=c++11 -Wall -Wextra -o sales_system.exe main.cpp
```

#### Windows (MSVC):
```cmd
cl /EHsc /std:c++11 main.cpp /Fe:sales_system.exe
```

### Method 2: CMake Build (Recommended for development)

```bash
# Create build directory
mkdir build
cd build

# Configure build
cmake ..

# Alternative configuration with specific generator
cmake -G "Unix Makefiles" ..        # Linux/macOS
cmake -G "Visual Studio 16 2019" .. # Windows with VS2019
cmake -G "Ninja" ..                  # Fast builds with Ninja

# Build the project
cmake --build .

# Build with specific configuration
cmake --build . --config Release    # Release build
cmake --build . --config Debug      # Debug build

# Run the application
./bin/sales_system                   # Linux/macOS
.\bin\sales_system.exe               # Windows
```

### Build Options
```bash
# Clean build
cmake --build . --target clean

# Verbose build (see compilation commands)
cmake --build . --verbose

# Parallel build (faster)
cmake --build . -j 4  # Use 4 cores
```

## 🖥️ Usage

### Starting the Application
```bash
./sales_system              # Linux/macOS
.\sales_system.exe           # Windows
```

### Navigation
- Use **number keys** to select menu options
- Press **Enter** to confirm selections
- Follow on-screen prompts for data entry
- Use **0** to go back or exit from any menu

### Menu Structure
```
Main Menu (القائمة الرئيسية)
├── 1. Sales Management (تسجيل المبيعات)
│   ├── 1. Add Product to Cart
│   ├── 2. View Current Cart
│   ├── 3. Remove from Cart
│   ├── 4. Complete Sale
│   ├── 5. Clear Cart
│   └── 0. Back to Main Menu
├── 2. Inventory Management (إدارة المخزون)
│   ├── 1. Add New Product
│   ├── 2. View All Products
│   ├── 3. Edit Product
│   ├── 4. Delete Product
│   └── 0. Back to Main Menu
├── 3. Expense Management (المصروفات)
│   ├── 1. Add New Expense
│   ├── 2. View All Expenses
│   ├── 3. Delete Expense
│   └── 0. Back to Main Menu
├── 4. Reports (التقارير)
│   ├── 1. Daily Report
│   ├── 2. All Sales Report
│   ├── 3. Financial Summary
│   ├── 4. Best Selling Products
│   ├── 5. Credit Sales (Debts)
│   └── 0. Back to Main Menu
├── 5. Data Management
│   ├── 1. Export Data
│   ├── 2. Import Data
│   ├── 3. Clear All Data
│   └── 0. Back to Main Menu
└── 0. Exit
```

### Sample Workflow

#### 1. Initial Setup
```
1. Start the application
2. Go to Inventory Management (2)
3. Add your products (1)
   - Enter product name
   - Set price in EGP
   - Set initial stock quantity
4. Repeat for all products
```

#### 2. Making a Sale
```
1. Go to Sales Management (1)
2. Add products to cart (1)
   - Select product by ID
   - Enter quantity
3. Review cart (2)
4. Complete sale (4)
   - Choose payment method (Cash/Credit)
   - Enter customer name (if credit)
5. Print invoice
```

#### 3. Recording Expenses
```
1. Go to Expense Management (3)
2. Add new expense (1)
   - Enter description
   - Enter amount in EGP
3. View all expenses (2)
```

#### 4. Viewing Reports
```
1. Go to Reports (4)
2. Select report type:
   - Daily Report (1): Today's sales and expenses
   - Financial Summary (3): Overall business performance
   - Best Sellers (4): Top-selling products
   - Credit Sales (5): Outstanding debts
```

## 📁 File Structure

```
sales-management-system/
├── main.cpp                 # Complete application source code
├── CMakeLists.txt          # CMake build configuration
├── README.md               # This documentation
├── requirements.txt        # System requirements (for reference)
├── .gitignore              # Git ignore patterns
├── sales_data.json         # Auto-generated data file
├── build/                  # CMake build directory
│   ├── CMakeCache.txt      # CMake cache
│   ├── Makefile            # Generated Makefile
│   └── bin/
│       └── sales_system    # Compiled executable
└── docs/                   # Additional documentation
    ├── INSTALLATION.md     # Detailed installation guide
    ├── USER_GUIDE.md       # Complete user manual
    └── API_REFERENCE.md    # Code documentation
```

### Data Files

#### sales_data.json
```json
{
  "inventory": [
    {"id": 1, "name": "Sample Product", "price": 100.00, "stock": 10}
  ],
  "sales": 0,
  "expenses": 0
}
```

## 🌐 Arabic Support

### Terminal Configuration

#### Windows
```cmd
# Use Windows Terminal or PowerShell with UTF-8
chcp 65001
```

#### Linux
```bash
# Most modern distributions support UTF-8 by default
export LANG=en_US.UTF-8
export LC_ALL=en_US.UTF-8
```

#### macOS
```bash
# Terminal.app supports UTF-8 by default
# For best results, use iTerm2
```

### Font Recommendations
- **Windows**: Consolas, Cascadia Code, DejaVu Sans Mono
- **Linux**: Ubuntu Mono, DejaVu Sans Mono, Liberation Mono
- **macOS**: SF Mono, Menlo, Monaco

## 🔧 Troubleshooting

### Compilation Issues

#### "C++11 not supported"
```bash
# Update your compiler
# Ubuntu/Debian
sudo apt update && sudo apt install build-essential

# CentOS/RHEL
sudo yum install gcc-c++

# macOS
xcode-select --install
```

#### "CMake not found"
```bash
# Ubuntu/Debian
sudo apt install cmake

# CentOS/RHEL
sudo yum install cmake

# macOS with Homebrew
brew install cmake

# Windows
# Download from https://cmake.org/download/
```

### Runtime Issues

#### "Permission denied"
```bash
# Make executable
chmod +x sales_system
```

#### "Cannot create sales_data.json"
```bash
# Check write permissions
ls -la
chmod 755 .
```

#### "Arabic text not displaying"
```bash
# Check terminal encoding
locale
echo $LANG

# Set UTF-8 encoding
export LANG=en_US.UTF-8
```

### Performance Issues

#### "Application slow to start"
- Compile with optimization: `g++ -O3`
- Check available memory: `free -h`
- Close unnecessary applications

#### "Large data file"
- Use Export/Import functionality
- Clear old data regularly
- Backup important data

### Data Recovery

#### Corrupted sales_data.json
```bash
# Backup corrupted file
mv sales_data.json sales_data.json.backup

# Start application (creates new file)
./sales_system

# Try to recover data manually by editing JSON
```

## 📈 Performance Tips

- **Regular Maintenance**: Clear old data periodically
- **Backup Strategy**: Export data weekly
- **Hardware**: SSD storage recommended for large datasets
- **Terminal**: Use a modern terminal emulator for best performance

## 🤝 Contributing

1. **Fork** the repository
2. **Create** a feature branch (`git checkout -b feature/AmazingFeature`)
3. **Commit** your changes (`git commit -m 'Add some AmazingFeature'`)
4. **Push** to the branch (`git push origin feature/AmazingFeature`)
5. **Open** a Pull Request

### Development Guidelines
- Follow C++11 standard
- Use consistent indentation (4 spaces)
- Add comments for complex logic
- Test on multiple platforms
- Update documentation

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- Original HTML/JavaScript version developers
- C++ Standard Library contributors
- CMake development team
- UTF-8 and internationalization support communities

## 📞 Support

For support and questions:
- **Issues**: Create a GitHub issue
- **Documentation**: Check the `/docs` folder
- **Community**: Join our discussions

---

**نظام إدارة المبيعات والمصروفات - النسخة المكتبية**

تم تحويل النظام من تطبيق ويب إلى تطبيق سطح مكتب مع الحفاظ على جميع الخصائص والوظائف الأساسية. النظام يدعم اللغة العربية بالكامل ويعمل على جميع أنظمة التشغيل الرئيسية.

**الخصائص الرئيسية:**
- إدارة شاملة للمبيعات والمخزون
- تتبع المصروفات والأرباح
- تقارير مالية مفصلة
- دعم المبيعات النقدية والآجلة
- واجهة باللغتين العربية والإنجليزية