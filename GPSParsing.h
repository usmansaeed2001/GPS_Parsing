typedef struct {
    int time;
    double latitude;
    double longitude;
    double altitude;
    bool isValid;
} gps_data_t;

static bool verifyCheckSum(const char* data);
gps_data_t parseGPS(const char *data);