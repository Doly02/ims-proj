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
        pow_station_t pow_station;
        double start_time;

    
        void choose_battery_cap(void);
        void choose_battery_station(void);
        void Behavior() override;

        void choose_battery_cap(void)
        {
            double battery_state = Random();

            if (battery_state < 0.1)
            {
                char_state = CHAR_STATE_0_20;
            }        
            else if (battery_state < 0.9)
            {   
                char_state = CHAR_STATE_20_80;
            }
            else
            {
                char_state = CHAR_STATE_80_100;
            }

        }

        void choose_battery_station(void)
        {
            double station = Random();

            if (station < 0.25)
            {
                pow_station = POW_STATION_AC_12_KWH; // 25% chance of choosing AC 12 kW
            }
            else if (station < 0.5)
            {
                pow_station = POW_STATION_AC_22_KWH; // 25% chance of choosing AC 22 kW
            }
            else if (station < 0.75)
            {
                pow_station = POW_STATION_DC_50_KWH; // 25% chance of choosing DC 50 kW
            }
            else
            {
                pow_station = POW_STATION_DC_108_KWH; // 25% chance of choosing DC 108 kW
            }
        }

        /**
         * @brief Defines behavior of process EletricCar.
         */
        //void Behavior() override
        //{
        //    start_time = Time;      /* Get Model Time From SIMLIB */
        //    choose_start();         /* Choose Starting Battery State */
        //
        //
        //    Terminate();            /* Terminate Process */
        //}
};