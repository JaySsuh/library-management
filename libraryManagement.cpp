#include <algorithm> // std::find_if
#include <iostream>
#include <limits>
#include <string>
#include <vector> //Book objects are stored in a vector

// Book class and its derived classes
class Book {
protected: //protected vals
  int isbn;
  std::string title;
  std::string author;
  int edition;
  std::string publisher;

public: 
  Book(int isbn, const std::string &title, const std::string &author,
       int edition, const std::string &publisher)
      : isbn(isbn), title(title), author(author), edition(edition),
        publisher(publisher) {}
  // Book constructor for constants isbn, title, author, edition, and publisher
  virtual ~Book() {} // deconstructor for Book constructor

  int getIsbn() const { return isbn; }          // Getter constructor for ISBN
  void setIsbn(int newIsbn) { isbn = newIsbn; } // Setter constructor for ISBN

  const std::string &getTitle() const {
    return title;
  } // Getter constructor for title
  void setTitle(const std::string &newTitle) { title = newTitle; }
  // Setter constructor for title

  const std::string &getAuthor() const {
    return author;
  } // Getter constructor for author
  void setAuthor(const std::string &newAuthor) { author = newAuthor; }
  // Setter constructor for author

  int getEdition() const { return edition; } // Getter constructor for edition
  void setEdition(int newEdition) { edition = newEdition; }
  // Setter constructor for edition

  const std::string &getPublisher() const { return publisher; }
  // Getter constructor for publisher
  void setPublisher(const std::string &newPublisher) {
    publisher = newPublisher;
  }
  // Setter constructor for publisher

  virtual void display() const {
    std::cout << "ISBN: " << isbn << "\nTitle: " << title
              << "\nAuthor: " << author << "\nEdition: " << edition
              << "\nPublisher: " << publisher << std::endl;
  } // virtual member function to display entered inputs for each book
};

class Fiction : public Book {
  std::string genre;

public:
  Fiction(int isbn, const std::string &title, const std::string &author,
          int edition, const std::string &publisher, const std::string &genre)
      : Book(isbn, title, author, edition, publisher), genre(genre) {}
  // fiction constructor derived from book class and incorporates genre string
  void display() const override { // display override for genre
    Book::display();              // calls virutal member function display
    std::cout << "Genre: " << genre << std::endl; // outputs genre
  }
};

class NonFiction : public Book {
  std::string subject;

public:
  NonFiction(int isbn, const std::string &title, const std::string &author,
             int edition, const std::string &publisher,
             const std::string &subject)
      : Book(isbn, title, author, edition, publisher), subject(subject) {}
  // nonfiction constructor derived from book class and incorporates subject
  // string
  void display() const override { // display override for subject
    Book::display();              // calls virtual member function display
    std::cout << "Subject: " << subject << std::endl; // outputs subject
  }
};

// Function to clear std::cin buffer
void clearCin() {
  std::cin.clear(); // Reset any error flags
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                  '\n'); // Ignore any characters in the input buffer
}

// Function to display the main menu
void displayMenu() {
  std::cout << "\nLIBRARY MANAGEMENT SYSTEM\n\n";
  std::cout << "[1] ADD BOOK\n";
  std::cout << "[2] DELETE BOOK\n";
  std::cout << "[3] EDIT BOOK\n";
  std::cout << "[4] SEARCH BOOKS\n";
  std::cout << "[5] VIEW ALL BOOKS\n";
  std::cout << "[6] QUIT\n\n";
  std::cout << "ENTER CHOICE: ";
}

// Function to add a new book
void addBook(std::vector<Book *> &library) {
  int isbn, edition;
  std::string title, author, publisher, type, genre, subject;

  //Take each user input (Including Genre)
  std::cout << "Enter ISBN: ";
  std::cin >> isbn;
  clearCin(); // clears input to continue prompt

  std::cout << "Enter Title: ";
  getline(std::cin, title);

  std::cout << "Enter Author: ";
  getline(std::cin, author);

  std::cout << "Enter Edition: ";
  std::cin >> edition;
  clearCin();

  std::cout << "Enter Publisher: ";
  getline(std::cin, publisher);

  std::cout << "Enter book type (Fiction/NonFiction): ";
  getline(std::cin, type);
  // Creates book depending on type using Fiction/NonFiction
  if (type == "Fiction") {
    std::cout << "Enter Genre: ";
    getline(std::cin, genre); // extracts from input stream and appends to
                              // string
    library.push_back( // push_back adds new element of type Fiction at the end of the vector
        new Fiction(isbn, title, author, edition, publisher, genre));
  } else if (type == "NonFiction") {
    std::cout << "Enter Subject: ";
    getline(std::cin, subject);
    library.push_back( // push_back adds new element of type NonFiction at the end of the vector
        new NonFiction(isbn, title, author, edition, publisher, subject));
  } 

  else { // If the genre entered is neither NonFiction or Fiction, the program returns it as invalid and exits
    std::cout << "Invalid book type entered." << std::endl;
    return;
  }

  std::cout << "Book added successfully!" << std::endl;
}

// Function to delete a book by ISBN
// Uses an iterator in order to make the deletion part much easier, though it IS harder
// to implement in the search part
void deleteBook(std::vector<Book *> &library) {
  int isbn;
  std::cout << "Enter ISBN of book to delete: ";
  std::cin >> isbn;
  clearCin(); // clears buffer for chosen book

  auto it = std::find_if(library.begin(), library.end(), [isbn](Book *book) {
    return book->getIsbn() == isbn;
  }); // find_if returns an iterator to the first element in the range [begin,end) with
      // a matching isbn, or end if no such element is found, creates element "it" (iterator)
  if (it != library.end()) { // If no such element is there (if the iterator is
                             // one past the end of the vector)
    // Deletes the book (Or rather the element indicated by the iterator)
    delete *it;
    library.erase(it); // erase removes an element of a vector
    std::cout << "Book deleted successfully!" << std::endl;
  } else { // Does not delete a book, as the specified one does not exist
    std::cout << "Book not found." << std::endl;
  }
}

// Function to edit an existing book's title (only edits the title, nothing else)
void editBook(std::vector<Book *> &library) {
  int isbn;
  std::cout << "Enter ISBN of book to edit: ";
  std::cin >> isbn; //reads ISBN
  clearCin(); // clears buffer for chosen book to avoid errors

  for (Book *book : library) { // loop through each book in library
    if (book->getIsbn() == isbn) { // Checks if the current ISBN matches input
      std::string newTitle; //Declare string to store new title
      std::cout << "Enter new title: ";
      getline(std::cin, newTitle); // reads new input
      book->setTitle(newTitle); // sets new title
      std::cout << "Book title updated successfully!" << std::endl; //success and exit
      return;
    }
  }
  std::cout << "Book not found." << std::endl; 
}

// Function to search books by title
void searchBooks(const std::vector<Book *> &library) { 
  std::string query; // Declare string to store the search query
  std::cout << "Enter title to search for: ";
  getline(std::cin, query); //read search from user

  bool found = false; // boolean for vector search
  for (const Book *book : library) { //Only sets as true if book is found
    if (book->getTitle().find(query) != std::string::npos) { // check if book title contains query
      book->display(); // displays book details
      found = true;   // Initialize a boolean to track if any book is found

    }
  }
  if (!found) { //if NOT found
    std::cout << "No books found with that title." << std::endl;
  }
}

// Function to view all books
void viewAllBooks(const std::vector<Book *> &library) {
  if (library.empty()) {
    std::cout << "No books in the library." << std::endl;
    return;
  }
  for (const Book *book : library) { //For each book in the library, displays book using display() of the book class
    book->display();
    std::cout << "-----------------" << std::endl; //Seperator for distinction
  }
}

// Main program entry point
int main() {
  std::vector<Book *> library; //Declares a vector to store pointers to book objects
  char choice;

  do {
    displayMenu(); //Display the menu
    std::cin >> choice; //User input stored in choice 
    clearCin(); //Clear any input

    switch (choice) { //Switch statement for choices
    case '1':
      addBook(library);
      break;
    case '2':
      deleteBook(library);
      break;
    case '3':
      editBook(library);
      break;
    case '4':
      searchBooks(library);
      break;
    case '5':
      viewAllBooks(library);
      break;
    case '6':
      std::cout << "Exiting the program...\n";
      break;
    default:
      std::cout << "Invalid choice, please try again.\n";
    }
  } while (choice != '6'); // Exits Code

  return 0;
}
