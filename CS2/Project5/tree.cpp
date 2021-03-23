#include <iostream>
#include <string>
#include <cassert>
using namespace std;

typedef string ItemType;

struct WordNode {
    ItemType m_data;
    WordNode* m_left;
    WordNode* m_right;
    int count;
    // You may add additional data members and member functions in WordNode
};

class WordTree {

private:
    WordNode* root;
    //---------------------------------> student made function below
    void addingItem(WordNode* &ptr, ItemType item)
    {

        if (ptr == nullptr)
        {
            ptr = new WordNode{ item, nullptr,nullptr, 1};
            return;
        }

        if (ptr->m_data == item)
        {
            (ptr ->count)++;
            return;
        }

        if (item < ptr->m_data)
        {
            addingItem(ptr->m_left, item);
        }

        else if (item > ptr->m_data)
        {
            addingItem(ptr->m_right, item);
        }

    }

    void cleanUp(WordNode*& seed) {
        if (seed == nullptr)
        {
            return;
        }
        cleanUp(seed->m_left);
        cleanUp(seed->m_right);
        delete seed;
        seed = nullptr;
    }

    void Copy(WordNode* &newtree, WordNode* Originaltree) {
        if (Originaltree == nullptr)
        {
            return;
        }
        
        newtree = new WordNode{ Originaltree->m_data , nullptr,nullptr, Originaltree->count };
        Copy(newtree->m_left,Originaltree->m_left );
        Copy(newtree->m_right, Originaltree->m_right);
        
    }

    int traverseTree(WordNode* traverse) const
    {
        if (traverse == nullptr)
        {
            return 0;
        }
        
       return traverseTree(traverse->m_left) + 1 + traverseTree(traverse->m_right);
    }

    int TallyUp(WordNode* counting) const{
        if (counting == nullptr)
        {
            return 0;
        }
        

       return TallyUp(counting->m_left) + counting->count + TallyUp(counting->m_right);
    }

    void PrintingTree(ostream& out, WordNode* printptr) const {
        if (printptr == nullptr)
        {
            return;
        }

        PrintingTree(out, printptr->m_left);
        out << printptr->m_data << " " << printptr->count << endl;
        PrintingTree(out, printptr->m_right);
    }

public:

    // default constructor            
    WordTree() : root(nullptr) { };

    // copy constructor
    WordTree(const WordTree& rhs) {
        Copy(root, rhs.root);
       
    }

    // assignment operator
    const WordTree& operator=(const WordTree& rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        cleanUp(root); // we call the cleanup function because the code can function without it, but it will have memory leaks. in the long run we will run out of stack.
        Copy(root, rhs.root);
        return *this;
    }



    // Inserts v into the WordTree    
    void add(ItemType v)
    {
       addingItem(root, v);
    }

    // Returns the number of distince words / nodes   
    int distinctWords() const {
        
        return traverseTree(root);
        
    }

    // Returns the total number of words inserted, including duplicate
    // values    
    int totalWords() const
    {
        return TallyUp(root);
        
    }

    // Prints the LinkedList 
    friend ostream& operator<<(ostream& out, const WordTree& rhs)
    {
        rhs.PrintingTree(out, rhs.root);
        return out;
    }

    // Destroys all the dynamically allocated memory
    // in the tree.
    ~WordTree()
    { 
        cleanUp(root);
    }
};

int main()
{

    //WordTree t;
    //WordTree t2;

    //t2.add("Mario");
    //t2.add("Ryan");

    //t = t2;
    //assert(t2.distinctWords() == 2);
    //assert(t2.totalWords() == 2);

    //cout << t << endl;
    //cout << t2 << endl;
    
    WordTree t;

    t.add("Walter");
    t.add("WALTER");
    
    WordTree t2;

    t = t2;

    cout << t;



    /*WordTree hasStuf;
    WordTree t2;*/

   /* hasStuf.add("Skyler");
    hasStuf.add("Joanne");
    hasStuf.add("Joanne");
    hasStuf.add("Russell");*/
    /*t.add("Walter");
    t.add("walter");
    t.add("Hank");
    t.add("Gus");
    t.add("WALTER");
    t.add("Gus");*/


    /*t2 = hasStuf;

    assert(t2.distinctWords() == 0);
    assert(t2.totalWords() == 0);*/
   /* cout << t2.distinctWords() << endl;
    cout << t2.totalWords() << endl;*/
    /*WordTree t;

    t.add("Skyler");
    t.add("Walter");
    t.add("Walter");
    t.add("Walter");*/

    /*cout << t.distinctWords() << endl;*/


    /*assert(t.distinctWords() == 2);
    assert(t.totalWords() == 4);*/
}

/*

check list:
finished add function
finished destructor
finished copy constructor
finished assignment operator
finished distinced words function
finsihed printing


notes for assignment operator order it actually processes
1. check for alias ( making sure that the object is not deleted before copied if both pointers point to the same thing.)
EXAMPLE: if t1=t2 and they both point to the same object, then t1 is an alias for t2. an alias is another name for. in c++ it means both pointers 
point to the same object. in this case t1 is that alias.

not an alias if t1 = a,b,c and t2 = a,b,c. they are not alias' for they do not have the same memory adress. we never made the statement that t1=t2 
in this example. contents are the same, but the adresses are different.




*/