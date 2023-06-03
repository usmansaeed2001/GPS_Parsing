# GPS Data Parsing Library
This library parses GPS Data in NMEA format to extract Latitude, Longitude and Time information from the data.
It also verifies the checksum of the data.
## Usage:
This library needs to be added in the project directory to be used in the code. Please add GPSParsing.h, GPSParsing.c and CMakeLists.txt file in the root directory of your esp project. This library provides a single function 'parse_gps_data' to parse the data. This funtion returns true or false depending on if the checksum is verified or not.
