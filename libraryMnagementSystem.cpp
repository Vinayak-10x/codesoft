#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

// ── Constants ──────────────────────────────────────
const double FINE_PER_DAY = 5.0;
const int    LOAN_DAYS    = 14;

// ── Get today as days since epoch ──────────────────
long today() {
    return time(nullptr) / 86400;
}

// ══════════════════════════════════════════════════
struct Book {
    string isbn, title, author;
    int    copies, available;
};

struct Borrower {
    string id, name;
};

struct Transaction {
    string txnId, isbn, borrowerId;
    long   checkoutDay, dueDay;
    bool   returned = false;
    double fine     = 0;
};

// ── Global data ────────────────────────────────────
vector<Book>        books;
vector<Borrower>    borrowers;
vector<Transaction> txns;
int                 txnCounter = 100;

// ── Helpers ────────────────────────────────────────
Book*        findBook    (const string& isbn) { for (auto& b : books)     if (b.isbn == isbn)           return &b; return nullptr; }
Borrower*    findBorrower(const string& id)   { for (auto& b : borrowers) if (b.id   == id)             return &b; return nullptr; }
Transaction* findActiveTxn(const string& isbn, const string& bid) {
    for (auto& t : txns) if (!t.returned && t.isbn == isbn && t.borrowerId == bid) return &t;
    return nullptr;
}

// ══════════════════════════════════════════════════
void addBook() {
    Book b;
    cout << "ISBN: ";   cin >> b.isbn;
    cin.ignore();
    cout << "Title: ";  getline(cin, b.title);
    cout << "Author: "; getline(cin, b.author);
    cout << "Copies: "; cin >> b.copies;
    b.available = b.copies;
    books.push_back(b);
    cout << "Book added.\n";
}

void searchBook() {
    string q; cout << "Search: "; cin >> q;
    bool found = false;
    for (auto& b : books)
        if (b.isbn.find(q)!=string::npos || b.title.find(q)!=string::npos || b.author.find(q)!=string::npos) {
            cout << b.isbn << " | " << b.title << " | " << b.author
                 << " | Avail: " << b.available << "/" << b.copies << "\n";
            found = true;
        }
    if (!found) cout << "Not found.\n";
}

void listBooks() {
    for (auto& b : books)
        cout << b.isbn << " | " << b.title << " | " << b.author
             << " | " << b.available << "/" << b.copies << "\n";
}

void addBorrower() {
    Borrower b;
    cout << "ID: ";   cin >> b.id;
    cin.ignore();
    cout << "Name: "; getline(cin, b.name);
    borrowers.push_back(b);
    cout << "Borrower added.\n";
}

void checkoutBook() {
    string isbn, bid;
    cout << "ISBN: ";       cin >> isbn;
    cout << "Borrower ID: "; cin >> bid;

    Book*     b = findBook(isbn);
    Borrower* p = findBorrower(bid);
    if (!b)  { cout << "Book not found.\n";     return; }
    if (!p)  { cout << "Borrower not found.\n"; return; }
    if (b->available == 0) { cout << "No copies available.\n"; return; }

    b->available--;
    Transaction t;
    t.txnId       = "T" + to_string(txnCounter++);
    t.isbn        = isbn;
    t.borrowerId  = bid;
    t.checkoutDay = today();
    t.dueDay      = today() + LOAN_DAYS;
    txns.push_back(t);
    cout << "Checked out! Txn: " << t.txnId << "  Due in " << LOAN_DAYS << " days.\n";
}

void returnBook() {
    string isbn, bid;
    cout << "ISBN: ";        cin >> isbn;
    cout << "Borrower ID: "; cin >> bid;

    Book*        b = findBook(isbn);
    Transaction* t = findActiveTxn(isbn, bid);
    if (!b) { cout << "Book not found.\n";      return; }
    if (!t) { cout << "No active checkout.\n";  return; }

    long overdue = today() - t->dueDay;
    t->fine      = (overdue > 0) ? overdue * FINE_PER_DAY : 0;
    t->returned  = true;
    b->available++;

    cout << "Returned. ";
    if (t->fine > 0) cout << "Fine: $" << t->fine << "\n";
    else             cout << "No fine.\n";
}

void viewTransactions() {
    for (auto& t : txns)
        cout << t.txnId << " | " << t.isbn << " | " << t.borrowerId
             << " | Fine: $" << t.fine
             << " | " << (t.returned ? "Returned" : "Active") << "\n";
}

// ══════════════════════════════════════════════════
int main() {
    int choice;
    do {
        cout << "\n=== Library Menu ===\n"
             << "1. Add Book\n2. Search Book\n3. List Books\n"
             << "4. Add Borrower\n5. Checkout\n6. Return\n"
             << "7. Transactions\n0. Exit\n> ";
        cin >> choice;
        switch (choice) {
        case 1: addBook();         break;
        case 2: searchBook();      break;
        case 3: listBooks();       break;
        case 4: addBorrower();     break;
        case 5: checkoutBook();    break;
        case 6: returnBook();      break;
        case 7: viewTransactions();break;
        }
    } while (choice != 0);
}
