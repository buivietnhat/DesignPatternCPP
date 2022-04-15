#include <iostream>
#include "boost/signals2.hpp"

struct EventData
{
  virtual ~EventData() = default;
  virtual void print() = 0;
};

struct PlayerScoredData : EventData
{
  std::string who_scrored;
  int goals_scored_so_far;

  PlayerScoredData(const std::string& who_scrored, int goals_scored_so_far)
    : who_scrored(who_scrored), goals_scored_so_far(goals_scored_so_far) {}

  void print() override
  {
    std::cout << who_scrored << " has scored (their " << goals_scored_so_far
        << " scores so far\n";
  }
};

struct Game
{
  boost::signals2::signal<void(EventData*)> events;
};

struct Player
{
  Game& game;
  std::string name;
  int scores_so_far = 0;

  Player(Game& game, const std::string& name) : game(game), name(name) {}

  void score()
  {
    scores_so_far += 1;
    auto data = PlayerScoredData(name,scores_so_far);
    game.events(&data);
  }
};

struct Coach
{
  Game& game;

  explicit Coach(Game& game) : game(game)
  {
    game.events.connect([](EventData* data){
      PlayerScoredData* ps = dynamic_cast<PlayerScoredData*>(data);
      if (ps)
        std::cout << "coach says: well done " << ps->who_scrored << std::endl;
    });
  }

};

int main()
{
  Game game;
  Player nhat{game, "Nhat"};
  Coach coach(game);

  nhat.score();
  nhat.score();
  nhat.score();

  return 0;
}
