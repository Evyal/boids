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

// inline constexpr float defaultSeparationRange{12.0f};
// inline constexpr float defaultAlignmentStrenght{0.03f};
// inline constexpr float defaultCohesionStrenght{0.015f};
inline constexpr float defaultSeparationRange{15.0f};
inline constexpr float defaultAlignmentStrenght{0.015f};
inline constexpr float defaultCohesionStrenght{0.015f};

inline constexpr float defaultInteractionRange{300.f};

inline constexpr float defaultRepelStrenght{0.3f};
inline constexpr float defaultRepelRange{20.0f};

inline constexpr float scalingFactor{1000.0f};

// SELECT OPTION

inline constexpr TguiPar button1{770, 20, 80, 50};
inline constexpr TguiPar button2{860, 20, 80, 50};
inline constexpr TguiPar button3{950, 20, 80, 50};

inline const sf::Color onThreeWayBGColor{sf::Color(255, 255, 160)};
inline const sf::Color onThreeWayBGColorHover{sf::Color(255, 255, 160)};

inline const sf::Color offThreeWayBGColor{sf::Color(128, 128, 128)};
inline const sf::Color offThreeWayBGColorHover{sf::Color(190, 190, 190)};

inline const sf::Color threeWayBGColorDown{sf::Color(160, 160, 160)};

// OPTION 1

inline constexpr TguiPar toroidalButton{770, 80, 260, 50};

inline const sf::Color onToroidalColor{sf::Color(204, 255, 153)};
inline const sf::Color onToroidalHover{sf::Color(229, 255, 204)};
inline const sf::Color onToroidalDown{sf::Color(229, 255, 204)};

inline const sf::Color offToroidalColor{sf::Color(153, 255, 255)};
inline const sf::Color offToroidalHover{sf::Color(204, 255, 255)};
inline const sf::Color offToroidalDown{sf::Color(204, 255, 255)};

// DRAW STATISTICS

inline const RectanglePar statsRectangle1{770, 140, 260, 110};
inline const RectanglePar statsRectangle2{775, 145, 250, 100};
inline const RectanglePar statsRectangle3{765, 150, 15, 90};

inline constexpr TguiPar deleteFlockButton{1020, 185, 15, 15};
inline constexpr int distancePerIndex{120};

inline constexpr LabelsPar statisticsLabel{825, 150, 15};
inline constexpr int labelsDistance{25};

inline constexpr LabelsPar flockSizeLabel{790, 180, 20};
inline constexpr LabelsPar statisticsValueLabel{975, 145, 20};

// OPTION 2
// SLIDERS

inline constexpr int slidersPosX{775};
inline constexpr int slidersWidth{250};
inline constexpr int slidersHeight{20};
inline constexpr int colorSliderMax{255};
inline constexpr int colorSliderTotal{510};

inline constexpr SlidersPar boidsNumberSlider{
    {slidersPosX, 190, slidersWidth, slidersHeight}, 5, 100, 10};
inline constexpr SlidersPar centerXSlider{
    {slidersPosX, 270, slidersWidth, slidersHeight}, 0, 720, 360};
inline constexpr SlidersPar centerYSlider{
    {slidersPosX, 330, slidersWidth, slidersHeight}, 0, 720, 360};
inline constexpr SlidersPar redSlider{
    {slidersPosX, 410, slidersWidth, slidersHeight}, 0, colorSliderMax, 0};
inline constexpr SlidersPar greenSlider{
    {slidersPosX, 470, slidersWidth, slidersHeight}, 0, colorSliderMax, 0};
inline constexpr SlidersPar blueSlider{
    {slidersPosX, 530, slidersWidth, slidersHeight}, 0, colorSliderMax, 0};

inline constexpr LabelsPar boidsNumberSliderLabel{slidersPosX, 160, 15};
inline constexpr LabelsPar centerXSliderLabel{slidersPosX, 240, 15};
inline constexpr LabelsPar centerYSliderLabel{slidersPosX, 300, 15};
inline constexpr LabelsPar redSliderLabel{slidersPosX, 380, 15};
inline constexpr LabelsPar greenSliderLabel{slidersPosX, 440, 15};
inline constexpr LabelsPar blueSliderLabel{slidersPosX, 500, 15};
inline constexpr LabelsPar maxBoidsNumberLabel{slidersPosX, 115, 19};

inline constexpr TguiPar addFlockButton{775, 645, 250, 80};
inline constexpr LabelsPar addFlockButtonLabel{775, 600, 20};

// OPTION 3

inline constexpr SlidersPar separationSlider{
    {slidersPosX, 150, slidersWidth, slidersHeight},
    0,
    maxSeparationStrength *constants::scalingFactor,
    defaultSeparationStrenght *constants::scalingFactor};

inline constexpr SlidersPar separationRangeSlider{
    {slidersPosX, 210, slidersWidth, slidersHeight},
    0,
    maxSeparationRange,
    defaultSeparationRange};

inline constexpr SlidersPar alignmentSlider{
    {slidersPosX, 270, slidersWidth, slidersHeight},
    0,
    maxAlignmentStrength *constants::scalingFactor,
    defaultAlignmentStrenght *constants::scalingFactor};

inline constexpr SlidersPar cohesionSlider{
    {slidersPosX, 330, slidersWidth, slidersHeight},
    0,
    maxCohesionStrength *constants::scalingFactor,
    defaultCohesionStrenght *constants::scalingFactor};

inline constexpr SlidersPar interactionSlider{
    {slidersPosX, 390, slidersWidth, slidersHeight},
    0,
    maxInteractionRange,
    defaultInteractionRange};

inline constexpr SlidersPar repelSlider{
    {slidersPosX, 450, slidersWidth, slidersHeight},
    0,
    maxRepelStrenght *constants::scalingFactor,
    defaultRepelStrenght *constants::scalingFactor};

inline constexpr SlidersPar repelRangeSlider{
    {slidersPosX, 510, slidersWidth, slidersHeight},
    0,
    maxRepelRange,
    defaultRepelRange};

inline constexpr LabelsPar separationSliderLabel{slidersPosX, 120, 15};
inline constexpr LabelsPar separationRangeSliderLabel{slidersPosX, 180, 15};
inline constexpr LabelsPar alignmentSliderLabel{slidersPosX, 240, 15};
inline constexpr LabelsPar cohesionSliderLabel{slidersPosX, 300, 15};
inline constexpr LabelsPar interactionSliderLabel{slidersPosX, 360, 15};
inline constexpr LabelsPar repelSliderLabel{slidersPosX, 420, 15};
inline constexpr LabelsPar repelRangeSliderLabel{slidersPosX, 480, 15};

// INTERFACE

inline const RectanglePar topMargin{0, 0, 750, 15};
inline const RectanglePar bottomMargin{0, 735, 750, 15};
inline const RectanglePar leftMargin{0, 15, 15, 720};
inline const RectanglePar rightMargin{735, 15, 15, 720};

inline const RectanglePar topSettingMargin{755, 5, 290, 5};
inline const RectanglePar bottomSettingMargin{755, 740, 290, 5};
inline const RectanglePar leftSettingMargin{755, 5, 5, 740};
inline const RectanglePar rightSettingMargin{1040, 5, 5, 740};

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace constants
#endif