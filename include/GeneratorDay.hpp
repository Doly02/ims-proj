/******************************
 *  Project:        IMS Project - Electromobility in Brno
 *  File Name:      GenerateDay.cpp
 *  Authors:        Tomas Dolak, Monika Zahradnikova
 *  Date:           20.11.2024
 *  Description:    Implements Generator of The Day Time, Night Time or All Day Time.
 *
 * ****************************/

/******************************
 *  @package        IMS Project - Electromobility in Brno
 *  @file           GeneratorDay.cpp
 *  @authors        Tomas Dolak, Monika Zahradnikova
 *  @date           20.11.2024
 *  @brief          Implements Generator of The Day Time, Night Time or All Day Time.
 * ****************************/

#ifndef GENERATOR_DAY_HPP
#define GENERATOR_DAY_HPP

#include "../include/definitions.hpp"

/************************************************/
/*                   Globals                    */
/************************************************/
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
/*             Generator Modes                  */
/************************************************/
enum GeneratorMode {
    DAYTIME,    /** Generate transactions during the daytime. */
    NIGHTTIME,  /** Generate transactions during the nighttime. */
    ALLTIME     /** Generate transactions throughout the entire day. */
};

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
    GeneratorMode mode; /** Mode of the generator (DAYTIME, NIGHTTIME, ALLTIME). */

public:
    /**
     * @brief Constructor for TransactionDay.
     */
    explicit TransactionDay(GeneratorMode mode);

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
    int total_cars;                /** Total number of cars */
    double charging_percentage;    /** Percentage of cars charging */
    double current_time;           /** Current simulation time. */
    GeneratorMode mode;            /** Mode of the generator (DAYTIME, NIGHTTIME, ALLTIME). */

public:
    /**
     * @brief Constructor for GeneratorDay.
     * @param total_cars Total number of cars.
     * @param charging_percentage Percentage of cars charging daily.
     * @param mode Generator mode (daytime, nighttime, or all-day).
     */
    GeneratorDay(int total_cars, double charging_percentage, GeneratorMode mode);

    /**
     * @brief Behavior function to manage the generation of EV transactions.
     */
    void Behavior() override;
};

/************************************************/
/*             Helper Functions                 */
/************************************************/

/**
 * @brief Calculate the generation rate (lambda) for the exponential distribution.
 * @param total_cars Total number of cars.
 * @param charging_percentage Percentage of cars to charge daily.
 * @param period Time period for the simulation (in minutes).
 * @return Lambda value for exponential distribution.
 */
double calculateGenerationLambda(double total_cars, double charging_percentage, double period);

#endif /* GENERATOR_DAY_HPP */