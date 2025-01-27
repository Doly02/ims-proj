# IMS Project: Model of Electromobility in Brno
- Authors: Tomáš Dolák, Monika Zahradníková
- Logins: [xdolak09](https://www.vut.cz/lide/tomas-dolak-247220), [xzahra33](https://www.vut.cz/lide/monika-zahradnikova-250462)
- Emails: <xdolak09@stud.fit.vutbr.cz>, <xzahra33@stud.fit.vutbr.cz>

## Project Overview
The goal of this project in the subject Modeling and Simulations was to create a model in the energy sector. Project focuses on modeling electromobility in Brno, a city poised to embrace the future of electric vehicle (EV) adoption. With the increasing popularity of electromobility globally, this simulation aims to assess Brno's readiness for an electrified future. By analyzing the city's EV charging infrastructure and forecasting future demands, the project provides insights for optimizing the charging network to meet growing needs.

## Objectives
The primary objective of this project is to create a simulation model that evaluates the charging infrastructure for electric vehicles in Brno. The model considers:

- EV Fleet: The number of electric vehicles in Brno and their charging behavior.
- Charging Stations: The current and forecasted network of public charging stations, including different station types.
- Load Simulation: The impact of varying charging loads on the city's infrastructure based on daily and nighttime usage patterns.
- Adjustable Parameters: Users can configure parameters such as the number of EVs, daily public charging usage percentage, and the simulation timeframe (24 hours, daytime, or nighttime).

The results of this model should help to analyze and optimize the charging infrastructure to ensure sustainable electromobility in Brno.

## Requirements
To build and run `sim`, you will need the following:

### Compiler
- **GNU G++** with support for **C++17** standard. This project uses specific compiler flags to enforce code quality and standards. Make sure your compiler version supports `-std=c++17` along with the flags `-Wall -Wextra -Werror -Wshadow -Wnon-virtual-dtor -pedantic`.

### Libraries
- **SIMLIB/C++ - SIMulation LIBrary for C++**: Required for compiling and running application. Ensure you have SIMLIB installed on your system as it uses `-lm  -lsimlib` flags for linking.
- **Google Test (gtest)**: Required for compiling and running the unit tests. Ensure you have Google Test installed on your system as it uses `-lgtest -lgtest_main -pthread` flags for linking.

### Build tools
- **Make**: This project uses a `Makefile` for easy building and testing. Ensure you have Make installed on your system.

### Operating system
- The Makefile and C++ code were designed with Unix-like environments in mind (Linux, MacOS). While it may be possible to compile and run the project on Windows, using a Unix-like environment (or WSL for Windows users) is recommended.

### Debugging (Optional)
- For debugging, this project uses Clang++'s AddressSanitizer which requires `-fsanitize=address` flag. Ensure your development environment supports AddressSanitizer if you intend to use the debug build.

## Installation
1. Clone the repository to your local machine.
2. Navigate to the project directory.
3. Run `make` to build the client application. This will create the `ims-proj` executable.
4. (Optional) Run `make test` to build and run the unit tests. Ensure you have Google Test installed.
5. (Optional) Run `make debug` to build the application with debug flags enabled.

Please refer to the Makefile for additional targets and commands.

## Project organization 
```
ims-proj/
│
├── include/                # Header files for class declarations.
│   
├── src/                    # Source files containing class definitions and main application logic.
│
├── output/                 # Examples of program output
│
├── docs.zip                # Documentation folder (documentation.tex, pictures, ...)
│
├── documentation.pdf       # Simulation study
│
├── Makefile                # Makefile for compiling the project
│
└── README.md               # Project README
```


## Outputs
for running the application two files with simulation results are created in the root directory, the first one is the file starting with `ev_charging_stats...` this file contains records of all received EVs to the single types of charging stations (the record always contains `the time of arrival` and `the length of charging`), the second file is called `sim_out-...` this file contains statistics of individual stores, queues and histogram of the simulation. 

Example of `ev_charging_stats...`:
```
ev_charging_stats-day-cars=20000-charge=0.250000-ac11=400-ac12=400-ac22=400-dc50=240-dc108=220-dc150=200.txt
```
- **note**: file creation can be disabled by switching the `EXTRA_PRINTS` argument from 1 to 0 in the `main.c` file.

Example of `sim_out-...`:
```
sim_out-day-cars=20000-charge=0.250000-ac11=400-ac12=400-ac22=400-dc50=240-dc108=220-dc150=200.txt
```
Both files contain in their name the parameters with which the simulation was launched.

## Resources
[1] "SIMLIB/C++ - SIMulation LIBrary for C++" [online]. [cited 2024-10-28]. Available at [https://www.fit.vut.cz/person/peringer/public/SIMLIB/](https://www.fit.vut.cz/person/peringer/public/SIMLIB/)

[2] "Seznam veřejných dobíjecích stanic — stav k 31. 7. 2023" [online]. [cited 2024-10-28]. Available at [https://www.mpo.gov.cz/cz/energetika/statistika/statistika-a-evidence-cerpacich-a-dobijecich-stanic/seznam-verejnych-dobijecich-stanic-_-stav-k-31--7--2023--276204/](https://www.mpo.gov.cz/cz/energetika/statistika/statistika-a-evidence-cerpacich-a-dobijecich-stanic/seznam-verejnych-dobijecich-stanic-_-stav-k-31--7--2023--276204/)

[3] "Electric Vehicle Database: Useable battery capacity of full electric vehicles" [online]. [cited 2024-10-28]. Available at [https://ev-database.org/cheatsheet/useable-battery-capacity-electric-car](https://ev-database.org/cheatsheet/useable-battery-capacity-electric-car)

[4] "Datový portál města Brna: Elektrické nabíjecí stanice pro auta / EV charging points" [online]. [cited 2024-10-28]. Available at [https://data.brno.cz/datasets/51a34d787c2c403cb36b094ab5f0d779_0/explore](https://data.brno.cz/datasets/51a34d787c2c403cb36b094ab5f0d779_0/explore)

[5] "How long do electric car batteries last? What 10,000 electric vehicles tell us about EV battery life" [online]. [cited 2024-10-28]. Available at [https://www.geotab.com/blog/ev-battery-health/](https://www.geotab.com/blog/ev-battery-health/)

[6] "techradar: EV battery size, charge speeds and range explained" [online]. [cited 2024-10-28]. Available at [https://www.techradar.com/news/ev-battery-size-charge-speeds-and-range-explained](https://www.techradar.com/news/ev-battery-size-charge-speeds-and-range-explained)

[7] "Přehledně: Všechny typy elektromotorů! Čím se liší? A jaké mají výhody/nevýhody? [online]. [cited 2024-10-28]. Available at [https://www.auto.cz/prehledne-vsechny-typy-elektromotoru-cim-se-lisi-a-jake-maji-vyhody-nevyhody-141704](https://www.auto.cz/prehledne-vsechny-typy-elektromotoru-cim-se-lisi-a-jake-maji-vyhody-nevyhody-141704)

[8] "Techmania: Elektromotory" [online]. [cited 2024-10-28]. Available at [http://edu.techmania.cz/cs/encyklopedie/fyzika/elektromagneticka-indukce/elektromotory](http://edu.techmania.cz/cs/encyklopedie/fyzika/elektromagneticka-indukce/elektromotory) 

[9] "AC vs. DC nabíjecí stanice elektromobilů" [online]. [cited 2024-10-28]. Available at [https://www.kalkulator.cz/clanky/112/ac-vs-dc-nabijeci-stanice-elektromobilu](https://www.kalkulator.cz/clanky/112/ac-vs-dc-nabijeci-stanice-elektromobilu)

[8] "Teplárny Brno příští rok vybudují dalších 50 nabíječek pro elektroauta" [online]. [cited 2024-10-28]. Available at [https://www.seznamzpravy.cz/clanek/regiony-zpravy-jihomoravsky-kraj-teplarny-brno-pristi-rok-vybuduji-dalsich-50-nabijecek-pro-elektroauta-241833](https://www.seznamzpravy.cz/clanek/regiony-zpravy-jihomoravsky-kraj-teplarny-brno-pristi-rok-vybuduji-dalsich-50-nabijecek-pro-elektroauta-241833)

[9] "Jaká je degradace baterie elektromobilu po ujetých 224 tisících km?" [online]. [cited 2024-10-28]. Available at [https://www.autonabijecka.cz/jaka-je-degradace-baterie-elektromobilu-po-ujetych-224-tisicich-km/](https://www.autonabijecka.cz/jaka-je-degradace-baterie-elektromobilu-po-ujetych-224-tisicich-km/)

[10] "Víte, jak se v zimě správně postarat o elektromobil?" [online]. [cited 2024-10-28]. Available at [https://www.essox.cz/blog/stories/vite-jak-se-v-zime-spravne-postarat-o-elektromobil](https://www.essox.cz/blog/stories/vite-jak-se-v-zime-spravne-postarat-o-elektromobil)

[11] "Teplarny: Teplárny Brno ve spolupráci s TSB instalovaly první nabíjecí stanici na stožáru veřejného osvětlení" [online]. [cited 2024-10-28]. Available at [https://www.teplarny.cz/cs/teplarny-brno-ve-spolupraci-s-tsb-instalovaly-prvni-nabijeci-stanici-na-stozaru-verejneho-osvetleni](https://www.teplarny.cz/cs/teplarny-brno-ve-spolupraci-s-tsb-instalovaly-prvni-nabijeci-stanici-na-stozaru-verejneho-osvetleni)
