#include"stdafx.h"
#include "plcdemos.h"
#define NSIZE    41

int
main(int argc, char *argv[])
{
	PLFLT x[NSIZE], y[NSIZE];
	PLFLT xmin = -2., xmax = 2., ymin = -4., ymax = 2.;
	float   i;
	int a = 0;

	// Prepare data to be plotted.
	for (i = -2.0; i < 2.1; )
	{
		x[a] = i;
		y[a] = x[a] * x[a] * x[a] * x[a]  -2* x[a] * x[a] -3;
		i = i + 0.1;
			a++;
	}

	// Parse and process command line arguments
	plparseopts(&argc, argv, PL_PARSE_FULL);

	// Initialize plplot
	plinit();

	// Create a labelled box to hold the plot.
	plenv(xmin, xmax, ymin, ymax, 0, 0);
	pllab("x", "y=100 x#u2#d", "Simple PLplot demo of a 2D line plot");

	// Plot the data that was prepared above.
	plline(NSIZE, x, y);

	// Close PLplot library
	plend();

	exit(0);
}