#include "AutoPtr.hpp"
#include "UniquePtr.hpp"
#include "SharedPtr.hpp"

class Date
{
public:
    Date(int year = 2019, int month = 5, int day = 12)
        :_year(year),
        _month(month),
        _day(day)
    {
        std::cout << "Date()" << std::endl;
    }

    ~Date()
    {
        std::cout << "~Date" << std::endl;
    }

    int _year;
    int _month;
    int _day;
};

int main(void)
{
    //Test AutoPtr//////////////////////////// 
    //AutoPtr<int> p1(new int);
    //*p1 = 1;

    //AutoPtr<int> p2(p1);
    //*p2 = 3;
   
    //std::cout << *p1 << std::endl;
    //std::cout << *p2 << std::endl;
    //end of test AutoPtr////////////////////
    
    //Test UniquePtr/////////////////////////
    //UniquePtr<int> p1(new int);
    //*p1 = 1;
    //std::cout << *p1 << std::endl;

    //copy construct 
    //UniquePtr<int> p2(p1);
    
    //operator=
    //UniquePtr<int> p3;
    //p3 = p1;
    //end of test UniquePtr///////////////////
    
    //Test SharedPtr///////////////////////////
    SharedPtr<Date> p1(new Date());
    p1->_year = 1997;
    p1->_month = 9;
    p1->_day = 21;
    std::cout << p1->_year << "-" << p1->_month << "-" << p1->_day << std::endl;
    SharedPtr<Date> p2(p1);
    std::cout << p2->_year << "-" << p2->_month << "-" << p2->_day << std::endl;

    SharedPtr<Date> p3(new Date());
    p3 = p1;
    std::cout << p3->_year << "-" << p3->_month << "-" << p3->_day << std::endl;

    return 0;
}
