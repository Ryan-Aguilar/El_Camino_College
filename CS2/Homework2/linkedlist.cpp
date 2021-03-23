#include <iostream>
#include <string>
#include <cassert>
using namespace std;

using ItemType = string;

struct Node {
    ItemType value;
    Node* next;
};

class LinkedList {

private:
    void InsertToEnd(string value)
    {
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
    LinkedList() : head(nullptr) { }

    // copy constructor
    LinkedList(const LinkedList& rhs)
    {
        head = nullptr;
        Node* p;
        Node* T = head;
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
            Node* garbage = new Node;
            Node* temp = new Node;

            temp = head;
            garbage = temp;
            while (garbage != nullptr)
            {
                temp = garbage->next;
                /*cout << garbage->value << endl;*/
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
    void insertToFront(const ItemType& val)
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
            cout << p->value << " ";
            p = p->next;
        }
        cout << endl;
    }

    // Sets item to the value at position i in this
    // LinkedList and return true, returns false if 
    // there is no element i
    bool get(int i, ItemType& item) const
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
        
        cout << reverse->value << " ";


    }
    // Appends the values of other onto the end of this
    // LinkedList.
    void append(const LinkedList& other) 
    {
        string item;
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



int main()
{
    /*LinkedList ls;


    ls.insertToFront("Jack");
    ls.insertToFront("Germaine");
    ls.insertToFront("Agatha");
    ls.insertToFront("Agnes");

    for (int k = 0; k < ls.size(); k++)
    {
        string x;
        ls.get(k, x);
        cout << x << endl;
    }*/

   /* LinkedList ls;
    ls.insertToFront("George");
    ls.insertToFront("Louise");
    ls.insertToFront("Lionel");
    ls.insertToFront("Helen");

    ls.printList();
    ls.printReverse();*/

    //LinkedList e1;
    //e1.insertToFront("bell");
    //e1.insertToFront("biv");
    //e1.insertToFront("devoe");
    //LinkedList e2;
    //e2.insertToFront("Andre");
    //e2.insertToFront("Big Boi");
    //e1.append(e2);  // adds contents of e2 to the end of e1
    //string s;
    //assert(e1.size() == 5 && e1.get(3, s) && s == "Big Boi");
    //assert(e2.size() == 2 && e2.get(1, s) && s == "Andre");
    //LinkedList e3;
    //e3.insertToFront("Rare Essence");
    //e3.insertToFront("JunkYard");
    //e3.insertToFront("Chuck Brown");
    //e3.append(e3);
    //assert(e3.size() == 6 && e3.get(3, s) && s == "Chuck Brown");

    //LinkedList e1;
    //e1.insertToFront("Sam");
    //e1.insertToFront("Carla");
    //e1.insertToFront("Cliff");
    //e1.insertToFront("Norm");

    //e1.reverseList();  // reverses the contents of e1
    //string s;
    //assert(e1.size() == 4 && e1.get(0, s) && s == "Sam");

    //LinkedList e1;
    //e1.insertToFront("A");
    //e1.insertToFront("B");
    //e1.insertToFront("C");
    //e1.insertToFront("D");
    //LinkedList e2;
    //e2.insertToFront("X");
    //e2.insertToFront("Y");
    //e2.insertToFront("Z");
    //e1.swap(e2);  // exchange contents of e1 and e2
    //string s;
    //assert(e1.size() == 3 && e1.get(0, s) && s == "Z");
    //assert(e2.size() == 4 && e2.get(2, s) && s == "B");

}