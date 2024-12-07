#include <iostream>
#include <vector>
#include <string>

class Student {
private:
    int id;
    std::string name;
    std::string email;
    bool graduated;

public:
    Student(int id, const std::string& name, const std::string& email)
        : id(id), name(name), email(email), graduated(false) {}

    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getEmail() const { return email; }
    bool isGraduated() const { return graduated; }

    void graduate() { graduated = true; }

    void display() const {
        std::cout << "ID: " << id << ", Name: " << name
                  << ", Email: " << email << ", Status: "
                  << (graduated ? "Graduated" : "Enrolled") << std::endl;
    }
};

class Faculty {
private:
    std::string name;
    std::vector<Student> students;

public:
    Faculty(const std::string& name)
        : name(name) {}

    void addStudent(const Student& student) {
        students.push_back(student);
    }

    void graduateStudent(int studentId) {
        for (auto& student : students) {
            if (student.getId() == studentId) {
                student.graduate();
                break;
            }
        }
    }

    void displayCurrentStudents() const {
        bool found = false;
        for (const auto& student : students) {
            if (!student.isGraduated()) {
                student.display();
                found = true;
            }
        }
        if (!found) {
            std::cout << "No current students in this faculty." << std::endl;
        }
    }

    void displayGraduates() const {
        bool found = false;
        for (const auto& student : students) {
            if (student.isGraduated()) {
                student.display();
                found = true;
            }
        }
        if (!found) {
            std::cout << "No graduates in this faculty." << std::endl;
        }
    }

    bool isStudentInFaculty(int studentId) const {
        for (const auto& student : students) {
            if (student.getId() == studentId) {
                return true;
            }
        }
        return false;
    }

    std::string getName() const { return name; }

    // Getter method to allow access to students in the faculty
    std::vector<Student>& getStudents() { return students; }
};

class University {
private:
    std::vector<Faculty> faculties;

public:
    void addFaculty(const Faculty& faculty) {
        faculties.push_back(faculty);
    }

    void assignStudentToFaculty(int facultyIndex, const Student& student) {
        if (facultyIndex >= 0 && facultyIndex < faculties.size()) {
            faculties[facultyIndex].addStudent(student);
        }
    }

    void graduateStudentFromFaculty(int facultyIndex, int studentId) {
        if (facultyIndex >= 0 && facultyIndex < faculties.size()) {
            faculties[facultyIndex].graduateStudent(studentId);
        }
    }

    Faculty* getFacultyByIndex(int index) {
        if (index >= 0 && index < faculties.size()) {
            return &faculties[index];
        }
        return nullptr;
    }

    const std::vector<Faculty>& getFaculties() const {
        return faculties;
    }

    void displayAllFaculties() const {
        for (size_t i = 0; i < faculties.size(); ++i) {
            std::cout << i + 1 << ". Faculty: " << faculties[i].getName() << std::endl;
        }
    }
};

// Function to show menu and process the selected option
void showMenu() {
    std::cout << "\nUniversity Student Management System" << std::endl;
    std::cout << "1. Add Student to Faculty" << std::endl;
    std::cout << "2. Graduate Student" << std::endl;
    std::cout << "3. Display Current Students" << std::endl;
    std::cout << "4. Display Graduates" << std::endl;
    std::cout << "5. Display All Faculties" << std::endl;
    std::cout << "6. Exit" << std::endl;
    std::cout << "Choose an option: ";
}

int main() {
    University tum;

    // Create faculties (no field information now)
    Faculty foodTech("Food Technology");
    Faculty computerScience("Computer Science");
    tum.addFaculty(foodTech);
    tum.addFaculty(computerScience);

    bool running = true;
    while (running) {
        showMenu();
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int studentId;
                std::string name, email;
                std::cout << "Enter student ID: ";
                std::cin >> studentId;
                std::cin.ignore();  // To clear newline from input buffer
                std::cout << "Enter student name: ";
                std::getline(std::cin, name);
                std::cout << "Enter student email: ";
                std::getline(std::cin, email);

                Student newStudent(studentId, name, email);
                std::cout << "Select the faculty to assign the student to:" << std::endl;
                tum.displayAllFaculties();
                int facultyChoice;
                std::cout << "Enter the faculty number: ";
                std::cin >> facultyChoice;
                if (facultyChoice >= 1 && facultyChoice <= tum.getFaculties().size()) {
                    tum.assignStudentToFaculty(facultyChoice - 1, newStudent);
                    std::cout << "Student added successfully!" << std::endl;
                } else {
                    std::cout << "Invalid faculty choice." << std::endl;
                }
                break;
            }
            case 2: {
                int studentId;
                std::cout << "Enter student ID to graduate: ";
                std::cin >> studentId;
                std::cout << "Select the faculty the student is graduating from:" << std::endl;
                tum.displayAllFaculties();
                int facultyChoice;
                std::cout << "Enter the faculty number: ";
                std::cin >> facultyChoice;
                if (facultyChoice >= 1 && facultyChoice <= tum.getFaculties().size()) {
                    tum.graduateStudentFromFaculty(facultyChoice - 1, studentId);
                    std::cout << "Student graduated successfully!" << std::endl;
                } else {
                    std::cout << "Invalid faculty choice." << std::endl;
                }
                break;
            }
            case 3: {
                // Display current students for selected faculty
                std::cout << "Select a faculty to view current students:" << std::endl;
                tum.displayAllFaculties();
                int facultyChoice;
                std::cout << "Enter the faculty number: ";
                std::cin >> facultyChoice;
                if (facultyChoice >= 1 && facultyChoice <= tum.getFaculties().size()) {
                    tum.getFaculties()[facultyChoice - 1].displayCurrentStudents();
                } else {
                    std::cout << "Invalid faculty choice." << std::endl;
                }
                break;
            }
            case 4: {
                // Display graduates for selected faculty
                std::cout << "Select a faculty to view graduates:" << std::endl;
                tum.displayAllFaculties();
                int facultyChoice;
                std::cout << "Enter the faculty number: ";
                std::cin >> facultyChoice;
                if (facultyChoice >= 1 && facultyChoice <= tum.getFaculties().size()) {
                    tum.getFaculties()[facultyChoice - 1].displayGraduates();
                } else {
                    std::cout << "Invalid faculty choice." << std::endl;
                }
                break;
            }
            case 5: {
                tum.displayAllFaculties();
                break;
            }
            case 6:
                running = false;
                break;
            default:
                std::cout << "Invalid option, please try again." << std::endl;
        }
    }

    return 0;
}
