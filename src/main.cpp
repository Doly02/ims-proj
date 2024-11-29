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

#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <fstream>

/************************************************/
/*                  Definitions                 */
/************************************************/
#define EXTRA_PRINTS            0  
#define DEBUG                   0
/************************************************/
/*                  Global Variables            */
/************************************************/
int num_of_cars_in_city = NUM_OF_CARS_IN_CITY;
double charging_percentage_of_cars;

int ac11_chargers = NUM_11_KWH_AC_STATIONS;
int ac12_chargers = NUM_12_KWH_AC_STATIONS;
int ac22_chargers = NUM_22_KWH_AC_STATIONS;
int dc50_chargers = NUM_50_KWH_DC_STATIONS;
int dc108_chargers = NUM_108_KWH_DC_STATIONS;
int dc150_chargers = NUM_150_KWH_DC_STATIONS;

double chance_11_kwh_ac_station = CHANCE_11_KWH_AC_STATIONS;
double chance_12_kwh_ac_station = CHANCE_12_KWH_AC_STATIONS;
double chance_22_kwh_ac_station = CHANCE_22_KWH_AC_STATIONS;
double chance_50_kwh_dc_station = CHANCE_50_KWH_DC_STATIONS;
double chance_108_kwh_dc_station = CHANCE_108_KWH_DC_STATIONS;
double chance_150_kwh_dc_station = CHANCE_150_KWH_DC_STATIONS;

bool is_day = false;
bool is_24_hours = false;


/************************************************/
/*                   Main                       */
/************************************************/
void print_usage(void)
{
    printf("Usage: ./sim [d|n|24h] [-tc [number]] [-p [number]] [-ac11 [number]] [-ac12 [number]] [-ac22 [number]] [-dc50 [number]] [-dc108 [number]] [-dc150 [number]] [-h]\n");
    printf("Options:\n");
    printf("  -tc [number]         : Specify The Number of Cars in The City\n");
    printf("  -p [number]          : Specify The Percentage of Cars to Charge During the Period (value must be between 0 and 1, e.g., 0.25 for 25%%)\n");
    printf("  -ac11  [number]      : Specify The Number of AC 11 kWh Chargers\n");
    printf("  -ac12  [number]      : Specify The Number of AC 12 kWh Chargers\n");
    printf("  -ac22  [number]      : Specify The Number of AC 22 kWh Chargers\n");
    printf("  -dc50  [number]      : Specify The Number of DC 50 kWh Chargers\n");
    printf("  -dc108 [number]      : Specify The Number of DC 108 kWh Chargers\n");
    printf("  -dc150 [number]      : Specify The Number of DC 150 kWh Chargers\n");
    printf("  -h                   : Display Usage Message\n");
}

bool parse_args(int argc, char *argv[])
{
    if (argc < 2)
    {
        print_usage();
        return false;
    }

    if (strcmp(argv[1], "d") == 0)
    {
        is_day = true;
        charging_percentage_of_cars = CHARGING_PERCENTAGE_OF_CARS_DAY;
    }
    else if (strcmp(argv[1], "n") == 0)
    {
        is_day = false;
        charging_percentage_of_cars = CHARGING_PERCENTAGE_OF_CARS_NIGHT;
    }
    else if (strcmp(argv[1], "24h") == 0)
    {
        is_24_hours = true;
        charging_percentage_of_cars = CHARGING_PERCENTAGE_OF_CARS_DAY;
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
        else if (strcmp(argv[i], "-tc") == 0 && i + 1 < argc)
        {
            num_of_cars_in_city = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-p") == 0 && i + 1 < argc)
        {
            charging_percentage_of_cars = atof(argv[++i]);
            if (charging_percentage_of_cars < 0.0 || charging_percentage_of_cars > 1.0)
            {
                printf("Error: charging_percentage must be between 0 and 1.\n");
                return false;
            }
        }
        else if (strcmp(argv[i], "-ac11") == 0 && i + 1 < argc)
        {
            ac11_chargers = atoi(argv[++i]);
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
        else if (strcmp(argv[i], "-dc150") == 0 && i + 1 < argc)
        {
            dc150_chargers = atoi(argv[++i]);
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

/* Update Store Capacities Based on Parsed Arguments */
void update_store_values() 
{
    CHAR_STATION_AC_11KWH.SetCapacity(ac11_chargers);
    CHAR_STATION_AC_12KWH.SetCapacity(ac12_chargers);
    CHAR_STATION_AC_22KWH.SetCapacity(ac22_chargers);
    CHAR_STATION_DC_50KWH.SetCapacity(dc50_chargers);
    CHAR_STATION_DC_108KWH.SetCapacity(dc108_chargers);
    CHAR_STATION_DC_150KWH.SetCapacity(dc150_chargers);
}

/* Update Chances to Choose the Stations Based on Parsed Arguments */
void update_stations_chance() 
{
    double count = ac11_chargers + ac12_chargers + ac22_chargers + dc50_chargers + dc108_chargers + dc150_chargers;
    
    chance_11_kwh_ac_station = ac11_chargers / count;
    chance_12_kwh_ac_station = chance_11_kwh_ac_station + (ac12_chargers / count);
    chance_22_kwh_ac_station = chance_12_kwh_ac_station + (ac22_chargers / count);
    chance_50_kwh_dc_station = chance_22_kwh_ac_station + (dc50_chargers / count);
    chance_108_kwh_dc_station = chance_50_kwh_dc_station + (dc108_chargers / count);
    chance_150_kwh_dc_station = chance_108_kwh_dc_station + (dc150_chargers / count);
    
}

std::string get_params(void)
{
    std::string params = "-cars=" + std::to_string(num_of_cars_in_city) + "-";
    params = params + "charge=" + std::to_string(charging_percentage_of_cars) + "-";
    params = params + "ac11=" + std::to_string(ac12_chargers) + "-";
    params = params + "ac12=" + std::to_string(ac12_chargers) + "-";
    params = params + "ac22=" + std::to_string(ac22_chargers) + "-";
    params = params + "dc50=" + std::to_string(dc50_chargers) + "-";
    params = params + "dc50=" + std::to_string(dc50_chargers) + "-";
    params = params + "dc150=" + std::to_string(dc108_chargers);
    return params;
}

/* Calculate charging time average for every phase (0-20%, 20-80%, 80-100%) */
double calculate_phase_average(
        const std::vector<std::pair<double, double>>& stats1,
        const std::vector<std::pair<double, double>>& stats2,
        const std::vector<std::pair<double, double>>& stats3,
        const std::vector<std::pair<double, double>>& stats4,
        const std::vector<std::pair<double, double>>& stats5,
        const std::vector<std::pair<double, double>>& stats6
) {
    double total_time = 0.0;
    int total_count = 0;

    for (const auto& stats : {stats1, stats2, stats3, stats4, stats5, stats6}) {
        for (const auto& stat : stats) {
            total_time += stat.second;
        }
        total_count += stats.size();
    }

    return (total_count > 0) ? (total_time / total_count) : 0.0;
}

/* Calculate total charging time average of car */
double calculate_total_average() {
    double phase_0_20_avg = calculate_phase_average(
            ev_stats_ac11_0_20, ev_stats_ac12_0_20, ev_stats_ac22_0_20, ev_stats_dc50_0_20, ev_stats_dc108_0_20, ev_stats_dc150_0_20);
    double phase_20_80_avg = calculate_phase_average(
            ev_stats_ac11_20_80, ev_stats_ac12_20_80, ev_stats_ac22_20_80, ev_stats_dc50_20_80, ev_stats_dc108_20_80, ev_stats_dc150_20_80);
    double phase_80_100_avg = calculate_phase_average(
            ev_stats_ac11_80_100, ev_stats_ac12_80_100, ev_stats_ac22_80_100, ev_stats_dc50_80_100, ev_stats_dc108_80_100, ev_stats_dc150_80_100);

    return phase_0_20_avg + phase_20_80_avg + phase_80_100_avg;
}


void print_ev_stats(const std::vector<std::pair<double, double>>& stats, const std::string& charger_name, std::ofstream& out_file)
{
    double total_charging_time = 0.0;

    out_file << "Statistics for " << charger_name << ":\n";
    out_file << "--------------------------------------\n";
    for (const auto& stat : stats)
    {
        out_file << std::fixed << std::setprecision(6);
        out_file << "Start Time: " << stat.first << ", Charging Time: " << stat.second << '\n';
        total_charging_time += stat.second;
    }

    double average_charging_time = stats.empty() ? 0.0 : total_charging_time / stats.size();
    out_file << "--------------------------------------\n";
    out_file << "Average Charging Time: " << average_charging_time << " mins\n";
    out_file << "======================================\n";
}

int main(int argc, char *argv[]) 
{
    bool retVal;

#if (1 == DEBUG)

    DebugOFF();
    
#endif /* (1 == DEBUG) */

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

    if (is_24_hours)    /* Simulation Of 24 hours period */
    {
        Init(0, WHOLE_DAY_TIME);
        (new TransactionDay(ALLTIME))->Activate();
        (new GeneratorDay(num_of_cars_in_city, charging_percentage_of_cars, ALLTIME))->Activate();
    }
    else if (is_day)    /* Simulation Of Day */
    {
        Init(0, DAYTIME_LENGTH);
        (new TransactionDay(DAYTIME))->Activate();
        (new GeneratorDay(num_of_cars_in_city, charging_percentage_of_cars, DAYTIME))->Activate();
    }
    else    /* Simulation Of Night */
    {
        Init(0, NIGHTTIME_LENGTH);
        (new TransactionDay(NIGHTTIME))->Activate();
        (new GeneratorDay(num_of_cars_in_city, charging_percentage_of_cars, NIGHTTIME))->Activate();
    }

    Run();

    /* Print Statistics */
    std::string params = get_params();
    std::string outputFileName = "output/sim_out" + params + ".txt";
    SetOutput(outputFileName.c_str());

    CHAR_STATION_AC_11KWH.Output();
    CHAR_STATION_AC_12KWH.Output();
    CHAR_STATION_AC_22KWH.Output();
    CHAR_STATION_DC_50KWH.Output();
    CHAR_STATION_DC_108KWH.Output();
    CHAR_STATION_DC_108KWH.Output();

    if (is_24_hours)
    {
        printf("Statistics during 24 hours period\n");
    }
    else if (is_day)
    {
        printf("Statistics during the day period 7:00-21:00\n");
    }
    else
    {
        printf("Statistics during the night period 21:00-7:00\n");
    }

    printf("---------------------------------------------------------------\n");


    std::cout << "Number of generated vehicles: " << num_generated_cars << std::endl;
    std::cout << "Number of charged vehicles: " << num_charged_cars_per_period << std::endl;
    std::cout << "Number of vehicles that start to charging: " << num_cars_on_station << std::endl;

    std::string out_stats_file = "output/ev_charging_stats" + params + ".txt";
    std::ofstream out_file(out_stats_file);
    if (!out_file)
    {
        std::cerr << "ERR: Unable to open file for writing.\n";
        return 1;
    }

#if (1 == EXTRA_PRINTS)

    /* Statistics For 1. Phase (0-20%) */
    print_ev_stats(ev_stats_ac11_0_20, "AC 12kWh Charger (0-20%)", out_file);
    print_ev_stats(ev_stats_ac12_0_20, "AC 12kWh Charger (0-20%)", out_file);
    print_ev_stats(ev_stats_ac22_0_20, "AC 22kWh Charger (0-20%)", out_file);
    print_ev_stats(ev_stats_dc50_0_20, "DC 50kWh Charger (0-20%)", out_file);
    print_ev_stats(ev_stats_dc108_0_20, "DC 108kWh Charger (0-20%)", out_file);
    print_ev_stats(ev_stats_dc150_0_20, "DC 150kWh Charger (0-20%)", out_file);

    /* Statistics For 2. Phase (20-80%) */
    print_ev_stats(ev_stats_ac11_20_80, "AC 11kWh Charger (20-80%)", out_file);
    print_ev_stats(ev_stats_ac12_20_80, "AC 12kWh Charger (20-80%)", out_file);
    print_ev_stats(ev_stats_ac22_20_80, "AC 22kWh Charger (20-80%)", out_file);
    print_ev_stats(ev_stats_dc50_20_80, "DC 50kWh Charger (20-80%)", out_file);
    print_ev_stats(ev_stats_dc108_20_80, "DC 108kWh Charger (20-80%)", out_file);
    print_ev_stats(ev_stats_dc150_20_80, "DC 150kWh Charger (20-80%)", out_file);

    /* Statistics For 3. Phase (20-80%) */
    print_ev_stats(ev_stats_ac11_80_100, "AC 11kWh Charger (80-100%)", out_file);
    print_ev_stats(ev_stats_ac12_80_100, "AC 12kWh Charger (80-100%)", out_file);
    print_ev_stats(ev_stats_ac22_80_100, "AC 22kWh Charger (80-100%)", out_file);
    print_ev_stats(ev_stats_dc50_80_100, "DC 50kWh Charger (80-100%)", out_file);
    print_ev_stats(ev_stats_dc108_80_100, "DC 108kWh Charger (80-100%)", out_file);
    print_ev_stats(ev_stats_dc150_80_100, "DC 150kWh Charger (80-100%)", out_file);



#endif /* (1 == EXTRA_PRINTS) */

    /* Average charging time of car */
    double total_average = calculate_total_average();

    std::cout << "Total average charging time: " << total_average << " minutes\n";

    time_spend_in_system.Output();

#if (1 == DEBUG)

    DebugOFF();

#endif /* (1 == DEBUG) */
    return 0;
}