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
inline constexpr int windowFrameRate{60};

// Size of the field where the boids can fly
inline constexpr float fieldSide{720.f};
inline constexpr float marginSize{15.f};
inline const sf::Color fieldColor{sf::Color{48, 48, 48}};

// A flock with 20 boids is generated at the beginning of the program.
inline constexpr int initBoidNumber{20};
inline constexpr int initFlockNumber{1};

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
// BOIDS CONSTANTS

// minimum and maximum speed component of any boid
inline constexpr float minBoidSpeed{150.f};
inline constexpr float maxBoidSpeed{300.f};

// sets a scale on the distance moved per frame
inline constexpr float speedScale{150.f};

// speed boost on mirror mode
inline constexpr float speedBoostMirror{15.f};

// size of the boid
inline constexpr float boidSize{4.3f};

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
// Random generation constants
inline constexpr float randomMinimumX{0.f};
inline constexpr float randomMaximumX{fieldSide};
inline constexpr float randomMinimumY{0.f};
inline constexpr float randomMaximumY{fieldSide};
inline constexpr float randomPositionRange{50.f};

inline constexpr float randomMinimumSpeed{minBoidSpeed};
inline constexpr float randomMaximumSpeed{maxBoidSpeed};
inline constexpr float randomAngleRange{0.002f};

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
inline constexpr float maxSeparationRange{360.f};
inline constexpr float maxAlignmentStrength{0.3f};
inline constexpr float maxCohesionStrength{0.3f};
inline constexpr float maxInteractionRange{360.f};
inline constexpr float maxRepelStrength{1.};
inline constexpr float maxRepelRange{360.f};
inline constexpr float maxClickStrenght{1.f};

inline constexpr FlockPar maxFlockParameters{
    maxSeparationStrength, maxSeparationRange,  maxAlignmentStrength,
    maxCohesionStrength,   maxInteractionRange, maxRepelStrength,
    maxRepelRange,         maxClickStrenght};

// DEFAULT VALUES
inline constexpr float defaultSeparationStrength{0.48f};
inline constexpr float defaultSeparationRange{15.0f};
inline constexpr float defaultAlignmentStrength{0.03f};
inline constexpr float defaultCohesionStrength{0.015f};
inline constexpr float defaultInteractionRange{150.f};
inline constexpr float defaultRepelStrength{0.15f};
inline constexpr float defaultRepelRange{30.0f};
inline constexpr float defaultClickStrenght{0.15f};

inline constexpr float scalingFactor{1000.0f};

inline constexpr FlockPar defaultFlockParameters{
    defaultSeparationStrength, defaultSeparationRange,
    defaultAlignmentStrength,  defaultCohesionStrength,
    defaultInteractionRange,   defaultRepelStrength,
    defaultRepelRange,         defaultClickStrenght};

////////////////////////////////////////////////////////////////////////////////////////////////////
// SELECT OPTION

inline constexpr TguiPar button1{770, 20, 80, 50};
inline constexpr TguiPar button2{860, 20, 80, 50};
inline constexpr TguiPar button3{950, 20, 80, 50};

inline const sf::Color onThreeWayBGColor{sf::Color(255, 255, 204)};
inline const sf::Color onThreeWayBGColorHover{sf::Color(255, 255, 204)};

inline const sf::Color offThreeWayBGColor{sf::Color(204, 204, 204)};
inline const sf::Color offThreeWayBGColorHover{sf::Color(204, 204, 204)};
inline const sf::Color threeWayBGColorDown{sf::Color(224, 224, 224)};

////////////////////////////////////////////////////////////////////////////////////////////////////
// OPTION 1

// BUTTON to change the COLOUR of the BACKGROUND
inline const std::string onGraphicsButtonText{"White Mode"};
inline const std::string offGraphicsButtonText{"Black Mode"};
inline const sf::Color onGraphicsButtonColor{sf::Color(224, 224, 224)};
inline const sf::Color offGraphicsButtonColor{sf::Color(32, 32, 32)};
inline const SwitchButtonPar graphicsButton{{770, 80, 260, 50},
                                            onGraphicsButtonText,
                                            offGraphicsButtonText,
                                            onGraphicsButtonColor,
                                            offGraphicsButtonColor};

inline const sf::Color onGraphicsColor{sf::Color(224, 224, 224)};
inline const sf::Color offGraphicsColor{sf::Color(32, 32, 32)};

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

////////////////////////////////////////////////////////////////////////////////////////////////////
// OPTION 2
// SLIDERS

inline constexpr int slidersPosX{775};
inline constexpr int slidersWidth{250};
inline constexpr int slidersHeight{20};
inline constexpr int colorSliderTotalMin{128};
inline constexpr int colorSliderTotalMax{640};

inline constexpr SlidersPar boidsNumberSlider{
    {slidersPosX, 190, slidersWidth, slidersHeight}, 5, 100, 10};
inline constexpr SlidersPar centerXSlider{
    {slidersPosX, 270, slidersWidth, slidersHeight}, 0, 720, 360};
inline constexpr SlidersPar centerYSlider{
    {slidersPosX, 330, slidersWidth, slidersHeight}, 0, 720, 360};
inline constexpr SlidersPar redSlider{
    {slidersPosX, 410, slidersWidth, slidersHeight}, 0, 255, 128};
inline constexpr SlidersPar greenSlider{
    {slidersPosX, 470, slidersWidth, slidersHeight}, 0, 255, 128};
inline constexpr SlidersPar blueSlider{
    {slidersPosX, 530, slidersWidth, slidersHeight}, 0, 255, 128};

inline constexpr LabelsPar boidsNumberSliderLabel{slidersPosX, 160, 15};
inline constexpr LabelsPar centerXSliderLabel{slidersPosX, 240, 15};
inline constexpr LabelsPar centerYSliderLabel{slidersPosX, 300, 15};
inline constexpr LabelsPar redSliderLabel{slidersPosX, 380, 15};
inline constexpr LabelsPar greenSliderLabel{slidersPosX, 440, 15};
inline constexpr LabelsPar blueSliderLabel{slidersPosX, 500, 15};
inline constexpr LabelsPar maxBoidsNumberLabel{slidersPosX, 115, 19};

inline constexpr TguiPar addFlockButton{775, 645, 250, 80};
inline constexpr LabelsPar addFlockButtonLabel{775, 600, 20};

////////////////////////////////////////////////////////////////////////////////////////////////////
// OPTION 3

inline constexpr SlidersPar separationSlider{
    {slidersPosX, 150, slidersWidth, slidersHeight},
    0,
    maxSeparationStrength *constants::scalingFactor,
    defaultSeparationStrength *constants::scalingFactor};

inline constexpr SlidersPar separationRangeSlider{
    {slidersPosX, 200, slidersWidth, slidersHeight},
    0,
    maxSeparationRange,
    defaultSeparationRange};

inline constexpr SlidersPar alignmentSlider{
    {slidersPosX, 250, slidersWidth, slidersHeight},
    0,
    maxAlignmentStrength *constants::scalingFactor,
    defaultAlignmentStrength *constants::scalingFactor};

inline constexpr SlidersPar cohesionSlider{
    {slidersPosX, 300, slidersWidth, slidersHeight},
    0,
    maxCohesionStrength *constants::scalingFactor,
    defaultCohesionStrength *constants::scalingFactor};

inline constexpr SlidersPar interactionSlider{
    {slidersPosX, 350, slidersWidth, slidersHeight},
    0,
    maxInteractionRange,
    defaultInteractionRange};

inline constexpr SlidersPar repelSlider{
    {slidersPosX, 400, slidersWidth, slidersHeight},
    0,
    maxRepelStrength *constants::scalingFactor,
    defaultRepelStrength *constants::scalingFactor};

inline constexpr SlidersPar repelRangeSlider{
    {slidersPosX, 450, slidersWidth, slidersHeight},
    0,
    maxRepelRange,
    defaultRepelRange};

inline constexpr SlidersPar clickStrengthSlider{
    {slidersPosX, 500, slidersWidth, slidersHeight},
    0,
    maxClickStrenght *constants::scalingFactor,
    defaultClickStrenght *constants::scalingFactor};

inline constexpr SlidersPar frameRateLimitSlider{
    {slidersPosX, 600, slidersWidth, slidersHeight}, 10, 120, windowFrameRate};

inline constexpr LabelsPar parametersLabel{slidersPosX, 90, 18};

inline constexpr LabelsPar separationSliderLabel{slidersPosX, 125, 15};
inline constexpr LabelsPar separationRangeSliderLabel{slidersPosX, 175, 15};
inline constexpr LabelsPar alignmentSliderLabel{slidersPosX, 225, 15};
inline constexpr LabelsPar cohesionSliderLabel{slidersPosX, 275, 15};
inline constexpr LabelsPar interactionSliderLabel{slidersPosX, 325, 15};
inline constexpr LabelsPar repelSliderLabel{slidersPosX, 375, 15};
inline constexpr LabelsPar repelRangeSliderLabel{slidersPosX, 425, 15};
inline constexpr LabelsPar clickStrengthSliderLabel{slidersPosX, 475, 15};

inline constexpr LabelsPar extraLabel{slidersPosX, 540, 18};

inline constexpr LabelsPar frameRateLimitSliderLabel{slidersPosX, 575, 15};

////////////////////////////////////////////////////////////////////////////////////////////////////

inline const std::string onToroidalButtonText{"Border Toroidal Mode"};
inline const std::string offToroidalButtonText{"Border Mirror Mode"};
inline const sf::Color onToroidalButtonColor{sf::Color(255, 255, 153)};
inline const sf::Color offToroidalButtonColor{sf::Color(204, 255, 153)};
inline const SwitchButtonPar toroidalButton{{770, 640, 260, 40},
                                            onToroidalButtonText,
                                            offToroidalButtonText,
                                            onToroidalButtonColor,
                                            offToroidalButtonColor};

inline const std::string onInteractionButtonText{"Click Repulsive Mode"};
inline const std::string offInteractionButtonText{"Click Attractive Mode"};
inline const sf::Color onInteractionButtonColor{sf::Color(255, 153, 153)};
inline const sf::Color offInteractionButtonColor{sf::Color(153, 255, 255)};
inline const SwitchButtonPar clickInteractionButton{{770, 690, 260, 40},
                                                    onInteractionButtonText,
                                                    offInteractionButtonText,
                                                    onInteractionButtonColor,
                                                    offInteractionButtonColor};

////////////////////////////////////////////////////////////////////////////////////////////////////
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