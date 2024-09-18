#include <iostream>

class Base {
public:
    Base() {
        std::cout << "Base class constructor called" << std::endl;
    }

    ~Base() {
        std::cout << "Base class destructor called" << std::endl;
    }
};

class Derived : public Base {
public:
    Derived() {
        std::cout << "Derived class constructor called" << std::endl;
    }

    ~Derived() {
        std::cout << "Derived class destructor called" << std::endl;
    }
};

int main() {
    Derived obj;

    // Constructor order:
    // 1. Base class constructor
    // 2. Derived class constructor
    // Destructor order:
    // 1. Derived class destructor
    // 2. Base class destructor
    return 0;
}
