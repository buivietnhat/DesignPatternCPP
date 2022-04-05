#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct HtmlElement
{
  string name;
  string text;
  vector<HtmlElement> elements;

  HtmlElement() {}

  HtmlElement(const string& name, const string& text) : name(name),
    text(text) {}

  string str(int indent = 0) const
  {
    ostringstream oss;
    string i(indent * indent, ' ');
    oss << i << "<" << name << ">" << endl;
    if (text.size() > 0)
      oss << string(indent * (indent + 1), ' ') << text << endl;

    for (auto const& e : elements)
      oss << e.str(indent + 1);

    oss << i << "</" << name << ">" << endl;
    return oss.str();
  }
};

struct HtmlBuilder
{
  HtmlElement root;

  HtmlBuilder(const string& root_name)
  {
    root.name = root_name;
  }

  HtmlBuilder& add_child(const string& name, const string& word)
  {
    root.elements.emplace_back(name, word);
    return *this;
  }

  HtmlElement build()
  {
    return std::move(root);
  }

  string str() { return root.str(); }
};

void better_using_builder()
{
  string words[] = { "hello", "world" };
  HtmlBuilder builder{"ul"};
  for (auto& w : words)
    builder.add_child("li", w);

  cout << builder.str();
}

void fluent_buidler_style()
{
  auto builder = HtmlBuilder{"ul"};
  auto root_element = builder.add_child("li", "hello")
                .add_child("li", "world").build();

  cout << root_element.str();
}

int main()
{
  string words[] = { "hello", "world" };
  HtmlElement list{"ul", ""};

  for (auto& w : words)
    list.elements.emplace_back("li", w);

//  cout << list.str();
//  ostringstream oss;
//
//  oss << "<ul>\n";
//
//  for (auto& w : words)
//    oss << "  <li>" << w << "</li>\n";
//
//  oss << "</ul>";
//  cout << oss.str();

//  better_using_builder();

  fluent_buidler_style();

  return 0;
}
