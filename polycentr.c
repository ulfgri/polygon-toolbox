/*
 * A mex function to compute the center of gravity of one or more polygons.
 * 
 * [cg] = polycentr(pa);
 *
 * pa :  cell array of length N containing polygons (nx2 matrices)
 * cg :  Nx2 array with centers of gravity, one per row
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

static void
polygon_centroid(double * RESTRICT p, int M, int isopen, double *cgx, double *cgy);


/*-------------------------------------------------------------*/

void 
mexFunction(int nlhs, mxArray *plhs[], 
	    int nrhs, const mxArray *prhs[])
{
   mxArray *par;     /* pointer to array structure */
   double *pda;      /* polynom data */
   double *pout;     /* pointer to output data */
   double eps;
   int M, isopen;
   int k, Nc;

   /* check argument pa */
   if ( !mxIsCell(prhs[0]) ) {
      mexErrMsgTxt("argument must be a cell array.");
   }
   Nc = mxGetNumberOfElements(prhs[0]);
   if (!Nc) {
      mexErrMsgTxt("no input polygons pa.");
   }

   /* create output array */
   plhs[0] = mxCreateDoubleMatrix(Nc, 2, mxREAL);
   pout = (double *)mxGetData(plhs[0]);

   /* machine resolution */
   eps = mxGetEps();
   
   /* calculate polygon areas */
   for (k=0; k<Nc; k++) {

      /* get the next polygon from the cell array */ 
      par = mxGetCell(prhs[0], k); /* ptr to mxArray */
      pda = mxGetData(par);        /* ptr to a data */     
      M = mxGetM(par);             /* rows = vertex number */

      /* check if the polygon is closed or open */
      if ((pda[0] - pda[M-1] > 2*eps) || (pda[M] - pda[2*M-1] > 2*eps)) {
	isopen = 1;
      }
      else {
	isopen = 0;
      }

      /* check if enough vertices */
      if (M < 2) {
	  mexErrMsgTxt("polygons must have at least 3 vertices.");
      }

      /* calculate centroids */
      polygon_centroid(pda, M, isopen, &pout[k], &pout[Nc+k]);
   }
}


/*
 * calculate the centroid of a simple polygon
 */
static void
polygon_centroid(double * RESTRICT p, int M, int isopen, double *cgx, double *cgy)
{
    int k;
    double X,Y;
    double A, beta;

    A = X = Y = 0.0;

    for (k=0; k<M-1; k++) {
        beta = p[k]*p[M+k+1] - p[k+1]*p[M+k];
	A += beta;
        X += beta * (p[k] + p[k+1]);
	Y += beta * (p[M+k] + p[M+k+1]);
    }
    if (isopen) {
        beta = p[M-1]*p[M] - p[0]*p[2*M-1]; 
        A += beta; 
	X += beta * (p[M-1] + p[0]);
	Y += beta * (p[2*M-1] + p[M]);
    }

    A *= 3.0;
    *cgx = X / A;
    *cgy = Y / A;
}
