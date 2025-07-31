#!/bin/bash

# Sales & Expense Management System - Installation Script
# نظام إدارة المبيعات والمصروفات - سكريبت التثبيت
# For Linux and macOS

set -e  # Exit on any error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Print functions
print_header() {
    echo -e "${BLUE}================================${NC}"
    echo -e "${BLUE}Sales & Expense Management System${NC}"
    echo -e "${BLUE}نظام إدارة المبيعات والمصروفات${NC}"
    echo -e "${BLUE}Installation Script${NC}"
    echo -e "${BLUE}================================${NC}"
    echo
}

print_success() {
    echo -e "${GREEN}✓ $1${NC}"
}

print_error() {
    echo -e "${RED}✗ $1${NC}"
}

print_warning() {
    echo -e "${YELLOW}⚠ $1${NC}"
}

print_info() {
    echo -e "${BLUE}ℹ $1${NC}"
}

# Check if command exists
command_exists() {
    command -v "$1" >/dev/null 2>&1
}

# Detect OS
detect_os() {
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        if command_exists apt; then
            OS="ubuntu"
        elif command_exists yum; then
            OS="centos"
        elif command_exists dnf; then
            OS="fedora"
        else
            OS="linux"
        fi
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        OS="macos"
    else
        OS="unknown"
    fi
    echo "$OS"
}

# Install dependencies
install_dependencies() {
    local os=$(detect_os)
    
    print_info "Detected OS: $os"
    print_info "Installing dependencies..."
    
    case $os in
        ubuntu)
            print_info "Updating package lists..."
            sudo apt update
            print_info "Installing build-essential and cmake..."
            sudo apt install -y build-essential cmake
            ;;
        centos)
            print_info "Installing gcc-c++ and cmake..."
            sudo yum install -y gcc-c++ cmake
            ;;
        fedora)
            print_info "Installing gcc-c++ and cmake..."
            sudo dnf install -y gcc-c++ cmake
            ;;
        macos)
            if ! command_exists brew; then
                print_warning "Homebrew not found. Please install Xcode Command Line Tools manually:"
                print_info "Run: xcode-select --install"
                print_info "Then optionally install Homebrew from: https://brew.sh"
            else
                print_info "Installing cmake via Homebrew..."
                brew install cmake
            fi
            ;;
        *)
            print_warning "Unknown OS. Please install build tools manually:"
            print_info "- C++11 compatible compiler (GCC 7+ or Clang 6+)"
            print_info "- CMake 3.10+"
            ;;
    esac
}

# Check prerequisites
check_prerequisites() {
    print_info "Checking prerequisites..."
    
    local missing=0
    
    # Check for C++ compiler
    if command_exists g++; then
        local gcc_version=$(g++ --version | head -n1)
        print_success "GCC found: $gcc_version"
    elif command_exists clang++; then
        local clang_version=$(clang++ --version | head -n1)
        print_success "Clang found: $clang_version"
    else
        print_error "No C++ compiler found (g++ or clang++)"
        missing=1
    fi
    
    # Check for CMake
    if command_exists cmake; then
        local cmake_version=$(cmake --version | head -n1)
        print_success "CMake found: $cmake_version"
    else
        print_warning "CMake not found (optional but recommended)"
    fi
    
    # Check for make
    if command_exists make; then
        print_success "Make found"
    else
        print_warning "Make not found"
    fi
    
    return $missing
}

# Build with direct compilation
build_direct() {
    print_info "Building with direct compilation..."
    
    if command_exists g++; then
        g++ -std=c++11 -Wall -Wextra -O2 -o sales_system main.cpp
    elif command_exists clang++; then
        clang++ -std=c++11 -Wall -Wextra -O2 -o sales_system main.cpp
    else
        print_error "No suitable compiler found"
        return 1
    fi
    
    print_success "Build completed: sales_system"
}

# Build with CMake
build_cmake() {
    print_info "Building with CMake..."
    
    # Create build directory
    mkdir -p build
    cd build
    
    # Configure
    cmake ..
    
    # Build
    cmake --build . --config Release
    
    # Copy executable to project root for convenience
    if [ -f "bin/sales_system" ]; then
        cp bin/sales_system ../sales_system
        print_success "Build completed: sales_system"
    else
        print_error "Build failed - executable not found"
        return 1
    fi
    
    cd ..
}

# Main build function
build_project() {
    print_info "Starting build process..."
    
    if [ ! -f "main.cpp" ]; then
        print_error "main.cpp not found. Please run this script from the project directory."
        exit 1
    fi
    
    # Try CMake first, fallback to direct compilation
    if command_exists cmake; then
        if build_cmake; then
            return 0
        else
            print_warning "CMake build failed, trying direct compilation..."
            build_direct
        fi
    else
        build_direct
    fi
}

# Test the built application
test_application() {
    print_info "Testing the application..."
    
    if [ -f "sales_system" ]; then
        # Make executable
        chmod +x sales_system
        
        # Test run (exit immediately)
        if echo "0" | ./sales_system >/dev/null 2>&1; then
            print_success "Application test passed"
        else
            print_warning "Application test failed, but build appears successful"
        fi
    else
        print_error "Executable not found"
        return 1
    fi
}

# Setup UTF-8 locale
setup_locale() {
    print_info "Setting up UTF-8 locale for Arabic text support..."
    
    if [ -z "$LANG" ] || [[ "$LANG" != *"UTF-8"* ]]; then
        export LANG=en_US.UTF-8
        export LC_ALL=en_US.UTF-8
        print_success "UTF-8 locale configured"
        print_info "Add these lines to your ~/.bashrc or ~/.zshrc:"
        print_info "export LANG=en_US.UTF-8"
        print_info "export LC_ALL=en_US.UTF-8"
    else
        print_success "UTF-8 locale already configured"
    fi
}

# Print usage instructions
print_usage() {
    echo
    print_info "Installation completed! Usage instructions:"
    echo
    echo "To run the application:"
    echo "  ./sales_system"
    echo
    echo "To rebuild the project:"
    echo "  # Using CMake (recommended):"
    echo "  mkdir build && cd build && cmake .. && cmake --build ."
    echo
    echo "  # Using direct compilation:"
    echo "  g++ -std=c++11 -Wall -Wextra -O2 -o sales_system main.cpp"
    echo
    echo "For Arabic text support, ensure your terminal:"
    echo "  - Uses UTF-8 encoding"
    echo "  - Has a font that supports Arabic characters"
    echo
    print_info "Documentation: README.md"
    print_info "Requirements: requirements.txt"
}

# Main installation function
main() {
    print_header
    
    # Parse command line arguments
    INSTALL_DEPS=false
    FORCE_DIRECT=false
    
    for arg in "$@"; do
        case $arg in
            --install-deps)
                INSTALL_DEPS=true
                ;;
            --direct)
                FORCE_DIRECT=true
                ;;
            --help|-h)
                echo "Usage: $0 [options]"
                echo "Options:"
                echo "  --install-deps  Install system dependencies"
                echo "  --direct        Use direct compilation instead of CMake"
                echo "  --help, -h      Show this help message"
                exit 0
                ;;
        esac
    done
    
    # Install dependencies if requested
    if $INSTALL_DEPS; then
        install_dependencies
    fi
    
    # Check prerequisites
    if ! check_prerequisites; then
        print_error "Missing prerequisites. Run with --install-deps to install them."
        exit 1
    fi
    
    # Build project
    if $FORCE_DIRECT; then
        build_direct
    else
        build_project
    fi
    
    # Test application
    test_application
    
    # Setup locale
    setup_locale
    
    # Print usage instructions
    print_usage
    
    print_success "Installation completed successfully!"
}

# Run main function with all arguments
main "$@"