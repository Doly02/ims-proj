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
Histogram time_spend_in_system("Total time in the system", 0, 20, 12);

/**
 * @brief Number of Charged Cars Per Period (Day/Night).
 */
double num_charged_cars_per_period = 0.0;


/**
 * @brief Number of Cars That Start Charging.
 */
double num_cars_on_station = 0.0;

/**
 * @struct Contains Information About Each Electric Vehicle Starts In Stage 1, and Uses 11kW AC Charger [0 - 20%]
 *         and That Leaves The System.
 */
std::vector<std::pair<double, double>> ev_stats_ac11_0_20;
/**
 * @struct Contains Information About Each Electric Vehicle Starts In Stage 1, and Uses 12kW AC Charger [0 - 20%]
 *         and That Leaves The System.
 */
std::vector<std::pair<double, double>> ev_stats_ac12_0_20;

/**
 * @struct Contains Information About Each Electric Vehicle Starts In Stage 1, and Uses 22kW AC Charger [0 - 20%]
 *         and That Leaves The System.
 */
std::vector<std::pair<double, double>> ev_stats_ac22_0_20;

/**
 * @struct Contains Information About Each Electric Vehicle Starts In Stage 1, and Uses 50kW DC Charger [0 - 20%]
 *         and That Leaves The System.
 */
std::vector<std::pair<double, double>> ev_stats_dc50_0_20;

/**
 * @struct Contains Information About Each Electric Vehicle Starts In Stage 1, and Uses 80kW DC Charger [0 - 20%]
 *         and That Leaves The System.
 */
std::vector<std::pair<double, double>> ev_stats_dc80_0_20;

/**
 * @struct Contains Information About Each Electric Vehicle Starts In Stage 1, and Uses 108kW DC Charger [0 - 20%]
 *         and That Leaves The System.
 */
std::vector<std::pair<double, double>> ev_stats_dc108_0_20;

/**
 * @struct Contains Information About Each Electric Vehicle Starts In Stage 1, and Uses 150kW DC Charger [0 - 20%]
 *         and That Leaves The System.
 */
std::vector<std::pair<double, double>> ev_stats_dc150_0_20;

/**
 * @struct Contains Information About Each Electric Vehicle Starts In Stage 1, and Uses 160kW DC Charger [0 - 20%]
 *         and That Leaves The System.
 */
std::vector<std::pair<double, double>> ev_stats_dc160_0_20;

/**
 * @struct Contains Information About Each Electric Vehicle Starts In Stage 2, and Uses 11kW AC Charger [20 - 80%]
 *         and That Leaves The System.
 */
std::vector<std::pair<double, double>> ev_stats_ac11_20_80;
/**
 * @struct Contains Information About Each Electric Vehicle Starts In Stage 2, and Uses 12kW AC Charger [20 - 80%]
 *         and That Leaves The System.
 */
std::vector<std::pair<double, double>> ev_stats_ac12_20_80;

/**
 * @struct Contains Information About Each Electric Vehicle Starts In Stage 2, and Uses 22kW AC Charger [20 - 80%]
 *         and That Leaves The System.
 */
std::vector<std::pair<double, double>> ev_stats_ac22_20_80;

/**
 * @struct Contains Information About Each Electric Vehicle Starts In Stage 2, and Uses 50kW DC Charger [20 - 80%]
 *         and That Leaves The System.
 */
std::vector<std::pair<double, double>> ev_stats_dc50_20_80;

/**
 * @struct Contains Information About Each Electric Vehicle Starts In Stage 2, and Uses 80kW DC Charger [20 - 80%]
 *         and That Leaves The System.
 */
std::vector<std::pair<double, double>> ev_stats_dc80_20_80;

/**
 * @struct Contains Information About Each Electric Vehicle Starts In Stage 2, and Uses 108kW DC Charger [20 - 80%]
 *         and That Leaves The System.
 */
std::vector<std::pair<double, double>> ev_stats_dc108_20_80;

/**
 * @struct Contains Information About Each Electric Vehicle Starts In Stage 2, and Uses 150kW DC Charger [20 - 80%]
 *         and That Leaves The System.
 */
std::vector<std::pair<double, double>> ev_stats_dc150_20_80;

/**
 * @struct Contains Information About Each Electric Vehicle Starts In Stage 2, and Uses 160kW DC Charger [20 - 80%]
 *         and That Leaves The System.
 */
std::vector<std::pair<double, double>> ev_stats_dc160_20_80;

/**
 * @struct Contains Information About Each Electric Vehicle Starts In Stage 3, and Uses 11kW AC Charger [80 - 100%]
 *         and That Leaves The System.
 */
std::vector<std::pair<double, double>> ev_stats_ac11_80_100;
/**
 * @struct Contains Information About Each Electric Vehicle Starts In Stage 3, and Uses 12kW AC Charger [80 - 100%]
 *         and That Leaves The System.
 */
std::vector<std::pair<double, double>> ev_stats_ac12_80_100;

/**
 * @struct Contains Information About Each Electric Vehicle Starts In Stage 3, and Uses 22kW AC Charger [80 - 100%]
 *         and That Leaves The System.
 */
std::vector<std::pair<double, double>> ev_stats_ac22_80_100;

/**
 * @struct Contains Information About Each Electric Vehicle Starts In Stage 3, and Uses 50kW DC Charger [80 - 100%]
 *         and That Leaves The System.
 */
std::vector<std::pair<double, double>> ev_stats_dc50_80_100;

/**
 * @struct Contains Information About Each Electric Vehicle Starts In Stage 3, and Uses 80kW DC Charger [80 - 100%]
 *         and That Leaves The System.
 */
std::vector<std::pair<double, double>> ev_stats_dc80_80_100;

/**
 * @struct Contains Information About Each Electric Vehicle Starts In Stage 3, and Uses 108kW DC Charger [80 - 100%]
 *         and That Leaves The System.
 */
std::vector<std::pair<double, double>> ev_stats_dc108_80_100;

/**
 * @struct Contains Information About Each Electric Vehicle Starts In Stage 3, and Uses 150kW DC Charger [80 - 100%]
 *         and That Leaves The System.
 */
std::vector<std::pair<double, double>> ev_stats_dc150_80_100;

/**
 * @struct Contains Information About Each Electric Vehicle Starts In Stage 3, and Uses 160kW DC Charger [80 - 100%]
 *         and That Leaves The System.
 */
std::vector<std::pair<double, double>> ev_stats_dc160_80_100;


/************************************************/
/*                   Stores                     */
/************************************************/
Store CHAR_STATION_AC_11KW("Charging Station 11kW", NUM_11_KW_AC_STATIONS);

Store CHAR_STATION_AC_12KW("Charging Station 12kW", NUM_12_KW_AC_STATIONS);

Store CHAR_STATION_AC_22KW("Charging Station 22kW", NUM_22_KW_AC_STATIONS);

Store CHAR_STATION_DC_50KW("Charging Station 50kW", NUM_50_KW_DC_STATIONS);

Store CHAR_STATION_DC_80KW("Charging Station 80kW", NUM_80_KW_DC_STATIONS);

Store CHAR_STATION_DC_108KW("Charging Station 108kW", NUM_108_KW_DC_STATIONS);

Store CHAR_STATION_DC_150KW("Charging Station 150kW", NUM_150_KW_DC_STATIONS);

Store CHAR_STATION_DC_160KW("Charging Station 160kW", NUM_160_KW_DC_STATIONS);


/************************************************/
/*                   Implementation             */
/************************************************/

void ElectricVehicle::choose_battery_cap(void) {
    double battery_state = Random();

    // 15 % of vehicles come with a battery capacity 0-20 %
    if (battery_state < 0.15) {
        char_state = CHAR_STATE_0_20;
    }
    // 75 % of vehicles come with a battery capacity 20-80 %
    else if (battery_state < 0.90) {
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

    if (station < chance_11_kw_ac_station)             // Chance of Choosing AC 11 kW
    {
        pow_station = POW_STATION_AC_11_KW;
    }
    else if (station < chance_12_kw_ac_station)        // Chance of Choosing AC 12 kW
    {
        pow_station = POW_STATION_AC_12_KW;
    }
    else if (station < chance_22_kw_ac_station)        // Chance of Choosing AC 22 kW
    {
        pow_station = POW_STATION_AC_22_KW;
    }
    else if (station < chance_50_kw_dc_station)        // Chance of Choosing DC 50 kW
    {
        pow_station = POW_STATION_DC_50_KW; 
    }
    else if (station < chance_80_kw_dc_station)        // Chance of Choosing DC 80 kW
    {
        pow_station = POW_STATION_DC_80_KW;
    }
    else if (station < chance_108_kw_dc_station)       // Chance of Choosing DC 108 kW
    {
        pow_station = POW_STATION_DC_108_KW; 
    }
    else if (station < chance_150_kw_dc_station)       // Chance of Choosing DC 150 kW
    {
        pow_station = POW_STATION_DC_150_KW;
    }
    else                                               // Chance of Choosing DC 160 kW
    {
        pow_station = POW_STATION_DC_160_KW;
    }
}

void ElectricVehicle::charge_battery_in_stage_0_20(void)
{
    double t_start_charging;

    double t_charging_0_20_on_ac11     = 0.0;
    double t_charging_0_20_on_ac12     = 0.0;
    double t_charging_0_20_on_ac22     = 0.0;
    double t_charging_0_20_on_dc50     = 0.0;
    double t_charging_0_20_on_dc80     = 0.0;
    double t_charging_0_20_on_dc108    = 0.0;
    double t_charging_0_20_on_dc150    = 0.0;
    double t_charging_0_20_on_dc160    = 0.0;

    if (POW_STATION_AC_11_KW == pow_station)
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_AC_11KW, 1);

        num_cars_on_station++;

        /* Generate Time In Uniform Distribution */
        time_spend_charging = Uniform(0, MAX_TIME_11_KW_AC_STATIONS_0_20);

        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;

        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on AC 11kW Charger In Stage 1 (0-20%) */
        t_charging_0_20_on_ac11 = Time - t_start_charging;

        /* Statistics - Store Time Spend on Charging in Stage 1, Use t_start_charging For Next Charging In Stage 2 [20-80%]*/
        ev_stats_ac11_0_20.emplace_back(t_start_charging, t_charging_0_20_on_ac11);

        /* The Vehicle Continues To Charge At More Than 20 % */
        continue_charge_battery_in_stage_20_80();
    }
    else if (POW_STATION_AC_12_KW == pow_station)
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_AC_12KW, 1);

        num_cars_on_station++;

        /* Generate Time In Uniform Distribution */
        time_spend_charging = Uniform(0, MAX_TIME_12_KW_AC_STATIONS_0_20);

        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;

        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on AC 12kW Charger In Stage 1 (0-20%) */
        t_charging_0_20_on_ac12 = Time - t_start_charging;

        /* Statistics - Store Time Spend on Charging in Stage 1, Use t_start_charging For Next Charging In Stage 2 [20-80%]*/
        ev_stats_ac12_0_20.emplace_back(t_start_charging, t_charging_0_20_on_ac12);

        /* The Vehicle Continues To Charge At More Than 20 % */
        continue_charge_battery_in_stage_20_80();
    }
    else if (POW_STATION_AC_22_KW == pow_station)
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_AC_22KW, 1);

        num_cars_on_station++;

        time_spend_charging = Uniform(0, MAX_TIME_22_KW_AC_STATIONS_0_20);

        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;

        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on AC 22kW Charger In Stage 1 (0-20%) */
        t_charging_0_20_on_ac22 = Time - t_start_charging;

        /* Statistics - Store Time Spend on Charging in Stage 1, Use t_start_charging For Next Charging In Stage 2 [20-80%]*/
        ev_stats_ac22_0_20.emplace_back(t_start_charging, t_charging_0_20_on_ac22);

        /* The Vehicle Continues To Charge At More Than 20 % */
        continue_charge_battery_in_stage_20_80();
    }
    else if (POW_STATION_DC_50_KW == pow_station)
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_DC_50KW, 1);

        num_cars_on_station++;

        time_spend_charging = Uniform(0, MAX_TIME_50_KW_DC_STATIONS_0_20);

        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;

        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on DC 50kW Charger In Stage 1 (0-20%) */
        t_charging_0_20_on_dc50 = Time - t_start_charging;
        
        /* Statistics - Store Time Spend on Charging in Stage 1, Use t_start_charging For Next Charging In Stage 2 [20-80%]*/
        ev_stats_dc50_0_20.emplace_back(t_start_charging, t_charging_0_20_on_dc50);

        /* The Vehicle Continues To Charge At More Than 20 % */
        continue_charge_battery_in_stage_20_80();
    }
    else if (POW_STATION_DC_80_KW == pow_station)
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_DC_80KW, 1);

        num_cars_on_station++;

        time_spend_charging = Uniform(0, MAX_TIME_80_KW_DC_STATIONS_0_20);

        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;

        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on DC 80kW Charger In Stage 1 (0-20%) */
        t_charging_0_20_on_dc80 = Time - t_start_charging;

        /* Statistics - Store Time Spend on Charging in Stage 1, Use t_start_charging For Next Charging In Stage 2 [20-80%]*/
        ev_stats_dc80_0_20.emplace_back(t_start_charging, t_charging_0_20_on_dc80);

        /* The Vehicle Continues To Charge At More Than 20 % */
        continue_charge_battery_in_stage_20_80();
    }
    else if (POW_STATION_DC_108_KW == pow_station)
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_DC_108KW, 1);

        num_cars_on_station++;

        time_spend_charging = Uniform(0, MAX_TIME_108_KW_DC_STATIONS_0_20);

        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;

        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on DC 108kW Charger In Stage 1 (0-20%) */
        t_charging_0_20_on_dc108 = Time - t_start_charging;

        /* Statistics - Store Time Spend on Charging in Stage 1, Use t_start_charging For Next Charging In Stage 2 [20-80%]*/
        ev_stats_dc108_0_20.emplace_back(t_start_charging, t_charging_0_20_on_dc108);

        /* The Vehicle Continues To Charge At More Than 20 % */
        continue_charge_battery_in_stage_20_80();
    }
    else if (POW_STATION_DC_150_KW == pow_station)
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_DC_150KW, 1);

        num_cars_on_station++;

        time_spend_charging = Uniform(0, MAX_TIME_150_KW_DC_STATIONS_0_20);

        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;

        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on DC 150kW Charger In Stage 1 (0-20%) */
        t_charging_0_20_on_dc150 = Time - t_start_charging;

        /* Statistics - Store Time Spend on Charging in Stage 1, Use t_start_charging For Next Charging In Stage 2 [20-80%]*/
        ev_stats_dc150_0_20.emplace_back(t_start_charging, t_charging_0_20_on_dc150);

        /* The Vehicle Continues To Charge At More Than 20 % */
        continue_charge_battery_in_stage_20_80();
    }
    else
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_DC_160KW, 1);

        num_cars_on_station++;

        time_spend_charging = Uniform(0, MAX_TIME_160_KW_DC_STATIONS_0_20);

        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;

        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on DC 160kW Charger In Stage 1 (0-20%) */
        t_charging_0_20_on_dc160 = Time - t_start_charging;

        /* Statistics - Store Time Spend on Charging in Stage 1, Use t_start_charging For Next Charging In Stage 2 [20-80%]*/
        ev_stats_dc160_0_20.emplace_back(t_start_charging, t_charging_0_20_on_dc160);

        /* The Vehicle Continues To Charge At More Than 20 % */
        continue_charge_battery_in_stage_20_80();
    }
    
}

void ElectricVehicle::continue_charge_battery_in_stage_20_80(void)
{
    double t_start_charging;

    double t_charging_20_80_on_ac11     = 0.0;
    double t_charging_20_80_on_ac12     = 0.0;
    double t_charging_20_80_on_ac22     = 0.0;
    double t_charging_20_80_on_dc50     = 0.0;
    double t_charging_20_80_on_dc80     = 0.0;
    double t_charging_20_80_on_dc108    = 0.0;
    double t_charging_20_80_on_dc150    = 0.0;
    double t_charging_20_80_on_dc160    = 0.0;

    /**
     * @warning The Vehicle Has Already Taken Up Space In The Store, So There
     *          Is No Need To Call Enter() Function.
     * */ 

    if (POW_STATION_AC_11_KW == pow_station)
    {
        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;

        /* Generate Time In Uniform Distribution */
        time_spend_charging = Uniform(0, MAX_TIME_11_KW_AC_STATIONS_20_80);

        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on AC 11kW Charger In Stage 2 (20-80%) */
        t_charging_20_80_on_ac11 = Time - t_start_charging;

        /* Statistics - Store Time Spend on Charging in Stage 2*/
        ev_stats_ac11_20_80.emplace_back(t_start_charging, t_charging_20_80_on_ac11);

        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_AC_11KW, 1);

        num_charged_cars_per_period++;

    }
    else if (POW_STATION_AC_12_KW == pow_station)
    {
        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;

        /* Generate Time In Uniform Distribution */
        time_spend_charging = Uniform(0, MAX_TIME_12_KW_AC_STATIONS_20_80);

        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on AC 12kW Charger In Stage 2 (20-80%) */
        t_charging_20_80_on_ac12 = Time - t_start_charging;

        /* Statistics - Store Time Spend on Charging in Stage 2 */
        ev_stats_ac12_20_80.emplace_back(t_start_charging, t_charging_20_80_on_ac12);

        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_AC_12KW, 1);

        num_charged_cars_per_period++;

    }
    else if (POW_STATION_AC_22_KW == pow_station)
    {
        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;

        time_spend_charging = Uniform(0, MAX_TIME_22_KW_AC_STATIONS_20_80);

        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on AC 22kW Charger In Stage 2 (20-80%) */
        t_charging_20_80_on_ac22 = Time - t_start_charging;

        /* Statistics - Store Time Spend on Charging in Stage 2*/
        ev_stats_ac22_20_80.emplace_back(t_start_charging, t_charging_20_80_on_ac22);

        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_AC_22KW, 1);

        num_charged_cars_per_period++;

    }
    else if (POW_STATION_DC_50_KW == pow_station)
    {
        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;

        time_spend_charging = Uniform(0, MAX_TIME_50_KW_DC_STATIONS_20_80);

        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on DC 50kW Charger In Stage 2 (20-80%) */
        t_charging_20_80_on_dc50 = Time - t_start_charging;

        /* Statistics - Store Time Spend on Charging in Stage 2*/
        ev_stats_dc50_20_80.emplace_back(t_start_charging, t_charging_20_80_on_dc50);

        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_DC_50KW, 1);

        num_charged_cars_per_period++;
    }
    else if (POW_STATION_DC_80_KW == pow_station)
    {
        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;

        time_spend_charging = Uniform(0, MAX_TIME_80_KW_DC_STATIONS_20_80);

        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on DC 80kW Charger In Stage 2 (20-80%) */
        t_charging_20_80_on_dc80 = Time - t_start_charging;

        /* Statistics - Store Time Spend on Charging in Stage 2*/
        ev_stats_dc80_20_80.emplace_back(t_start_charging, t_charging_20_80_on_dc80);

        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_DC_80KW, 1);

        num_charged_cars_per_period++;
    }
    else if (POW_STATION_DC_108_KW == pow_station)
    {
        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;

        time_spend_charging = Uniform(0, MAX_TIME_108_KW_DC_STATIONS_20_80);

        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on DC 108kW Charger In Stage 2 (20-80%) */
        t_charging_20_80_on_dc108 = Time - t_start_charging;

        /* Statistics - Store Time Spend on Charging in Stage 2*/
        ev_stats_dc108_20_80.emplace_back(t_start_charging, t_charging_20_80_on_dc108);

        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_DC_108KW, 1);

        num_charged_cars_per_period++;
    }
    else if (POW_STATION_DC_150_KW == pow_station)
    {
        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;

        time_spend_charging = Uniform(0, MAX_TIME_150_KW_DC_STATIONS_0_20);

        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on DC 150kW Charger In Stage 2 (20-80%) */
        t_charging_20_80_on_dc150 = Time - t_start_charging;

        /* Statistics - Store Time Spend on Charging in Stage 2*/
        ev_stats_dc150_20_80.emplace_back(t_start_charging, t_charging_20_80_on_dc150);

        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_DC_150KW, 1);

        num_charged_cars_per_period++;
    }
    else
    {
        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;

        time_spend_charging = Uniform(0, MAX_TIME_160_KW_DC_STATIONS_0_20);

        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on DC 160kW Charger In Stage 2 (20-80%) */
        t_charging_20_80_on_dc160 = Time - t_start_charging;

        /* Statistics - Store Time Spend on Charging in Stage 2*/
        ev_stats_dc160_20_80.emplace_back(t_start_charging, t_charging_20_80_on_dc160);

        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_DC_160KW, 1);

        num_charged_cars_per_period++;
    }
}

void ElectricVehicle::charge_battery_in_stage_20_80(void)
{
    double t_start_charging;

    double t_charging_20_80_on_ac11     = 0.0;
    double t_charging_20_80_on_ac12     = 0.0;
    double t_charging_20_80_on_ac22     = 0.0;
    double t_charging_20_80_on_dc50     = 0.0;
    double t_charging_20_80_on_dc80     = 0.0;
    double t_charging_20_80_on_dc108    = 0.0;
    double t_charging_20_80_on_dc150    = 0.0;
    double t_charging_20_80_on_dc160    = 0.0;

    if (POW_STATION_AC_11_KW == pow_station)
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_AC_11KW, 1);

        num_cars_on_station++;

        /* Generate Time In Uniform Distribution */
        time_spend_charging = Uniform(0, MAX_TIME_11_KW_AC_STATIONS_20_80);

        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;

        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on AC 11kW Charger In Stage 2 (20-80%) */
        t_charging_20_80_on_ac11 = Time - t_start_charging;

        /* Statistics - Store Time Spend on Charging in Stage 2*/
        ev_stats_ac11_20_80.emplace_back(t_start_charging, t_charging_20_80_on_ac11);

        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_AC_11KW, 1);

        num_charged_cars_per_period++;
    }
    else if (POW_STATION_AC_12_KW == pow_station)
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_AC_12KW, 1);

        num_cars_on_station++;

        /* Generate Time In Uniform Distribution */
        time_spend_charging = Uniform(0, MAX_TIME_12_KW_AC_STATIONS_20_80);

        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;

        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on AC 12kW Charger In Stage 2 (20-80%) */
        t_charging_20_80_on_ac12 = Time - t_start_charging;

        /* Statistics - Store Time Spend on Charging in Stage 2*/
        ev_stats_ac12_20_80.emplace_back(t_start_charging, t_charging_20_80_on_ac12);

        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_AC_12KW, 1);

        num_charged_cars_per_period++;
    }
    else if (POW_STATION_AC_22_KW == pow_station)
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_AC_22KW, 1);

        num_cars_on_station++;

        time_spend_charging = Uniform(0, MAX_TIME_22_KW_AC_STATIONS_20_80);

        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;

        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on AC 22kW Charger In Stage 2 (20-80%) */
        t_charging_20_80_on_ac22 = Time - t_start_charging;

        /* Statistics - Store Time Spend on Charging in Stage 2*/
        ev_stats_ac22_20_80.emplace_back(t_start_charging, t_charging_20_80_on_ac22);

        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_AC_22KW, 1);

        num_charged_cars_per_period++;

    }
    else if (POW_STATION_DC_50_KW == pow_station)
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_DC_50KW, 1);

        num_cars_on_station++;

        time_spend_charging = Uniform(0, MAX_TIME_50_KW_DC_STATIONS_20_80);

        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;

        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on DC 50kW Charger In Stage 2 (20-80%) */
        t_charging_20_80_on_dc50 = Time - t_start_charging;

        /* Statistics - Store Time Spend on Charging in Stage 2*/
        ev_stats_dc50_20_80.emplace_back(t_start_charging, t_charging_20_80_on_dc50);
        
        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_DC_50KW, 1);

        num_charged_cars_per_period++;
    }
    else if (POW_STATION_DC_80_KW == pow_station)
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_DC_80KW, 1);

        num_cars_on_station++;

        time_spend_charging = Uniform(0, MAX_TIME_80_KW_DC_STATIONS_20_80);

        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;

        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on DC 80kW Charger In Stage 2 (20-80%) */
        t_charging_20_80_on_dc80 = Time - t_start_charging;

        /* Statistics - Store Time Spend on Charging in Stage 2*/
        ev_stats_dc80_20_80.emplace_back(t_start_charging, t_charging_20_80_on_dc80);

        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_DC_80KW, 1);

        num_charged_cars_per_period++;
    }
    else if (POW_STATION_DC_108_KW == pow_station)
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_DC_108KW, 1);

        num_cars_on_station++;

        time_spend_charging = Uniform(0, MAX_TIME_108_KW_DC_STATIONS_20_80);

        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;

        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on DC 108kW Charger In Stage 2 (20-80%) */
        t_charging_20_80_on_dc108 = Time - t_start_charging;

        /* Statistics - Store Time Spend on Charging in Stage 2*/
        ev_stats_dc108_20_80.emplace_back(t_start_charging, t_charging_20_80_on_dc108);

        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_DC_108KW, 1);

        num_charged_cars_per_period++;
    }
    else if (POW_STATION_DC_150_KW == pow_station)
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_DC_150KW, 1);

        num_cars_on_station++;

        time_spend_charging = Uniform(0, MAX_TIME_150_KW_DC_STATIONS_20_80);

        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;

        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on DC 150kW Charger In Stage 2 (20-80%) */
        t_charging_20_80_on_dc150 = Time - t_start_charging;

        /* Statistics - Store Time Spend on Charging in Stage 2*/
        ev_stats_dc150_20_80.emplace_back(t_start_charging, t_charging_20_80_on_dc150);

        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_DC_150KW, 1);

        num_charged_cars_per_period++;
    }
    else
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_DC_160KW, 1);

        num_cars_on_station++;

        time_spend_charging = Uniform(0, MAX_TIME_160_KW_DC_STATIONS_20_80);

        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;

        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on DC 160kW Charger In Stage 2 (20-80%) */
        t_charging_20_80_on_dc160 = Time - t_start_charging;

        /* Statistics - Store Time Spend on Charging in Stage 2*/
        ev_stats_dc160_20_80.emplace_back(t_start_charging, t_charging_20_80_on_dc160);

        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_DC_160KW, 1);

        num_charged_cars_per_period++;
    }
}

void ElectricVehicle::charge_battery_in_stage_80_100(void)
{
    double t_start_charging;

    double t_charging_80_100_on_ac11     = 0.0;
    double t_charging_80_100_on_ac12     = 0.0;
    double t_charging_80_100_on_ac22     = 0.0;
    double t_charging_80_100_on_dc50     = 0.0;
    double t_charging_80_100_on_dc80     = 0.0;
    double t_charging_80_100_on_dc108    = 0.0;
    double t_charging_80_100_on_dc150    = 0.0;
    double t_charging_80_100_on_dc160    = 0.0;

    if (POW_STATION_AC_11_KW == pow_station)
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_AC_11KW, 1);

        num_cars_on_station++;

        /* Generate Time In Uniform Distribution */
        time_spend_charging = Uniform(0, MAX_TIME_11_KW_AC_STATIONS_80_100);

        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;

        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on AC 11kW Charger In Stage 3 (80-100%) */
        t_charging_80_100_on_ac11 = Time - t_start_charging;

        /* Statistics - Store Time Spend on Charging in Stage 2*/
        ev_stats_ac11_80_100.emplace_back(t_start_charging, t_charging_80_100_on_ac11);

        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_AC_11KW, 1);

        num_charged_cars_per_period++;

    }
    else if (POW_STATION_AC_12_KW == pow_station)
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_AC_12KW, 1);

        num_cars_on_station++;

        /* Generate Time In Uniform Distribution */
        time_spend_charging = Uniform(0, MAX_TIME_12_KW_AC_STATIONS_80_100);

        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;

        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on AC 12kW Charger In Stage 3 (80-100%) */
        t_charging_80_100_on_ac12 = Time - t_start_charging;

        /* Statistics - Store Time Spend on Charging in Stage 2*/
        ev_stats_ac12_80_100.emplace_back(t_start_charging, t_charging_80_100_on_ac12);

        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_AC_12KW, 1);

        num_charged_cars_per_period++;

    }
    else if (POW_STATION_AC_22_KW == pow_station)
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_AC_22KW, 1);

        num_cars_on_station++;

        time_spend_charging = Uniform(0, MAX_TIME_22_KW_AC_STATIONS_80_100);

        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;

        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on AC 22kW Charger In Stage 3 (80-100%) */
        t_charging_80_100_on_ac22 = Time - t_start_charging;

        /* Statistics - Store Time Spend on Charging in Stage 2*/
        ev_stats_ac22_80_100.emplace_back(t_start_charging, t_charging_80_100_on_ac22);

        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_AC_22KW, 1);

        num_charged_cars_per_period++;

    }
    else if (POW_STATION_DC_50_KW == pow_station)
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_DC_50KW, 1);

        num_cars_on_station++;

        time_spend_charging = Uniform(0, MAX_TIME_50_KW_DC_STATIONS_80_100);

        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;

        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on DC 50kW Charger In Stage 3 (80-100%) */
        t_charging_80_100_on_dc50 = Time - t_start_charging;

        /* Statistics - Store Time Spend on Charging in Stage 2*/
        ev_stats_dc50_80_100.emplace_back(t_start_charging, t_charging_80_100_on_dc50);
        
        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_DC_50KW, 1);

        num_charged_cars_per_period++;
    }
    else if (POW_STATION_DC_80_KW == pow_station)
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_DC_80KW, 1);

        num_cars_on_station++;

        time_spend_charging = Uniform(0, MAX_TIME_80_KW_DC_STATIONS_80_100);

        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;

        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on DC 80kW Charger In Stage 3 (80-100%) */
        t_charging_80_100_on_dc80 = Time - t_start_charging;

        /* Statistics - Store Time Spend on Charging in Stage 2*/
        ev_stats_dc80_80_100.emplace_back(t_start_charging, t_charging_80_100_on_dc80);

        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_DC_80KW, 1);

        num_charged_cars_per_period++;
    }
    else if (POW_STATION_DC_108_KW == pow_station)
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_DC_108KW, 1);

        num_cars_on_station++;

        time_spend_charging = Uniform(0, MAX_TIME_108_KW_DC_STATIONS_80_100);

        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;

        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on DC 108kW Charger In Stage 3 (80-100%) */
        t_charging_80_100_on_dc108 = Time - t_start_charging;

        /* Statistics - Store Time Spend on Charging in Stage 2*/
        ev_stats_dc108_80_100.emplace_back(t_start_charging, t_charging_80_100_on_dc108);

        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_DC_108KW, 1);

        num_charged_cars_per_period++;

    }
    else if (POW_STATION_DC_150_KW == pow_station)
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_DC_150KW, 1);

        num_cars_on_station++;

        time_spend_charging = Uniform(0, MAX_TIME_150_KW_DC_STATIONS_80_100);

        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;

        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on DC 150kW Charger In Stage 3 (80-100%) */
        t_charging_80_100_on_dc150 = Time - t_start_charging;

        /* Statistics - Store Time Spend on Charging in Stage 2*/
        ev_stats_dc150_80_100.emplace_back(t_start_charging, t_charging_80_100_on_dc150);

        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_DC_150KW, 1);

        num_charged_cars_per_period++;
    }
    else
    {
        /* Will Take Up One Place In The Store or Will Wait */
        Enter(CHAR_STATION_DC_160KW, 1);

        num_cars_on_station++;

        time_spend_charging = Uniform(0, MAX_TIME_160_KW_DC_STATIONS_80_100);

        /* Statistics - Current Time When Charging Started */
        t_start_charging = Time;

        /* Charging */
        Wait(time_spend_charging);

        /* Statistics - Time of Charging on DC 160kW Charger In Stage 3 (80-100%) */
        t_charging_80_100_on_dc160 = Time - t_start_charging;

        /* Statistics - Store Time Spend on Charging in Stage 2*/
        ev_stats_dc160_80_100.emplace_back(t_start_charging, t_charging_80_100_on_dc160);

        /* Leave The Space In Charging Station */
        Leave(CHAR_STATION_DC_160KW, 1);

        num_charged_cars_per_period++;
    }
}

/**
 * @brief Defines behavior of process EletricVehicle.
 */
void ElectricVehicle::Behavior()
{
    /* Get Model Time From SIMLIB */
    start_time = Time;

    /* Choose Starting Battery State */
    choose_battery_cap();

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

    /* Histogram statistics */
    time_spend_in_system(Time-start_time);

    /* Terminate Process */
    Terminate();
}
