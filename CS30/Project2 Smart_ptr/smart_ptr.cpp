#include <iostream>
#include <stdexcept>
class null_ptr_exception : public std::runtime_error
{

public:
    null_ptr_exception(const char* temp) : std :: runtime_error(temp) {}; // this function is just setting up an error message
};


template <typename T>
class smart_ptr {
public:
    smart_ptr() noexcept : ptr_(nullptr), ref_(nullptr) {} // here we construct a default pointer to have its contents point to nullptr
    // Create a smart_ptr that is initialized to nullptr. The reference count
    // should be initialized to nullptr.

    explicit smart_ptr(T*& raw_ptr) : ptr_(raw_ptr), ref_(new int{ 1 }) {} // this is an lvalue constructor because your taking in data from the right
    // in this functon we make a smart pointer point to an object that raw pointer points to and so we must 
    // take the adress of raw pointer and set a reference count to point to one since the smart pointer now 
    // points to something.

                                                                           
    // Create a smart_ptr that is initialized to raw_ptr. The reference count
    // should be one. No change is made to raw_ptr.

    explicit smart_ptr(T*&& raw_ptr) // rvalue constructor
    {
        try // here we do a try catch block beacause of the fact that this function could throw a bad alloc and 
            // in doing that, we must catch the bad alloc before the program crashes.
        {
            ptr_ = raw_ptr; // take the adress of rawptr
            ref_ = new int{ 1 }; // create a new int so ref points to it.
        }
        catch (...)
        {
            delete raw_ptr; // we delete rawptr if we catch a bad alloc
            throw; // we rethrow so we can let the user know that there was a problem
        }
    }
    // Create a smart_ptr that is initialized to raw_ptr. The reference count
    // should be one. If the constructor fails raw_ptr is deleted.	



    // the function below has to run through more test cases.


    smart_ptr(const smart_ptr& rhs) noexcept : ptr_(rhs.ptr_) , ref_(rhs.ref_) // lvalue copy constructor
    { // the initialization list is making ptr_ and ref_ equal to the same value as rhs
        
        *ref_ += 1; // this is suppose to increment the refcount by one for everytime. look back at this ryan.
        

    }
    // Copy construct a pointer from rhs. The reference count should be 
    // incremented by one.

    smart_ptr(smart_ptr&& rhs) noexcept
    {
        ptr_ = rhs.ptr_; // here what we are doing is taking the adress and reference from rhs and let the
        ref_ = rhs.ref_; // left hand side hold all of its contents and move rhs pointers to point to null.
        rhs.ptr_ = nullptr; // here we indicate we have stolen
        rhs.ref_ = nullptr;
    }
        
    // Move construct a pointer from rhs.

    smart_ptr& operator=(const smart_ptr& rhs) noexcept
    {
        if (ptr_ != rhs.ptr_)
        {
            if (ptr_ != nullptr) // we have to check here that we were not dereferencing a nullptr. if so we crash.
            {
                if (*ref_ == 1) // here we have to check if the ref is equal to one
                {
                    delete ptr_; // if it is equal to one, then we just want to delete.
                    delete ref_;
                }
                else
                {
                    (*ref_)--; // if the ref is greater than one, we will want to decrement the value by one.


                }
            }
            if (rhs.ref_ != nullptr) // in this case we want  if the ref is not nulptr. if we dereference nullptr we will crash
            {
                (*rhs.ref_)++;
            }
                ptr_ = rhs.ptr_; // now we can set the lhs point to the rhs.
                ref_ = rhs.ref_;
        }
        return *this;
    }
    // This assignment should make a shallow copy of the right-hand side's
    // pointer data. The reference count should be incremented as appropriate.

    smart_ptr& operator=(smart_ptr&& rhs) noexcept
    {
        if (ptr_ != rhs.ptr_)
        {
            if (ptr_ != nullptr) // we have to check here that we were not dereferencing a nullptr. if so we crash.
            {
                if (*ref_ == 1) // here we have to check if the ref is equal to one
                {
                    delete ptr_; // if it is equal to one, then we just want to delete.
                    delete ref_;
                }
                else
                {
                    (*ref_)--; // if the ref is greater than one, we will want to decrement the value by one.


                }
            }

            ptr_ = rhs.ptr_; // now we can set the lhs point to the rhs.
            ref_ = rhs.ref_;
            rhs.ptr_ = nullptr;
            rhs.ref_ = nullptr;


            // ask preofessor russell should you return rhs instead of *this


        }
        return *this;
    }
    // This move assignment should steal the right-hand side's pointer data.

    bool clone()
    {
        if (ptr_ == nullptr || *ref_ <= 1)
        {
            return false;
        }

        --(*ref_);
        ptr_ = new T{ *ptr_ }; // we use T because ptr_ pointer type is a T type. it is subjective to change. cannot always be one thing
        ref_ = new int{ 1 };
        return true;

        
    }
    // If the smart_ptr is either nullptr or has a reference count of one, this
    // function will do nothing and return false. Otherwise, the referred to
    // object's reference count will be decreased and a new deep copy of the
    // object will be created. This new copy will be the object that this
    // smart_ptr points and its reference count will be one. 

    int ref_count() const noexcept
    {
        if (ref_ == nullptr) //  we check to see if ref equals null. if so it means we point to nothing and return zero
        {
            return 0;
        }
        return *ref_; // if it does point to some integer then we can dereference the ref pointer to get the value and return that.
    }
    // Returns the reference count of the pointed to data.

    T& operator*()
    {
        if (ptr_ == nullptr)
        {
            throw null_ptr_exception("Error: Trying to dereference a nullptr using the dereference operator ");
        }
        return *ptr_;
    }
    // The dereference operator shall return a reference to the referred object.
    // Throws null_ptr_exception on invalid access. 

    T* operator->()
    {
        if (ptr_ == nullptr)
        {
            throw null_ptr_exception("Error: Trying to dereference a nullptr using the arrow operator ");
        }
        return ptr_; // the way we know what to return is we want the object because it does not make sense someone comes and 
        // says hey send me to jack in the box and I tell them how many people are really there. no I take that person to the resturaunt
    }
    // The arrow operator shall return the pointer ptr_. Throws null_ptr_exception
    // on invalid access.

    ~smart_ptr() noexcept// deallocate all dynamic memory
    {
       clearUp(ptr_);
    }
private:
    T* ptr_;               // pointer to the referred object
    int* ref_;             // pointer to a reference count

    void clearUp(T* head) noexcept
    {

        if (ref_ == nullptr)
        {
            return;
        }
        
        --* (ref_);

        if (*ref_ == 0)
        {
            delete ptr_;
            ptr_ = nullptr;
            delete ref_;
            ref_ = nullptr;
        }
        return;
    }

};
