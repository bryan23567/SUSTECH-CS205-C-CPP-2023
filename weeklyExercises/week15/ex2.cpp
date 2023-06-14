#include <iostream>
#include <typeinfo>

class Base
{
protected:
    int bvalue;

public:
    Base(int i) : bvalue(i) {}

    virtual bool equal(const Base &b) const
    {
        return (bvalue == b.bvalue);
    }

    friend bool operator==(const Base &obj1, const Base &obj2)
    {
        if (typeid(obj1) != typeid(obj2))
        {
            throw std::runtime_error("The two objects have different types, they cannot be compared.");
        }
        return obj1.equal(obj2);
    }
};

class Derived : public Base
{
private:
    int dvalue;

public:
    Derived(int a, int b) : Base(a), dvalue(b) {}

    virtual bool equal(const Base &b) const override
    {
        const Derived *derivedObj = dynamic_cast<const Derived *>(&b);
        return (derivedObj != nullptr) && (bvalue == derivedObj->bvalue) && (dvalue == derivedObj->dvalue);
    }
};

void process(const Base &obj1, const Base &obj2)
{
    try
    {
        if (obj1 == obj2)
        {
            std::cout << "Two " << (typeid(obj1) == typeid(Derived) ? "Derived" : "Base")
                      << " type objects are equal." << std::endl;
        }
        else
        {
            std::cout << "Two " << (typeid(obj1) == typeid(Derived) ? "Derived" : "Base")
                      << " type objects are not equal because they have different values." << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}

int main()
{
    Base b1(2);
    Base b2(2);

    Derived d1(1, 2);
    Derived d2(2, 2);
    process(b1, b2);
    process(d1, d2);
    process(b1, d1);
    return 0;
}
