#include "graphics.hpp"
#include "SFML/Graphics.hpp"
#include "boid.hpp"
#include "constants.hpp"
#include "control.hpp"
#include "egui.hpp"
#include "flock.hpp"
#include "statistics.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <cmath>
#include <cstddef>
#include <vector>

float windowX{715.f};
float windowY{715.f};
float baseWidth{5.f};
float height{10.f};

// DRAW

size_t spacing{30};
void drawGrid(sf::RenderWindow &window) {
  for (size_t i{0}; i < static_cast<size_t>(windowX); i += spacing) {
    sf::Vertex column[] = {
        sf::Vertex(sf::Vector2f(static_cast<float>(i), 0.f), sf::Color::Black),
        sf::Vertex(sf::Vector2f(static_cast<float>(i), windowY),
                   sf::Color::Black)};
    window.draw(column, 2, sf::Lines);
  }
  for (size_t i{0}; i < static_cast<size_t>(windowY); i += spacing) {
    sf::Vertex column[] = {
        sf::Vertex(sf::Vector2f(0, static_cast<float>(i)), sf::Color::Black),
        sf::Vertex(sf::Vector2f(windowX, static_cast<float>(i)),
                   sf::Color::Black)};
    window.draw(column, 2, sf::Lines);
  }
}




void drawRectangles(sf::RenderWindow &window,
                    const std::vector<Flock> &flockstack) {


}

// DRAW FLOCK

sf::CircleShape boidBody(const Flock &flock, size_t i) {
  sf::CircleShape boidBody{constants::boidSize};
  boidBody.setOrigin(constants::boidSize, constants::boidSize);
  boidBody.setPosition(flock.getBoid(i).getPositionX(),
                       flock.getBoid(i).getPositionY());
  boidBody.setFillColor(flock.getFlockColor());
  return boidBody;
}

sf::CircleShape boidTriangle(const Flock &flock, size_t i) {
  sf::CircleShape boidBody(constants::boidSize, 3);
  boidBody.setScale(1, 2);
  boidBody.setFillColor(flock.getFlockColor());
  boidBody.setOrigin(constants::boidSize, constants::boidSize);
  boidBody.setPosition(flock.getBoid(i).getPositionX(),
                       flock.getBoid(i).getPositionY());

  // if (flock.getBoid(i).getSpeedY() >= 0) {
  boidBody.rotate(180 *
                  std::atan2(flock.getBoid(i).getVelocityX(),
                             -flock.getBoid(i).getVelocityY()) /
                  M_PIf);

  return boidBody;
}

void updateBodyStack(sf::RenderWindow &window,
                     const std::vector<Flock> &flockStack,
                     std::vector<std::vector<sf::CircleShape>> &bodyStack) {}

// PRINT FLOCK
// void printFlock(sf::RenderWindow &window, const Flock &flock, float center) {
//   sf::Font sans;
//   sans.loadFromFile("../OpenSans-Regular.ttf");

//   sf::Text meanDistance;

//   float meanDistanceValue{
//       calculateMean(calculateDistances(flock.getFlockPositions()))};
//   meanDistance.setString("mx = " +
//                          std::to_string(static_cast<int>(meanDistanceValue)));
//   meanDistance.setFont(sans);
//   meanDistance.setCharacterSize(20);
//   meanDistance.setFillColor(sf::Color::Black);
//   meanDistance.setPosition(790, 160.f + center);

//   sf::Text standardDeviation;

//   standardDeviation.setString(
//       "sx = " +
//       std::to_string(static_cast<int>(calculateStandardDeviation(
//           calculateDistances(flock.getFlockPositions()),
//           meanDistanceValue))));
//   standardDeviation.setFont(sans);
//   standardDeviation.setCharacterSize(20);
//   standardDeviation.setFillColor(sf::Color::Black);
//   standardDeviation.setPosition(790, 190.f + center);

//   sf::Text meanSpeed;

//   float meanSpeedValue{flock.getMeanSpeed()};
//   meanSpeed.setString("mv = " +
//                       std::to_string(static_cast<int>(meanSpeedValue)));
//   meanSpeed.setFont(sans);
//   meanSpeed.setCharacterSize(20);
//   meanSpeed.setFillColor(sf::Color::Black);
//   meanSpeed.setPosition(870, 160.f + center);

//   sf::Text SpeedStandardDeviation;

//   SpeedStandardDeviation.setString(
//       "sv = " + std::to_string(static_cast<int>(calculateStandardDeviation(
//                     flock.getSpeedVector(), meanSpeedValue))));
//   SpeedStandardDeviation.setFont(sans);
//   SpeedStandardDeviation.setCharacterSize(20);
//   SpeedStandardDeviation.setFillColor(sf::Color::Black);
//   SpeedStandardDeviation.setPosition(870, 190.f + center);

//   window.draw(meanDistance);
//   window.draw(standardDeviation);
//   window.draw(meanSpeed);
//   window.draw(SpeedStandardDeviation);
// }