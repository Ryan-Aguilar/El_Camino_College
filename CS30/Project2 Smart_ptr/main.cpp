#include <iostream>
#include <cassert>
#include <map>
#include "Source.cpp"
using namespace std;



int main()
{
	//smart_ptr <int> s1(new int{ 20 });
	//smart_ptr <int> s2(s1);

	//assert(s1.ref_count() == 2); // making sure s1 has 2 references.
	//assert(s2.ref_count() == 2); // making sure s2 has two references.


 //   int* raw = new int{ 11 };

	//smart_ptr <int> s3(raw);

 //   assert(s3.ref_count() == 1);
 //   assert(*s3 == 11);

 //   smart_ptr <int> s4;


 //   s4 = s1; // testing the assignment operator.

 //   assert(s4.ref_count() == 3);
 //   assert(s1.ref_count() == 3);

 //   s4 = s3;

 //   assert(s3.ref_count() == 2); 
 //   
 //   s4 = s1;


 //   assert(s3.ref_count() == 1);// making sure the reference does decrement

 //   s4.clone();

 //   assert(s1.ref_count() == 2);
 //   assert(s4.ref_count() == 1);


 //   try
 //   {
	//    smart_ptr <int> s5;
 //       *s5; //this is to test the dereference operator

 //   }
 //   catch(null_ptr_exception w) // testing the nullptrexception 
 //   {
 //       cerr << w.what() << endl;
 //   }
 //   try
 //   {
 //       smart_ptr <string> s6;
 //       s6->empty(); // trying to test the arrow operator
 //   }
 //   catch (null_ptr_exception a) // testing the nullptrexception class with the arrow operator
 //   {
 //       cerr << a.what() << endl;
 //   }


 //   smart_ptr <int> s10(new int{ 45 });
 //   smart_ptr <int> s11;

 //   s11 = std::move(s10);

 //   assert(*s11 == 45);
 //   assert(s11.ref_count() == 1);

 //   cout << "the move assignment operator works" << endl;

 //   if (s10.ref_count() == 0)
 //   {
 //       cout << "the s10 move assignment operator was indeed at nullptr" << endl;
 //   }
 //   else
 //   {
 //       cout << "something hapened" << endl;
 //   }



	//---------------BELOW IS PROFESSOR RUSSELL TEST CASE-----------------------



    //int* p{ new int { 42 } };
    //smart_ptr<int> sp1{ p };

    //cout << "Ref count is " << sp1.ref_count() << endl;	// Ref Count is 1
    //{
    //    smart_ptr<int> sp2{ sp1 };
    //    cout << "Ref count is " << sp1.ref_count() << endl;	// Ref Count is 2
    //    cout << "Ref count is " << sp2.ref_count() << endl;	// Ref Count is 2
    //}
    //cout << "Ref count is " << sp1.ref_count() << endl;	// Ref Count is 1

    //smart_ptr<int> sp3;

    //cout << "Ref count is " << sp3.ref_count() << endl;	// Ref Count is 0

    //sp3 = sp1;

    //cout << "Ref count is " << sp1.ref_count() << endl;	// Ref Count is 2
    //cout << "Ref count is " << sp3.ref_count() << endl;	// Ref Count is 2

    //smart_ptr<int> sp4 = std::move(sp1);

    //cout << *sp4 << " " << *sp3 << endl;        // prints 42 42
    //cout << *sp1 << endl;                       // throws null_ptr_exception



    struct Point { int x = 2; int y = -5; };
        smart_ptr<Point> sp{ new Point };
        cout << sp->x << " " << sp->y << endl;   // prints 2 -5

    smart_ptr<double> dsp1{ new double {3.14} };
    smart_ptr<double> dsp2, dsp3;

    dsp3 = dsp2 = dsp1;

    cout << dsp1.ref_count() << " " << dsp2.ref_count() << " " << dsp3.ref_count() << endl;
    // prints 3 3 3
    cout << *dsp1 << " " << *dsp2 << " " << *dsp3 << endl;
    // prints 3.14 3.14 3.14

    dsp1.clone();        // returns true

    cout << dsp1.ref_count() << " " << dsp2.ref_count() << " " << dsp3.ref_count() << endl;
    // prints 1 2 2
    cout << *dsp1 << " " << *dsp2 << " " << *dsp3 << endl;
    // prints 3.14 3.14 3.14
    

}