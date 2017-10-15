#include"stdafx.h"
// Simple demo of a 2D line plot.
//
// Copyright (C) 2011  Alan W. Irwin
//
// This file is part of PLplot.
//
// PLplot is free software; you can redistribute it and/or modify
// it under the terms of the GNU Library General Public License as published
// by the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// PLplot is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public License
// along with PLplot; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
//
//

#include "plcdemos.h"
#define NSIZE    61

int
main(int argc, char *argv[])
{
	PLFLT x[NSIZE], y[NSIZE];
	PLFLT xmin = -3., xmax = 2., ymin = -4., ymax = 2.;
	int   i;

	// Prepare data to be plotted.
	for (i = 0; i < NSIZE; i++)
	{
		x[i] = (PLFLT)(i) *(xmax - xmin)/ (PLFLT)(NSIZE - 1) +xmin;
		y[i] = x[i] * x[i] * x[i] + 3* x[i]* x[i] - 4;
	}

	// Parse and process command line arguments
	plparseopts(&argc, argv, PL_PARSE_FULL);

	// Initialize plplot
	plinit();

	// Create a labelled box to hold the plot.
	plcol0(1);
	plenv(xmin, xmax, ymin, ymax, 0, 1);
	plcol0(2);
	pllab("x", "y= x#u4#d + 3x#u2#d -4#d", "Simple PLplot demo of a 2D line plot");

	plcol0(3);
	// Plot the data that was prepared above.
	plline(NSIZE, x, y);

	// Close PLplot library
	plend();

	exit(0);
}