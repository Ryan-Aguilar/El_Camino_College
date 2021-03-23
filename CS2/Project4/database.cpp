#include<iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>
using std :: string;
const int MAX_MARTIANS = 100;

struct Martian {
    std::string fname_; // this variable contains the first name of the matians name.
    std::string lname_; // this variable contains the last name of the matians name.
    std::string SSN_; // this variable contains the social security of the martians.
    Martian(std::string fn, std::string ln, std::string ssn) // this is the constructor of the Martians class.
        : fname_(fn), lname_(ln), SSN_(ssn) { }

    // you may add other things to the structure	
};

enum class Criteria { first, last, ssn };

class MartianDatabase {
public:
    // creates a new empty Martian Database initialized with the
    // contents of filename.
    MartianDatabase(std::istream& infile)
    {
        counter = 0;
        /*m_unsorted[] = new Martian * [MAX_MARTIANS];*/
        if (infile.fail())
        {
            std::cout << "Bad file!" << std::endl;
            exit(0);
        }


        std::string Fn;
        std::string Ln;
        std::string Social_n;
        

        while (!infile.eof() && counter < MAX_MARTIANS) // we add the scond condition because of the fact of we do not want this program to try to inject more information when
            // it has reached maximum ocupancy.
        {
            infile >> Fn;
            infile >> Ln;
            infile >> Social_n; 
            
            Martian* M = new Martian(Fn,Ln,Social_n);
            m_unsorted[counter] = M;
            m_fname[counter] = M;
            m_lname[counter] = M;
            m_ssn[counter] = M;
            //std:: cout << m_unsorted[counter]->fname_ << std:: endl;
            //std::cout << m_unsorted[counter]->lname_ << std::endl;
            //std::cout << m_unsorted[counter]->SSN_ << std::endl;
            //std::cout << Fn << std:: endl;
            //std::cout << Ln << std::endl;
            //std::cout << Social_n << std::endl;

            counter++; // this is to keep track of the objects and we can use this index to keep track in the array when we begin to traverse through.

        }
    }

    // add item m to database, return true if successfully added.
    bool addMartian(const Martian& m) 
    {
        // the runtime is constant which is written as O(1). the reason for this is there is no for loop and there is no exponential increase or decrease.
        // the work process in this case is linear and consistent.
        if (isFull())
        {
            return false;
        }
        else
        {
            m_unsorted[counter] = new Martian(m.fname_, m.lname_, m.SSN_); // we do not override the information of satish because the index value is 4. we see 4 ends at index 3 of the array, but the index has 4 as a value. so it goes ahead 1.
            m_fname[counter] = m_unsorted[counter]; // if we do the ampersign, we give the adress of the pointers current adress. there is a operato precidence.
            m_lname[counter] = m_unsorted[counter]; // hence we cannot get the adress of a raw number or variable.
            m_ssn[counter] = m_unsorted[counter];
            counter++;
            // we add the parameter of because we are treating m as a object. so we hve to add all its parameters that the constuctor has.
            /*Martian** ptr = &(m_unsorted[counter]);
            std::cout << "here we are" << std::endl;*/
            return true;
        }
    }

    // delete item with the ssn in database, return true if successfully 
    // deleted.
    bool deleteMartian(std::string ssn) // I still ahve to move over all the elements in the othe thee arrays so they coordinate with the unsorted array.
    {
        // runtime is bigO(n + n) = O(2n) = O(n) because the first two for loops actually complete one entire for loop. 
        // in most cases it would be bigO(n^2), but here ultimately it would be be bigO(n).
        // n represents the length of the m_unsorted array.
        for (int i = 0; i < counter; i++) // we use the counter so we can mess with elements that is not null ptr
        {
            if ( m_unsorted[i]->SSN_ == ssn)
            {
                delete m_unsorted[i]; // we are deleting the martian object found
                
                int g;
                for ( g = i; g < counter - 1; g++)
                {
                    m_unsorted[g] = m_unsorted[g + 1];
                }
                m_unsorted[g] = nullptr;
               
                counter--; // we thew in this counter decerement because when testing the delete function, we hadd an issue of dereferenceing the nullptr. so if we delete in all the arrays, we also have to decrement the counter variable.
                for (int i = 0; i < counter; i++)
                {       
                   m_fname[i] = m_lname[i] = m_ssn[i] =  m_unsorted[i]; // here we do not want to delete the objects again because we will crash. rather let us copy the unsorted array into each other array and no everything is the same as the unsorted array.
                }
                return true;
            }

        }
        return false;
    }

    // return true if the database does not contain any items, false
    // otherwise.
    bool isEmpty()
    {
        /*for (int i = 0; i < MAX_MARTIANS; i++)
        {
            if (m_unsorted[i] == nullptr)
            {
                return true;
            }
        }*/

        
        return m_unsorted[0] == nullptr; //  here we are evlauating if the array is empty or not and returning the outcom of that statement.
    }

    // return true if the database is at its maximum storage, false
    // otherwise.
    bool isFull()
    {
        return m_unsorted[MAX_MARTIANS - 1] != nullptr; // similar to the is empty function. we are returning the outcome of the statement and if the last element in the array is not nullptr, we say it is occupied and there is no more space
    }

    // prints the list of Martians, sorted by last name, sorted
    // by first name and by MSSN.
    void printMartians(Criteria type) {
        // the runtime of this is O(nlgn = n) = nlgn because the the stl here uses either quick or merege sot and the two sorts have the run time of nlgn. .
        if (type == Criteria::last) {
            std::sort(m_lname, m_lname + counter, [](Martian* m1, Martian* m2) { return m1->lname_ < m2->lname_; }); // lambda expression. this is where we declare a function inside the function call and we do this because it can save us a little more work than creating a function. we pass in the same parameters as a sort would need, but gain we create the function in the call. same goes for each other sort calls.
            std::cout << "----- Sorted by Last Name -----" << std::endl; 
            std::cout << "  First Name Last Name      MSSN" << std::endl;

            for (int i = 0; i < counter; i++)
            {
                std::cout << std::setw(1) << std::right << i+1 << std::setw(11) << std::right << m_lname[i]->fname_ << " ";
                std::cout << std::setw(9) << std:: right << m_lname[i]->lname_ << " ";
                std::cout << std::setw(9) << std::right << m_lname[i]->SSN_ << std::endl;
            }
            std::cout << std::endl;
        }
        else if (type == Criteria::first) {
            std::sort(m_fname, m_fname + counter, [](Martian* m1, Martian* m2) { return m1->fname_ < m2->fname_; }); // lambda expression
            std::cout << "----- Sorted by First Name -----" << std::endl;
            std::cout << "  First Name Last Name      MSSN" << std::endl;

            for (int i = 0; i < counter; i++)
            {
                std::cout << std::setw(1) << std::right << i + 1 << std::setw(11) << std::right << m_fname[i]->fname_ << " ";
                std::cout << std::setw(9) << std::right << m_fname[i]->lname_ << " ";
                std::cout << std::setw(9) << std::right << m_fname[i]->SSN_ << std::endl;
            }
            std::cout << std::endl;
        }
        else if (type == Criteria::ssn) {
            std::sort(m_ssn, m_ssn + counter, [](Martian* m1, Martian* m2) { return m1->SSN_ < m2->SSN_; }); // lambda expression
            std::cout << "----- Sorted by Mars SSN -----" << std::endl;
            std::cout << "  First Name Last Name      MSSN" << std::endl;
            for (int i = 0; i < counter; i++)
            {
                std::cout << std::setw(1) << std::right << i + 1 << std::setw(11) << std::right << m_ssn[i]->fname_ << " ";
                std::cout << std::setw(9) << std::right << m_ssn[i]->lname_ << " ";
                std::cout << std::setw(9) << std::right << m_ssn[i]->SSN_ << std::endl;
            }
            std::cout << std::endl;
        }
    }

    // deletes all the dynamically created memory
    // Note: we are only going up to counter because counter is actually keeping track of how many martian objects are created. if we try to delete a nullptr, then the program crashes.
    // that will happen if we did not have the counter and we used 10 out of the 100 elements, then when the program goes to index 11, we access the nullptr and try to delete it. our program will crash. 
    // if we have the counter, counter goes only up to 10 and not further because it keeps track of how many objects there are. thus, not rcashing our program.
    ~MartianDatabase() {
        // runtime is O(n)
        for (int i = 0; i < counter; i++)
        {
            delete m_unsorted[i];
        }
    }
private:
    //this is important because these are the arrays we have to use so we can use that information.
    // we are using pointers because it makes modifying infomation easier than to actually copy it and modifying it.
    Martian* m_unsorted[MAX_MARTIANS] = {}; // this array is the array that contains all the information from the file.
    Martian* m_fname[MAX_MARTIANS] = {}; // this array is the array that contains the martians first name.
    Martian* m_lname[MAX_MARTIANS] = {}; // this aray is the array that contains The martians lasts name.
    Martian* m_ssn[MAX_MARTIANS] = {}; // this is the array that contains the matians social security number.
    int counter;
};

int main()
{
    std::string name;
    std::string last;
    std::string social;
    /*Martian X = Martian("Ryan", "Aguilar", "4321");*/
   std:: ifstream infile("C:\\Users\\Ryan Aguilar\\source\\repos\\Project_5\\Infomation.txt");
   MartianDatabase M(infile); // we input a file because we created the variable
   /*M.deleteMartian("3456");*/
   int input;
   bool keepGoing = true;
   while (keepGoing)
   {
       std::cout << " Martian Database" << std::endl;
       std::cout << std::endl;
       std::cout << " 1. Add a martian" << std::endl;
       std::cout << " 2. Delete a martian" << std::endl;
       std::cout << " 3. Print by first name" << std::endl;
       std::cout << " 4. Print by last name" << std::endl;
       std::cout << " 5. Print by SSN" << std::endl;
       std::cout << " 6. Quit" << std::endl;
       std::cout << " ----------------------" <<std::endl;
       std::cout << " > ";
       std::cin >> input;

       if (input == 1)
       {

          /* std::string name;
           std::string last;
           std::string social;*/
           std::cout << " Please enter a first name: ";
           std::cin >> name;
           std::cout << " Please enter a last name: ";
           std::cin >> last;
           std::cout << " Please enter a SSN: ";
           std::cin >> social;
           Martian X = Martian(name, last, social);
           M.addMartian(X);
       }
       else if (input == 2) 
       {
           std::string Social_Security;
           std::cout << " Please enter a SSN: ";
           std::cin >> Social_Security;
           if (!M.deleteMartian(Social_Security)) // fix if statement
           {
               std::cout << " SSN not found. " << std::endl;
           }
       }
       else if (input == 3)
       {
           M.printMartians(Criteria::first);
       }
       else if (input == 4) 
       {
           M.printMartians(Criteria::last);
       }
       else if (input == 5)
       {
           M.printMartians(Criteria::ssn);
       }
       else if (input == 6)
       {
           break;
       }
       else {
           std::cout << " Please enter a valid input ranging from 1 to 6 " << std::endl;
       }
      
   }
   //M.printMartians(Criteria :: ssn);
   //std::cout << " --------------------------------------------------------------------------- " << std::endl;
   //M.printMartians(Criteria::first);

   //M.addMartian(X);

   /*std::cout << "I am adding Ryan" << std::endl;
   M.printMartians(Criteria::ssn);
   std::cout << " --------------------------------------------------------------------------- " << std::endl;
   M.printMartians(Criteria::first);*/
}
//while (infile << name && infile & lname && infile << ssn) { … }
// sort(m_lname, m_lname + counter, [](Martian* m1, Martian* m2) { return m1->lname_ < m2->lname_; });
