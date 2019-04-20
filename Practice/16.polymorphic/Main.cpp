#include "virtual_destructor.h"

int main(void)
{
    Person* p = new Person;
    Person* c = (Person*)new Child;

    delete p;
    delete c;
    
    return 0;
}
