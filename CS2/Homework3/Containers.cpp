#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <list>
using namespace std;

// Remove the odd integers from v.
// It is acceptable if the order of the remaining even integers is not
// the same as in the original vector.
void removeOdds(vector<int>& v)
{
	for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
	{
		if (*it % 2 == 1) // this alone is enough to access the element.
		{
			it = v.erase(it);// there is a default erase function in the list stl. so we can use those to do the erase. erase is for singular and arange of elements you want to delete.
			// erase returns the next position of the iterator.
			--it; // this balaces from us skipping 1 extra spot.
		}

	}
}



void removeOdds(list<int>& li)
{

	for (list<int>::iterator it = li.begin(); it != li.end(); ++it)
	{
		if (*it % 2 == 1) // this alone is enough to access the element.
		{
			it = li.erase(it);// there is a default erase function in the list stl. so we can use those to do the erase. erase is for singular and arange of elements you want to delete.
			// erase returns the next position of the iterator.
			--it; // this balaces from us skipping 1 extra spot.
		}

	}
}

vector<int> destroyedOnes3;

class Movie3
{
public:
	Movie3(int r) : m_rating(r) {}
	~Movie3() { destroyedOnes3.push_back(m_rating); }
	int rating() const { return m_rating; }
private:
	int m_rating;
};

// Remove the movies in li with a rating below 50 and destroy them.
// It is acceptable if the order of the remaining movies is not
// the same as in the original list.



//thoughts
/*so we need to know what we have going on in the perameters as it is something i have never seen before.
so we see an astrics which leads me to believe it has something to do with arrays pointers. and it is in the data type for templates syntax.
I see from main that it appears to be an array.

so can this be an array of pointers that point to something?

well we see the movies is actually a class. and the class only contains the raiting data member.

we can think that movies class is an object. if it helps, think of it as a node.

so my best assumption of what i have is an array of pointers that point to movie objects.

I also have an iterator that points to the array as well.

so the iterator traverses through the array and it works like a pointer, so my assumption is that it can use the arrow syntax, but not sure.

I know it works for pointers.

*/

void removeBad(list<Movie3*>& li)
{
	for (list<Movie3*>::iterator it = li.begin(); it != li.end(); ++it)
	{
		if ((*it)->rating() < 50) // here is where i really need to think of the syntax, because I have an iterator that points to an index, that points to a pointer and that pointer
			// points to the movie object that has what we want to delete.  I cannot use brakets with iterators unless its a vector.
			// the iterator is pointing to the container. when we do star next to the iterator, it gets whats inside the container.
			//we can to the arrow after because the *it  boils down to the movie pointer. so since it is a pointer, we can now do the arrow rating().
			// we can do this because m_rating is a private data member. so we do the function because it returns the private data mmber.
		{
			delete (*it);
			it = li.erase(it); // we do it in the erase because we want to delete the element that it points to. when we do that, it also deletes the object.

			it--; // we do this so we do not traverse through the array rapidly.
		}
	}
}


vector<int> destroyedOnes4;

class Movie
{
public:
	Movie(int r) : m_rating(r) {}
	~Movie() { destroyedOnes4.push_back(m_rating); }
	int rating() const { return m_rating; }
private:
	int m_rating;
};

// Remove the movies in v with a rating below 50 and destroy them.
// It is acceptable if the order of the remaining movies is not
// the same as in the original vector.
void removeBad(vector<Movie*>& v)
{
	for (vector<Movie*>::iterator it = v.begin(); it != v.end(); ++it)
	{
		if ((*it)->rating() < 50)
		{
			delete* it; // we delete it because ti points ot the movie object and then we can delete the element because it only deleted the object.
			// so we can follow this up with doing the erase where the iterator is pointing to.
			it = v.erase(it); // we set it to equal the following expressions so we can delete the element. review this all over again.
			//  then we want to do -- so we do not skip any elements.
			--it;
		}
	}
}
void test1()
{
	int a[8] = { 2, 8, 5, 6, 7, 3, 4, 1 };
	list<int> x(a, a + 8);  // construct x from the array
	assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
	removeOdds(x);
	assert(x.size() == 4);
	vector<int> v(x.begin(), x.end());  // construct v from x
	sort(v.begin(), v.end());
	int expect[4] = { 2, 4, 6, 8 };
	for (int k = 0; k < 4; k++)
		assert(v[k] == expect[k]);
}

void test2()
{
	int a[8] = { 2, 8, 5, 6, 7, 3, 4, 1 };
	vector<int> x(a, a + 8);  // construct x from the array
	assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
	removeOdds(x);
	assert(x.size() == 4);
	sort(x.begin(), x.end());
	int expect[4] = { 2, 4, 6, 8 };
	for (int k = 0; k < 4; k++)
		assert(x[k] == expect[k]);
}

void test3()
{
	int a[8] = { 85, 80, 30, 70, 20, 15, 90, 10 };
	list<Movie3*> x;
	for (int k = 0; k < 8; k++)
		x.push_back(new Movie3(a[k]));
	assert(x.size() == 8 && x.front()->rating() == 85 && x.back()->rating() == 10);
	removeBad(x);
	assert(x.size() == 4 && destroyedOnes3.size() == 4);
	vector<int> v;
	for (list<Movie3*>::iterator p = x.begin(); p != x.end(); p++)
	{
		Movie3* mp = *p;
		v.push_back(mp->rating());
	}
	sort(v.begin(), v.end());
	int expect[4] = { 70, 80, 85, 90 };
	for (int k = 0; k < 4; k++)
		assert(v[k] == expect[k]);
	sort(destroyedOnes3.begin(), destroyedOnes3.end());
	int expectGone[4] = { 10, 15, 20, 30 };
	for (int k = 0; k < 4; k++)
		assert(destroyedOnes3[k] == expectGone[k]);
}
void test4()
{
	int a[8] = { 85, 80, 30, 70, 20, 15, 90, 10 };
	vector<Movie*> x;
	for (int k = 0; k < 8; k++)
		x.push_back(new Movie(a[k]));
	assert(x.size() == 8 && x.front()->rating() == 85 && x.back()->rating() == 10);
	removeBad(x);
	assert(x.size() == 4 && destroyedOnes4.size() == 4);
	vector<int> v;
	for (int k = 0; k < 4; k++)
		v.push_back(x[k]->rating());
	sort(v.begin(), v.end());
	int expect[4] = { 70, 80, 85, 90 };
	for (int k = 0; k < 4; k++)
		assert(v[k] == expect[k]);
	sort(destroyedOnes4.begin(), destroyedOnes4.end());
	int expectGone[4] = { 10, 15, 20, 30 };
	for (int k = 0; k < 4; k++)
		assert(destroyedOnes4[k] == expectGone[k]);
}
