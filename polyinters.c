/*
 * A mex function to compute the line intersections of
 * two polygons
 * 
 * [ints,nseg] = polyinters(pa,pb);
 *
 * pa :    a polygon, nx2 matrix
 * pb :    a polygon, nx2 matrix
 * ints :  nx2 matrix with line intersections, empty if no intersections exist.
 * nseg :  nx1 vector with the polygon segment numbers on which the 
 *         intersections are found
 *
 * This software was developed at the National Institute of Standards and Technology
 * by employees of the Federal Government in the course of their official duties.
 * Pursuant to title 17 Section 105 of the United States Code this software is not
 * subject to copyright protection and is in the public domain. This software is an
 * experimental system. NIST assumes no responsibility whatsoever for its use by other
 * parties, and makes no guarantees, expressed or implied, about its quality, reliability,
 * or any other characteristic.
 *
 * Ulf Griesmann, NIST, July 2019
 */

#include <math.h>
#include <string.h>
#include <mex.h>

#ifdef __GNUC__
   #define RESTRICT __restrict
#else
   #define RESTRICT
#endif

#define TRUE  1
#define FALSE 0
#define NUM_ALLOC 64 /* number of vertices to pre-allocate */


/*-- local prototypes -----------------------------------------*/

static int
find_intersection(double x1, double y1, 
		  double x2, double y2,
		  double x3, double y3, 
		  double x4, double y4,
		  double *x, double *y);


/*-------------------------------------------------------------*/

void 
mexFunction(int nlhs, mxArray *plhs[], 
	    int nrhs, const mxArray *prhs[])
{
   double *pid;      /* pointer to output data */
   double *pda;      /* data for polygon A */
   double *pdb;      /* data for polygon B */
   double *px,*py;   /* pointers to buffers with x,y intersection coordinates */
   double *pia,*pib; /* pointers to buffers with intersection segment numbers */
   double x, y;      /* intersection coordinates */
   int Ma, Mb;
   int ka, kb;
   int numi = 0;     /* intersection counter */
   int nall = 0;     /* buffer reallocation counter */


   /* check number of arguments */
   if (nrhs != 2) {
       mexErrMsgTxt("function must have two input arguments.");
   }

   /* get input args */
   pda = mxGetData(prhs[0]);    /* ptr to a polygon a data */
   Ma = mxGetM(prhs[0]);
   pdb = mxGetData(prhs[1]);    /* ptr to a polygon b data */     
   Mb = mxGetM(prhs[1]);


   /* compare polygon segments */
   for (ka=0; ka<Ma-1; ka++) {   /* polygon a segments */
     for (kb=0; kb<Mb-1; kb++) { /* polygon b segments */

       if (find_intersection(pda[ka],pda[Ma+ka],pda[ka+1],pda[Ma+ka+1],
			     pdb[kb],pdb[Mb+kb],pdb[kb+1],pdb[Mb+kb+1],
			     &x, &y) ) {
	   if (!numi) {            /* create the output buffers */
	       px  = (double *)mxMalloc(NUM_ALLOC*sizeof(double));
	       py  = (double *)mxMalloc(NUM_ALLOC*sizeof(double));
	       pia = (double *)mxMalloc(NUM_ALLOC*sizeof(double));
	       pib = (double *)mxMalloc(NUM_ALLOC*sizeof(double));
	       nall = 1;
	   }
	   if (numi && !(numi % NUM_ALLOC)) { /* re-allocate larger buffers */
	       nall++;
	       px  = (double *)mxRealloc(px,  nall*NUM_ALLOC*sizeof(double));
	       py  = (double *)mxRealloc(py,  nall*NUM_ALLOC*sizeof(double));
	       pia = (double *)mxRealloc(pia, nall*NUM_ALLOC*sizeof(double));
	       pib = (double *)mxRealloc(pib, nall*NUM_ALLOC*sizeof(double));
	   } 

	   px[numi] = x;           /* add intersection to buffers */
	   py[numi] = y;
	   pia[numi] = ka+1;       /* segment intersection number to buffers */
	   pib[numi] = kb+1;
	   numi++;                 /* number of intersections */
       }
     }
   }
   
   /* create output matrices */
   if (!numi) { /* return empty matrices */     
       plhs[0] = mxCreateDoubleMatrix(0, 0, mxREAL);
       plhs[1] = mxCreateDoubleMatrix(0, 0, mxREAL);
   }
   else {
       plhs[0] = mxCreateDoubleMatrix(numi, 2, mxREAL);
       plhs[1] = mxCreateDoubleMatrix(numi, 2, mxREAL);

       pid = mxGetData(plhs[0]);
       memcpy(pid,      px, numi*sizeof(double));
       memcpy(pid+numi, py, numi*sizeof(double));
       
       pid = mxGetData(plhs[1]);
       memcpy(pid,      pia, numi*sizeof(double));
       memcpy(pid+numi, pib, numi*sizeof(double));

       mxFree(px);
       mxFree(py);
       mxFree(pia);
       mxFree(pib);
   }

}


/*
 * Determine the intersection point of two line segments
 * Return FALSE if the lines don't intersect.
 *
 * Ulf Griesmann, September 2018
 * Derived from code by Paul Bourke, http://paulbourke.net/geometry/
 */
static int
find_intersection(double x1, double y1, 
		  double x2, double y2,
		  double x3, double y3, 
		  double x4, double y4,
		  double *x, double *y)
{
   double mua,mub,eps;
   double denom,numera,numerb;
   double max_xa,max_xb,min_xa,min_xb,max_ya,max_yb,min_ya,min_yb;

   
   /* check if intersection is possible with bounding box overlap test */
   max_xa = fmax(x1,x2); min_xa = fmin(x1,x2);
   max_xb = fmax(x3,x4); min_xb = fmin(x3,x4);
   max_ya = fmax(y1,y2); min_ya = fmin(y1,y2);
   max_yb = fmax(y3,y4); min_yb = fmin(y3,y4);

   if ( ( (max_xa < min_xb) || (min_xa > max_xb) ) &&
	( (max_ya < min_yb) || (min_ya > max_yb) ) ) {
     *x = 0.0;
     *y = 0.0;
     return FALSE;
   }
   
   eps = mxGetEps();

   /* lines may intersect, proceed with further tests */
   denom  = (y4-y3) * (x2-x1) - (x4-x3) * (y2-y1);
   numera = (x4-x3) * (y1-y3) - (y4-y3) * (x1-x3);
   numerb = (x2-x1) * (y1-y3) - (y2-y1) * (x1-x3);

   /* Are the lines coincident ? */
   if (fabs(numera) <= eps && fabs(numerb) <= eps && fabs(denom) <= eps) {
      *x = 0.5 * (x1 + x2);
      *y = 0.5 * (y1 + y2);
      return TRUE;
   }

   /* Are the lines parallel ? */
   if (fabs(denom) <= eps) {
      *x = 0.0;
      *y = 0.0;
      return FALSE;
   }

   /* Is the intersection along the the segments */
   mua = numera / denom;
   mub = numerb / denom;
   if (mua < 0 || mua > 1 || mub < 0 || mub > 1) {
      *x = 0.0;
      *y = 0.0;
      return FALSE;
   }
   *x = x1 + mua * (x2 - x1);
   *y = y1 + mua * (y2 - y1);
   return TRUE;
}
