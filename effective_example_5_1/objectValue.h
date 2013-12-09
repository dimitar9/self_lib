#include <string>

template <class T>
class NameObject {
    public:
        NameObject(const std::string& name, const T& value);
//        NameObject(const std::string& name, const T& value);

        std::string nameValue;
        const T objectValue;
};
//first constructor.
/*template <class T>
NameObject<T>::NameObject(std::string& name, const T& value)
{
    nameValue = name;
    objectValue = value;
}*/

//second constructor.
template <class T>
NameObject<T>::NameObject(const std::string& name, const T& value)
{
    nameValue = name;
    objectValue = value;
}
