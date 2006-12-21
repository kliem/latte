// This is a -*- C++ -*- header file.

/* RegularTriangulationWithCddlib.h -- Regular triangulation using CDDLIB
	       
   Copyright 2006 Matthias Koeppe

   This file is part of LattE.
   
   LattE is free software; you can redistribute it and/or modify it
   under the terms of the version 2 of the GNU General Public License
   as published by the Free Software Foundation.

   LattE is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with LattE; if not, write to the Free Software Foundation,
   Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
*/

#ifndef REGULARTRIANGULATIONWITHCDDLIB_H
#define REGULARTRIANGULATIONWITHCDDLIB_H

#include "barvinok/barvinok.h"

/* Helper functions. */
#include <vector>
#include "latte_cddlib.h"

std::vector<listVector *>
ray_array(listCone *cone);

listCone *
cone_from_ray_set(vector<listVector *> &rays,
		  set_type ray_set,
		  Vertex *vertex);

/* Height functions for regular triangulations. */
typedef void
height_function_type(mpq_t height, const vec_ZZ &ray, void *data);

void
random_height(mpq_t height, const vec_ZZ &ray, void *data);

void
delone_height(mpq_t height, const vec_ZZ &ray, void *data);

/* General function to compute a regular triangulation. */
listCone *
triangulate_cone_with_cddlib(listCone *cone,
			     BarvinokParameters *Parameters,
			     height_function_type height_function,
			     void *height_function_data,
			     int cone_dimension);

/* Triangulate a full-dimensional CONE. */
listCone *
random_regular_triangulation_with_cddlib(listCone *cone,
					 BarvinokParameters *Parameters);

listCone *
refined_delone_triangulation_with_cddlib(listCone *cone,
					 BarvinokParameters *Parameters);

#endif
