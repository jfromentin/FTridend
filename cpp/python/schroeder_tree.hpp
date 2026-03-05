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

#ifndef PYTHON_SCHROEDER_TREE_HPP
#define PYTHON_SCHROEDER_TREE_HPP

#include <Python.h>
#include <sstream>
#include "../kernel/schroeder_tree.hpp"
#include "doc/schroeder_tree.hpp"

//************************
//* SchroederTree object *
//************************

typedef struct {
  PyObject_HEAD
  SchroederTree data;
} SchroederTreeObject;

//-----------------
// Python operator
//-----------------

int SchroederTreeInit(SchroederTreeObject*, PyObject*, PyObject*);
PyObject* PyObjectFromCpp(const SchroederTree& p);
Py_hash_t SchroederTreeHash(SchroederTreeObject*);
PyObject* SchroederTreeRepr(SchroederTreeObject*);


//------------------
// Member functions
//------------------

PyObject* SchroederTree_height(SchroederTreeObject*, PyObject*);
PyObject* SchroederTree_leaves(SchroederTreeObject*, PyObject*);
PyObject* SchroederTree_layer(SchroederTreeObject*, PyObject*);
PyObject* SchroederTree_left_forests_length(SchroederTreeObject*, PyObject*);
PyObject* SchroederTree_right_forests_length(SchroederTreeObject*, PyObject*);
PyObject* SchroederTree_left_forest(SchroederTreeObject*, PyObject*);
PyObject* SchroederTree_right_forest(SchroederTreeObject*, PyObject*);
PyObject* SchroederTree_display(SchroederTreeObject*, PyObject*);
PyObject* SchroederTree_tikz(SchroederTreeObject*, PyObject*);

static PyMethodDef SchroederTreeMethods[] = {
  {"height", (PyCFunction)SchroederTree_height, METH_NOARGS, SchroederTree_height_doc},
  {"leaves", (PyCFunction)SchroederTree_leaves, METH_NOARGS, SchroederTree_leaves_doc},
  {"layer", (PyCFunction)SchroederTree_layer, METH_VARARGS, SchroederTree_layer_doc},
  /*{"left_forests_length", (PyCFunction)SchroederTree_left_forests_length, METH_VARARGS, SchroederTree_left_forests_length_doc},
  {"right_forests_length", (PyCFunction)SchroederTree_right_forests_length, METH_VARARGS, SchroederTree_right_forests_length_doc},
  
  {"left_forest", (PyCFunction)SchroederTree_left_forest, METH_VARARGS, SchroederTree_left_forest_doc},
  {"right_forest", (PyCFunction)SchroederTree_right_forest, METH_VARARGS, SchroederTree_right_forest_doc},*/
  {"display", (PyCFunction)SchroederTree_display, METH_NOARGS, SchroederTree_display_doc},
  {"tikz", (PyCFunction)SchroederTree_tikz, METH_NOARGS, "Return tikz code to draw current SchroederTree"},
  {NULL}
};

//--------------------
// Object declaration
//--------------------

extern PyTypeObject SchroederTreeType;

//**************************
//* Inline Python operator *
//**************************

// Hash operator
inline
Py_hash_t SchroederTreeHash(SchroederTreeObject* self) {
  return self -> data.hash();
}

// Repr operator
inline
PyObject* SchroederTreeRepr(SchroederTreeObject* self) {
  string res = to_string(self -> data);
  return PyUnicode_FromString(res.c_str());
}

// FromCpp operator
inline
PyObject* PyObjectFromCpp(const SchroederTree& cpp) {
  SchroederTreeObject* res = (SchroederTreeObject*)SchroederTreeType.tp_alloc(&SchroederTreeType, 1);
  res -> data = cpp;
  return (PyObject*)res;
}

//***************************
//* Inline member functions *
//***************************

inline PyObject* SchroederTree_height(SchroederTreeObject* self, PyObject *Py_UNUSED(ignored)) {
  return PyLong_FromLong(self -> data.height());
}

inline PyObject* SchroederTree_leaves(SchroederTreeObject* self, PyObject *Py_UNUSED(ignored)) {
  return PyLong_FromLong(self -> data.leaves());
}

/*inline PyObject* SchroederTree_left_forests_length(SchroederTreeObject* self, PyObject *Py_UNUSED(ignored)) {
  return PyLong_FromLong(self -> data.left_forests_length());
}

inline PyObject* SchroederTree_right_forests_length(SchroederTreeObject* self, PyObject *Py_UNUSED(ignored)) {
  return PyLong_FromLong(self -> data.right_forests_length());
  }*/

inline PyObject* SchroederTree_display(SchroederTreeObject* self, PyObject *Py_UNUSED(ignored)) {
  ostringstream os;
  self -> data.display(os);
  return PyUnicode_FromString(os.str().c_str());
}

inline PyObject* SchroederTree_tikz(SchroederTreeObject* self, PyObject *Py_UNUSED(ignored)) {
  return PyUnicode_FromString(self -> data.to_latex().c_str());
}

#endif
