/******************************
 *  Project:        IMS Project - Electromobility in Brno
 *  File Name:      ElectricVehicle.cpp
 *  Authors:        Tomas Dolak, Monika Zahradnikova
 *  Date:           17.11.2024
 *  Description:    Implements The Final Program.
 *
 * ****************************/

/******************************
 *  @package        IMS Project - Electromobility in Brno
 *  @file           ElectricVehicle.cpp
 *  @authors        Tomas Dolak, Monika Zahradnikova
 *  @date           17.11.2024
 *  @brief          Implements The Final Program.
 * ****************************/


/************************************************/
/*                  Libraries                   */
/************************************************/
#include "../include/ElectricVehicle.hpp"

/************************************************/
/*                   Statistics                 */
/************************************************/
/**
 * @brief Number of Charged Car Per Period (Day/Night).
 */
double num_charged_cars_per_period = 0.0;


//TODO: Zatial je potrebna, neskor mozno vymazat
double num_cars_on_station = 0.0;


/**
 * @brief Average Time That Car Spends In The System.
 */
double avg_time_in_system = 0.0;
 
/**
 * @struct Contains Information About Each Electric Vehicle Starts In Stage 1, and Uses 12kWh AC Charger [0 - 20%]
 *         and That Leaves The System.
 */
std::vector<std::pair<double, double>> ev_stats_ac12_0_20;

/**
 * @struct Contains Information About Each Electric Vehicle Starts In Stage 1, and Uses 22kWh AC Charger [0 - 20%]
 *         and That Leaves The System.
 */
std::vector<std::pair<double, double>> ev_stats_ac22_0_20;

/**
 * @struct Contains Information About Each Electric Vehicle Starts In Stage 1, and Uses 50kWh DC Charger [0 - 20%]
 *         and That Leaves The System.
 */
std::vector<std::pair<double, double>> ev_stats_dc50_0_20;

/**
 * @struct Contains Information About Each Electric Vehicle Starts In Stage 1, and Uses 108kWh DC Charger [0 - 20%]
 *         and That Leaves The System.
 */
std::vector<std::pair<double, double>> ev_stats_dc108_0_20;

/************************************************/
/*                   Stores                     */
/************************************************/
Store CHAR_STATION_AC_12KWH("Charging Station 12kWh", NUM_12_KWH_AC_STATIONS);

Store CHAR_STATION_AC_22KWH("Charging Station 22kWh", NUM_22_KWH_AC_STATIONS);

Store CHAR_STATION_DC_50KWH("Charging Station 50kWh", NUM_50_KWH_DC_STATIONS);

Store CHAR_STATION_DC_108KWH("Charging Station 108kWh", NUM_108_KWH_DC_STATIONS);


/************************************************/
/*                   Implementation             */
/************************************************/

void ElectricVehicle::choose_battery_cap(void) {
    double battery_state = Random();

    // 10 % of vehicles come with a battery capacity 0-20 %
    if (battery_state < 0.1) {
        char_state = CHAR_STATE_0_20;
    }
        // 80 % of vehicles come with a battery capacity 20-80 %
    else if (battery_state < 0.9) {
        char_state = CHAR_STATE_20_80;
    }
        // 10 % of vehicles come with a battery capacity 80-100 %
    else {
        char_state = CHAR_STATE_80_100;
    }

}

void ElectricVehicle::choose_battery_station(void)
{
    double station = Random();

    if (station < chance_12_kwh_ac_station)        // Chance of Choosing AC 12 kW
    {
        pow_station = POW_STATION_AC_12_KWH;
    }
    else if (station < chance_22_kwh_ac_station)   // Chance of Choosing AC 22 kW
    {
        pow_station = POW_STATION_AC_22_KWH;
    }
    else if (station < chance_50_kwh_dc_station)   // Chance of Choosing DC 50 kW
    {
        pow_station = POW_STATION_DC_50_KWH; 
    }
    else                                            // Chance of Choosing DC 108 kW
    {
        pow_station = POW_STATION_DC_108_KWH;
    }
}

void ElectricVehicle::charge_battery_in_stage_0_20(void)
{
    double t_start_charging     = Time;

    double t_charging_0_20_on_ac12     = 0.0;
    double t_charging_0_20_on_ac22     = 0.0;
    double t_charging_0_20_on_dc50     = 0.0;
    double t_charging_0_20_on_dc108    = 0.0;

    if (POW_STATION_AC_12_KWH == pow_station)
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_AC_12KWH, 1);

        num_cars_on_station++;

        /* Generate Time In Uniform Distribution */
        time_spend_charging = Uniform(0, MAX_TIME_12_KWH_AC_STATIONS_0_20);

        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;
        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on AC 12kWh Charger In Stage 1 (0-20%) */
        t_charging_0_20_on_ac12 = Time - t_start_charging;

        /* Statistics - Store Time Spend on Charging in Stage 1, Use t_start_charging For Next Charging In Stage 2 [20-80%]*/
        ev_stats_ac12_0_20.emplace_back(t_start_charging, t_charging_0_20_on_ac12);

        /* The Vehicle Continues To Charge At More Than 20 % */
        continue_charge_battery_in_stage_20_80();
    }
    else if (POW_STATION_AC_22_KWH == pow_station)
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_AC_22KWH, 1);

        num_cars_on_station++;

        time_spend_charging = Uniform(0, MAX_TIME_22_KWH_AC_STATIONS_0_20);

        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;

        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on AC 22kWh Charger In Stage 1 (0-20%) */
        t_charging_0_20_on_ac22 = Time - t_start_charging;

        /* Statistics - Store Time Spend on Charging in Stage 1, Use t_start_charging For Next Charging In Stage 2 [20-80%]*/
        ev_stats_ac22_0_20.emplace_back(t_start_charging, t_charging_0_20_on_ac22);

        /* The Vehicle Continues To Charge At More Than 20 % */
        continue_charge_battery_in_stage_20_80();
    }
    else if (POW_STATION_DC_50_KWH == pow_station)
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_DC_50KWH, 1);

        num_cars_on_station++;

        time_spend_charging = Uniform(0, MAX_TIME_50_KWH_DC_STATIONS_0_20);

        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;

        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on DC 50kWh Charger In Stage 1 (0-20%) */
        t_charging_0_20_on_dc50 = Time - t_start_charging;
        
        /* Statistics - Store Time Spend on Charging in Stage 1, Use t_start_charging For Next Charging In Stage 2 [20-80%]*/
        ev_stats_dc50_0_20.emplace_back(t_start_charging, t_charging_0_20_on_dc50);

        /* The Vehicle Continues To Charge At More Than 20 % */
        continue_charge_battery_in_stage_20_80();
    }
    else
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_DC_108KWH, 1);

        num_cars_on_station++;

        time_spend_charging = Uniform(0, MAX_TIME_108_KWH_DC_STATIONS_0_20);

        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;

        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on DC 108kWh Charger In Stage 1 (0-20%) */
        t_charging_0_20_on_dc108 = Time - t_start_charging;

        /* Statistics - Store Time Spend on Charging in Stage 1, Use t_start_charging For Next Charging In Stage 2 [20-80%]*/
        ev_stats_dc108_0_20.emplace_back(t_start_charging, t_charging_0_20_on_dc108);

        /* The Vehicle Continues To Charge At More Than 20 % */
        continue_charge_battery_in_stage_20_80();
    }
    
}

void ElectricVehicle::continue_charge_battery_in_stage_20_80(void)
{
    double time_spend_charging = 0.0;

    if (POW_STATION_AC_12_KWH == pow_station)
    {
        /* The Vehicle Has Already Taken Up Space In The Store*/

        /* Generate Time In Uniform Distribution */
        time_spend_charging = Uniform(0, MAX_TIME_12_KWH_AC_STATIONS_20_80);

        /* Charging */
        Wait(time_spend_charging);

        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_AC_12KWH, 1);

        num_charged_cars_per_period++;

    }
    else if (POW_STATION_AC_22_KWH == pow_station)
    {
        /* The Vehicle Has Already Taken Up Space In The Store*/

        time_spend_charging = Uniform(0, MAX_TIME_22_KWH_AC_STATIONS_20_80);

        /* Charging */
        Wait(time_spend_charging);

        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_AC_22KWH, 1);

        num_charged_cars_per_period++;

    }
    else if (POW_STATION_DC_50_KWH == pow_station)
    {
        /* The Vehicle Has Already Taken Up Space In The Store*/

        time_spend_charging = Uniform(0, MAX_TIME_50_KWH_DC_STATIONS_20_80);

        /* Charging */
        Wait(time_spend_charging);

        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_DC_50KWH, 1);

        num_charged_cars_per_period++;
    }
    else
    {
        /* The Vehicle Has Already Taken Up Space In The Store*/

        time_spend_charging = Uniform(0, MAX_TIME_108_KWH_DC_STATIONS_0_20);

        /* Charging */
        Wait(time_spend_charging);

        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_DC_108KWH, 1);

        num_charged_cars_per_period++;
    }
}

void ElectricVehicle::charge_battery_in_stage_20_80(void)
{
    double time_spend_charging = 0.0;

    if (POW_STATION_AC_12_KWH == pow_station)
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_AC_12KWH, 1);

        num_cars_on_station++;

        /* Generate Time In Uniform Distribution */
        time_spend_charging = Uniform(0, MAX_TIME_12_KWH_AC_STATIONS_20_80);

        /* Charging */
        Wait(time_spend_charging);

        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_AC_12KWH, 1);

        num_charged_cars_per_period++;
    }
    else if (POW_STATION_AC_22_KWH == pow_station)
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_AC_22KWH, 1);

        num_cars_on_station++;

        time_spend_charging = Uniform(0, MAX_TIME_22_KWH_AC_STATIONS_20_80);

        /* Charging */
        Wait(time_spend_charging);

        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_AC_22KWH, 1);

        num_charged_cars_per_period++;

    }
    else if (POW_STATION_DC_50_KWH == pow_station)
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_DC_50KWH, 1);

        num_cars_on_station++;

        time_spend_charging = Uniform(0, MAX_TIME_50_KWH_DC_STATIONS_20_80);

        /* Charging */
        Wait(time_spend_charging);
        
        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_DC_50KWH, 1);

        num_charged_cars_per_period++;
    }
    else
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_DC_108KWH, 1);

        num_cars_on_station++;

        time_spend_charging = Uniform(0, MAX_TIME_108_KWH_DC_STATIONS_0_20);

        /* Charging */
        Wait(time_spend_charging);

        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_DC_108KWH, 1);

        num_charged_cars_per_period++;
    }
}

void ElectricVehicle::charge_battery_in_stage_80_100(void)
{
    double time_spend_charging = 0.0;

    if (POW_STATION_AC_12_KWH == pow_station)
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_AC_12KWH, 1);

        num_cars_on_station++;

        /* Generate Time In Uniform Distribution */
        time_spend_charging = Uniform(0, MAX_TIME_12_KWH_AC_STATIONS_80_100);

        /* Charging */
        Wait(time_spend_charging);

        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_AC_12KWH, 1);

        num_charged_cars_per_period++;

    }
    else if (POW_STATION_AC_22_KWH == pow_station)
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_AC_22KWH, 1);

        num_cars_on_station++;

        time_spend_charging = Uniform(0, MAX_TIME_22_KWH_AC_STATIONS_80_100);

        /* Charging */
        Wait(time_spend_charging);

        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_AC_22KWH, 1);

        num_charged_cars_per_period++;

    }
    else if (POW_STATION_DC_50_KWH == pow_station)
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_DC_50KWH, 1);

        num_cars_on_station++;

        time_spend_charging = Uniform(0, MAX_TIME_50_KWH_DC_STATIONS_80_100);

        /* Charging */
        Wait(time_spend_charging);
        
        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_DC_50KWH, 1);

        num_charged_cars_per_period++;
    }
    else
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_DC_108KWH, 1);

        num_cars_on_station++;

        time_spend_charging = Uniform(0, MAX_TIME_108_KWH_DC_STATIONS_80_100);

        /* Charging */
        Wait(time_spend_charging);

        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_DC_108KWH, 1);

        num_charged_cars_per_period++;

    }
}

/**
 * @brief Defines behavior of process EletricVehicle.
 */
void ElectricVehicle::Behavior()
{
    start_time = Time;              /* Get Model Time From SIMLIB */

    choose_battery_cap();           /* Choose Starting Battery State */

    if (CHAR_STATE_0_20 == char_state)
    {
        /* Choose Charging Station */
        choose_battery_station();

        /* Charge The Car In Stage 1 [0 - 20 %]*/
        charge_battery_in_stage_0_20();
        
    }
    else if (CHAR_STATE_20_80 == char_state)
    {
        choose_battery_station();   /* Choose Charging Station */
        
        /* Charge The Car In Stage 2 [20 - 80 %]*/
        charge_battery_in_stage_20_80();
    }
    else
    {
        choose_battery_station();   /* Choose Charging Station */
        
        /* Charge The Car In Stage 3 [80 - 100 %]*/
        charge_battery_in_stage_80_100();
    }        

    /* Terminate Process */
    Terminate();
}
