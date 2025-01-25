#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "boid.hpp"
#include "doctest.h"
#include "flock.hpp"
#include "random.hpp"
#include "vec2D.hpp"
TEST_CASE("Testing the rules") {
  SUBCASE("testing the generation function") { // generare il flock
    Limits limits{4, 5, 4, 5, 8, 9, 8, 9};
    Flock f1{};

    generateFlock(f1, 4, limits);
    CHECK(f1.getBoids().size() == 4);
    CHECK(f1.getBoids()[2].GetPosition()[0] >= 4 &&
          f1.getBoids()[2].GetPosition()[0] <= 5);
    CHECK(f1.getBoids()[2].GetPosition()[1] >= 4 &&
          f1.getBoids()[2].GetPosition()[1] <= 5);
    CHECK(f1.getBoids()[0].GetSpeed()[0] >= 8 &&
          f1.getBoids()[0].GetSpeed()[0] <= 9);
    CHECK(f1.getBoids()[3].GetSpeed()[1] >= 8 &&
          f1.getBoids()[3].GetSpeed()[1] <= 9);
  }

  SUBCASE("testing the rules") {
    // creazione boids vicini
    Boid b1(Vec2D{0.0, 0.0}, Vec2D{1.0, 0.0});
    Boid b2(Vec2D{1.0, 0.0}, Vec2D{-1.0, 0.0});
    Boid b3(Vec2D{0.0, 2.0}, Vec2D{3.0, 0.0});
    std::vector<Boid> boids = {b1, b2, b3};
    Flock flock(boids);

    // parametri
    double s = 1.0;
    double ds = 1.5;
    // testing the separation rule

    // Check Minimale, velocitÃ  di separazione non nulla (preparo anche quelli
    // con dei valori)
    auto separationSpeed = flock.Separation(
        s, ds); // si possono mettere anche qui dentro i valori direttamente
    CHECK(separationSpeed[0].x() != 0.0);
    CHECK(separationSpeed[0].y() != 0.0);
    // test con 3 boids, uno non e' vicino
    CHECK(separationSpeed[0].x() == 1.0);
    CHECK(separationSpeed[0].y() == 0.0);
    CHECK(separationSpeed[1].x() == -1.0);
    CHECK(separationSpeed[1].y() == 0.0);
    CHECK(separationSpeed[2].x() == 0.0);
    CHECK(separationSpeed[2].y() == 0.0);
    // testing the align rule
    // parametro
    double a = 0.5;

    // Check Minimale, le velocitÃ  dei boids devono cambiare
    auto alignSpeed = Flock.Align(a, boids);
    CHECK(alignSpeed[0].x() != 1.0);
    CHECK(alignSpeed[0].y() != 2.0);
    CHECK(alignSpeed[1].x() != -3.0);
    CHECK(alignSpeed[1].y() != -4.0);

    // testing the Cohesion rule
    // parametro
    double c = 0.3;

    // Check Minimale, velocitÃ  di coesione non nulla
    auto coesionSpeed = Flock.Coesion(c, boids);
    CHECK(coesionSpeed[0].x() != 0.0);
    CHECK(coesionSpeed[0].y() != 0.0);
    CHECK(coesionSpeed[1].x() != 0.0);
    CHECK(coesionSpeed[1].y() != 0.0);
    CHECK(coesionSpeed[2].x() != 0.0);
    CHECK(coesionSpeed[2].y() != 0.0);
  }
}