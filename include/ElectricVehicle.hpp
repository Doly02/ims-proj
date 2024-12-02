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


#ifndef ELECTRIC_VEHICLE_HPP
#define ELECTRIC_VEHICLE_HPP
/************************************************/
/*                  Libraries                   */
/************************************************/
#include <vector>
#include <utility>
#include "../include/definitions.hpp"

/************************************************/
/*                  Global Variables            */
/************************************************/
/**
 * @brief Stores statistical data for electric vehicle charging sessions.
 */
extern double num_charged_cars_per_period;
extern double num_cars_on_station;

extern std::vector<std::pair<double, double>> ev_stats_ac11_0_20;
extern std::vector<std::pair<double, double>> ev_stats_ac12_0_20;
extern std::vector<std::pair<double, double>> ev_stats_ac22_0_20;
extern std::vector<std::pair<double, double>> ev_stats_dc50_0_20;
extern std::vector<std::pair<double, double>> ev_stats_dc108_0_20;
extern std::vector<std::pair<double, double>> ev_stats_dc150_0_20;

extern std::vector<std::pair<double, double>> ev_stats_ac11_20_80;
extern std::vector<std::pair<double, double>> ev_stats_ac12_20_80;
extern std::vector<std::pair<double, double>> ev_stats_ac22_20_80;
extern std::vector<std::pair<double, double>> ev_stats_dc50_20_80;
extern std::vector<std::pair<double, double>> ev_stats_dc108_20_80;
extern std::vector<std::pair<double, double>> ev_stats_dc150_20_80;

extern std::vector<std::pair<double, double>> ev_stats_ac11_80_100;
extern std::vector<std::pair<double, double>> ev_stats_ac12_80_100;
extern std::vector<std::pair<double, double>> ev_stats_ac22_80_100;
extern std::vector<std::pair<double, double>> ev_stats_dc50_80_100;
extern std::vector<std::pair<double, double>> ev_stats_dc108_80_100;
extern std::vector<std::pair<double, double>> ev_stats_dc150_80_100;

extern Histogram time_spend_in_system;

/**
 * @brief Chances to choose the stations.
 */
extern double chance_11_kwh_ac_station;
extern double chance_12_kwh_ac_station;
extern double chance_22_kwh_ac_station;
extern double chance_50_kwh_dc_station;
extern double chance_108_kwh_dc_station;
extern double chance_150_kwh_dc_station;


/**
 * @brief Charging station stores.
 */
extern Store CHAR_STATION_AC_11KWH;
extern Store CHAR_STATION_AC_12KWH;
extern Store CHAR_STATION_AC_22KWH;
extern Store CHAR_STATION_DC_50KWH;
extern Store CHAR_STATION_DC_108KWH;
extern Store CHAR_STATION_DC_150KWH;

/**
 * @class ElectricVehicle
 * @brief Represents an electric car in the simulation.
 */
class ElectricVehicle : public Process
{
    private:
        char_state_t char_state;
        pow_station_t pow_station;

        double start_time;
        double time_spend_in_front;
        double time_spend_charging;

        void choose_battery_cap();
        void choose_battery_station();
        void charge_battery_in_stage_0_20();
        void continue_charge_battery_in_stage_20_80();
        void charge_battery_in_stage_20_80();
        void charge_battery_in_stage_80_100();
        void Behavior() override;

    public:
        ElectricVehicle() = default;
        ~ElectricVehicle() = default;
};

#endif /* ELECTRIC_VEHICLE_HPP */
