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
#include "../include/GeneratorDay.hpp"
#include "../include/ElectricVehicle.hpp"

/************************************************/
/*                  Global Variables            */
/************************************************/
int num_of_cars_in_city = NUM_OF_CARS_IN_CITY;
double charging_percentage_of_cars = CHARGING_PERCENTAGE_OF_CARS;

int ac12_chargers = NUM_12_KWH_AC_STATIONS;
int ac22_chargers = NUM_22_KWH_AC_STATIONS;
int dc50_chargers = NUM_50_KWH_DC_STATIONS;
int dc108_chargers = NUM_108_KWH_DC_STATIONS;

double chance_12_kwh_ac_station = CHANCE_12_KWH_AC_STATIONS;
double chance_22_kwh_ac_station = CHANCE_22_KWH_AC_STATIONS;
double chance_50_kwh_dc_station = CHANCE_50_KWH_DC_STATIONS;
double chance_108_kwh_dc_station = CHANCE_108_KWH_DC_STATIONS;

bool is_day = false;
bool is_24_hours = false;
/************************************************/
/*                   Statistics                 */
/************************************************/

/**
 * TODO:    Create HERE The Variables For Model Statistics. Variables Then Should Be Extern Into Electric Vehicle Class.
 *          Or Create in The Electric Vehicle Class And Then Use Them Here.
 *
 */

/************************************************/
/*                   Main                       */
/************************************************/
void print_usage(void)
{
    printf("Usage: ./sim [day|night|24hours] [-total_cars [number]] [-charging_percentage [number]] [-ac12 [number]] [-ac22 [number]] [-dc50 [number]] [-dc108 [number]] [-h]\n");
    printf("Options:\n");
    printf("  -total_cars [number]             : Specify The Number of Cars in The City\n");
    printf("  -charging_percentage [number]    : Specify The Percentage of Cars to Charge During the Period (value must be between 0 and 1, e.g., 0.25 for 25%%)\n");
    printf("  -ac12  [number]                  : Specify The Number of AC 12 kWh Chargers\n");
    printf("  -ac22  [number]                  : Specify The Number of AC 22 kWh Chargers\n");
    printf("  -dc50  [number]                  : Specify The Number of DC 50 kWh Chargers\n");
    printf("  -dc108 [number]                  : Specify The Number of DC 108 kWh Chargers\n");
    printf("  -h                               : Display Usage Message\n");
}

bool parse_args(int argc, char *argv[])
{
    if (argc < 2)
    {
        print_usage();
        return false;
    }

    if (strcmp(argv[1], "day") == 0)
    {
        is_day = true;
    }
    else if (strcmp(argv[1], "night") == 0)
    {
        is_day = false;
    }
    else if (strcmp(argv[1], "24hours") == 0)
    {
        is_24_hours = true;
    }
    else
    {
        print_usage();
        return false;
    }

    for (int i = 2; i < argc; ++i)
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            print_usage();
            return false;
        }
        else if (strcmp(argv[i], "-total_cars") == 0 && i + 1 < argc)
        {
            num_of_cars_in_city = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-charging_percentage") == 0 && i + 1 < argc)
        {
            charging_percentage_of_cars = atof(argv[++i]);
            if (charging_percentage_of_cars < 0.0 || charging_percentage_of_cars > 1.0)
            {
                printf("Error: charging_percentage must be between 0 and 1.\n");
                return false;
            }
        }
        else if (strcmp(argv[i], "-ac12") == 0 && i + 1 < argc)
        {
            ac12_chargers = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-ac22") == 0 && i + 1 < argc)
        {
            ac22_chargers = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-dc50") == 0 && i + 1 < argc)
        {
            dc50_chargers = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-dc108") == 0 && i + 1 < argc)
        {
            dc108_chargers = atoi(argv[++i]);
        }
        else
        {
            printf("Unknown option or missing value: %s\n", argv[i]);
            print_usage();
            return false;
        }
    }

    return true;
}

void update_store_values() {
    CHAR_STATION_AC_12KWH.SetCapacity(ac12_chargers);
    CHAR_STATION_AC_22KWH.SetCapacity(ac22_chargers);
    CHAR_STATION_DC_50KWH.SetCapacity(dc50_chargers);
    CHAR_STATION_DC_108KWH.SetCapacity(dc108_chargers);
}

void update_stations_chance() {
    double count = ac12_chargers + ac22_chargers + dc50_chargers + dc108_chargers;
    chance_12_kwh_ac_station = ac12_chargers / count;
    chance_22_kwh_ac_station = chance_12_kwh_ac_station + (ac22_chargers / count);
    chance_50_kwh_dc_station = chance_22_kwh_ac_station + (dc50_chargers / count);
    chance_108_kwh_dc_station = chance_50_kwh_dc_station + (dc108_chargers / count);
}

int main(int argc, char *argv[]) 
{
    bool retVal;
    
    /* Parse Arguments */
    retVal = parse_args(argc, argv);
    if (!retVal){
        return 1;
    }

    /* Update Store Capacities Based on Parsed Arguments */
    update_store_values();

    /* Update Chances to Choose the Stations Based on Parsed Arguments */
    update_stations_chance();

    printf("Modeling & Simulation Project - Electromobility in Brno 2024\n");

    // TODO: Simulation of whole 24 hours
    if (is_24_hours)   /* Simulation Of 24 hours period */
    {
        Init(0, WHOLE_DAY_TIME);
        (new TransactionDay(WHOLE_DAY_TIME))->Activate();
        (new GeneratorDay(num_of_cars_in_city, charging_percentage_of_cars))->Activate();
    }

    else if (is_day)    /* Simulation Of Day */
    {
        Init(0, DAYTIME_LENGTH);
        (new TransactionDay(DAYTIME_LENGTH))->Activate();
        (new GeneratorDay(num_of_cars_in_city, charging_percentage_of_cars))->Activate();
    }
    else           /* Simulation Of Night */
    {
        Init(0, NIGHTTIME_LENGTH);
        (new TransactionDay(NIGHTTIME_LENGTH))->Activate();
        (new GeneratorDay(num_of_cars_in_city, charging_percentage_of_cars))->Activate();
        /**
         * TODO: Update The Code, Current Implementation Is The Same For Day/Night Mode,
         * In Both Modes Runs The Day Mode And After That The Night Mode.
         **/  
    }   
    Run();

    /* Print Statistics */
    SetOutput("SimOutput");
    CHAR_STATION_AC_12KWH.Output();
    CHAR_STATION_AC_22KWH.Output();
    CHAR_STATION_DC_50KWH.Output();
    CHAR_STATION_DC_108KWH.Output();

    if (is_24_hours)
        printf("Statistics during 24 hours period\n");
    else if (is_day)
        printf("Statistics during the day period 7:00-21:00\n");
    else
        printf("Statistics during the night period 21:00-7:00\n");

    printf("---------------------------------------------------------------\n");
    std::cout << "Number of generated vehicles: " << num_generated_cars << std::endl;
    std::cout << "Number of charged vehicles: " << num_charged_cars_per_period << std::endl;
    std::cout << "Number of vehicles on stations: " << num_cars_on_station << std::endl;

    return 0;
}