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
/************************************************/
/*                   Main                       */
/************************************************/
void print_usage(void)
{
    printf("Usage: ./ims_project [OPTIONS]\n");
}

bool parse_args(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i)
    {
        if (0 == strcmp(argv[i], "-h"))
        {
            print_usage();
        }
        else if (0 == strcmp(argv[i], "day"))
        {
            return true;
        }
        else if (0 == strcmp(argv[i], "night"))
        {
            return false;
        }
    }
}

int main(int argc, char *argv[]) 
{
    bool retVal;
    
    /* Parse Arguments */
    retVal = parse_args(argc, argv);

    printf("Modeling & Simulation Project - Electromobility in Brno 2024\n");
    Init(0, DAY_TIME);

    if (1 == retVal)    /* Simulation Of Day */
    {

    }
    else                /* Simulation Of Night */
    {

    }

    return 0;
}