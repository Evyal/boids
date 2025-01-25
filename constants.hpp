#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <SFML/Graphics.hpp>

namespace constants {
////////////////////////////////////////////////////////////////////////////////////////////////////
// Window constanst
inline constexpr float windowWidth{1050.f};
inline constexpr float windowHeight{750.f};

// Size of the field where the boids can fly
inline constexpr float fieldSide{720.f};

inline constexpr float marginSize{15.f};

// width of the space dedicated to sliders and buttons
inline constexpr float controlsWidth{300.f};
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
// BOIDS CONSTANTS

// minimum and maximum speed component of any boid
inline constexpr float minBoidSpeed{-150.f};
inline constexpr float maxBoidSpeed{150.f};

// minimum and maximum speed of randoml generated boid
inline constexpr float minRandomSpeed{-300.f};
inline constexpr float maxRandomSpeed{300.f};

// size of the boid
inline constexpr float boidSize{3.6f};

// FLOCKS CONSTANTS

// the following represent the maximum values achievable through sliders
inline constexpr float maxCohesionStrength{0.02f};
inline constexpr float maxSeparationStrength{0.5};
inline constexpr float maxAlignmentStrength{0.2f};

// maximum boids in a flock, and maximum number of flocks
inline constexpr size_t maxFlockSize{100};
inline constexpr size_t maxFlockNumber{5};

// the strength and range of the repel force between different flocks
inline constexpr float repelCoefficient{2.};
inline constexpr float repelRange{100.};

// DEFAULT CONSTANTS
inline constexpr float defaultSeparation{0.1f};
inline constexpr float defaultSeparationRange{20.0f};
inline constexpr float defaultAlignment{0.01f};
inline constexpr float defaultCoesion{0.003f};
inline constexpr float defaultInteracion{300.f};
inline constexpr float defaultRepel{0.f};
inline constexpr float defaultRepelRange{0.f};
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
// gui constants
// height and width of sliders, buttons and text
inline constexpr float widget_width{200.};
inline constexpr float widget_height{25.};

// the position of the first element of the panel
inline constexpr float first_element_x_position{10.};
inline constexpr float first_element_y_position{10.};

// the distance between panel elements
inline constexpr float gui_element_distance{30.};

// colors of displayed ranges
inline const sf::Color range_color{sf::Color::Yellow};
inline const sf::Color separation_range_color{sf::Color::Blue};
inline const sf::Color prey_range_color{sf::Color::Red};

// thickness of displayed ranges
inline const float range_thickness{1.};
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
// INITIAL VALUES
// the following represents the initial position of the correspoding sliders,
// with 0 indicating the slider all the way to the left, and 10 indicating the
// slider all the way to the right.
inline constexpr float initSeparationStrength{3.};
inline constexpr float initCohesionStrength{3.};
inline constexpr float initAlignmentStrength{7.};

inline constexpr float initRange{6.};
inline constexpr float initSeparationRange{6.};

// the following represent the initial value of the corresponding constants
inline constexpr int initBoidNumber{20};
inline constexpr int initFlockNumber{1};
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace constants
#endif