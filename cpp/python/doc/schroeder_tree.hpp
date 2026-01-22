//****************************************************************************//
//    Copyright (C) 2026 Jean Fromentin <jean.fromentin@univ-littoral.fr>     //
//                       Pierre Catoire <catoire_research@proton.me>          //
//                                                                            //
//  This file is part of FTridend <https://github.com/jfromentin/FTridend>    //
//                                                                            //
//  FTridend is free software: you can redistribute it and/or modify it       //
//  under ethe terms of the GNU General Public License as published by the    //
//  Free Software Foundation, either version 3 of the License, or             //
//  (at your option) any later version.                                       //
//                                                                            //
//  FTridend is distributed in the hope that it will be useful, but WITHOUT   //
//  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or     //
//  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License      //
//  for more details.                                                         //
//                                                                            //
//  You should have received a copy of the GNU General Public License along   //
//  with FTridend. If not, see <https://www.gnu.org/licenses/>.               //
//****************************************************************************//

#ifndef SCHROEDER_TREE_DOC_HPP
#define SCHROEDER_TREE_DOC_HPP

static const char* SchroederTree_height_doc = R"'''(
Return the height of the current SchroederTree.

EXAMPLES::

  >>> T = SchroederTree([511, 510,  494, 302, 14, 2])
  >>> T.height()
      7
)'''";

static const char* SchroederTree_leaves_doc = R"'''(
Return the number of leaves of the current SchroederTree.
)'''";

static const char* SchroederTree_layer_doc = R"'''(
Return the specified layer of the current SchroederTree.
)'''";

static const char* SchroederTree_left_forests_length_doc = R"'''(
Return the number of forests of the tree seen as left comb.
)'''";

static const char* SchroederTree_right_forests_length_doc = R"'''(
Return the number  of forests of the tree seen as right comb.
)'''";

static const char* SchroederTree_left_forest_doc = R"'''(
Return the ith forest of the tree seen as left comb.
)'''";

static const char* SchroederTree_right_forest_doc = R"'''(
Return the ith forest of the tree seen as right comb.
)'''"; 

static const char* SchroederTree_display_doc = R"'''(
Return a string to display the current SchroederTree.
)'''"; 

#endif
