#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "GPSParsing.h"

typedef struct {
    int hours;
    int minutes;
    int seconds;
    double latitude;
    double longitude;
    double altitude;
    bool isValid;
} gps_data_t;