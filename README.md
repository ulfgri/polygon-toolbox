
Planar Polygon Functions for Octave & MATLAB
============================================

Ulf GRIESMANN, 2016 ... 2020  

An [Octave](https://octave.org) and [Matlab](https://www.mathworks.com)  mex interface to the
[Clipper library by Angus Johnson](https://sourceforge.net/projects/polyclipping),
and additional mex functions for fast calculation of polygon orientation, polygon
area, testing if a point is inside a polygon, etc.


Polygon clipping:
-----------------

       [pc,hc] = polybool(pa, pb, 'op', ha, hb, ug);
       
where 'op' can be 'and' (intersection), 'or' (union), 'notb' or 'diff'
(difference), and 'xor'. pa, pb, and pc are cell arrays with nx2
matrices containing polygon vertices (one vertex per row). ha, hb, hc
are logical arrays with hole flags. If ha(k) > 0, then pa{k} is an
interior polygon belonging to a polygon with one or more holes. The 
clipping operation is performed on an integer grid. The polygon data
are multiplied with the scale factor 'ug' prior to the clipping
operation and the resulting polygons are scaled by 1/ug.


Polygon orientation:
--------------------

       cw = iscw(pa);
       
Make polygons oriented clockwise (cw) or counter clockwise (ccw):

       P = polycw(pa);

where P and pa are cell arrays of polygons.


Check if points are inside a polygon:
-------------------------------------

       inp = isinpolygon(polygon, xy);

where 'polygon' is a n x 2 array of polygon vertices and 'xy' an n x 2 array
of points. 'inp' is a logical arrray.


Polygon area
------------

       A = polyarea(pa);

where 'pa' is a cell array of polygons and 'A' is a vector with polygon areas.


Polygon centroid
----------------

       C = polycentr(pa);

where 'pa' is a cell array of polygons and 'C' is an nx2 array with centroids,
one per row for each input polygon. Call twice to calculate the combined 
centroid of multiple polygons.


Polygon intersections
---------------------
Calculates all line intersections of two open or closed polygons.

	[xy,nseg] = polyinters(pa,pb);

where 'pa', 'pb' are Nx2 matrices with vertices for two polygons, 'xy' is a
matrix with polygon intersections, nseg(:,1) are the corresponding numbers
of the segments of polygon pa and nseg(:,2) the segment numbers of polygon pb
on which the intersections are found.


Compilation:
------------
The mex functions must be compiled before they can used.

On Octave/Windows or Matlab type the command
   
   makemex

at the Octave/Matlab prompt (the polybool directory must be the current 
directory). For Octave on Linux compile the mex functions by 
running 

   ./makemex-octave

at a shell prompt.
