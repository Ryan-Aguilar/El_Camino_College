#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>

template <typename T> // this is the syntax for creating a template class. 
// we nade struct node go in the private section of linked list so we can use the idea of incapsolation.
class LinkedList {

private:

    struct Node {
        T value;
        Node* next;
    };


    void InsertToEnd(T value) {
        Node* Create = new Node;
        Create->value = value;
        Create->next = nullptr;
        if (head == nullptr)
        {
            head = Create;
        }
        else
        {
            Node* Traverse = head;
            while (Traverse->next != nullptr) // While N pointer does not point to a null ptr, we set our pointers to point where the logic intends.
            {
                Traverse = Traverse->next;
            }

            Traverse->next = Create;
        }
    }
    Node* head;

public:

    // default constructor done
    LinkedList() :head(nullptr) {}

    // copy constructor
    LinkedList(const LinkedList& rhs)
    {
        head = nullptr;
        Node* p;

        p = rhs.head;
        while (p != nullptr)
        {
            InsertToEnd(p->value);
            p = p->next;
        }
    }

    // Destroys all the dynamically allocated memory
    // in the list.
    ~LinkedList()
    {
        if (head != nullptr)
        {
            Node* garbage;
            Node* temp;

            temp = head;
            garbage = temp;
            while (garbage != nullptr)
            {
                temp = garbage->next;
                /*std:: cout << garbage->value << endl;*/
                delete garbage;
                garbage = temp;
            }
            head = nullptr;
        }
    }

    // assignment operator
    const LinkedList& operator=(const LinkedList& rhs)
    {
        LinkedList temp(rhs);
        swap(temp);
        return *this;
    }

    // Inserts val at the front of the list
    void insertToFront(const T& val)
    {
        Node* temp = new Node;
        temp->value = val;
        temp->next = head;
        head = temp;
    }

    // Prints the LinkedList
    void printList() const
    {
        Node* p;
        p = head;
        while (p != nullptr)
        {
            std::cout << p->value << " ";
            p = p->next;
        }
        std::cout << std::endl;
    }

    // Sets item to the value at position i in this
    // LinkedList and return true, returns false if 
    // there is no element i
    bool get(int i, T& item) const// here we do not do T i because
    {

        Node* p = head;
        for (int counter = 0; counter < i + 1 && p != nullptr; counter++)
        {
            if (counter == i)
            {
                item = p->value;
                return true;
            }
            p = p->next;
        }
        return false;
    }

    // Reverses the LinkedList
    void reverseList() // we need to see if this actually does what it is suppose to.
    {

        Node* N = head; // This node will play as the original Pointer.
        Node* p = nullptr; // We wan this pointer to point to the previous nodes.
        Node* F = nullptr; // This will keep track of the upcoming nodes.

        while (N != nullptr) // While N pointer does not point to a null ptr, we set our pointers to point where the logic intends.
        {
            F = N->next; // here we are saving next.
            N->next = p; // Here we are reversing the nodes pointer.
            p = N; // we move one spot ahead.
            N = F;
        }
        head = p;

    }
    // Prints the LinkedList in reverse order
    void printReverse() const
    {
        HelperPrintReverse(head);
    }

    void HelperPrintReverse(Node* reverse) const
    {
        if (reverse == nullptr)
        {
            return;
        }

        HelperPrintReverse(reverse->next);

        std::cout << reverse->value << " ";


    }
    // Appends the values of other onto the end of this
    // LinkedList.
    void append(const LinkedList& other)
    {
        std::string item;
        int InitialSize = other.size();
        for (int i = 0; i < InitialSize; i++) {
            other.get(i, item);
            InsertToEnd(item);
        }

    }

    // Exchange the contents of this LinkedList with the other one.
    void swap(LinkedList& other)
    {
        Node* temp = head;
        head = other.head;
        other.head = temp;
    }

    // Returns the number of items in the Linked List.
    int size() const
    {
        Node* p = head;
        int size = 0;
        while (p != nullptr)
        {
            size++;
            p = p->next;
        }
        return size;
    }

};
#endif