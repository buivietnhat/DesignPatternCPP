#include <iostream>
#include <memory>

using namespace std;

struct ILogger
{
  virtual ~ILogger(){}
  virtual void log(const string& s) = 0;
};

struct ConsoleLogger : ILogger
{
  ConsoleLogger() {}

  void log(const string& s) override
  {
    cout << "LOG: " << s.c_str() << endl;
  }
};

struct Engine
{
  float volume = 5;
  float horse_power = 400;

  friend ostream& operator<<(ostream& os, const Engine& engine)
  {
    os << "volume: " << engine.volume << " horse_power: " << engine.horse_power;
    return os;
  }
};

struct Car
{

};

class Reporting
{
  ILogger& logger;

public:
  Reporting(ILogger& logger) : logger(logger) {}
};

int main()
{
  std::cout << "Hello, World!" << std::endl;
  return 0;
}
