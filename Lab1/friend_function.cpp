#include <iostream>

class Box {
private:
    int width;

public:
    Box() : width(0) {}

    friend void setWidth(Box& b, int w);
};

void setWidth(Box& b, int w) {
    b.width = w;
    std::cout << "Width set to: " << b.width << std::endl;
}

int main() {
    Box box;
    setWidth(box, 10);
    return 0;
}
