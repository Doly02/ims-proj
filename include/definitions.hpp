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
    POW_STATION_AC_12_KWH = 0,
    POW_STATION_AC_22_KWH,
    POW_STATION_DC_50_KWH,
    POW_STATION_DC_108_KWH

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
#define CHARGING_PERCENTAGE_OF_CARS         (0.3)

/**
 * @brief   Chance That Car Will Choose 12kWh AC Charging Station.
 * @details 12 / 102 = 11.77%
 */
#define CHANCE_12_KWH_AC_STATIONS           (0.1177)

/**
 * @brief   Chance That Car Will Choose 22kWh AC Charging Station.
 * @details 58 / 102 = 56.86% 
 */
#define CHANCE_22_KWH_AC_STATIONS           (0.1177 + 0.5686)

/**
 * @brief   Chance That Car Will Choose 58kWh DC Charging Station.
 * @details 22 / 102 = 21.57% 
 */
#define CHANCE_50_KWH_DC_STATIONS           (0.1177 + 0.5686 + 0.2157)

/**
 * @brief   Chance That Car Will Choose 108kWh DC Charging Station.
 * @details 10 / 102 = 9.80% 
 */
#define CHANCE_108_KWH_DC_STATIONS          (0.1177 + 0.5686 + 0.2157 + 0.0980)

/**
 * @brief Number of 12kWh AC Charging Stations in Brno.
 */
#define NUM_12_KWH_AC_STATIONS              (12)

/**
 * @brief Number of 22kWh AC Charging Stations in Brno.
 */
#define NUM_22_KWH_AC_STATIONS              (58)

/**
 * @brief Number of 50kWh DC Charging Stations in Brno.
 */
#define NUM_50_KWH_DC_STATIONS              (22)

/**
 * @brief Number of 108kWh DC Charging Stations in Brno.
 */
#define NUM_108_KWH_DC_STATIONS             (10)

/**
 * @brief   Max. Time For Charging on AC 12 kWh Charger,
 *          In First Stage of Charging (0% - 20%).
 * @details 1.19 hours => 4284 seconds
 */
#define MAX_TIME_12_KWH_AC_STATIONS_0_20     (4284)

/**
 * @brief   Max. Time For Charging on AC 22 kWh Charger,
 *          In First Stage of Charging (0% - 20%).
 * @details 0.65 hours => 2340 seconds
 */
#define MAX_TIME_22_KWH_AC_STATIONS_0_20     (2340)

/**
 * @brief   Max. Time For Charging on DC 50 kWh Charger,
 *          In First Stage of Charging (0% - 20%).
 * @details 0.57 hours => 2052 seconds
 */
#define MAX_TIME_50_KWH_DC_STATIONS_0_20     (2052)

/**
 * @brief   Max. Time For Charging on DC 108 kWh Charger,
 *          In First Stage of Charging (0% - 20%).
 * @details 0.26 hours => 936 seconds
 */
#define MAX_TIME_108_KWH_DC_STATIONS_0_20    (936)

/**
 * @brief   Max. Time For Charging on AC 12 kWh Charger,
 *          In First Stage of Charging (20% - 80%).
 * @details 3.58 hours => 12888 seconds
 */
#define MAX_TIME_12_KWH_AC_STATIONS_20_80    (12888)

/**
 * @brief   Max. Time For Charging on AC 22 kWh Charger,
 *          In First Stage of Charging (20% - 80%).
 * @details 1.95 hours => 7020 seconds
 */
#define MAX_TIME_22_KWH_AC_STATIONS_20_80    (7020)

/**
 * @brief   Max. Time For Charging on DC 50 kWh Charger,
 *          In First Stage of Charging (20% - 80%).
 * @details 1.01 hours => 3636 seconds
 */
#define MAX_TIME_50_KWH_DC_STATIONS_20_80    (3636)

/**
 * @brief   Max. Time For Charging on DC 108 kWh Charger,
 *          In First Stage of Charging (20% - 80%).
 * @details 0.47 hours => 1692 seconds
 */
#define MAX_TIME_108_KWH_DC_STATIONS_20_80   (1692)

/**
 * @brief   Max. Time For Charging on AC 12 kWh Charger,
 *          In First Stage of Charging (80% - 100%).
 * @details 2.38 hours => 8568 seconds
 */
#define MAX_TIME_12_KWH_AC_STATIONS_80_100   (8568)

/**
 * @brief   Max. Time For Charging on AC 22 kWh Charger,
 *          In First Stage of Charging (80% - 100%).
 * @details 1.30 hours => 4680 seconds
 */
#define MAX_TIME_22_KWH_AC_STATIONS_80_100   (4680)

/**
 * @brief   Max. Time For Charging on DC 50 kWh Charger,
 *          In First Stage of Charging (80% - 100%).
 * @details 0.82 hours => 2952 seconds
 */
#define MAX_TIME_50_KWH_DC_STATIONS_80_100   (2952)

/**
 * @brief   Max. Time For Charging on DC 108 kWh Charger,
 *          In First Stage of Charging (80% - 100%).
 * @details 0.38 hours => 1368 seconds
 */
#define MAX_TIME_108_KWH_DC_STATIONS_80_100  (1368)

#endif // DEFINITIONS_HPP