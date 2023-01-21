//
// Created by Suekru on 1/21/2023.
//

#include "zone_info.h"

int zone = 0;
char zoneName[] = "Zone 4";

const char* chipNames[][21] = {
        {}, {}, {}, {}, {"6 Pkg","13 Pkg","12 Pkg", "10 Whse 6", "2 Whse 6", "2 Sub", "6 Whse 4",
                         "8 Whse 4", "8 Whse 7", "8 CH2", "7N CH1", "13 CH2", "6 CH1", "6 Ch3",
                         "1 Whse 7", "Bsm Whse 7", "Bsm CH3", "Bsm Elev-C", "Bsm CH2", "Bsm Elev-A", "Bsm Cobs"}
};

const int chipTimes[][21] = {
        {}, {}, {}, {}, {120,75,90,90,75,90,85,85,85,85,150,120,65,90,75,75,75,75,120,90,0}
};

const int zoneLengths[] = {0, 0, 0, 0, 21};