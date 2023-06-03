typedef struct {
    double latitude;
    double longitude;
    int hour;
    int minute;
    int second;
} GPSData;

static unsigned char calculate_checksum(const char *data);
gps_data_t parseGPS(const char *data);