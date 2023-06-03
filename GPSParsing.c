#include <stdio.h>
#include <stdbool.h>
#include "GPSParsing.h"

typedef struct {
    int time;
    double latitude;
    double longitude;
    double altitude;
    bool isValid;
} gps_data_t;

static bool verifyCheckSum(const char* data)
{
    //Expected CheckSum
    unsigned char expectedCheckSum;
    //Calculated CheckSum
    unsigned char CheckSum = 0;

    // Skip the leading '$' character
    data++;

    // Calculate expected checksum
    sscanf(data, "%*[^*]*%hhx", &expectedCheckSum);

    // XOR all characters until '*' or '\0' is encountered
    while (*data && *data != '*') {
        CheckSum ^= *data;
        data++;
    }

    // Compare expected and actual checksums
    return CheckSum == expectedCheckSum;
}

gps_data_t parseGPS(const char *data)
{
    gps_data_t parsedData;

    //CheckSum verification
    if (verifyCheckSum(data)) {
        parsedData->isValid = true;
    }
    else {
        parsedData->isValid = false;
    }

    //Check empty String
    if (data == NULL || *data == '\0' || *data == '\n') {
        parsedData->isValid = false;
    }

    //Ignore the first character
    data++;



}