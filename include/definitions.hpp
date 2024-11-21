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

} char_state_t
/************************************************/
/*                   Definitions                */
/************************************************/

/**
 * @brief Whole Day Time In Seconds.
 */
#define WHOLE_DAY_TIME                      (86400)

/**
 * @brief Daytime Length In Seconds.
 */
#define DAYTIME_LENGTH                      (14 * 3600)

/**
 * @brief Nighttime Length In Seconds.
 */
#define NIGHTTIME_LENGTH                    (10 * 3600)

#define PERIOD_DAYTIME                      (true)

#define PERIOD_NIGHTTIME                    (false)

/**
 * @brief   Chance That Car Will Choose 12kWh AC Charging Station.
 * @details 12 / 102 = 11.76% 
 */
#define CHANCE_12_KWH_AC_STATIONS           (0.1176)

/**
 * @brief   Chance That Car Will Choose 22kWh AC Charging Station.
 * @details 58 / 102 = 56.86% 
 */
#define CHANCE_22_KWH_AC_STATIONS           (0.5686)

/**
 * @brief   Chance That Car Will Choose 58kWh DC Charging Station.
 * @details 22 / 102 = 21.57% 
 */
#define CHANCE_50_KWH_DC_STATIONS           (0.2156)

/**
 * @brief   Chance That Car Will Choose 108kWh DC Charging Station.
 * @details 10 / 102 = 9.80% 
 */
#define CHANCE_108_KWH_DC_STATIONS          (0.0980)

/**
 * @brief Number of 12kWh AC Charging Stations.
 */
#define NUM_12_KWH_AC_STATIONS              (12)

/**
 * @brief Number of 22kWh AC Charging Stations.
 */
#define NUM_22_KWH_AC_STATIONS              (58)

/**
 * @brief Number of 50kWh DC Charging Stations.
 */
#define NUM_50_KWH_DC_STATIONS              (22)

/**
 * @brief Number of 108kWh DC Charging Stations.
 */
#define NUM_108_KWH_DC_STATIONS             (10)

/**
 * @brief Max. Time For Charging on AC 12 kWh Charger,
 *        In First Stage of Charging (0% - 20%).
 */
#define MAX_TIME_12_KWH_AC_STATIONS_0_20     (0.5)

/**
 * @brief Max. Time For Charging on AC 22 kWh Charger,
 *        In First Stage of Charging (0% - 20%).
 */
#define MAX_TIME_22_KWH_AC_STATIONS_0_20     (0.5)

/**
 * @brief Max. Time For Charging on DC 50 kWh Charger,
 *        In First Stage of Charging (0% - 20%).
 */
#define MAX_TIME_50_KWH_DC_STATIONS_0_20     (0.5)

/**
 * @brief Max. Time For Charging on DC 108 kWh Charger,
 *        In First Stage of Charging (0% - 20%).
 */
#define MAX_TIME_108_KWH_DC_STATIONS_0_20    (0.5)

/**
 * @brief Max. Time For Charging on AC 12 kWh Charger,
 *        In First Stage of Charging (20% - 80%).
 */
#define MAX_TIME_12_KWH_AC_STATIONS_20_80    (0.5)

/**
 * @brief Max. Time For Charging on AC 22 kWh Charger,
 *        In First Stage of Charging (20% - 80%).
 */
#define MAX_TIME_22_KWH_AC_STATIONS_20_80    (0.5)

/**
 * @brief Max. Time For Charging on DC 50 kWh Charger,
 *        In First Stage of Charging (20% - 80%).
 */
#define MAX_TIME_50_KWH_DC_STATIONS_20_80    (0.5)

/**
 * @brief Max. Time For Charging on DC 108 kWh Charger,
 *        In First Stage of Charging (20% - 80%).
 */
#define MAX_TIME_108_KWH_DC_STATIONS_20_80   (0.5)

/**
 * @brief Max. Time For Charging on AC 12 kWh Charger,
 *        In First Stage of Charging (80% - 100%).
 */
#define MAX_TIME_12_KWH_AC_STATIONS_80_100   (0.5)

/**
 * @brief Max. Time For Charging on AC 22 kWh Charger,
 *        In First Stage of Charging (80% - 100%).
 */
#define MAX_TIME_22_KWH_AC_STATIONS_80_100   (0.5)

/**
 * @brief Max. Time For Charging on DC 50 kWh Charger,
 *        In First Stage of Charging (80% - 100%).
 */
#define MAX_TIME_50_KWH_DC_STATIONS_80_100   (0.5)

/**
 * @brief Max. Time For Charging on DC 108 kWh Charger,
 *        In First Stage of Charging (80% - 100%).
 */
#define MAX_TIME_108_KWH_DC_STATIONS_80_100  (0.5)

#endif // DEFINITIONS_HPP