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

/************************************************/
/*                  Libraries                   */
/************************************************/
#include "../include/definitions.hpp"

/************************************************/
/*                   Implementation             */
/************************************************/

/**
 * @brief Flag With Information If Actual Period Is Daytime or Nighttime 
 */
bool curr_period;

class GeneratorDay : public Event
{

    double current_time = 0.0; /**< Current simulation time. */

    /**
     * @brief Behavior function override from Event class.
     */
    void Behavior() override
    {
        /* Model Time In Local Form */
        current_time = Time;

        if (PERIOD_NIGHTTIME == current_time)
        {
            Cancel(); /* Stops The Generator */
        }

    }
};
