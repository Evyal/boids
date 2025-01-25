
#include "SFML/Graphics.hpp"
#include "constants.hpp"
#include "flock.hpp"
#include "graphics.hpp"
#include "iostream"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstddef>
#include <vector>

extern float separation;
extern float separationRange;
extern float alignment;
extern float cohesion;
extern float repel;
extern float repelRange;
extern bool toroidal;

void addRandomFlock(std::vector<Flock> &flockStack) {
  if (flockStack.size() < constants::maxFlockNumber) {
    flockStack.emplace_back(createRandomFlock());
  } else {
    std::cout << "There are already 5 flocks!\n";
  }
}




  // for (auto &flock : flockStack) {
  // flock.updateFlock(flock.Separation(separation, separationRange), flock.Alignment(alignment),
  //                   flock.Cohesion(cohesion, toroidal), toroidal);

  // flock.updateFlockRepel(
  //     flock.Separation(s, ds), flock.Alignment(a), flock.Coesion(c,
  //     toroidal), flock.Repel(flockStack, repel, repelRange), toroidal);


void assignFlock(const Flock &flock, std::vector<sf::CircleShape> &flockBody) {

}

void drawFlock(sf::RenderWindow &window,
               const std::vector<sf::CircleShape> &flockBody) {
  for (const auto &flock : flockBody) {
    window.draw(flock);
  }
}
