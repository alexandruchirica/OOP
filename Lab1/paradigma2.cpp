#include <iostream>
#include <string>

// Base class
class Animal {
protected:
    std::string species;

public:
    Animal(std::string s) : species(s) {}

    void makeSound() const {
        std::cout << "The " << species << " makes a sound." << std::endl;
    }
};

// Derived class
class Dog : public Animal {
public:
    Dog() : Animal("Dog") {}

    void bark() const {
        std::cout << "The " << species << " barks." << std::endl;
    }
};

int main() {
    Dog myDog;
    myDog.makeSound(); // Inherited from the base class
    myDog.bark();      // Defined in the derived class

    return 0;
}
