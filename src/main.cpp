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
/************************************************/
/*                  Global Variables            */
/************************************************/
int ac12_chargers = NUM_12_KWH_AC_STATIONS;
int ac22_chargers = NUM_22_KWH_AC_STATIONS;
int dc50_chargers = NUM_50_KWH_DC_STATIONS;
int dc108_chargers = NUM_108_KWH_DC_STATIONS;
double speed_value = 0.0;
bool is_day = false;
/************************************************/
/*                   Statistics                 */
/************************************************/

/**
 * TODO:    Create HERE The Variables For Model Statistics. Variables Then Should Be Extern Into Electric Vehicle Class.
 *          Or Create in The Electric Vehicle Class And Then Use Them Here.
 */


/************************************************/
/*                   Main                       */
/************************************************/
void print_usage(void)
{
    printf("Usage: ./ims [day|night] [-ac12 [number]] [-ac22 [number]] [-dc50 [number]] [-dc108 [number]] [-s <speed_value>] [-h]\n");
    printf("Options:\n");
    printf("  -ac12  [number]       : Specify The Number of AC 12 kWh Chargers\n");
    printf("  -ac22  [number]       : Specify The Number of AC 22 kWh Chargers\n");
    printf("  -dc50  [number]       : Specify The Number of DC 50 kWh Chargers\n");
    printf("  -dc108 [number]       : Specify The Number of DC 108 kWh Chargers\n");
    printf("  -s <speed_value>      : Specify Speed Value (In Double)\n");
    printf("  -h                    : Display Usage Message\n");
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
        else if (strcmp(argv[i], "-s") == 0 && i + 1 < argc)
        {
            speed_value = atof(argv[++i]);
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

int main(int argc, char *argv[]) 
{
    bool retVal;
    
    /* Parse Arguments */
    retVal = parse_args(argc, argv);

    printf("Modeling & Simulation Project - Electromobility in Brno 2024\n");
    Init(0, WHOLE_DAY_TIME);

    if (1 == retVal)    /* Simulation Of Day */
    {
        (new TransactionDay(DAYTIME_LENGTH))->Activate();
        (new GeneratorDay())->Activate();
    }
    else                /* Simulation Of Night */
    {
        (new TransactionDay(DAYTIME_LENGTH))->Activate();
        (new GeneratorDay())->Activate();
        /**
         * TODO: Update The Code, Current Implementation Is The Same For Day/Night Mode,
         * In Both Modes Runs The Day Mode And After That The Night Mode.
         **/  
    }   
    Run();

    /* Print Statistics */
    /* TODO: Code For Printing */

    return 0;
}