#include <iostream>

class Hungry_Mode
{
public:
    static Hungry_Mode* get_instance()
    {
        return &_m_instance;
    }

private:
    Hungry_Mode(){};
    Hungry_Mode(Hungry_Mode const&);
    Hungry_Mode& operator=(Hungry_Mode const&);

    //or C++11
    //Hungry_Mode(Hungry_Mode const&) = delete;
    //Hungry_Mode& operator=(Hungry_Mode const&) = delete;

    static Hungry_Mode _m_instance;
};

Hungry_Mode Hungry_Mode::_m_instance;
