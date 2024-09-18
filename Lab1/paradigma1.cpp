#include <iostream>
#include <string>

class Person {
private:
    std::string name;
    int age;

public:
    Person(std::string n, int a) : name(n), age(a) {}

    std::string getName() const {
        return name;
    }

    void setName(std::string n) {
        name = n;
    }

    int getAge() const {
        return age;
    }

    void setAge(int a) {
        age = a;
    }
};

int main() {
    Person person("Alice", 25);

    std::cout << "Name: " << person.getName() << std::endl;
    std::cout << "Age: " << person.getAge() << std::endl;

    person.setName("Bob");
    person.setAge(30);

    std::cout << "Updated Name: " << person.getName() << std::endl;
    std::cout << "Updated Age: " << person.getAge() << std::endl;

    return 0;
}
