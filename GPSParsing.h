typedef struct {
    double latitude;
    double longitude;
    int hour;
    int minute;
    int second;
} GPSData;

static unsigned char calculate_checksum(const char *data);
bool parse_gps_data(const char *gps_string, GPSData *data);