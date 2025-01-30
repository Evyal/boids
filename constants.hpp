#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>

namespace constants {
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
// Window constanst
inline constexpr float windowWidth{1050.f};
inline constexpr float windowHeight{750.f};

// Size of the field where the boids can fly
inline constexpr float fieldSide{720.f};
inline constexpr float marginSize{15.f};

// A flock with 20 boids is generated at the beginning of the program.
inline constexpr int initBoidNumber{20};
inline constexpr int initFlockNumber{1};

////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
// Random generation constants
inline constexpr float randomMinimumX{15.f};
inline constexpr float randomMaximumX{735.f};
inline constexpr float randomMinimumY{15.f};
inline constexpr float randomMaximumY{735.f};
inline constexpr float randomPositionRange{50.f};

inline constexpr float randomMinimumSpeed{150.f};
inline constexpr float randomMaximumSpeed{300.f};
inline constexpr float randomSpeedRange{50.f};
inline constexpr float randomAngleRange{0.002f};

////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
// BOIDS CONSTANTS

// minimum and maximum speed component of any boid
inline constexpr float minBoidSpeed{150.f};
inline constexpr float maxBoidSpeed{300.f};

// minimum and maximum speed of randoml generated boid
inline constexpr float minRandomSpeed{150.f};
inline constexpr float maxRandomSpeed{300.f};

// speed boost on mirror mode
inline constexpr float speedBoostMirror{15.f};

// size of the boid
inline constexpr float boidSize{3.6f};

////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
// FLOCKS CONSTANTS

// maximum boids in a flock, and maximum number of flocks
inline constexpr size_t maxFlockSize{100};
inline constexpr size_t minFlockSize{5};
inline constexpr size_t maxFlockNumber{5};

////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
// Values for PARAMETERS

// MAXIMUM VALUES
inline constexpr float maxSeparationStrength{1.f};
inline constexpr float maxSeparationRange{720.f};
inline constexpr float maxAlignmentStrength{1.f};
inline constexpr float maxCohesionStrength{1.f};
inline constexpr float maxInteractionRange{720.f};

inline constexpr float maxRepelStrenght{1.};
inline constexpr float maxRepelRange{720.f};

// DEFAULT VALUES
inline constexpr float defaultSeparationStrenght{0.5f};
inline constexpr float defaultSeparationRange{12.0f};
inline constexpr float defaultAlignmentStrenght{0.03f};
inline constexpr float defaultCohesionStrenght{0.015f};
inline constexpr float defaultInteractionRange{300.f};

inline constexpr float defaultRepelStrenght{0.3f};
inline constexpr float defaultRepelRange{20.0f};

// COLOUR SLIDERS
inline constexpr int colorSliderMax{255};
inline constexpr int colorSliderTotal{510};

////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace constants
#endif