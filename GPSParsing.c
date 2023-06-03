#include <stdio.h>
#include <stdbool.h>
#include "GPSParsing.h"
#include <string.h>

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

void main() 
{
    const char *nmeaString = "$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47";
    gps_data_t Data = parseGPS(nmeaString);
    if(Data.isValid) {
        printf("Reahh");
    }
}