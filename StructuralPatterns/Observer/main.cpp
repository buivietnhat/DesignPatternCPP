#include <iostream>
#include <any>

using namespace std;

class Person
{
  int age;

public:
  Person(int age) : age(age) {}

  int get_age() const
  {
    return age;
  }

  void set_age(int age)
  {
    Person::age = age;
  }
};

//struct PersonListener
//{
//  virtual void person_changed(Person& person, const string& property_name,
//                              const any new_value);
//};

template <typename T> struct Observer
{
  virtual void field_changed(T& source, const string& field_name) = 0;
};

struct ConsolePersonObserver : Observer<Person>
{
  void field_changed(Person& source, const string& field_name) override
  {
    cout << "Person's " << field_name << " has changed to " ;
  }
};

int main()
{
//  std::cout << "Hello, World!" << std::endl;
  return 0;
}
