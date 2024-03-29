/////////////////////////////////////////////////////////////////////////////
/// @file CubicalBettiNumbers
///
/// @author Mateusz Juda <mateusz.juda@{ii.uj.edu.pl,gmail.com}>
///
/// @date 2015-04-26
/////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2000-2015 by the CAPD Group.
//
// This file constitutes a part of the CAPD library (capdRedHom),
// distributed under the terms of the GNU General Public License.
// Consult http://capd.ii.uj.edu.pl and  http://redhom.ii.edu.pl/ for details.
/////////////////////////////////////////////////////////////////////////////

#include "capd/apiRedHom/Algorithms.h"
#include "capd/apiRedHom/ComplexHelper.h"

#include <iostream>
#include <string>

using namespace capd::apiRedHom;

std::vector<CubicalHelper::FullCube> kleinCubes = {
   {12, 6, 6, 6}, {11, 6, 6, 6}, {11, 6, 6, 7}, {10, 6, 6, 7}, {9, 6, 6, 7},  {8, 6, 6, 7},  {8, 6, 6, 6},
   {8, 6, 6, 5},  {9, 6, 6, 5},  {10, 6, 6, 5}, {11, 6, 6, 5}, {11, 7, 6, 6}, {11, 7, 6, 7}, {11, 7, 6, 5},
   {11, 8, 6, 6}, {10, 8, 6, 7}, {10, 7, 6, 7}, {9, 7, 6, 7},  {8, 7, 6, 7},  {7, 6, 6, 6},  {8, 7, 6, 5},
   {9, 7, 6, 5},  {10, 7, 6, 5}, {10, 8, 6, 5}, {10, 9, 6, 6}, {10, 9, 6, 7}, {9, 8, 6, 7},  {7, 7, 6, 7},
   {7, 7, 6, 6},  {7, 7, 6, 5},  {9, 8, 6, 5},  {10, 9, 6, 5}, {9, 10, 6, 6}, {9, 9, 6, 7},  {8, 8, 6, 7},
   {8, 8, 6, 5},  {9, 9, 6, 5},  {8, 10, 6, 6}, {8, 10, 6, 7}, {8, 9, 6, 7},  {7, 9, 6, 7},  {7, 8, 6, 7},
   {7, 8, 6, 5},  {7, 9, 6, 5},  {8, 9, 6, 5},  {8, 10, 6, 5}, {7, 11, 7, 6}, {7, 10, 6, 7}, {6, 9, 6, 7},
   {6, 8, 6, 7},  {6, 8, 5, 6},  {6, 8, 6, 5},  {6, 9, 6, 5},  {7, 10, 6, 5}, {6, 11, 7, 6}, {6, 10, 6, 7},
   {6, 8, 5, 7},  {6, 8, 5, 5},  {6, 10, 6, 5}, {5, 10, 7, 6}, {5, 10, 7, 7}, {5, 10, 6, 7}, {5, 9, 6, 7},
   {5, 9, 6, 5},  {5, 10, 6, 5}, {5, 10, 7, 5}, {4, 10, 7, 6}, {4, 10, 7, 7}, {4, 9, 6, 7},  {5, 8, 5, 7},
   {5, 8, 5, 6},  {5, 8, 5, 5},  {4, 9, 6, 5},  {4, 10, 7, 5}, {3, 9, 7, 6},  {3, 9, 7, 7},  {4, 8, 6, 7},
   {4, 8, 5, 7},  {4, 8, 5, 6},  {4, 8, 5, 5},  {4, 8, 6, 5},  {3, 9, 7, 5},  {3, 8, 7, 6},  {3, 8, 7, 7},
   {3, 8, 6, 7},  {4, 7, 5, 6},  {3, 8, 6, 5},  {3, 8, 7, 5},  {2, 7, 7, 6},  {3, 7, 7, 7},  {3, 7, 6, 7},
   {3, 7, 5, 7},  {3, 7, 5, 6},  {3, 7, 5, 5},  {3, 7, 6, 5},  {3, 7, 7, 5},  {2, 6, 7, 6},  {2, 6, 7, 7},
   {3, 6, 6, 7},  {3, 6, 5, 7},  {3, 6, 5, 6},  {3, 6, 5, 5},  {3, 6, 6, 5},  {2, 6, 7, 5},  {2, 6, 8, 6},
   {2, 6, 6, 7},  {2, 6, 6, 5},  {3, 6, 7, 6},  {3, 6, 7, 7},  {2, 6, 5, 7},  {2, 6, 5, 6},  {2, 6, 5, 5},
   {3, 6, 7, 5},  {3, 5, 7, 6},  {3, 5, 7, 7},  {3, 5, 6, 7},  {3, 5, 5, 7},  {2, 5, 5, 6},  {3, 5, 5, 5},
   {3, 5, 6, 5},  {3, 5, 7, 5},  {4, 5, 7, 6},  {4, 4, 7, 6},  {4, 4, 7, 7},  {3, 4, 6, 7},  {3, 4, 5, 7},
   {3, 4, 5, 6},  {3, 4, 5, 5},  {3, 4, 6, 5},  {4, 4, 7, 5},  {4, 4, 6, 7},  {4, 3, 6, 7},  {3, 3, 5, 7},
   {3, 3, 5, 6},  {3, 3, 5, 5},  {4, 3, 6, 5},  {4, 4, 6, 5},  {5, 4, 7, 6},  {5, 4, 7, 7},  {5, 3, 6, 7},
   {4, 2, 5, 7},  {4, 2, 5, 6},  {4, 2, 5, 5},  {5, 3, 6, 5},  {5, 4, 7, 5},  {6, 4, 7, 6},  {6, 3, 7, 7},
   {5, 2, 6, 7},  {5, 2, 5, 7},  {5, 2, 5, 6},  {5, 2, 5, 5},  {5, 2, 6, 5},  {6, 3, 7, 5},  {6, 3, 6, 7},
   {6, 2, 6, 7},  {6, 1, 5, 7},  {6, 1, 5, 6},  {6, 1, 5, 5},  {6, 2, 6, 5},  {6, 3, 6, 5},  {6, 4, 6, 7},
   {6, 4, 6, 5},  {7, 3, 6, 7},  {7, 2, 6, 7},  {7, 1, 6, 7},  {7, 1, 5, 6},  {7, 1, 6, 5},  {7, 2, 6, 5},
   {7, 3, 6, 5},  {7, 5, 6, 6},  {7, 4, 6, 6},  {7, 4, 6, 7},  {8, 3, 6, 7},  {8, 2, 6, 7},  {8, 2, 6, 6},
   {8, 2, 6, 5},  {8, 3, 6, 5},  {7, 4, 6, 5},  {8, 4, 6, 7},  {9, 3, 6, 7},  {9, 2, 6, 7},  {9, 2, 6, 6},
   {9, 2, 6, 5},  {9, 3, 6, 5},  {8, 4, 6, 5},  {8, 5, 6, 7},  {9, 4, 6, 7},  {10, 4, 6, 7}, {10, 3, 6, 7},
   {10, 3, 6, 6}, {10, 3, 6, 5}, {10, 4, 6, 5}, {9, 4, 6, 5},  {8, 5, 6, 5},  {9, 5, 6, 7},  {11, 4, 6, 7},
   {11, 4, 6, 6}, {11, 4, 6, 5}, {9, 5, 6, 5},  {10, 5, 6, 7}, {11, 5, 6, 7}, {11, 5, 6, 6}, {11, 5, 6, 5},
   {10, 5, 6, 5}};

void KleinBetti()
{
   std::vector<int> betti = CubicalHelper::BettiNumbers(kleinCubes);
   std::vector<int> expectedBetti = {1, 1};
   assert(expectedBetti == betti);
   std::cout << "OK\n";
}

void KleinBettiZ2()
{
   std::vector<int> betti = CubicalHelper::BettiNumbers(kleinCubes, 2);
   std::vector<int> expectedBetti = {1, 2, 1};
   assert(expectedBetti == betti);
   std::cout << "OK\n";
}

void KleinBettiZp()
{
   std::vector<int> betti = CubicalHelper::BettiNumbers(kleinCubes, 1019);
   std::vector<int> expectedBetti = {1, 1};
   assert(expectedBetti == betti);
   std::cout << "OK\n";
}

void BuildComplexBetti()
{
   std::vector<size_t> complexSize = {20, 20, 20, 20};  // size in each dimension
   CubicalComplex complex(complexSize);

   for (auto cube : kleinCubes) {
      complex.insert(cube);  // insert full cube
   }

   complex.fillWithBoundaries();  // generates all cubes in boundary
   std::vector<int> betti = ComputeBettiNumbers(complex);
   std::vector<int> expectedBetti = {1, 1};

   assert(expectedBetti == betti);
   std::cout << "OK\n";
}

void BuildComplexBettiZ2()
{
   std::vector<size_t> complexSize = {20, 20, 20, 20};  // size in each dimension
   CubicalComplex complex(complexSize);

   for (auto cube : kleinCubes) {
      complex.insert(cube);  // insert full cube
   }

   complex.fillWithBoundaries();  // generates all cubes in boundary
   std::vector<int> betti = ComputeBettiNumbers(complex, 2);
   std::vector<int> expectedBetti = {1, 2, 1};

   assert(expectedBetti == betti);
   std::cout << "OK\n";
}

void BuildComplexBettiZp()
{
   std::vector<size_t> complexSize = {20, 20, 20, 20};  // size in each dimension
   CubicalComplex complex(complexSize);

   for (auto cube : kleinCubes) {
      complex.insert(cube);  // insert full cube
   }

   complex.fillWithBoundaries();  // generates all cubes in boundary
   std::vector<int> betti = ComputeBettiNumbers(complex, 1019);
   std::vector<int> expectedBetti = {1, 1};

   assert(expectedBetti == betti);
   std::cout << "OK\n";
}
