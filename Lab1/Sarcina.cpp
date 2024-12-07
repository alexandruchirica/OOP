#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Book {
private:
    string title;
    string author;
    string ISBN;

public:
    // Constructor
    Book(string t, string a, string i) : title(t), author(a), ISBN(i) {}

    // Getter for title
    string getTitle() const {
        return title;
    }

    // Getter for author
    string getAuthor() const {
        return author;
    }

    // Getter for ISBN
    string getISBN() const {
        return ISBN;
    }

    // Display book details
    void displayBook() const {
        cout << "Title: " << title << ", Author: " << author << ", ISBN: " << ISBN << endl;
    }
};

class Library {
private:
    vector<Book> books;

public:
    // Add book to library
    void addBook(const Book& book) {
        books.push_back(book);
        cout << "Book added: " << book.getTitle() << endl;
    }

    // Remove book from library by ISBN
    void removeBook(const string& isbn) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->getISBN() == isbn) {
                cout << "Book removed: " << it->getTitle() << endl;
                books.erase(it);
                return;
            }
        }
        cout << "Book with ISBN " << isbn << " not found." << endl;
    }

    // Display all books in library
    void displayBooks() const {
        if (books.empty()) {
            cout << "The library is empty." << endl;
            return;
        }

        for (const auto& book : books) {
            book.displayBook();
        }
    }
};

int main() {
    Library library;
    int choice;
    string title, author, isbn;

    while (true) {
        cout << "\nLibrary Menu:\n";
        cout << "1. Add a book\n";
        cout << "2. Remove a book\n";
        cout << "3. Display all books\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Adding a book
                cout << "Enter book title: ";
                cin.ignore(); // To consume any leftover newline characters
                getline(cin, title);
                cout << "Enter book author: ";
                getline(cin, author);
                cout << "Enter book ISBN: ";
                getline(cin, isbn);
                library.addBook(Book(title, author, isbn));
                break;

            case 2:
                // Removing a book
                cout << "Enter the ISBN of the book to remove: ";
                cin.ignore();
                getline(cin, isbn);
                library.removeBook(isbn);
                break;

            case 3:
                // Displaying all books
                library.displayBooks();
                break;

            case 4:
                // Exit
                cout << "Exiting the program." << endl;
                return 0;

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
}
