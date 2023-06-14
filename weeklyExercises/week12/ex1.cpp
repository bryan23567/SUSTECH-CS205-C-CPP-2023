class Base
{
private:
    int x;

protected:
    int y;

public:
    int z;
    void funBase(Base &b)
    {
        ++x;
        ++y;
        ++z;
        ++b.x;
        ++b.y;
        ++b.z;
    }
};
class Derived : public Base
{
public:
    void funDerived(Base &b, Derived &d)
    {
        ++x;
        ++y;
        ++z;
        ++b.x;
        ++b.y;
        ++b.z;
        ++d.x;
        ++d.y;
        ++d.z;
    }
};
void fun(Base &b, Derived &d)
{
    ++x;
    ++y;
    ++z;
    ++b.x;
    ++b.y;
    ++b.z;
    ++d.x;
    ++d.y;
    ++d.z;
}
