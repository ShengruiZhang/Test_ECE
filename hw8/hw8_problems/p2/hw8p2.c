/*
Author: Shengrui Zhang
Student ID: 23426900
Email: shengruizhang@email.arizona.edu
Created Date: 10/26/17
*/
/*/////////////////////////// HOMEWORK 8 PROBLEM TWO ////////////////////*/
/* Input: READS DATA FROM EXTERNAL FILE
   Output: DISPLAY DATA IN THE ORDING OR DISTANCE
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <math.h>
#define LANT 32.225750
#define LONG -110.979413
typedef unsigned char uchar;
typedef unsigned int uint;
typedef struct plc_s {
	uchar name[100];
	uchar CUN[30];
	double LAT;
	double LON;
	double dist_r;
}place;
double dist(double lat1, double long1, double lat2, double long2);
void swap(place *a, place *b);
void sorting(place x[], int amount);
int main(void)
{
	FILE *raw = fopen("placelist.txt", "r");
	place info[10]; // DECL VARI
	uint i = 0; // ARRARY COUNTER
	while (!feof(raw))
	{
		fgets(info[i].name, 100, raw); // READS THE INFO
		fgets(info[i].CUN, 100, raw);
		fscanf(raw, "%lf", &info[i].LAT);
		fscanf(raw, "%lf\n", &info[i].LON);
		info[i].name[strlen(info[i].name) - 1] = 0; // GET RID OF THE NEW LINE
		info[i].CUN[strlen(info[i].CUN) - 1] = 0;
		if (strstr(info[i].CUN, "USA") == NULL) { // PRINTS THOSE NON US INFO
			printf("%s, %s\n", info[i].name, info[i].CUN);
			printf("[Latitude, Longtitude] = [%.6lf, %.6lf]\n\n", info[i].LAT, info[i].LON);
		}
		++i; // UPDATE COUNTER
	}
	printf("[its latitude and longtitude are %.6lf and %.6lf]\n\n", LANT, LONG);
	for (i = 0; i < 10; ++i) {
		info[i].dist_r = dist(LANT, LONG, info[i].LAT, info[i].LON);
	}
	sorting(info, 10); // SORTING
	for (i = 0; i < 10; ++i) {
		printf("%s, %s\n", info[i].name, info[i].CUN);
		printf("[Latitude, Longtitude] = [%.6lf, %.6lf]\n\n", info[i].LAT, info[i].LON);
		printf("Distance is %.3lf miles\n\n", info[i].dist_r);
	}
	printf("Reading ended.\n"); // FOR DEBUGGING
	return 0;
}

double dist(double lat1, double long1, double lat2, double long2)  // COPY PASTE FROM PDF
{
	double R = 6371;
	double PI = 3.1415926536;
	double dx, dy, dz;
	double dist_mile;
	long1 = long1 - long2;
	long1 = long1 * (PI / 180);
	lat1 = lat1 * (PI / 180);
	lat2 = lat2 * (PI / 180);
	dz = sin(lat1) - sin(lat2);
	dx = (cos(long1) * cos(lat1)) - cos(lat2);
	dy = sin(long1) * cos(lat1);
	dist_mile = (asin(sqrt(dx * dx + dy * dy + dz * dz) / 2)*2*R)/1.609344;
	return dist_mile;
}

void swap(place *a, place *b)
{
	double temp;
	uchar temp_c;
	temp = (*a).dist_r;
	(*a).dist_r = (*b).dist_r;
	(*b).dist_r = temp;
	strcpy(temp_c, (*a).name);
	strcpy((*a).name, (*b).name);
	strcpy((*a).name, temp_c);
}

void sorting(place x[], int amount)
{
	int min = 0; // MAX VALUE
	int i, j; // LOOP VARI
	for (i = 0; i < amount; ++i)
	{
		min = x[i].dist_r; // STARTS WITH THE FRIST ELEMENT
		for (j = 0; j < amount; ++j)
		{
			if (x[j].dist_r < min) { // IF THERE IS A NUMBER SMALLER THAN MIN, THEN MOVE THE MIN DOWN
				min = j; // GET THE INDEX
			}
		}
		swap(&x[j], &x[i]);
	}
}