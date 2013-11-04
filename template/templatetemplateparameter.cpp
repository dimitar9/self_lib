#include <stdio.h>
template <class T>
struct OpNewCreator
{
    static T* Create()
    {
        printf("helloworld from TTP world.\n");
        return new T;
    }
};


class Widget
{
};
template <template <class Created> class CreationPolicy>
class WidgetManager : public CreationPolicy<Widget>
{

};

typedef WidgetManager<OpNewCreator> MyWidgetMgr;

int main ()
{
    MyWidgetMgr mywm ;    
    mywm.Create();
    return 0;
}

