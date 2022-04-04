#include <iostream>
#include <vector>

using namespace std;

enum class Color { RED, GREEN, BLUE };
enum class Size { SMALL, MEDIUM, LARGE };

struct Product
{
  string name;
  Color color;
  Size size;
};

//struct ProductFilter
//{
//  using Items = vector<Product*>;

//  Items by_color(Items items, Color color)
//  {
//    Items result;
//    for (auto& item : items)
//      if (item->color == color)
//        result.push_back(item);
//
//    return result;
//  }
//
//  Items by_size(Items items, Size size)
//  {
//    Items result;
//    for (auto& item : items)
//      if (item->size == size)
//        result.push_back(item);
//
//    return result;
//  }
//
//  Items by_color_and_size(Items items, Color color, Size size)
//  {
//    Items result;
//    for (auto& item : items)
//      if (item->color == color && item->size == size)
//        result.push_back(item);
//
//    return result;
//  }
//};

template <typename T> struct AndSpecification;

template <typename T> struct Specification
{
  virtual bool is_satisfied(T* item) = 0;

  AndSpecification<T> operator&&(Specification<T>&& other)
  {
//    AndSpecification<T>(*this, other);
    return {*this, other};
  }
};

template <typename T>
struct AndSpecification : Specification<T>
{
  Specification<T>& first;
  Specification<T>& second;

  AndSpecification(Specification<T>& first, Specification<T>& second) : first(
    first), second(second) {}

  bool is_satisfied(T* item) override
  {
    return first.is_satisfied(item) && second.is_satisfied(item);
  }
};

template <typename T> struct Filter
{
  virtual vector<T*> filter(Specification<T>& spec, vector<T*> items) = 0;
};

struct ColorSpecification : Specification<Product>
{
  Color color;

  ColorSpecification(Color color) : color(color) {}

  bool is_satisfied(Product* item) override
  {
    return item->color == color;
  }
};

struct SizeSpecification : Specification<Product>
{
  Size size;

  SizeSpecification(Size size) : size(size) {}

  bool is_satisfied(Product* item) override
  {
    return size == item->size;
  }
};


struct ProductFilter : Filter<Product>
{
  vector<Product*> filter(Specification<Product>& spec, vector<Product*> items) override
  {
    vector<Product*> result;
    for (auto& item : items)
      if (spec.is_satisfied(item))
        result.push_back(item);

    return result;
  }
};


int main()
{
  auto apple = Product{"apple", Color::RED, Size::SMALL};
  auto tree = Product{"tree", Color::GREEN, Size::MEDIUM};
  auto house = Product{"house", Color::BLUE, Size::LARGE};

  vector<Product*> items = {&apple, &tree, &house};

//  ProductFilter pf;
//  for (auto& item : pf.by_color(items, Color::RED))
//    cout << item->name << " has color red" << endl;
//
//  for (auto& item : pf.by_size(items, Size::MEDIUM))
//    cout << item->name << " has size medium" << endl;
//
//  for (auto& item : pf.by_color_and_size(items, Color::BLUE, Size::LARGE))
//    cout << item->name << " has color blue and size large" << endl;

  ProductFilter pf;
  auto green = ColorSpecification{Color::GREEN};
  auto medium = SizeSpecification{Size::MEDIUM};

  for (auto& item : pf.filter(green, items))
    cout << item->name << " has color green" << endl;

  auto green_and_medium = AndSpecification(green, medium);

  for (auto& item : pf.filter(green_and_medium, items))
    cout << item->name << " has color green and size medium" << endl;

//  for (auto& item : pf.by_size(items, Size::MEDIUM))
//    cout << item->name << " has size medium" << endl;
//
//  for (auto& item : pf.by_color_and_size(items, Color::BLUE, Size::LARGE))
//    cout << item->name << " has color blue and size large" << endl;

  auto blue_and_large = ColorSpecification{Color::BLUE}
                        && SizeSpecification{Size::LARGE};

  for (auto& item : pf.filter(blue_and_large, items))
    cout << item->name << " has color blue and size large" << endl;


  return 0;
}
