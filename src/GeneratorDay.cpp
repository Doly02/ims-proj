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

/************************************************/
/*                  Libraries                   */
/************************************************/
#include "../include/GeneratorDay.hpp"
#include "../include/ElectricVehicle.hpp"
/************************************************/
/*                   Global Variables           */
/************************************************/
/**
 * @brief Number of Generated Cars. 
 */
int num_generated_cars = 0;

/**
 * @brief Flag With Information If Model Is Active.
 * @details If Model Is Not Active, The Generator Will Stop Generating Cars.
 */
bool model_active = true;

/************************************************/
/*                   Implementation             */
/************************************************/

/************************************************/
/*             TransactionDay Methods           */
/************************************************/

/**
 * @brief Timer of The Day. Switches Between Daytime and Nighttime.
 */
TransactionDay::TransactionDay(GeneratorMode mode) : mode(mode) {}

void TransactionDay::Behavior()
{
    model_active = true;

    switch (mode) {
        case DAYTIME:
            /* Simulate Daytime */
            Wait(DAYTIME_LENGTH);
            break;
        case NIGHTTIME:
            /* Simulate Nighttime */
            Wait(NIGHTTIME_LENGTH);
            break;
        case ALLTIME:
            /* Simulate 24 hours */
            Wait(WHOLE_DAY_TIME);
            break;
    }

    model_active = false;
    Cancel(); // End of The Day
}

double calculateGenerationLambda(double total_cars, double charging_percentage, double period)
{
    period = period / 60;
    double lambda = 60 / ((total_cars * charging_percentage)/period);
    return lambda;
}

/**
 * @brief Generator of The EV Transaction In The Day Time.
 */
/************************************************/
/*             GeneratorDay Methods             */
/************************************************/
GeneratorDay::GeneratorDay(int total_cars, double charging_percentage, GeneratorMode mode) :
        total_cars(total_cars),
        charging_percentage(charging_percentage),
        current_time(0.0),
        mode(mode) {}


void GeneratorDay::Behavior() {
    current_time = Time; // Model Time In Local Form

    if (!model_active) {
        Cancel(); // Stops The Generator
    } else {
        (new ElectricVehicle)->Activate();

        // Generate New EV (new ElectricCar)->Activate();
        num_generated_cars++;

        double lambda;

        switch (mode) {
            case DAYTIME:
                lambda = calculateGenerationLambda(total_cars, charging_percentage, DAYTIME_LENGTH);
                Activate(Time + Exponential(lambda));
                break;

            case NIGHTTIME:
                lambda = calculateGenerationLambda(total_cars, charging_percentage, NIGHTTIME_LENGTH);
                Activate(Time + Exponential(lambda));
                break;

            case ALLTIME:
                if (current_time < DAYTIME_LENGTH) {
                    lambda = calculateGenerationLambda(total_cars, charging_percentage, DAYTIME_LENGTH);
                    Activate(Time + Exponential(lambda));
                } else {
                    lambda = calculateGenerationLambda(total_cars, charging_percentage, NIGHTTIME_LENGTH);
                    Activate(Time + Exponential(lambda));
                }
        }
    }
}