#include <iostream>
using namespace std;

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(T val) : data(val), next(nullptr), prev(nullptr) {}
    };

    Node* head;

public:
    DoublyLinkedList() : head(nullptr) {}

    ~DoublyLinkedList() {
        while (head != nullptr) {
            deleteFromStart();
        }
    }

    void insertSorted(T data) {
        Node* newNode = new Node(data);

        if (head == nullptr) {
            head = newNode;
            return;
        }

        if (data < head->data) {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            return;
        }

        Node* temp = head;
        while (temp->next != nullptr && temp->next->data < data) {
            temp = temp->next;
        }

        newNode->next = temp->next;
        if (temp->next != nullptr) {
            temp->next->prev = newNode;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }

    void deleteFromStart() {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }

        Node* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        delete temp;
    }

    void deleteFromEnd() {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }

        Node* temp = head;
        if (temp->next == nullptr) {
            head = nullptr;
            delete temp;
            return;
        }

        while (temp->next != nullptr) {
            temp = temp->next;
        }

        temp->prev->next = nullptr;
        delete temp;
    }

    void deleteByValue(T data) {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }

        if (head->data == data) {
            deleteFromStart();
            return;
        }

        Node* temp = head;
        while (temp != nullptr && temp->data != data) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Node not found.\n";
            return;
        }

        if (temp->next != nullptr) {
            temp->next->prev = temp->prev;
        }
        if (temp->prev != nullptr) {
            temp->prev->next = temp->next;
        }

        delete temp;
    }

    int search(T data) {
        Node* temp = head;
        int position = 1;
        while (temp != nullptr) {
            if (temp->data == data) {
                return position;
            }
            temp = temp->next;
            position++;
        }
        return -1;
    }

    void traverseForward() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    void traverseBackward() {
        if (head == nullptr) return;

        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }

        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->prev;
        }
        cout << endl;
    }

    void menu() {
        int choice;
        T value;

        // Ha   ve Inserted some random values into the list for demonstration
        insertSorted(11);
        insertSorted(9);
        insertSorted(20);

        do {
            cout<< "\n**********************************";
            cout << "\nMenu: \n";
            cout << "1. Insert\n";
            cout << "2. Delete from start\n";
            cout << "3. Delete from end\n";
            cout << "4. Delete by value\n";
            cout << "5. Search\n";
            cout << "6. Traverse Forward\n";
            cout << "7. Traverse Backward\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                insertSorted(value);
                break;
            case 2:
                deleteFromStart();
                break;
            case 3:
                deleteFromEnd();
                break;
            case 4:
                cout << "Enter value to delete: ";
                cin >> value;
                deleteByValue(value);
                break;
            case 5:
                cout << "Enter value to search: ";
                cin >> value;
                int pos;
                pos = search(value);
                if (pos != -1) {
                    cout << "Value found at position: " << pos << endl;
                }
                else {
                    cout << "Value not found\n";
                }
                break;
            case 6:
                traverseForward();
                break;
            case 7:
                traverseBackward();
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 0);
    }
};

int main() {
    DoublyLinkedList<int> list;
    list.menu();
    return 0;
}
