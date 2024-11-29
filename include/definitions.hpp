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
    POW_STATION_AC_11_KWH = 0,
    POW_STATION_AC_12_KWH,
    POW_STATION_AC_22_KWH,
    POW_STATION_DC_50_KWH,
    POW_STATION_DC_108_KWH,
    POW_STATION_DC_150_KWH

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
#define NUM_OF_CARS_IN_CITY                 (2120)

/**
 * @brief   Percentage Of Cars To Charge In Period
 */
#define CHARGING_PERCENTAGE_OF_CARS         (0.05)

/**
 * @brief   Chance That Car Will Choose 11kWh AC Charging Station.
 * @details 6 / 173 = 3.4%
 */
#define CHANCE_11_KWH_AC_STATIONS            (0.034)

/**
 * @brief   Chance That Car Will Choose 12kWh AC Charging Station.
 * @details 20 / 173 = 11.6%
 */
#define CHANCE_12_KWH_AC_STATIONS           (CHANCE_11_KWH_AC_STATIONS + 0.116)

/**
 * @brief   Chance That Car Will Choose 22kWh AC Charging Station.
 * @details 77 / 173 = 44.5%
 */
#define CHANCE_22_KWH_AC_STATIONS           (CHANCE_12_KWH_AC_STATIONS + 0.445)

/**
 * @brief   Chance That Car Will Choose 50kWh DC Charging Station.
 * @details 54 / 173 = 31.1%
 */
#define CHANCE_50_KWH_DC_STATIONS           (CHANCE_22_KWH_AC_STATIONS + 0.312)

/**
 * @brief   Chance That Car Will Choose 108kWh DC Charging Station.
 * @details 11 / 173 = 6.3%
 */
#define CHANCE_108_KWH_DC_STATIONS          (CHANCE_50_KWH_DC_STATIONS + 0.063)

/**
 * @brief   Chance That Car Will Choose 150kWh DC Charging Station.
 * @details 5 / 173 = 2.9%
 */
#define CHANCE_150_KWH_DC_STATIONS          (CHANCE_108_KWH_DC_STATIONS + 0.029)

/**
 * @brief Number of 11kWh AC Charging Stations in Brno.
 */
#define NUM_11_KWH_AC_STATIONS              (12)

/**
 * @brief Number of 12kWh AC Charging Stations in Brno.
 */
#define NUM_12_KWH_AC_STATIONS              (24)

/**
 * @brief Number of 22kWh AC Charging Stations in Brno.
 */
#define NUM_22_KWH_AC_STATIONS              (77)

/**
 * @brief Number of 50kWh DC Charging Stations in Brno.
 */
#define NUM_50_KWH_DC_STATIONS              (54)

/**
 * @brief Number of 108kWh DC Charging Stations in Brno.
 */
#define NUM_108_KWH_DC_STATIONS             (11)

/**
 * @brief Number of 150kWh DC Charging Stations in Brno.
 */
#define NUM_150_KWH_DC_STATIONS             (5)

/**
 * @brief Number Charging Stations in Brno.
 */
#define NUM_ALL_STATIONS (NUM_12_KWH_AC_STATIONS + NUM_22_KWH_AC_STATIONS + NUM_50_KWH_DC_STATIONS + NUM_108_KWH_DC_STATIONS + NUM_150_KWH_DC_STATIONS)

/**
 * @brief   Max. Time For Charging on AC 11 kWh Charger,
 *          In First Stage of Charging (0% - 20%).
 * @details 1.30 hours => 78 minutes
 */
#define MAX_TIME_11_KWH_AC_STATIONS_0_20     (78)
/**
 * @brief   Max. Time For Charging on AC 12 kWh Charger,
 *          In First Stage of Charging (0% - 20%).
 * @details 1.19 hours => 71.4 minutes
 */
#define MAX_TIME_12_KWH_AC_STATIONS_0_20     (71.4)

/**
 * @brief   Max. Time For Charging on AC 22 kWh Charger,
 *          In First Stage of Charging (0% - 20%).
 * @details 0.65 hours => 39 minutes
 */
#define MAX_TIME_22_KWH_AC_STATIONS_0_20     (39)

/**
 * @brief   Max. Time For Charging on DC 50 kWh Charger,
 *          In First Stage of Charging (0% - 20%).
 * @details 0.57 hours => 34.2 minutes
 */
#define MAX_TIME_50_KWH_DC_STATIONS_0_20     (34.2)

/**
 * @brief   Max. Time For Charging on DC 108 kWh Charger,
 *          In First Stage of Charging (0% - 20%).
 * @details 0.26 hours => 15.6 minutes
 */
#define MAX_TIME_108_KWH_DC_STATIONS_0_20    (15.6)

/**
 * @brief   Max. Time For Charging on DC 150 kWh Charger,
 *          In First Stage of Charging (0% - 20%).
 * @details 0.19 hours => 11.4 minutes
 */
#define MAX_TIME_150_KWH_DC_STATIONS_0_20    (11.4)

/**
 * @brief   Max. Time For Charging on AC 11 kWh Charger,
 *          In Second Stage of Charging (20% - 80%).
 * @details 3.90 hours => 234 minutes
 */
#define MAX_TIME_11_KWH_AC_STATIONS_20_80    (234)
/**
 * @brief   Max. Time For Charging on AC 12 kWh Charger,
 *          In Second Stage of Charging (20% - 80%).
 * @details 3.58 hours => 214.8 minutes
 */
#define MAX_TIME_12_KWH_AC_STATIONS_20_80    (214.8)

/**
 * @brief   Max. Time For Charging on AC 22 kWh Charger,
 *          In Second Stage of Charging (20% - 80%).
 * @details 1.95 hours => 117 minutes
 */
#define MAX_TIME_22_KWH_AC_STATIONS_20_80    (117)

/**
 * @brief   Max. Time For Charging on DC 50 kWh Charger,
 *          In Second Stage of Charging (20% - 80%).
 * @details 1.01 hours => 60.6 minutes
 */
#define MAX_TIME_50_KWH_DC_STATIONS_20_80    (60.6)

/**
 * @brief   Max. Time For Charging on DC 108 kWh Charger,
 *          In Second Stage of Charging (20% - 80%).
 * @details 0.47 hours => 28.2 minutes
 */
#define MAX_TIME_108_KWH_DC_STATIONS_20_80   (28.2)

/**
 * @brief   Max. Time For Charging on DC 150 kWh Charger,
 *          In Second Stage of Charging (20% - 80%).
 * @details 0.34 hours => 20.4 minutes
 */
#define MAX_TIME_150_KWH_DC_STATIONS_20_80   (20.4)

/**
 * @brief   Max. Time For Charging on AC 11 kWh Charger,
 *          In Third Stage of Charging (80% - 100%).
 * @details 2.60 hours => 156 minutes
 */
#define MAX_TIME_11_KWH_AC_STATIONS_80_100   (156)

/**
 * @brief   Max. Time For Charging on AC 12 kWh Charger,
 *          In Third Stage of Charging (80% - 100%).
 * @details 2.38 hours => 142.8 minutes
 */
#define MAX_TIME_12_KWH_AC_STATIONS_80_100   (142.8)

/**
 * @brief   Max. Time For Charging on AC 22 kWh Charger,
 *          In Third Stage of Charging (80% - 100%).
 * @details 1.30 hours => 78 minutes
 */
#define MAX_TIME_22_KWH_AC_STATIONS_80_100   (78)

/**
 * @brief   Max. Time For Charging on DC 50 kWh Charger,
 *          In Third Stage of Charging (80% - 100%).
 * @details 0.82 hours => 49.2 minutes
 */
#define MAX_TIME_50_KWH_DC_STATIONS_80_100   (49.2)

/**
 * @brief   Max. Time For Charging on DC 108 kWh Charger,
 *          In Third Stage of Charging (80% - 100%).
 * @details 0.38 hours => 22.8 minutes
 */
#define MAX_TIME_108_KWH_DC_STATIONS_80_100  (22.8)

/**
 * @brief   Max. Time For Charging on DC 108 kWh Charger,
 *          In Third Stage of Charging (80% - 100%).
 * @details 0.27 hours => 16.2 minutes
 */
#define MAX_TIME_150_KWH_DC_STATIONS_80_100  (16.2)

#endif // DEFINITIONS_HPP