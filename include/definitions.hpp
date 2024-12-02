/******************************
 *  Project:        IMS Project - Electromobility in Brno
 *  File Name:      definitions.hpp
 *  Author:         Tomas Dolak, Monika Zahradnikova
 *  Date:           17.11.2024
 *  Description:    Includes Definitions For Simulation.
 *
 * ****************************/

/******************************
 *  @package        IMS Project - Electromobility in Brno
 *  @file           definitions.hpp
 *  @author         Tomas Dolak, Monika Zahradnikova
 *  @date           17.11.2024
 *  @brief          Includes Definitions For Simulation.
 * ****************************/

#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

/************************************************/
/*                  Libraries                   */
/************************************************/
#include "simlib.h"
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
#include <iostream>

/************************************************/
/*                   Structures                 */
/************************************************/

/**
 * @brief Type of Power Charging Station.
 */
typedef enum
{
    POW_STATION_AC_11_KW = 0,
    POW_STATION_AC_12_KW,
    POW_STATION_AC_22_KW,
    POW_STATION_DC_50_KW,
    POW_STATION_DC_108_KW,
    POW_STATION_DC_150_KW

} pow_station_t;

/**
 * @brief Charging State In Which The Car Is.
 */
typedef enum
{
    CHAR_STATE_0_20 = 0,
    CHAR_STATE_20_80,
    CHAR_STATE_80_100

} char_state_t;
/************************************************/
/*                   Definitions                */
/************************************************/

/**
 * @brief Whole Day Time In Seconds.
 */
#define WHOLE_DAY_TIME                      (24 * 60)

/**
 * @brief Daytime Length In Seconds.
 */
#define DAYTIME_LENGTH                      (14 * 60)

/**
 * @brief Nighttime Length In Seconds.
 */
#define NIGHTTIME_LENGTH                    (10 * 60)


#define PERIOD_DAYTIME                      (true)

#define PERIOD_NIGHTTIME                    (false)

/**
 * @brief   Number Of Cars In The City
 */
#define NUM_OF_CARS_IN_CITY                 (1700)

/**
 * @brief   Percentage Of Cars To Charge In Day
 */
#define CHARGING_PERCENTAGE_OF_CARS_DAY         (0.177)

/**
 * @brief   Percentage Of Cars To Charge At Night
 */
#define CHARGING_PERCENTAGE_OF_CARS_NIGHT       (0.0177)

/**
 * @brief   Chance That Car Will Choose 11kWh AC Charging Station.
 * @details 6 / 305 = 1.97%
 */
#define CHANCE_11_KW_AC_STATIONS            (0.0197)

/**
 * @brief   Chance That Car Will Choose 12kWh AC Charging Station.
 * @details 20 / 305 = 6.56%
 */
#define CHANCE_12_KW_AC_STATIONS           (CHANCE_11_KW_AC_STATIONS + 0.0656)

/**
 * @brief   Chance That Car Will Choose 22kWh AC Charging Station.
 * @details 197 / 305 = 64.59%
 */
#define CHANCE_22_KW_AC_STATIONS           (CHANCE_12_KW_AC_STATIONS + 0.6459)

/**
 * @brief   Chance That Car Will Choose 50kWh DC Charging Station.
 * @details 54 / 305 = 17.70%
 */
#define CHANCE_50_KW_DC_STATIONS           (CHANCE_22_KW_AC_STATIONS + 0.1770)

/**
 * @brief   Chance That Car Will Choose 108kWh DC Charging Station.
 * @details 11 / 305 = 3.61%
 */
#define CHANCE_108_KW_DC_STATIONS          (CHANCE_50_KW_DC_STATIONS + 0.0361)

/**
 * @brief   Chance That Car Will Choose 150kWh DC Charging Station.
 * @details 17 / 305 = 5.57%
 */
#define CHANCE_150_KW_DC_STATIONS          (CHANCE_108_KW_DC_STATIONS + 0.0557)

/**
 * @brief Number of 11kWh AC Charging Stations in Brno.
 */
#define NUM_11_KW_AC_STATIONS              (6)

/**
 * @brief Number of 12kWh AC Charging Stations in Brno.
 */
#define NUM_12_KW_AC_STATIONS              (20)

/**
 * @brief Number of 22kWh AC Charging Stations in Brno.
 */
#define NUM_22_KW_AC_STATIONS              (197)

/**
 * @brief Number of 50kWh DC Charging Stations in Brno.
 */
#define NUM_50_KW_DC_STATIONS              (54)

/**
 * @brief Number of 108kWh DC Charging Stations in Brno.
 */
#define NUM_108_KW_DC_STATIONS             (11)

/**
 * @brief Number of 150kWh DC Charging Stations in Brno.
 */
#define NUM_150_KW_DC_STATIONS             (17)

/**
 * @brief Number Charging Stations in Brno.
 */
#define NUM_ALL_STATIONS (NUM_11_KW_AC_STATIONS + NUM_12_KW_AC_STATIONS + NUM_22_KW_AC_STATIONS + NUM_50_KW_DC_STATIONS + NUM_108_KW_DC_STATIONS + NUM_150_KW_DC_STATIONS)

/**
 * @brief   Max. Time For Charging on AC 11 kW Charger,
 *          In First Stage of Charging (0% - 20%).
 * @details 1.30 hours => 78 minutes
 */
#define MAX_TIME_11_KW_AC_STATIONS_0_20     (78)
/**
 * @brief   Max. Time For Charging on AC 12 kW Charger,
 *          In First Stage of Charging (0% - 20%).
 * @details 1.19 hours => 71.4 minutes
 */
#define MAX_TIME_12_KW_AC_STATIONS_0_20     (71.4)

/**
 * @brief   Max. Time For Charging on AC 22 kW Charger,
 *          In First Stage of Charging (0% - 20%).
 * @details 0.65 hours => 39 minutes
 */
#define MAX_TIME_22_KW_AC_STATIONS_0_20     (39)

/**
 * @brief   Max. Time For Charging on DC 50 kW Charger,
 *          In First Stage of Charging (0% - 20%).
 * @details 0.57 hours => 34.2 minutes
 */
#define MAX_TIME_50_KW_DC_STATIONS_0_20     (34.2)

/**
 * @brief   Max. Time For Charging on DC 108 kW Charger,
 *          In First Stage of Charging (0% - 20%).
 * @details 0.26 hours => 15.6 minutes
 */
#define MAX_TIME_108_KW_DC_STATIONS_0_20    (15.6)

/**
 * @brief   Max. Time For Charging on DC 150 kW Charger,
 *          In First Stage of Charging (0% - 20%).
 * @details 0.19 hours => 11.4 minutes
 */
#define MAX_TIME_150_KW_DC_STATIONS_0_20    (11.4)

/**
 * @brief   Max. Time For Charging on AC 11 kW Charger,
 *          In Second Stage of Charging (20% - 80%).
 * @details 3.90 hours => 234 minutes
 */
#define MAX_TIME_11_KW_AC_STATIONS_20_80    (234)
/**
 * @brief   Max. Time For Charging on AC 12 kW Charger,
 *          In Second Stage of Charging (20% - 80%).
 * @details 3.58 hours => 214.8 minutes
 */
#define MAX_TIME_12_KW_AC_STATIONS_20_80    (214.8)

/**
 * @brief   Max. Time For Charging on AC 22 kW Charger,
 *          In Second Stage of Charging (20% - 80%).
 * @details 1.95 hours => 117 minutes
 */
#define MAX_TIME_22_KW_AC_STATIONS_20_80    (117)

/**
 * @brief   Max. Time For Charging on DC 50 kW Charger,
 *          In Second Stage of Charging (20% - 80%).
 * @details 1.01 hours => 60.6 minutes
 */
#define MAX_TIME_50_KW_DC_STATIONS_20_80    (60.6)

/**
 * @brief   Max. Time For Charging on DC 108 kW Charger,
 *          In Second Stage of Charging (20% - 80%).
 * @details 0.47 hours => 28.2 minutes
 */
#define MAX_TIME_108_KW_DC_STATIONS_20_80   (28.2)

/**
 * @brief   Max. Time For Charging on DC 150 kW Charger,
 *          In Second Stage of Charging (20% - 80%).
 * @details 0.34 hours => 20.4 minutes
 */
#define MAX_TIME_150_KW_DC_STATIONS_20_80   (20.4)

/**
 * @brief   Max. Time For Charging on AC 11 kW Charger,
 *          In Third Stage of Charging (80% - 100%).
 * @details 2.60 hours => 156 minutes
 */
#define MAX_TIME_11_KW_AC_STATIONS_80_100   (156)

/**
 * @brief   Max. Time For Charging on AC 12 kW Charger,
 *          In Third Stage of Charging (80% - 100%).
 * @details 2.38 hours => 142.8 minutes
 */
#define MAX_TIME_12_KW_AC_STATIONS_80_100   (142.8)

/**
 * @brief   Max. Time For Charging on AC 22 kW Charger,
 *          In Third Stage of Charging (80% - 100%).
 * @details 1.30 hours => 78 minutes
 */
#define MAX_TIME_22_KW_AC_STATIONS_80_100   (78)

/**
 * @brief   Max. Time For Charging on DC 50 kW Charger,
 *          In Third Stage of Charging (80% - 100%).
 * @details 0.82 hours => 49.2 minutes
 */
#define MAX_TIME_50_KW_DC_STATIONS_80_100   (49.2)

/**
 * @brief   Max. Time For Charging on DC 108 kW Charger,
 *          In Third Stage of Charging (80% - 100%).
 * @details 0.38 hours => 22.8 minutes
 */
#define MAX_TIME_108_KW_DC_STATIONS_80_100  (22.8)

/**
 * @brief   Max. Time For Charging on DC 150 kW Charger,
 *          In Third Stage of Charging (80% - 100%).
 * @details 0.27 hours => 16.2 minutes
 */
#define MAX_TIME_150_KW_DC_STATIONS_80_100  (16.2)

#endif // DEFINITIONS_HPP