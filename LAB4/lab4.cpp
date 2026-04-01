#include <iostream>
#include <string>

using namespace std;

struct Package {
    string packageID;
    string destinationCity;
    int dimensions[3];
};

struct Node {
    Package p;
    Node* next;
};

struct Courier {
    string courierName;
    string vehicleType;
};

class PackageStack {
private:
    Node* top;

public:
    PackageStack() { top = nullptr; }

    void push(Package newPkg) {
        Node* newNode = new Node;
        newNode->p = newPkg;
        newNode->next = top;
        top = newNode;
    }

    Package pop() {
        Node* temp = top;
        Package pkg = temp->p;
        top = top->next;
        delete temp;
        return pkg;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    void display() {
        if (isEmpty()) return;
        Node* curr = top;
        while (curr != nullptr) {
            cout << curr->p.packageID << " -> " << curr->p.destinationCity << endl;
            curr = curr->next;
        }
    }
};

class CourierQueue {
private:
    static const int SIZE = 5;
    Courier items[SIZE];
    int front, rear, count;

public:
    CourierQueue() {
        front = 0;
        rear = -1;
        count = 0;
    }

    void enqueue(Courier c) {
        if (count == SIZE) return;
        rear = (rear + 1) % SIZE;
        items[rear] = c;
        count++;
    }

    Courier dequeue() {
        Courier c = items[front];
        front = (front + 1) % SIZE;
        count--;
        return c;
    }

    bool isEmpty() {
        return count == 0;
    }

    void display() {
        for (int i = 0; i < count; i++) {
            int idx = (front + i) % SIZE;
            cout << items[idx].courierName << " [" << items[idx].vehicleType << "]" << endl;
        }
    }
};

int main() {
    PackageStack stack;
    CourierQueue queue;
    int choice;

    while (true) {
        cout << "\n1. Arrive, 2. Register, 3. Dispatch, 4. Display, 5. Exit: ";
        cin >> choice;

        if (choice == 1) {
            Package p;
            cin >> p.packageID >> p.destinationCity;
            cin >> p.dimensions[0] >> p.dimensions[1] >> p.dimensions[2];
            stack.push(p);
        }
        else if (choice == 2) {
            Courier c;
            cin >> c.courierName >> c.vehicleType;
            queue.enqueue(c);
        }
        else if (choice == 3) {
            if (!stack.isEmpty() && !queue.isEmpty()) {
                Package p = stack.pop();
                Courier c = queue.dequeue();
                cout << "Dispatched: " << p.packageID << " by " << c.courierName << endl;
            }
        }
        else if (choice == 4) {
            stack.display();
            cout << "---" << endl;
            queue.display();
        }
        else if (choice == 5) {
            break;
        }
    }
    return 0;
}
