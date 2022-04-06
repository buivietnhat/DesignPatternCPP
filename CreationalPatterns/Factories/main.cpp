#include <iostream>
#include <cmath>

using namespace std;

//struct Point
//{
//  float x, y;
//
//  Point(const float x, const float y) : x(x), y(y) {}
//};

class Point
{
private:
  float x,y;
  Point(float x, float y) : x(x), y(y) {}
  friend class PointFactory;

public:
//  static Point NewCartesian(float x, float y)
//  {
//    return {x,y};
//  }
//
//  static Point NewPolar(float r, float theta)
//  {
//    return {r*cos(theta), r*sin(theta)};
//  }
//
  friend ostream& operator<<(ostream& os, const Point& point)
  {
    os << "x: " << point.x << " y: " << point.y;
    return os;
  }
};

struct PointFactory
{
  static Point NewCartesian(float x, float y)
  {
    return {x,y};
  }

  static Point NewPolar(float r, float theta)
  {
    return {r*cos(theta), r*sin(theta)};
  }
};

int main()
{
    auto p = PointFactory::NewCartesian(1, 2);
    auto p2 = PointFactory::NewPolar(5, M_PI_4);
    cout << p2 << endl;
    return 0;
}
