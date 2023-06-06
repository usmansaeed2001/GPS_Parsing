#include <GPSParsing.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>


void app_main(void)
{
    while (true) {
    	const char* sentence = "$GPGGA,181908.00,3404.7041778,N,07044.3966270,W,4,13,1.00,495.144,M,29.200,M,0.10,0000*40";

    	    GPSData data;
    	    if(parse_gps_data(sentence, &data)) {
    	        printf("Latitude: %f\n", data.latitude);
    	        printf("Longitude: %f\n", data.longitude);
    	        printf("Time: %i:%i:%i\n", data.hour, data.minute, data.second);
    	    }
    	     else {
    	        printf("Invalid sentence!\n");
    	    }
        sleep(1);
    }
}