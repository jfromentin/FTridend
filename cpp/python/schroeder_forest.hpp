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

#ifndef PYTHON_SCHROEDER_FOREST_HPP
#define PYTHON_SCHROEDER_FOREST_HPP

#include <Python.h>
#include <sstream>
#include "../kernel/schroeder_forest.hpp"
#include "doc/schroeder_forest.hpp"

//************************
//* SchroederForest object *
//************************

typedef struct {
  PyObject_HEAD
  SchroederForest data;
} SchroederForestObject;

//-----------------
// Python operator
//-----------------

int SchroederForestInit(SchroederForestObject*, PyObject*, PyObject*);
PyObject* PyObjectFromCpp(const SchroederForest& p);
Py_hash_t SchroederForestHash(SchroederForestObject*);
PyObject* SchroederForestRepr(SchroederForestObject*);

//------------------
// Member functions
//------------------

PyObject* SchroederForest_size(SchroederForestObject*, PyObject*);
PyObject* SchroederForest_height(SchroederForestObject*, PyObject*);
PyObject* SchroederForest_leaves(SchroederForestObject*, PyObject*);
PyObject* SchroederForest_layer(SchroederForestObject*, PyObject*);
PyObject* SchroederForest_display(SchroederForestObject*, PyObject*);

static PyMethodDef SchroederForestMethods[] = {
  {"size", (PyCFunction)SchroederForest_size, METH_NOARGS, SchroederForest_size_doc},
  {"height", (PyCFunction)SchroederForest_height, METH_NOARGS, SchroederForest_height_doc},
  {"leaves", (PyCFunction)SchroederForest_leaves, METH_NOARGS, SchroederForest_leaves_doc},
  {"layer", (PyCFunction)SchroederForest_layer, METH_VARARGS, SchroederForest_layer_doc},
  {"display", (PyCFunction)SchroederForest_display, METH_NOARGS, SchroederForest_display_doc},
  {NULL}
};

//--------------------
// Object declaration
//--------------------

extern PyTypeObject SchroederForestType;

//**************************
//* Inline Python operator *
//**************************

// Hash operator
inline
Py_hash_t SchroederForestHash(SchroederForestObject* self) {
  return self -> data.hash();
}

// Repr operator
inline
PyObject* SchroederForestRepr(SchroederForestObject* self) {
  string res = to_string(self -> data);
  return PyUnicode_FromString(res.c_str());
}
  
// FromCpp operator
inline
PyObject* PyObjectFromCpp(const SchroederForest& cpp) {
  SchroederForestObject* res = (SchroederForestObject*)SchroederForestType.tp_alloc(&SchroederForestType, 1);
  res -> data = cpp;
  return (PyObject*)res;
}

//***************************
//* Inline member functions *
//***************************

inline PyObject* SchroederForest_size(SchroederForestObject* self, PyObject *Py_UNUSED(ignored)) {
  return PyLong_FromLong(self -> data.size());
}

inline PyObject* SchroederForest_height(SchroederForestObject* self, PyObject *Py_UNUSED(ignored)) {
  return PyLong_FromLong(self -> data.height());
}

inline PyObject* SchroederForest_leaves(SchroederForestObject* self, PyObject *Py_UNUSED(ignored)) {
  return PyLong_FromLong(self -> data.leaves());
}

inline PyObject* SchroederForest_display(SchroederForestObject* self, PyObject *Py_UNUSED(ignored)) {
  ostringstream os;
  self -> data.display(os);
  return PyUnicode_FromString(os.str().c_str());
}

#endif
