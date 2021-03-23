#include "Map.h"       // Create an empty map (i.e., one with no key/value pairs)



Map::Map() : head(nullptr) {
    /*std::cout << "constructed" << std::endl;*/
}


Map::Map(const Map& rhs)
{
    Copy(head, rhs.head);
}

void Map::Copy(Node* &Originaltree, const Node* newtree) 
{
    if (newtree == nullptr)
    {
        return;
    }

    Originaltree = new Node{ newtree->key ,newtree->value, nullptr,nullptr };
    Copy(Originaltree->left, newtree->left);
    Copy(Originaltree->right, newtree->right);
}

const Map& Map:: operator =(const Map& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
   
    clearUp(head);
    Copy(head, rhs.head);
    return *this;
}


int Map::numChildren(Node* parent) 
{
    if (parent == nullptr)
    {
        return 0;
    }

    return numChildren(parent->left) + 1 + numChildren(parent->right);
}


bool Map::getThreeParam(int& i, KeyType& key, ValueType& value, Node* temp, int current_Index) const {
    
    if (temp == nullptr) 
    {
        return false;
    }
    
    int r = 3;
    int j = 5;

    
    key = temp->key;
    value = temp->value;
    
    if (current_Index == i)
    {
        return true;
    }
    current_Index += 1;
    getThreeParam(i, key, value, temp->left, current_Index);
    getThreeParam(i, key, value, temp->right, current_Index);
    return true;
}

int Map::count(Node* seed) const {
    if (seed == nullptr) {
        return 0;
    }

    return count(seed->left) + 1 + count(seed->right);
}

//
Map :: ~Map() {
    clearUp(head);
}


void Map::clearUp(Node*& root) {
    if (root == nullptr) {
        return;
    }

    clearUp(root->left);
    clearUp(root->right);
    delete root;
    root = nullptr;

}

    // Return true if the map is empty, otherwise false.
bool Map::empty() const {
    if (head == nullptr) {
        return true;
    }
    else {
        return false;
    }
}

// Return the number of key/value pairs in the map.
// we can use recursion to traverse through the tree.
int Map::size() const {

    return count(head);
}


bool Map::insert(const KeyType& key, const ValueType& value) {

    /*
    Look back at this algorithm because i am looking at it in terms of numbers. if its numbers then I would think
    that if it is less, then I have to put it to the left. If what i am inseting is greater than what is allready there, then it goes to the right.
    I would like to think though that in this case that i dont have that occuring here, but I am not sure. maybe this wont make sense,
    but i have to type this down or i forget 7/23/21
    */



    // stopped here because I think I have to make another function.

    // It tuns out i did not have to make another function. this should be enough. 

    // get this checked below

    // we can do this recurseively, but at a cost of run time that can lead into exponential runtime. The program
    // can be solving problems it had already solved. well yes we can do dynamic programming to store then in a vector
    // so it can access data it needs, but it wiil still use a bit of memory and I believe there is a way to get logn 
    // runtime. why dont we use a while loop that helps us search only half of the tree so we can see what nodes child is actually
    // free so we can insert. 


    // base case is added. 

    if (head == nullptr) {
        Node* newNode = new Node;
        newNode->key = key;
        newNode->value = value;
        newNode->right = nullptr;
        newNode->left = nullptr;
        head = newNode;
        return true;
    }


    Node* current = head;
    Node* previous = head;
    int position;

    while (current != nullptr) {

        if (key < current->key) {
            previous = current;
            current = current->left;
            position = 0;

        }
        else if (key > current->key) {
            previous = current;
            current = current->right;
            position = 1;
        }
        else {
            return false;
        }
    }

    if (current == nullptr) {

        if (position == 1) {
            previous->right = new Node{ key,value,nullptr,nullptr };
            return true;
        }
        else {
            previous->left = new Node{ key,value,nullptr,nullptr };
            return true;
        }
    }

    return false;
}

// If key is not equal to any key currently in the map, and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that either the key is already in the map).

bool Map::update(const KeyType& key, const ValueType& value) {
    
    Node* traverse = head;

    if (traverse == nullptr) {
        return false;
    }

    while (traverse != nullptr) {
        
        if (key == traverse->key) {
            if (value == traverse->value)
            {
                return false;
            }
            traverse->value = value;
            return true;
        }

        else if (key < traverse->key) {
            traverse = traverse->left;
        }

        else {
            traverse = traverse->right;
        }
    }
    
    return false;
}

// If key is equal to a key currently in the map, then make that key no
// longer map to the value it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// Otherwise, make no change to the map and return false.

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {

    if (contains(key))
    {
        update(key, value);
    }
    else
    {
        insert(key, value);
    }
    return true;
        
}

    

// If key is equal to a key currently in the map, then make that key no
// longer map to the value it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// If key is not equal to any key currently in the map then add it and 
// return true. In fact this function always returns true.

bool Map::erase(const KeyType& key) {

    /*
    WE ARE NOT DONE. THERE IS ONE MORE THING TO DO AND THAT IS TO TAKE CARE OF A SITUTION OF WHAT IF HE DELETES SOMETHING
    FROM THE MIDDLE. THEN WE NEED TO REWIRE IT AND NOT HAVE MEMORY LEAKS.

    SO GO AND FIX IT RYAN.

    */

    if (head == nullptr)
    {
        return false;
    }


    Node* Current = head;
    Node* Previous = head; // we have a previous pointer beacuse we delete the node current when the key is found. so previous will
                           // work with position so if knows which branch to make nullptr so we do not have a dangaling pointer
    int position = -1; // we will have a variable that will contain 1 or 0 so one means it went to the right and 0 means left

    while (Current != nullptr) {

        if (key < Current->key)
        {
            Previous = Current;
            Current = Current->left;

        }

        else if (key > Current->key)
        {
            Previous = Current;
            Current = Current->right;

        }

        else
        {
            break;
            /*if (Current->left == nullptr && Current->right == nullptr) {
                delete Current;
                Current = nullptr;
                head = nullptr;
                return true;
            }
            delete Current;
            if (position == 1) {
                Previous->right = nullptr;
            }
            if (position == 0) {
                Previous->left = nullptr;
            }*/
            // this is for testing. 
            /*std::cout << "the following was deleted: " << key << std::endl;
            return true;*/
        }




    }

    // continue to work around.
    if (Current == nullptr)
    {
        return false;
    }

    // this is where we start handling the deletion.

    if (Current->numChildren() == 0) // we use current to check the nodes and we use current to change the BST(Binary Search Tree)
    {
        if (Current == head)  // this situation is if the Tree only has one node with no children.
        {
            head = nullptr;
        }
        else
        {
            if (Previous->left == Current) // this is if the node is in the left subtree
            {
                Previous->left = nullptr; // if we know this is the node to erase, then we can set it to nullptr
            }

            else if (Previous->right == Current) // this is if the node is in the right subtree
            {
                Previous->right = nullptr; // if we know this is the node to erase, then we can set it to nullptr
            }

        }
        
    }
    else if (Current->numChildren() == 1) // this is where the node we are erasing has one child.
    {
        Node* child = nullptr; // this wll have the adress of the children so we can have previous connect to it.
        if (Current->left != nullptr) // this is where we begin to store the nodes child's adress and save that to the child pointer
        {
            child = Current->left; //if child is found on the left 
        }
        else
        {
            child = Current->right; // if child is found on the right
        }

        if (Current == head) // this is 
        {
            head = child;
        }
        else
        {
            if (Previous->left == Current) // this is when we use child to connect to previous because we do not want any memory leaks.
            {
                Previous->left = child;
            }
            else
            {
                Previous->right = child;
            }
        }
        delete Current; // we delete current here because we are trying to remove it from the map.


    }
    else if (Current->numChildren() == 2)// this is when there are two children
    {
        Node* Traverse = Current;
        Traverse = Current->right;

        while (Traverse->left != nullptr)
        {
            Traverse = Traverse->left;
        }

        KeyType newkey = Traverse->key;
        ValueType newvalue = Traverse->value;

        erase (Traverse->key);
        Current->key = newkey;
        Current->value = newvalue;
    }


    return true;
}




// If key is equal to a key currently in the map, remove the key/value
// pair with that key from the map and return true.  Otherwise, make
// no change to the map and return false.

bool Map::contains(const KeyType& key) const {


    Node* current = head;

    while (current != nullptr) {
        
        if (key < current->key) 
        {
            current = current->left;
        }
        else if (key > current->key) 
        {
            current = current->right;
        }
        else 
        {
            return true;
        }
    }

    return false;
}
// Return true if key is equal to a key currently in the map, otherwise
// false.

bool Map::get(const KeyType& key, ValueType& value) const {

    Node* current = head;

    while (current != nullptr) {
        if (key < current->key) {
            current = current->left;
        }

        if (key > current->key) {
            current = current->right;
        }

        if (key == current->key) {
            value = current->value;
            return true;
        }
    }

    return false;
}
// If key is equal to a key currently in the map, set value to the
// value in the map that that key maps to, and return true. Otherwise,
// make no change to the value parameter of this function and return
// false.

bool Map::get(int i, KeyType& key, ValueType& value) const {
    int current_index = 0;
    if (i >= 0 && i < size()) {

        return getThreeParam(i, key, value, head, current_index);
    }
    return false;
}
// If 0 <= i < size(), copy into the key and value parameters the
// key and value of one of the key/value pairs in the map and return
// true.  Otherwise, leave the key and value parameters unchanged and
// return false.  (See below for details about this function.) m1(m2)
void Map::swap(Map& other) {
    Node* temp = head;
    head = other.head;
    other.head = temp;



    /*
    why bother copying all the information in a new dynamicly allocated memory and have more work to do when we can just
    swap the adresses.

    get this checked out.
                           */

}


void subtract(const Map& m1, const Map& m2, Map& result)
{
    Map temp;

    

    KeyType k;
    ValueType v;

    KeyType k2;
    ValueType v2;


    for (int i = 0; i < m1.size(); i++)
    {
        m1.get(i, k, v);
        temp.insert(k, v);
    }


    for (int i = 0; i < m2.size(); i++)
    {
        k2 = '/0';
        v2 = 0;

        m2.get(i, k2, v2);
        if (temp.contains(k2))
        {
            temp.erase(k2);
            
        }
        else
        {
            continue;
        }
    }

    result = temp;


}


bool combine(const Map& m1, const Map& m2, Map& result)
{
    /*
    WE CAN TRAVERSE THROUGH M1 AND INSERT UNTIL THERE IS NOTHING LEFT TO INSERT.

    WE ALSO DO THE SAME FOR M2

    WHERE WE INSERT ALL THESE NODES FROM M1 AND M2 IS GOING TO BE INSERTED TO THE RESULTS TREE MAP.

    WE RETURN TRUE IF THERE IS A NODE THAT LIES IN BOTH TREES, WE ADD IT ONCE IN RESULT AND CONTINUE ON.

    THIS WILL BE USING THE INSERT FUNCTION FROM THE MAP CLASS.

    THEN WE DETERMINE ITS TRUE AND FALSE CASES After.

    */
    Map temp;


    KeyType k;
    ValueType v;

    KeyType k2;
    ValueType v2;

    bool flag = true;


    // thoughts we can use a for loop with an index to traverse through a map object and a function.
    // that doesnt seem to be working out quite yet.
    // problem i also see is that this is very specific and i need this to be general.
    for (int count = 0; count < m1.size(); count++)
    {
        m1.get(count, k, v);
        temp.insert(k, v);
        /*
        using two param get allows us to pass in a value in the parameter and if the key is found in the map, then the value
        in the parameter is changed to the value in the map.
        */
    }

    for (int count = 0; count < m2.size(); count++)
    {
        m2.get(count, k2, v2);

        if (!temp.insert(k2, v2))
        {
            v = v2;
            temp.get(k2, v2);
                if (v != v2)
                {
                    temp.erase(k2);
                    flag = false;
                }
                else
                {
                    continue;
                }
        }

    }

    /*
    THE APPROACH IS TO USE THE FOR LOOP AND HAVE IT INSERT FOR M1 AND M2 INTO THE RESULTS TREE. IF THE FUNCTION RETURNS FALSE
    THEN WE CAN USE THE GET WITH TWO PARAMETERS AND COMPARE VALUES. IF THE VALUES ARE NOT THE SAME THEN WE HAVE TO ERASE THE NODE
    THAT WAS JUST INSERTED INTO RESULTS. IF THE VALUES ARE THE SAME THEN WE LEAVE NODE IN RESULTS UNTOUCHED. WE WILL HAVE TWO INT
    VARIABLES AND THOSE I CAN USE TO DETERMINE WHETHER THIS FUNCTION RETURNS TRUE OR FALSE.


    so right now, if insert returns false, you know that you have 2 of the same key
    case1: same key, same value (do nothing)
    case 2: same key, DIFF value (since we added this key already from inserting everything in map1, we must erase that key (according to spec do not include any key in tree if maps have same key diff val)

    and in case 2 after u remove, u have to find a way to make it so that at the end you will return false

    and then in case 2, after this, u just continue until u have inserted all you should have

    */

    result = temp;
    return flag;
}



// Exchange the contents of this map with the other one.






/*
*
this is old code. please delete. I kept this around just so i can reference back.
if (head == nullptr) {
        head = new Node{ key, value, nullptr,nullptr };
        return true;
    }
    void makeDelete(TreeNode *&tree)
    {
	//This is used to hold the node that will be deleted
  TreeNode *nodeToDelete = tree;
  
  TreeNode* attachPoint;
  
  if(tree->right == NULL){
  	tree = tree->left;
  }
  else if(tree->left == NULL){
  	tree = tree->right;
  }
  else{
  	//the node to be deleted has two children
    //move to right subtree
    attachPoint = tree->right;
    
    //locate the smallest node in the right subtree by moving as far to the left as possible
    while(attachPoint->left != NULL)
    	attachPoint = attachPoint->left;
      
    //attach the left subtree of the original tree as the left subtree of the smallest node in the right subtree
    attachPoint->left = tree->left;
    
    //replace the original tree with its right subtree
    tree = tree->right
  }
  
  //delete root of the original tree
  delete nodeToDelete;

}

    if (head->left == nullptr && head->key != key ) {
        Node* Create = new Node{ key, value, nullptr,nullptr };
        return true;
    }


    if (head->right == nullptr && head->key!= key) {
        Node* Create = new Node{ key, value, nullptr,nullptr };
        return true;
    }
    return false;

    
    
    insert or update
    if (contains(key))
    {
        update(key, value);
    }
    else
    {
        insert(key, value);
    }
    return true;





*/


