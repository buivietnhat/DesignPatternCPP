#include <iostream>
#include <sstream>

using namespace std;

struct Shape
{
  virtual string str() const = 0;
};

struct Circle : Shape
{
  float radius;

  Circle(float radius) : radius(radius) {}

  void resize(uint32_t factor)
  {
    radius *= factor;
  }

  string str() const override
  {
    ostringstream oss;
    oss << "A circle with radius " << radius;
    return oss.str();
  }
};


// Mixin Inheritance
template <typename T> struct ColoredShape : T
{
  static_assert(is_base_of<Shape, T>::value,
    "Template argument must be a Shape");

  string color;

  template <typename...Args>
  ColoredShape(string color, Args ...args)
    : T(std::forward<Args>(args)...), color{color}
  {}

  string str() const override
  {
    ostringstream oss;
    oss << T::str() << " has color " << color;
    return oss.str();
  }
};

int main()
{
  ColoredShape<Circle> red_circle{"red", 5};
  cout << red_circle.str() << endl;
  red_circle.resize(2);
  cout << red_circle.str() << endl;
}