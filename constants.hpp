#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include "structs.hpp"
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

inline constexpr float scalingFactor{1000.0f};

// SLIDERS

inline constexpr int slidersPosX{775};
inline constexpr int slidersWidth{250};
inline constexpr int slidersHeight{20};
inline constexpr int colorSliderMax{255};
inline constexpr int colorSliderTotal{510};

inline constexpr int labelsTextSize{15};

inline constexpr SlidersParameters boidsNumberSlider{
    {slidersPosX, 190, slidersWidth, slidersHeight}, 5, 100, 10};
inline constexpr SlidersParameters centerXSlider{
    {slidersPosX, 270, slidersWidth, slidersHeight}, 0, 720, 360};
inline constexpr SlidersParameters centerYSlider{
    {slidersPosX, 330, slidersWidth, slidersHeight}, 0, 720, 360};
inline constexpr SlidersParameters redSlider{
    {slidersPosX, 410, slidersWidth, slidersHeight}, 0, colorSliderMax, 0};
inline constexpr SlidersParameters greenSlider{
    {slidersPosX, 470, slidersWidth, slidersHeight}, 0, colorSliderMax, 0};
inline constexpr SlidersParameters blueSlider{
    {slidersPosX, 530, slidersWidth, slidersHeight}, 0, colorSliderMax, 0};

inline constexpr LabelsParameters boidsNumberSliderLabel{slidersPosX, 160,
                                                         labelsTextSize};
inline constexpr LabelsParameters centerXSliderLabel{slidersPosX, 240,
                                                     labelsTextSize};
inline constexpr LabelsParameters centerYSliderLabel{slidersPosX, 300,
                                                     labelsTextSize};
inline constexpr LabelsParameters redSliderLabel{slidersPosX, 380,
                                                 labelsTextSize};
inline constexpr LabelsParameters greenSliderLabel{slidersPosX, 440,
                                                   labelsTextSize};
inline constexpr LabelsParameters blueSliderLabel{slidersPosX, 500,
                                                  labelsTextSize};
inline constexpr LabelsParameters maxBoidsNumberLabel{slidersPosX, 115, 19};

inline constexpr TguiParameters addFlockButton{775, 645, 250, 80};
inline constexpr LabelsParameters addFlockButtonLabel{775, 600, 20};

// OPTION 3

inline constexpr SlidersParameters separationSlider{
    {slidersPosX, 150, slidersWidth, slidersHeight},
    0,
    maxSeparationStrength *constants::scalingFactor,
    defaultSeparationStrenght *constants::scalingFactor};

inline constexpr SlidersParameters separationRangeSlider{
    {slidersPosX, 210, slidersWidth, slidersHeight},
    0,
    maxSeparationRange,
    defaultSeparationRange};

inline constexpr SlidersParameters alignmentSlider{
    {slidersPosX, 270, slidersWidth, slidersHeight},
    0,
    maxAlignmentStrength *constants::scalingFactor,
    defaultAlignmentStrenght *constants::scalingFactor};

inline constexpr SlidersParameters cohesionSlider{
    {slidersPosX, 330, slidersWidth, slidersHeight},
    0,
    maxCohesionStrength *constants::scalingFactor,
    defaultCohesionStrenght *constants::scalingFactor};

inline constexpr SlidersParameters interactionSlider{
    {slidersPosX, 390, slidersWidth, slidersHeight},
    0,
    maxInteractionRange,
    defaultInteractionRange};

inline constexpr SlidersParameters repelSlider{
    {slidersPosX, 450, slidersWidth, slidersHeight},
    0,
    maxRepelStrenght *constants::scalingFactor,
    defaultRepelStrenght *constants::scalingFactor};

inline constexpr SlidersParameters repelRangeSlider{
    {slidersPosX, 510, slidersWidth, slidersHeight},
    0,
    maxRepelRange,
    defaultRepelRange};

inline constexpr LabelsParameters separationSliderLabel{slidersPosX, 120, 15};
inline constexpr LabelsParameters separationRangeSliderLabel{slidersPosX, 180,
                                                             15};
inline constexpr LabelsParameters alignmentSliderLabel{slidersPosX, 240, 15};
inline constexpr LabelsParameters cohesionSliderLabel{slidersPosX, 300, 15};
inline constexpr LabelsParameters interactionSliderLabel{slidersPosX, 360, 15};
inline constexpr LabelsParameters repelSliderLabel{slidersPosX, 420, 15};
inline constexpr LabelsParameters repelRangeSliderLabel{slidersPosX, 480, 15};

// INTERFACE

inline const RectangleParameters topMargin{0, 0, 750, 15, sf::Color::Black};
inline const RectangleParameters bottomMargin{0, 735, 750, 15,
                                              sf::Color::Black};
inline const RectangleParameters leftMargin{0, 15, 15, 720, sf::Color::Black};
inline const RectangleParameters rightMargin{735, 15, 15, 720,
                                             sf::Color::Black};

inline const RectangleParameters topSettingMargin{755, 5, 290, 5,
                                                   sf::Color::Black};
inline const RectangleParameters bottomSettingMargin{755, 740, 290, 5,
                                                      sf::Color::Black};
inline const RectangleParameters leftSettingMargin{755, 5, 5, 740,
                                                    sf::Color::Black};
inline const RectangleParameters rightSettingMargin{1040, 5, 5, 740,
                                                     sf::Color::Black};

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace constants
#endif