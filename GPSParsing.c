#include <stdio.h>
#include <stdbool.h>
#include "GPSParsing.h"
#include <string.h>

// Function to calculate the NMEA checksum
static unsigned char calculate_checksum(const char *data) 
{
    unsigned char checksum = 0;
    int i;
    for (i = 0; i < strlen(data); i++) {
        if (data[i] == '*')
            break;
        checksum ^= data[i];
    }
    return checksum;
}
// Function to parse the GPS data string
void parse_gps_data(const char *gps_string, GPSData *data) {
    if (strlen(gps_string) == 0 || gps_string[0] != '$') {
        // Invalid or empty string
        return;
    }

    // Validate checksum
    unsigned char checksum = calculate_checksum(gps_string);
    char checksum_str[3];
    strncpy(checksum_str, gps_string + strlen(gps_string) - 2, 2);
    checksum_str[2] = '\0';
    unsigned char received_checksum = (unsigned char)strtol(checksum_str, NULL, 16);
    if (checksum != received_checksum) {
        // Invalid checksum
        return;
    }

    // Extract individual parameters from GGA sentence
    char *token;
    char *data_copy = strdup(gps_string);  // Create a copy of the string to avoid modifying the original
    token = strtok(data_copy, ",");
    int count = 0;
    while (token != NULL && count < 14) {
        if (count == 2) {
            // Latitude
            double latitude = strtod(token, NULL);
            data->latitude = latitude;
        } else if (count == 4) {
            // Longitude
            double longitude = strtod(token, NULL);
            data->longitude = longitude;
        } else if (count == 1) {
            // Time
            double time = strtod(token, NULL);
            int hour = (int)(time / 10000);
            int minute = (int)((time - hour * 10000) / 100);
            int second = (int)(time - hour * 10000 - minute * 100);
            data->hour = hour;
            data->minute = minute;
            data->second = second;
        }

        token = strtok(NULL, ",");
        count++;
    }

    free(data_copy);
}