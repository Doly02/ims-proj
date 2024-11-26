/******************************
 *  Project:        IMS Project - Electromobility in Brno
 *  File Name:      GenerateDay.cpp
 *  Authors:        Tomas Dolak, Monika Zahradnikova
 *  Date:           20.11.2024
 *  Description:    Implements Generator of The Day Time.
 *
 * ****************************/

/******************************
 *  @package        IMS Project - Electromobility in Brno
 *  @file           GeneratorDay.cpp
 *  @authors        Tomas Dolak, Monika Zahradnikova
 *  @date           20.11.2024
 *  @brief          Implements Generator of The Day Time.
 * ****************************/

#ifndef GENERATOR_DAY_HPP
#define GENERATOR_DAY_HPP

#include "../include/definitions.hpp"

/************************************************/
/*                   Globals                    */
/************************************************/
/**
 * @brief Flag indicating if the current period is daytime or nighttime.
 */
extern bool curr_period;

/**
 * @brief Counter for the number of generated cars.
 */
extern int num_generated_cars;

/**
 * @brief Flag indicating if the model is active.
 * If the model is inactive, the generator stops generating cars.
 */
extern bool model_active;

/************************************************/
/*                   Classes                    */
/************************************************/
/**
 * @class TransactionDay
 * @brief Timer for the day, switching between daytime and nighttime.
 */
class TransactionDay : public Process
{
private:
    double day_length; /**< Duration of the daytime period. */

public:
    /**
     * @brief Constructor for TransactionDay.
     * @param dayLength Duration of the daytime in simulation time.
     */
    explicit TransactionDay(double dayLength);

    /**
     * @brief Behavior of the process simulating the day-night cycle.
     */
    void Behavior() override;
};

/**
 * @class GeneratorDay
 * @brief Generator for Electric Vehicle transactions during the day.
 */
class GeneratorDay : public Event
{
private:
    double current_time; /**< Current simulation time. */

public:
    /**
     * @brief Default constructor.
     */
    GeneratorDay();

    /**
     * @brief Behavior function to manage the generation of EV transactions.
     */
    void Behavior() override;
};

#endif /* GENERATOR_DAY_HPP */