gcc -o GPS_test.o GPS_test.c -lm -lgps

gcc -lm -pthread -lgps -lrt -o cangpsdump.o cangpsdump.c
