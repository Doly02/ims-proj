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


#endif // DEFINITIONS_HPP