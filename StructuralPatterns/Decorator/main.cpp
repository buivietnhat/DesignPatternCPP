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

  string str() const override
  {
    ostringstream oss;
    oss << "A circle with radius " << radius;
    return oss.str();
  }
};

struct ColoredShape : Shape
{
  const Shape& shape;
  string color;

  ColoredShape(const Shape& shape, const string& color) : shape(shape),
    color(color) {}

  string str() const override
  {
    ostringstream oss;
    oss << shape.str() << " has the color " << color;
    return oss.str();
  }

};

struct TranspanrentShape : Shape
{
  const Shape& shape;
  uint8_t transpanrency;

  TranspanrentShape(const Shape& shape, uint8_t transpanrency) : shape(shape),
    transpanrency(transpanrency) {}

  string str() const override
  {
    ostringstream oss;
    oss << shape.str() << " has " << static_cast<float>(transpanrency) / 255.f*100.f
                       << "% transparency";
    return oss.str();
  }


};

int main()
{
  Circle circle{0.5f};
  ColoredShape red_circle{circle, "red"};

  TranspanrentShape my_circle{ColoredShape{Circle{5}, "green"}, 64};

  cout << red_circle.str() << endl;
  cout << my_circle.str() << endl;
  return 0;
}
