/*
 * A mex function to compute the area of a polygon
 * 
 * [ar] = polyarea(pa);
 *
 * pa :  cell array of polygons (nx2 matrices)
 * ar :  array of polygon areas with same shape as 'pa'
 *
 * Reference:
 * mathworld.wolfram.com/PolygonArea.html
 *
 * This software was developed at the National Institute of Standards and Technology
 * by employees of the Federal Government in the course of their official duties.
 * Pursuant to title 17 Section 105 of the United States Code this software is not
 * subject to copyright protection and is in the public domain. This software is an
 * experimental system. NIST assumes no responsibility whatsoever for its use by other
 * parties, and makes no guarantees, expressed or implied, about its quality, reliability,
 * or any other characteristic.
 *
 * Ulf Griesmann, NIST, November 2016
 */

#include <math.h>
#include <string.h>
#include <mex.h>

#ifdef __GNUC__
   #define RESTRICT __restrict
#else
   #define RESTRICT
#endif


/*-- local prototypes -----------------------------------------*/

static double
polygon_area(double * RESTRICT p, int M, int isopen);


/*-------------------------------------------------------------*/

void 
mexFunction(int nlhs, mxArray *plhs[], 
	    int nrhs, const mxArray *prhs[])
{
   mxArray *par;     /* pointer to array structure */
   double *pda;      /* polygon data */
   double *pout;     /* pointer to output data */
   double eps;
   int k, M, Nc, isopen;

   /* check argument pa */
   if ( !mxIsCell(prhs[0]) ) {
      mexErrMsgTxt("argument must be a cell array.");
   }

   Nc = mxGetNumberOfElements(prhs[0]);
   if (!Nc) {
      mexErrMsgTxt("polyarea: no input polygons pa.");
   }

   /* create output array */
   plhs[0] = mxCreateDoubleMatrix(Nc, 1, mxREAL);
   pout = (double *)mxGetData(plhs[0]);

   /* machine resolution */
   eps = mxGetEps();
   
   /* calculate polygon areas */
   for (k=0; k<Nc; k++) {

      /* get the next polygon from the cell array */ 
      par = mxGetCell(prhs[0], k); /* ptr to mxArray */
      pda = mxGetData(par);        /* ptr to a data */     
      M = mxGetM(par);             /* rows = vertex number */

      /* check if enough vertices */
      if (M < 3) {
	  mexErrMsgTxt("polyarea: polygons must have 3 or more vertices.");
      }

      /* check if the polygon is closed or open */
      if ((pda[0] - pda[M-1] > 2*eps) || (pda[M] - pda[2*M-1] > 2*eps)) {
	isopen = 1;
      }
      else {
	isopen = 0;
      }

      /* calculate area */
      pout[k] = polygon_area(pda, M, isopen);
   }
}


/*
 * calculate the area of a simple polygon
 * Note: polygons are in column-major order
 */
static double
polygon_area(double * RESTRICT p, int M, int isopen)
{
    int k;
    double A = 0.0;

    for (k=0; k<M-1; k++) {
        A += p[k]*p[M+k+1] - p[k+1]*p[M+k];
    }
    if (isopen) {
        A += p[M-1]*p[M] - p[0]*p[2*M-1]; 
    }
    A *= 0.5;

    return A;    
}
