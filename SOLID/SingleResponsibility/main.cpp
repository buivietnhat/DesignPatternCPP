#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Journal
{
  string title;
  vector<string> entries;

  Journal(const string& title) : title(title) {}

  void add(const string& entry)
  {
    static int count = 1;
    entries.push_back(to_string(count++) + ": " + entry);
  }

//  void save(const string& file_name)
//  {
//    ofstream ofs(file_name);
//    for (auto& s : entries)
//      ofs << s << endl;
//  }
};

struct PersistenManager
{
  static void save(const Journal& j, const string& name)
  {
    ofstream ofs(name);
    for (auto& s : j.entries)
      ofs << s << endl;
  }
};

int main()
{
  Journal j{"Dear Diary"};
  j.add("I ate a bug");
  j.add("I cried today");
//  j.save("My Diary.txt");
  PersistenManager::save(j, "my_better_diary.txt");
  return 0;
}
