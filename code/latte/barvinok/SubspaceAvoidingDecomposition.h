// This is a -*- C++ -*- header file.

/* SubspaceAvoidingDecomposition.h -- Barvinok decomposition that avoids a prescribed subspace
	       
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

#ifndef SUBSPACEAVOIDINGDECOMPOSITION_H
#define SUBSPACEAVOIDINGDECOMPOSITION_H

#include "latte_ntl.h"

/* Compute a short vector suitable for making a signed decomposition
   of the cone whose rays are given by B and whose facets are given by
   DUAL.

   The subspace to be avoided is that where the last (homogenization)
   coordinate is 0. */

vec_ZZ
ComputeShortVectorAvoidingSubspace(const mat_ZZ & B, const mat_ZZ &Dual);


#endif
