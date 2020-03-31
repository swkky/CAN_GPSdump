#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <math.h>
#include <gps.h>

typedef struct GPS_info{
	int time;
	int status;
	int mode;
	int satellites_num;
	double latitude;
	double longitude;
	double speed;
	double climb;
} gps_t;

struct GPS_info gps_info;

void get_gps(void)
{
        int ret;
	struct gps_data_t gps_data;
	/* Open gpsd port(2947)) */
        ret = gps_open("localhost", "2947", &gps_data);
        (void)gps_stream(&gps_data, WATCH_ENABLE | WATCH_JSON, NULL);

        for (;;) {

                /* Put this in a loop with a call to a high resolution sleep () in it. */
                /* The second argument(500) is the maximum amount of time to wait (in microseconds) on input before returning.  */
		if (gps_waiting(&gps_data, 500)) {
                        errno = 0;
                        if (gps_read(&gps_data) == -1 || 0) {
                                printf("Read error\n");
                        } else {
                                if (gps_data.set) {
					gps_info.time = gps_data.fix.time;
					gps_info.status = gps_data.status;
					gps_info.mode = gps_data.fix.mode;
					gps_info.satellites_num = gps_data.satellites_used;;
					gps_info.latitude = gps_data.fix.latitude;
					gps_info.longitude = gps_data.fix.longitude;
					gps_info.speed = gps_data.fix.speed;
					gps_info.climb = gps_data.fix.climb;
                                        printf("\n--- GPS ---\n");
                                        printf("gps_data.online:           %f\n", gps_data.online);
                                        printf("gps_info.time:             %f\n", gps_info.time);
                                        printf("gps_data.fix.time:         %f\n", gps_data.fix.time);
                                        printf("gps_data.status:           %d\n", gps_data.status);
                                        printf("gps_data.satellites_used:  %d\n", gps_data.satellites_used);
                                        printf("gps_data.fix.mode:         %d\n", gps_data.fix.mode);
                                        printf("gps_data.fix.latitude:     %f\n", gps_data.fix.latitude);
                                        printf("gps_data.fix.epy:          %f\n", gps_data.fix.epy);
                                        printf("gps_data.fix.longitude:    %f\n", gps_data.fix.longitude);
                                        printf("gps_data.fix.epx:          %f\n", gps_data.fix.epx);
                                        printf("gps_data.fix.altitude:     %f\n", gps_data.fix.altitude);
                                        printf("gps_data.fix.speed:        %f\n", gps_data.fix.speed);
                                        printf("gps_data.fix.eps:          %f\n", gps_data.fix.eps);
                                        printf("gps_data.fix.track:        %f\n", gps_data.fix.track);
                                        printf("gps_data.fix.climb:        %f\n", gps_data.fix.climb);
                                        printf("gps_data.attitude.vx:      %f\n", gps_data.attitude.acc_x);
                                        printf("gps_data.attitude.xy:      %f\n", gps_data.attitude.acc_y);
                                        printf("gps_data.attitude.vz:      %f\n", gps_data.attitude.acc_z);
                                        printf("gps_data.dop.pdop:         %f\n", gps_data.dop.pdop);
	  			}
                        }
                }
        }
}
