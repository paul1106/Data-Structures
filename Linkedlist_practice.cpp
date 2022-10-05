#include<iostream>
using namespace std;


class LinkedList;

class ListNode{
    friend class LinkedList;

    public:
        ListNode():data(0), next(0){};
        ListNode(int a):data(a), next(0){};
    private:
        int data;
        ListNode *next;
    
};


class LinkedList{
    public:
        LinkedList():first(0){};
        void PrintList();
        void Push_front(int a);
        void Push_back(int a);
        void Push(int a, int n);
        void Delete(int a);
        void Clear();
        void Reverse();
    private:
        ListNode *first;
};


void LinkedList::PrintList() {
    // LinkedList is empty.
    if (first == 0) {
        cout << "List is empty. " << endl;
        return;
    }

    ListNode *current = first;
    while (current != 0) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

void LinkedList::Push_front (int a) {
    ListNode *newNode = new ListNode;
    newNode->data = a;
    newNode->next = first;
    first = newNode;
}

void LinkedList::Push_back (int a) {
    ListNode *newNode = new ListNode(a);

    // if Linkedlist is empty
    if (first == 0) {
        first = newNode;
    }
    else {
        ListNode *current = first;
        while (current->next != 0) {
            current = current->next;
        }
        current->next = newNode;
    }
}


void LinkedList::Push (int a, int n) {
    ListNode *current = first;
    ListNode *Preceding;

    for (int i = 0; i < n - 1; i++) {
        current = current->next;
    }
    
    Preceding = current->next;

    ListNode *newNode = new ListNode;
    newNode->data = a;
    newNode->next = Preceding;
    current->next = newNode;

}


void LinkedList::Clear() {

    while (first != 0) {
        ListNode *current = first;    
        first = first->next;
        delete current;
        current = 0;
    }
}

void LinkedList::Delete(int a) {
    ListNode *current = first;
    ListNode *Previous = 0;
    while (current!= 0) {
        if (current->data == a) {
            break;
        }
        else {
            Previous = current;
            current = current->next;
        }
    }

    
    if (current == 0) {
        cout << "LinkedList dosnt contain this data. " << endl;
    }
    else if (current == first) {
        first = first->next;
        delete current;
        current = 0;
    }
    else {
        Previous->next = current->next;
        delete current;
        current = 0;
    }
}

void LinkedList::Reverse() {
    ListNode *Previous = 0;
    ListNode *current = first;
    ListNode *Preceding = first->next;

    // if there is only one data or none in list
    if (first == 0 || first->next == 0) {
        return;
    }

    while (Preceding != 0) {
        current->next = Previous;
        Previous = current;
        current = Preceding;
        Preceding = Preceding->next;
    }
    current->next = Previous;
    first = current;
}

int main() {

    LinkedList list;     // 建立LinkedList的object
    list.PrintList();    // 目前list是空的
    list.Delete(4);      // list是空的, 沒有4
    list.Push_back(5);   // list: 5
    list.Push_back(3);   // list: 5 3
    list.PrintList();    

    list.Push_front(9);  // list: 9 5 3
    list.PrintList();    // 印出:  9 5 3
    list.Push_back(4);   // list: 9 5 3 4
    list.Delete(9);      // list: 5 3 4
    list.PrintList();    // 印出:  5 3 4
    list.Push_front(8);  // list: 8 5 3 4
    list.PrintList();    // 印出:  8 5 3 4
    list.Reverse();      // list: 4 3 5 8
    list.PrintList();    // 印出:  4 3 5 8
    list.Clear();        // 清空list
    list.PrintList();    // 印出: List is empty.

    return 0;
}