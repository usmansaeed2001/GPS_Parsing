# GPS Data Parsing Library
This library parses GPS Data in NMEA format to extract Latitude, Longitude and Time information from the data.
It also verifies the checksum of the data.
## Usage:
This library needs to be added in the project directory to be used in the code. Please add GPSParsing.h, GPSParsing.c and CMakeLists.txt file in the root directory of your esp project. This library provides a single function 'parse_gps_data' to parse the data. This funtion returns true or false depending on if the checksum is verified or not.
### Example NMEA Strings:
Here are some example strings that can be used to test this code:
CheckSum Verified:
### "$GPGGA,062153.00,3723.4658762,N,12158.1134279,W,2,08,1.2,21.0,M,-25.4,M,0000,0000*65"