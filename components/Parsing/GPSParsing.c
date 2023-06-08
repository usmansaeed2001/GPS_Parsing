#include <stdio.h>
#include <stdbool.h>
#include "GPSParsing.h"
#include <string.h>
#include <stdlib.h>

// Function to calculate the NMEA checksum
unsigned char calculate_checksum(const char *data) 
{
    data++;
    unsigned char checksum = 0;
    while (*data && *data != '*') {
        checksum ^= *data;
        data++;
    }
    return checksum;
}

// Function to parse the GPS data string
bool parse_gps_data(const char *gps_string, GPSData *data) 
{
    if (strlen(gps_string) == 0 || gps_string[0] != '$') {
         // Invalid or empty string
         return false;
     }
 
     // Validate checksum
     unsigned char checksum = calculate_checksum(gps_string);
     char checksum_str[3];
     strncpy(checksum_str, gps_string + strlen(gps_string) - 2, 2);
     checksum_str[2] = '\0';
     unsigned char received_checksum = (unsigned char)strtol(checksum_str, NULL, 16);
     if (checksum != received_checksum) {
         // Invalid checksum
         return false;
     }
 
     // Find the GGA sentence in the string
     const char *gga_prefix = "$GPGGA";
     const char *gga_start = strstr(gps_string, gga_prefix);
     if (gga_start == NULL) {
         // GGA sentence not found
         return false;
     }
 
     // Skip the GGA prefix and tokenize the rest of the sentence
     char *token;
     char *gga_data = strdup(gga_start + strlen(gga_prefix));
     token = strtok(gga_data, ",");
     int count = 0;
     while (token != NULL && count < 14) {
         if (count == 0) {
             // Time
             double time = strtod(token, NULL);
             int hour = (int)(time / 10000);
             int minute = (int)((time - hour * 10000) / 100);
             int second = (int)(time - hour * 10000 - minute * 100);
             data->hour = hour;
             data->minute = minute;
             data->second = second;
         } else if (count == 1) {
            // Latitude
             double latitude = strtod(token, NULL);
             data->latitude = latitude / 100;
             token = strtok(NULL, ",");
             if (token != NULL && strcmp(token, "S") == 0) {
                 data->latitude *= -1;
             }
         } else if (count == 2) {
             // Longitude
             double longitude = strtod(token, NULL);
            
             data->longitude = longitude / 100;
             token = strtok(NULL, ",");
             if (token != NULL && strcmp(token, "S") == 0) {
                 data->longitude *= -1;
             }
         }
 
         token = strtok(NULL, ",");
         count++;
     }
     free(gga_data);
     return true;
}
