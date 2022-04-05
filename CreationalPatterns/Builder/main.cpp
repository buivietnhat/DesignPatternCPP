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

int main()
{
  string words[] = { "hello", "world" };
//  ostringstream oss;
//
//  oss << "<ul>\n";
//
//  for (auto& w : words)
//    oss << "  <li>" << w << "</li>\n";
//
//  oss << "</ul>";
//  cout << oss.str();

  return 0;
}
