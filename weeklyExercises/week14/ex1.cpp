#include <iostream>
#include <string>
using namespace std;
class MyException : public exception
{
public:
    MyException(const string &msg) : m_msg(msg)
    {
        cout << "MyException::MyException - set m_msg to:" << m_msg << endl;
    }
    ~MyException()
    {
        cout << "MyException::~MyException" << endl;
    }
    virtual const char *what() const throw()
    {
        cout << "MyException::what" << endl;
        return m_msg.c_str();
    }
    const string m_msg;
};
void throwDerivedException()
{
    cout << "throwDerivedException - thrown a derived exception" << endl;
    string execptionMessage("MyException thrown");
    throw(MyException(execptionMessage));
}
void illustrateDerivedExceptionCatch()
{
    cout << "illustrateDerivedExceptionsCatch - start" << endl;
    try
    {
        throwDerivedException();
    }
  
    catch (const MyException &e)
    {
        cout << "illustrateDerivedExceptionsCatch - caught an MyException, e.what::" << e.what() << endl;
        // some additional code due to the fact that MyException was thrown...
    }
  catch (const exception &e)
    {
        cout << "illustrateDerivedExceptionsCatch - caught an std::exception, e.what:" << e.what() << endl;
        // some additional code due to the fact that std::exception was thrown...
    }
    cout << "illustrateDerivedExceptionsCatch - end" << endl;
}

int main(int argc, char **argv)
{
    cout << "main - start" << endl;
    illustrateDerivedExceptionCatch();
    cout << "main - end" << endl;
    return 0;
}
