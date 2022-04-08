//
// Created by Nhat Bui on 07/04/2022.
//

#include <iostream>
#include <vector>

using namespace std;

template <typename Self>
struct SomeNeuron
{
  template<typename T> void connect_to(T& other);
};



struct Neuron : SomeNeuron<Neuron>
{
  vector<Neuron*> in, out;
  unsigned int id;

  Neuron()
  {
    static int id = 1;
    this->id = id++;
  }

//  void connect_to(Neuron& other)
//  {
//    out.push_back(&other);
//    other.in.push_back(this);
//  }

  Neuron* begin()
  {
    return this;
  }

  Neuron* end()
  {
    return this+1;
  }

  friend ostream& operator<<(ostream& os, const Neuron& obj)
  {
    for (auto& n : obj.in)
      os << n->id << "\t--->\t[" << obj.id << "]" << endl;

    for (auto& n : obj.out)
      os << "[" << obj.id << "]\t--->\t" << n->id << endl;

    return os;
  }
};

struct NeuronLayer : SomeNeuron<NeuronLayer>, vector<Neuron>
{
  NeuronLayer(int count)
  {
    while (count --> 0)
    {
      emplace_back();
    }
  }

  friend ostream& operator<<(ostream& os, const NeuronLayer& layer)
  {
    for (auto& n : layer)
      os << n << endl;
    return os;
  }

};

template<typename Self>
template<typename T>
void SomeNeuron<Self>::connect_to(T& other)
{
  for (Neuron& from : *static_cast<Self*>(this))
  {
    for (Neuron& to : other)
    {
      from.out.push_back(&to);
      to.in.push_back(&from);
    }
  }
}

int main()
{
  Neuron n1, n2;
  NeuronLayer layer1{3}, layer2{4};

  n1.connect_to(n2);
  n1.connect_to(layer1);
  layer1.connect_to(layer2);

//  cout << n1 << endl << n2 << endl;
  cout << layer1 << endl;
  return 0;
}

