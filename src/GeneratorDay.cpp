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
 * @brief Flag With Information If Actual Period Is Daytime or Nighttime 
 */
bool curr_period;
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
TransactionDay::TransactionDay(double dayLength) : day_length(dayLength) {}

void TransactionDay::Behavior()
{
    model_active = true;
    double night_length = WHOLE_DAY_TIME - day_length;
    
    /* Simulate Daytime */
    curr_period = PERIOD_DAYTIME;
    Wait(day_length);

    /* Simulate Nighttime */
    curr_period = PERIOD_NIGHTTIME;
    Wait(night_length); 

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


void GeneratorDay::Behavior()
{
    current_time = Time; // Model Time In Local Form

    if (!model_active)
    {
        Cancel(); // Stops The Generator
    }
    else
    {
        (new ElectricVehicle)->Activate();
        
        // Generate New EV (new ElectricCar)->Activate();
        num_generated_cars++;

        double lambda;
        switch (mode)
        {
            case DAYTIME:
                if (current_time < DAYTIME_LENGTH) {
                    lambda = calculateGenerationLambda(total_cars, charging_percentage, DAYTIME_LENGTH);
                    Activate(Time + Exponential(lambda));
                } else {
                    Cancel();
                }
                break;

            case NIGHTTIME:
                if (current_time >= DAYTIME_LENGTH && current_time < WHOLE_DAY_TIME) {
                    lambda = calculateGenerationLambda(total_cars, charging_percentage, NIGHTTIME_LENGTH);
                    Activate(Time + Exponential(lambda));
                } else {
                    Cancel();
                }
                break;

            case ALLTIME:
                lambda = calculateGenerationLambda(total_cars, charging_percentage, WHOLE_DAY_TIME);
                Activate(Time + Exponential(lambda));
                break;

            default:
                Cancel();
                break;
        }
    }
}