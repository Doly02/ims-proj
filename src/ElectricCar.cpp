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
/*                   Statistics                 */
/************************************************/
/**
 * @brief Number of Charged Car Per Period (Day/Night).
 */
double num_charged_cars_per_period = 0.0;   
/**
 * @brief Average Time That Car Spends In The System.
 */
double avg_time_in_system = 0.0;

/************************************************/
/*                   Stores                     */
/************************************************/
Store CHAR_STATION_AC_12KWH("Charging Station 12kWh", NUM_12_KWH_AC_STATIONS);     // TODO:

Store CHAR_STATION_AC_22KWH("Charging Station 22kWh", NUM_22_KWH_AC_STATIONS);     // TODO:

Store CHAR_STATION_DC_50KWH("Charging Station 50kWh", NUM_50_KWH_DC_STATIONS);     // TODO:

Store CHAR_STATION_DC_108KWH("Charging Station 108kWh", NUM_108_KWH_DC_STATIONS);  // TODO:
/************************************************/
/*                   Implementation             */
/************************************************/

/**
 * @brief Implementation of Electric Cars That Are Transactions In The Model.
 */
class ElectricCar : public Process
{
        char_state_t char_state;
        pow_station_t pow_station;

        double start_time;
        double time_spend_in_system;
        double time_spend_in_front;
        double time_spend_charging;
    
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

            if (station < CHANCE_12_KWH_AC_STATIONS)        // Chance of Choosing AC 12 kW
            {
                pow_station = POW_STATION_AC_12_KWH;
            }
            else if (station < CHANCE_22_KWH_AC_STATIONS)   // Chance of Choosing AC 22 kW
            {
                pow_station = POW_STATION_AC_22_KWH;
            }
            else if (station < CHANCE_50_KWH_DC_STATIONS)   // Chance of Choosing DC 50 kW
            {
                pow_station = POW_STATION_DC_50_KWH; 
            }
            else                                            // Chance of Choosing DC 108 kW
            {
                pow_station = POW_STATION_DC_108_KWH;
            }
        }

        void charge_battery_in_stage_0_20(void)
        {
        
            double time_spend_charging = 0.0;

            if (POW_STATION_AC_12_KWH == pow_station)
            {
                /* Will Take Up One Place In The Store or Will Wait */
                Enter(CHAR_STATION_AC_12KWH, 1);

                /* Generate Time In Uniform Distribution */
                time_spend_charging = Uniform(0, MAX_TIME_12_KWH_AC_STATIONS_0_20);

                /* Charging */
                Wait(time_spend_charging);

                // TODO: Continue With 20% - 80% Charging
            }
            else if (POW_STATION_AC_22_KWH == pow_station)
            {
                /* Will Take Up One Place In The Store or Will Wait */
                Enter(CHAR_STATION_AC_22KWH, 1);

                time_spend_charging = Uniform(0, MAX_TIME_22_KWH_AC_STATIONS_0_20);

                /* Charging */
                Wait(time_spend_charging);

                // TODO: Continue With 20% - 80% Charging
            }
            else if (POW_STATION_DC_50_KWH == pow_station)
            {
                /* Will Take Up One Place In The Store or Will Wait */
                Enter(CHAR_STATION_DC_50KWH, 1);

                time_spend_charging = Uniform(0, MAX_TIME_50_KWH_DC_STATIONS_0_20);

                /* Charging */
                Wait(time_spend_charging);

                // TODO: Continue With 20% - 80% Charging
            }
            else
            {
                /* Will Take Up One Place In The Store or Will Wait */
                Enter(CHAR_STATION_DC_108KWH, 1);

                time_spend_charging = Uniform(0, MAX_TIME_108_KWH_DC_STATIONS_0_20);

                /* Charging */
                Wait(time_spend_charging);

                // TODO: Continue With 20% - 80% Charging

            }



        }

                /* Leave The Space In Charging Station */
                // Leave(CHAR_STATION_DC_108KWH, 1);

        /**
         * @brief Defines behavior of process EletricCar.
         */
        void Behavior() override
        {
            start_time = Time;              /* Get Model Time From SIMLIB */

            choose_battery_cap();           /* Choose Starting Battery State */
        
            if (CHAR_STATE_0_20 == char_state)
            {
                /* Choose Charging Station */
                choose_battery_station();

                /* Charge The Car*/
                charge_battery_in_stage_0_20();
                
            }
            else if (CHAR_STATE_20_80 == char_state)
            {
                choose_battery_station();   /* Choose Charging Station */
                time_spend_charging = 0.25; /* Charging Time */
            }
            else
            {
                choose_battery_station();   /* Choose Charging Station */
                time_spend_charging = 0.1;  /* Charging Time */
            }        
            Terminate();                    /* Terminate Process */
        }
};