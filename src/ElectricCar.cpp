/******************************
 *  Project:        IMS Project - Electromobility in Brno
 *  File Name:      main.cpp
 *  Authors:        Tomas Dolak, Monika Zahradnikova
 *  Date:           17.11.2024
 *  Description:    Implements The Final Program.
 *
 * ****************************/

/******************************
 *  @package        IMS Project - Electromobility in Brno
 *  @file           main.cpp
 *  @authors        Tomas Dolak, Monika Zahradnikova
 *  @date           17.11.2024
 *  @brief          Implements The Final Program.
 * ****************************/


/************************************************/
/*                  Libraries                   */
/************************************************/
#include "../include/definitions.hpp"

/************************************************/
/*                   Implementation             */
/************************************************/
class ElectricCar : public Process
{
    char_state_t char_state;

    void choose_start()
    {
        int battery_state = Random();
        if (battery_state < 0.1)
        {
            char_state = CHAR_STATE_0_20;
        }        
        else if (battery_state < 0.9)
        {   
            char_state = CHAR_STATE_0_20;
        }
        else
        {
            char_state = CHAR_STATE_80_100;
        }

    }
};