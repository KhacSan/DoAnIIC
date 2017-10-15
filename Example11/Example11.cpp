// Example11.cpp : Defines the entry point for the console application.
//
#include"stdafx.h"
#include "plcdemos.h"

#define XPTS      35            // Data points in x
#define YPTS      46            // Data points in y
#define LEVELS    10

static int           opt[] = { DRAW_LINEXY, DRAW_LINEXY };

static PLFLT         alt[] = { 33.0, 17.0 };
static PLFLT         az[] = { 24.0, 115.0 };

static PLCHAR_VECTOR title[4] =
{
	"#frPLplot Example 11 - Alt=33, Az=24, Opt=3",
	"#frPLplot Example 11 - Alt=17, Az=115, Opt=3",
};

static void
cmap1_init(void)
{
	PLFLT i[2], h[2], l[2], s[2];

	i[0] = 0.0;         // left boundary 
	i[1] = 1.0;         // right boundary

	h[0] = 240;         // blue -> green -> yellow ->
	h[1] = 0;           // -> red

	l[0] = 0.6;//anh sang
	l[1] = 0.6;

	s[0] = 0.8;
	s[1] = 0.8; //dam nhat

	plscmap1n(256); //Set number of colors in cmap1
	c_plscmap1l(0, 2, i, h, l, s, NULL);  //Set cmap1 colors using a piece-wise linear relationship
}

//--------------------------------------------------------------------------
// main
//
// Does a series of mesh plots for a given data set, with different
// viewing options in each plot.
//--------------------------------------------------------------------------

int
main(int argc, char *argv[])
{
	int   i, j, k;
	PLFLT *x, *y, **z;
	PLFLT xx, yy;
	int   nlevel = LEVELS;
	PLFLT clevel[LEVELS];
	PLFLT zmin, zmax, step;

	// Parse and process command line arguments

	(void)plparseopts(&argc, argv, PL_PARSE_FULL);

	// Initialize plplot
	plsdev("svg");
	//plssub(2, 4);
	plinit();

	x = (PLFLT *)calloc(XPTS, sizeof(PLFLT));
	y = (PLFLT *)calloc(YPTS, sizeof(PLFLT));

	plAlloc2dGrid(&z, XPTS, YPTS);
	for (i = 0; i < XPTS; i++)
	{
		x[i] = 10. * (PLFLT)(i - (XPTS / 2)) / (PLFLT)(XPTS / 2);
	}

	for (i = 0; i < YPTS; i++)
		y[i] = 10. * (PLFLT)(i - (YPTS / 2)) / (PLFLT)(YPTS / 2);

	for (i = 0; i < XPTS; i++)
	{
		xx = x[i];
		for (j = 0; j < YPTS; j++)
		{
			yy = y[j];
			z[i][j] = pow(xx, 2) + pow(yy, 2);
		}
	}

	plMinMax2dGrid((PLFLT_MATRIX)z, XPTS, YPTS, &zmax, &zmin);
	//step = (zmax - zmin) / (nlevel + 1);
	//for (i = 0; i < nlevel; i++)
	//	clevel[i] = zmin + step + step * i;

//	cmap1_init();
//	for (k = 0; k < 2; k++){
//		for (i = 0; i < 4; i++)		{
			//pladv(0);
			plcol0(1);
			plenv(-1.0, 1.0, -1.0, 1.5, 0, 1);
		    //plvpor(0.0, 1.0, 0.0, 0.9); // Specify viewport using normalized subpage coordinates (left,right,buttom,top)
			//plwind(-1.0, 1.0, -1.0, 1.5);  //Specify window
			plw3d(1.0, 1.0, 1.2, -10.0, 10.0, -10.0, 10.0, zmin, zmax, alt[0], az[0]); // Configure the transformations required for projecting a 3D surface on a 2D window
			plbox3("bnstu", "x axis", 0.0, 0,
	 	    	"bnstu", "y axis", 0.0, 0,
				"bcdmnstuv", "z axis", 0.0, 4);

			plcol0(2);

			// wireframe plot
			plmesh(x, y, (PLFLT_MATRIX)z, XPTS, YPTS, DRAW_LINEXY);

			if (i == 0)
				plmesh(x, y, (PLFLT_MATRIX)z, XPTS, YPTS, DRAW_LINEXY);

			// magnitude colored wireframe plot
			else if (i == 1)
				plmesh(x, y, (PLFLT_MATRIX)z, XPTS, YPTS, opt[0]| MAG_COLOR);

			// magnitude colored wireframe plot with sides
			else if (i == 2)
				plot3d(x, y, (PLFLT_MATRIX)z, XPTS, YPTS, opt[0] | MAG_COLOR, 1);

			// magnitude colored wireframe plot with base contour
			else if (i == 3)
				plmeshc(x, y, (PLFLT_MATRIX)z, XPTS, YPTS, opt[0] | MAG_COLOR | BASE_CONT,
					clevel, nlevel);

			plcol0(3);
			plmtex("t", 1.0, 0.5, 0.5, title[0]);
	//	}
	//}

	// Clean up

	free((void *)x);
	free((void *)y);
	plFree2dGrid(z, XPTS, YPTS);

	plend();
	system("pause");
	exit(0);
}
