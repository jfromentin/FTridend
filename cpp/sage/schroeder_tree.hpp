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
#include "../kernel/schroeder_tree.hpp"

typedef struct {
  PyObject_HEAD
  SchroederTree data;
} SchroederTreeObject;

int SchroederTreeInit(SchroederTreeObject*, PyObject*, PyObject*);
PyObject* SchroederTree_height(SchroederTreeObject*, PyObject*);
PyObject* SchroederTree_leaves(SchroederTreeObject*, PyObject*);
PyObject* SchroederTree_layer(SchroederTreeObject*, PyObject*);

static PyMethodDef SchroederTreeMethods[] = {
  {"height", (PyCFunction)SchroederTree_height, METH_NOARGS, "Return the height of the tree"},
  {"leaves", (PyCFunction)SchroederTree_leaves, METH_NOARGS, "Return the number of leaves of the tree"},
  {"layer", (PyCFunction)SchroederTree_layer, METH_VARARGS, "Return the specified layer of the tree"},
  {NULL}
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"

static PyTypeObject SchroederTreeType = {
  .ob_base = PyVarObject_HEAD_INIT(NULL, 0)
  .tp_name = "ftridend.kernel.SchroederTree",
  .tp_basicsize = sizeof(SchroederTreeObject),
  .tp_itemsize = 0,
  .tp_flags = Py_TPFLAGS_DEFAULT,
  .tp_doc = PyDoc_STR("ftridend kernel SchroederTree"),
  .tp_methods = SchroederTreeMethods,
  .tp_init = (initproc)SchroederTreeInit,
  .tp_new = PyType_GenericNew,
};
#pragma GCC diagnostic pop

inline PyObject* SchroederTree_height(SchroederTreeObject* self, PyObject *Py_UNUSED(ignored)) {
  return PyLong_FromLong(self -> data.height());
}

inline PyObject* SchroederTree_leaves(SchroederTreeObject* self, PyObject *Py_UNUSED(ignored)) {
  return PyLong_FromLong(self -> data.leaves());
}


#endif
