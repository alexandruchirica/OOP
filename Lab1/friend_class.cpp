#include <iostream>

class ClassA; // Forward declaration

class ClassB {
public:
    void showA(ClassA& a);
};

class ClassA {
private:
    int dataA;

public:
    ClassA() : dataA(10) {}

    friend class ClassB;
};

void ClassB::showA(ClassA& a) {
    std::cout << "ClassA data: " << a.dataA << std::endl;
}

int main() {
    ClassA a;
    ClassB b;
    b.showA(a); 
    return 0;
}
