//
// Created by nhatbui on 12/04/2022.
//

#include <iostream>
#include "boost/signals2.hpp"



template <typename T> struct Observable
{
  boost::signals2::signal<void(T&, const std::string&)> property_changed;
};

class Person : public Observable<Person>
{
  std::string name;
  int age;

public:
  Person(const std::string& name, int age) : name(name), age(age) {}
//  Person(){}

  int get_age() const
  {
    return age;
  }

  void set_age(int age)
  {
    if (this->age == age)
      return;

    Person::age = age;
    property_changed(*this, "age");
  }
};


int main()
{
  Person nhat{"Nhat", 27};
  auto conn = nhat.property_changed.connect([](Person& p, const std::string
  property_name)
  {
    std::cout << property_name << " has been changed to " << p.get_age() <<
    std::endl;
  });

  nhat.set_age(28);
  nhat.set_age(28);
  nhat.set_age(29);

  return 0;
}