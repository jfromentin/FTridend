//****************************************************************************//
//    Copyright (C) 2025 Jean Fromentin <jean.fromentin@univ-littoral.fr>     //
//                                                                            //
//  This file is part of FTridend <https://github.com/jfromentin/FTridend>    //
//                                                                            //
//  FTridend is a free software: you can redistribute it and/or modify it     //
//  under the terms of the GNU General Public License as published by the     //
//  Free Software Foundation, either version 3 of the License, or (at your    //
//  option) any later version.                                                //
//                                                                            //
//  FTridend is distributed in the hope that it will be useful, but WITHOUT   //
//  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or     //
//  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for  //
//  more details.                                                             //
//                                                                            //
//  You should have received a copy of the GNU General Public License along   //
//  with FTridend. If not, see <https://www.gnu.org/licenses/>.               //
//****************************************************************************//

#ifndef PYTHON_MATRIX_HPP
#define PYTHON_MATRIX_HPP

#include <Python.h>
#include <sstream>
#include "../kernel/schroeder_forest.hpp"

typedef struct {
  PyObject_HEAD
  SchroederForest data;
} SchroederForestObject;

int SchroederForestInit(SchroederForestObject*, PyObject*, PyObject*);
PyObject* SchroederForest_size(SchroederForestObject*, PyObject*);
PyObject* SchroederForest_height(SchroederForestObject*, PyObject*);
PyObject* SchroederForest_leaves(SchroederForestObject*, PyObject*);
PyObject* SchroederForest_layer(SchroederForestObject*, PyObject*);
PyObject* SchroederForest_display(SchroederForestObject*, PyObject*);

static PyMethodDef SchroederForestMethods[] = {
  {"size", (PyCFunction)SchroederForest_size, METH_NOARGS, "Return the size of the forest"},
  {"height", (PyCFunction)SchroederForest_height, METH_NOARGS, "Return the height of the forest"},
  {"leaves", (PyCFunction)SchroederForest_leaves, METH_NOARGS, "Return the number of leaves of the forest"},
  {"layer", (PyCFunction)SchroederForest_layer, METH_VARARGS, "Return the specified layer of the forest"},
  {"display", (PyCFunction)SchroederForest_display, METH_NOARGS, "Display the forest"},
  {NULL}
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"

static PyTypeObject SchroederForestType = {
  .ob_base = PyVarObject_HEAD_INIT(NULL, 0)
  .tp_name = "ftridend.kernel.SchroederForest",
  .tp_basicsize = sizeof(SchroederForestObject),
  .tp_itemsize = 0,
  .tp_flags = Py_TPFLAGS_DEFAULT,
  .tp_doc = PyDoc_STR("ftridend kernel SchroederForest"),
  .tp_methods = SchroederForestMethods,
  .tp_init = (initproc)SchroederForestInit,
  .tp_new = PyType_GenericNew,
};
#pragma GCC diagnostic pop

inline PyObject* SchroederForest_height(SchroederForestObject* self, PyObject *Py_UNUSED(ignored)) {
  return PyLong_FromLong(self -> data.height());
}

inline PyObject* SchroederForest_leaves(SchroederForestObject* self, PyObject *Py_UNUSED(ignored)) {
  return PyLong_FromLong(self -> data.leaves());
}

inline PyObject* SchroederForest_left_forests_length(SchroederForestObject* self, PyObject *Py_UNUSED(ignored)) {
  return PyLong_FromLong(self -> data.left_forests_length());
}

inline PyObject* SchroederForest_right_forests_length(SchroederForestObject* self, PyObject *Py_UNUSED(ignored)) {
  return PyLong_FromLong(self -> data.right_forests_length());
}

inline PyObject* SchroederForest_display(SchroederForestObject* self, PyObject *Py_UNUSED(ignored)) {
  ostringstream os;
  self -> data.display(os);
  return PyUnicode_FromString(os.str().c_str());
}



#endif
