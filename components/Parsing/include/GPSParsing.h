#include <stdbool.h>

//Struct to store individual parameters of GPS Data
typedef struct {
    double latitude;
    double longitude;
    int hour;
    int minute;
    int second;
} GPSData;

unsigned char calculate_checksum(const char *data);
bool parse_gps_data(const char *gps_string, GPSData *data);