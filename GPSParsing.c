#include <stdio.h>
#include <stdbool.h>
#include "GPSParsing.h"
#include <string.h>

// Function to calculate the NMEA checksum
static unsigned char calculate_checksum(const char *data) {
    unsigned char checksum = 0;
    int i;
    for (i = 0; i < strlen(data); i++) {
        if (data[i] == '*')
            break;
        checksum ^= data[i];
    }
    return checksum;
}

gps_data_t parseGPS(const char *data)
{
    gps_data_t parsedData;

    //CheckSum verification
    if (!(verifyCheckSum(data))) {
        parsedData.isValid = false;
    }
    
    //Check empty String
    if (data == NULL || *data == '\0' || *data == '\n') {
        parsedData.isValid = false;
    }

    //Ignore the first character
    data++;

    // Split the message into fields
    char *fields[15];
    int fieldCount = 0;
    char *token = strtok((char *)data, ",");
    
    while (token != NULL && fieldCount < 15) {
        fields[fieldCount] = token;
        fieldCount++;
        token = strtok(NULL, ",");
    }
    // Check if the required fields are present
    if (fieldCount < 15 || strncmp(fields[0], "GPGGA", 5) != 0) {
        parsedData.isValid = false;  // Wrong string or missing parameters
    }

    //Display the error message and return
    if (!(parsedData.isValid)) {
        printf("Invalid Data");
        return parsedData;
    }

    // Copy individual data parameters to the struct
    strncpy(parsedData->time, fields[0], 9);


}