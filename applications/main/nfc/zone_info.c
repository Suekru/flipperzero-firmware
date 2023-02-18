//
// Created by Suekru on 1/21/2023.
//

#include "zone_info.h"

char* zoneName = "Zone 0";

const char* chipNames[][38] = {
        {},
        {"13 D-Mill", "12 Pkg", "11 Pkg", "9 D-Mill", "8 Pkg", "7 Pkg", "6 Pkg", "5 Pkg", "4 Pkg", "4 Whse 6", "10 Whse 6", "8 Whse 6",
         "7 Whse 6", "6 Whse 6", "5 Whse 6", "8 Corn-Mill", "6 Corn-Mill", "5 Corn-Mill", "4 Corn-Mill", "4 Whse 5",
         "8 Whse 4", "8 Whse 7", "8 Whse 2", "7 CH1", "7 CH2", "13 CH2", "6 CH1", "7 Whse 7", "7 Whse 4", "6 Whse 4", "6 CH3",
         "6 Whse 2", "6 Whse 7", "5 Whse 7", "5 CH3", "5 Whse 4", "QA Lab"},
        {"1 Whse 10", "2 Whse 10", "2 Whse 9", "1 Whse 9", "2 Whse 4", "2 Whse 7", "2 CH3", "1 CH3", "1 Whse 2", "1 Whse 7",
                "Bsm Whse 7", "Bsm CH2", "Bsm Elev-C", "Bsm Elev-A", "3 Whse 7", "4 Whse 7", "4 Whse 4", "4 CH 3", "4 Whse 2",
                "3 Cobs", "3 CH3", "3 Whse 4", "3 Corn-Mill", "11 C-Mill", "9 C-Mill", "8 C-Mill", "7 C-Mill", "5 C-Mill",
                "4 C-Mill", "3 Whse 6", "Contractor's", "2 Pkg", "2 Whse 6", "2 Corn-Mill", "2 Sub", "1 Whse 5",
                "Bat Shop", "1 Whse 8"},
        {"1 Whse 6", "Bsm Whse 6", "Pump", "Bsm C-Mill", "2 A-Mill", "1 C-Mill", "Bsm G-West", "Corn Dryer", "Train Shed",
                "Bsm Dump", "Elev-G Bin", "G Balcony", "Elev-G Bridge", "Whse 4 Bridge", "Elev-A Bin", "Elev-F Bin", "Bsm Corn Dryer",
                "Bsm Elev-F", "Elev-E Top", "Elev-C Bin", "Elev-D Bin", "4 Cobs", "2 Cobs", "1 Cobs", "Oat Hull", "Elev-D"},
        {"6 Pkg","13 D-Mill","12 Pkg", "10 Whse 6", "2 Whse 6", "2 Sub", "6 Whse 4",
                         "8 Whse 4", "8 Whse 7", "7 CH2", "7 CH1", "13 CH2", "6 CH1", "6 CH3",
                         "1 Whse 7", "Bsm Whse 7", "Bsm CH3", "Bsm Elev-C", "Bsm CH2", "Bsm Elev-A", "Bsm Cobs"},
        {},
        {},
        {},
        {},
        {},
        {"2 A-Mill", "8 C-Mill", "9 Whse 6\nDump Hole", "9 Whse", ""}
};

const int chipTimes[][38] = {
        {},
        {},
        {},
        {},
        {120,75,90,90,75,90,85,85,85,85,150,120,65,90,75,75,75,75,120,90,0}
};

const int zoneLengths[] = {0, 37, 38, 26, 21};