//
// Created by Suekru on 1/21/2023.
//

#include "zone_info.h"

int zone = 0;
char* zoneName = "Zone 0";

const char* chipNames[][21] = {
        {}, {}, {}, {}, {"6_Pkg","13_Pkg","12_Pkg", "10_Whse_6", "2_Whse_6", "2_Sub", "6_Whse_4",
                         "8_Whse_4", "8_Whse_7", "8_CH2", "7N_CH1", "13_CH2", "6_CH1", "6_Ch3",
                         "1_Whse_7", "Bsm_Whse_7", "Bsm_CH3", "Bsm_Elev_C", "Bsm_CH2", "Bsm_Elev_A", "Bsm_Cobs"}
};

const int chipTimes[][21] = {
        {}, {}, {}, {}, {120,75,90,90,75,90,85,85,85,85,150,120,65,90,75,75,75,75,120,90,0}
};

const int zoneLengths[] = {0, 0, 0, 0, 21};