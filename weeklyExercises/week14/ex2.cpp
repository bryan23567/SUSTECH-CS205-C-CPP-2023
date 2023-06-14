#include <iostream>
#include <stdexcept>
#include <string>
class OutOfRangeException : public std::exception
{
public:
    OutOfRangeException(const std::string &msg) : m_msg(msg)
    {
    }
    virtual const char *what() const throw()
    {
        return m_msg.c_str();
    }
    const std::string m_msg;
};

float calculateAverage(int mark1, int mark2, int mark3, int mark4)
{
    if (mark1 < 0 || mark1 > 100)
    {
        throw OutOfRangeException("The parameter 1 is " + std::to_string(mark1) + " which out of range(0-100).");
    }
    if (mark2 < 0 || mark2 > 100)
    {
        throw OutOfRangeException("The parameter 2 is " + std::to_string(mark2) + " which out of range(0-100).");
    }
    if (mark3 < 0 || mark3 > 100)
    {
        throw OutOfRangeException("The parameter 3 is " + std::to_string(mark3) + " which out of range(0-100).");
    }
    if (mark4 < 0 || mark4 > 100)
    {
        throw OutOfRangeException("The parameter 4 is " + std::to_string(mark4) + " which out of range(0-100).");
    }

    int totalMarks = mark1 + mark2 + mark3 + mark4;
    float average = static_cast<float>(totalMarks) / 4.0f;
    return average;
}

int main()
{
    int mark1, mark2, mark3, mark4;
    char yesno;
    std::cout << "Please enter marks for 4 courses: ";
    while (std::cin >> mark1 >> mark2 >> mark3 >> mark4)
    {

        try
        {
            float average = calculateAverage(mark1, mark2, mark3, mark4);
            std::cout << "Average marks: " << average << std::endl;
        }
        catch (const OutOfRangeException &e)
        {
            std::cout <<  e.what() << std::endl;
        }
        std::cout << "Would you want to enter another marks for 4 courses(y/n)?";
        std::cin >> yesno;
        if (yesno == 'n')
        {
            break;
        }

        std::cout << "Please enter marks for 4 courses: ";
    }
    std::cout << "Bye, see you next time." << std::endl;
    return 0;
}
