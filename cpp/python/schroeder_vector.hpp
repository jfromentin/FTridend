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

#ifndef PYTHON_SCHROEDER_VECTOR_HPP
#define PYTHON_SCHROEDER_VECTOR_HPP

#include <Python.h>
#include <sstream>
#include "../kernel/schroeder_vector.hpp"
#include "doc/schroeder_vector.hpp"

//**************************
//* SchroederVector object *
//**************************

typedef struct {
  PyObject_HEAD
  SchroederVector<int> data;
} SchroederVectorObject;

//-----------------
// Python operator
//-----------------

int SchroederVectorInit(SchroederVectorObject*, PyObject*, PyObject*);
PyObject* PyObjectFromCpp(const SchroederVector<int>& p);
Py_hash_t SchroederVectorHash(SchroederVectorObject*);
PyObject* SchroederVectorRepr(SchroederVectorObject*);


//------------------
// Member functions
//------------------

PyObject* SchroederVector_add(SchroederVectorObject*, PyObject*);
PyObject* SchroederVector_tikz(SchroederVectorObject*, PyObject*);

static PyMethodDef SchroederVectorMethods[] = {
  {"add", (PyCFunction)SchroederVector_add, METH_VARARGS, SchroederVector_add_doc},
  {"tikz", (PyCFunction)SchroederVector_tikz, METH_NOARGS, "Return tikz code to draw current SchroederVector"},
  {NULL}
};

//--------------------
// Object declaration
//--------------------

extern PyTypeObject SchroederVectorType;

//**************************
//* Inline Python operator *
//**************************

// Hash operator
inline
Py_hash_t SchroederVectorHash(SchroederVectorObject* self) {
  return self -> data.hash();
}

// Repr operator
inline
PyObject* SchroederVectorRepr(SchroederVectorObject* self) {
  const 
  string res = to_string(self -> data);
  return PyUnicode_FromString(res.c_str());
}

// FromCpp operator
inline
PyObject* PyObjectFromCpp(const SchroederVector<int>& cpp) {
  SchroederVectorObject* res = (SchroederVectorObject*)SchroederVectorType.tp_alloc(&SchroederVectorType, 1);
  res -> data = cpp;
  return (PyObject*)res;
}

//***************************
//* Inline member functions *
//***************************


inline PyObject* SchroederVector_tikz(SchroederVectorObject* self, PyObject *Py_UNUSED(ignored)) {
  return PyUnicode_FromString(self -> data.to_latex().c_str());
}

#endif
