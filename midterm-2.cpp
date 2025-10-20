// COMSC-210 | Midterm #2 | Annie Morales
// IDE used: Visual Studio Code

// This program simulates a line at a coffee shop, which will run for 
// 20 time periods (minutes) and display the current line at the coffee shop.

#include <iostream>
#include <fstream> // For file operations
#include <ctime>    // For time()
#include <cstdlib>  // for rand() and srand()
#include <vector>   // For using vector
#include <string>   // For using string
#include <iomanip>
using namespace std;

const int MIN_NR = 1, MAX_NR = 100, MIN_LS = 5, MAX_LS = 20, W10 = 10;

class DoublyLinkedList {
private:
    struct Node {
        string name;
        Node* prev;
        Node* next;
        Node(string na, Node* p = nullptr, Node* n = nullptr) {
            name = na; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void insert_after(string na, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(na);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(string na) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->name != na)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(string na) {
        Node* newNode = new Node(na);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(string na) {
        Node* newNode = new Node(na);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        
        cout << setw(10) << "Resulting line:" << endl;
        while (current) {
            cout << setw(10) << current->name << " \n";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->name << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    srand(time(0)); // Seed for random number generation.

    //cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    vector<string> names; // Vector to store names (99 total names)
    ifstream fin;
    fin.open("names.txt");

    // Checks if file opened succesfully
    if (!fin.good()) throw "I/O error";

    // Reads names from file and stores them in vector
    string name;
    while (getline(fin, name))
    {
        names.push_back(name);
    }
    fin.close(); //Closes the file

    while (!fin.eof())
    {
        getline(fin, name);
        if (!getline(fin, name)) break; //Break if no more lines
    }
    
    DoublyLinkedList line;

    int lineSize = 0; // Size of line

    cout << "Store opens:" << endl; // The store's open and five customers are in line.
    for (int i = 0; i < 5; i++)
    {
        int randomN = rand() % names.size();
        cout << setw(W10) << names[randomN] << " joins the line" << endl;
        line.push_back(names[randomN]);
        lineSize++;
    }
    line.print();

    int timeSteps = 20; // Timesteps during simulation

    for (int i = 1; i < timeSteps; i++)
    {
        cout << setw(10) << "Time Step #" << i + 1 << endl;
    }
    
    fin.close();

    
    // 40 % probability of Event A happening:
    //int prob = rand() % 100 + 1  // returns random number 1-100
    //if (prob <= 40) 
    //{
    // perform Event A
    //}

    return 0;
}