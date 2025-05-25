//****************************************************************************//
//    Copyright (C) 2025 Jean Fromentin <jean.fromentin@univ-littoral.fr>     //
//                                                                            //
//  This file is part of CombO <https://gitlab.com/jfroment/combo>            //
//                                                                            //
//  CombO is free software: you can redistribute it and/or modify it          //
//  under ethe terms of the GNU General Public License as published by the     //
//  Free Software Foundation, either version 3 of the License, or             //
//  (at your option) any later version.                                       //
//                                                                            //
//  CombO is distributed in the hope that it will be useful, but WITHOUT      //
//  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or     //
//  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License      //
//  for more details.                                                         //
//                                                                            //
//  You should have received a copy of the GNU General Public License along   //
//  with CombO. If not, see <https://www.gnu.org/licenses/>.                  //
//****************************************************************************//

#include "schroeder_tree.hpp"

int SchroederTreeInit(SchroederTreeObject* self, PyObject* args, PyObject* Py_UNUSED(ignored)) {
  PyObject* ob = NULL;
  if (PyArg_UnpackTuple(args, "SchroederTreenInit", 0, 1, &ob)) {
    if (ob == NULL) {
      // Call empty constructor
      return 0;
    }
    else {
      if (PyList_CheckExact(ob)) {
	Int h = PyList_Size(ob) + 1;
	Int v = PyLong_AsLong(PyList_GetItem(ob, 0));
	Int n = popcount(v) + 1;
	self -> data.sage_init(h, n);
	self -> data.sage_set_value(0, v);
	for (int i = 1; i < h - 1; ++ i) {
	  v = PyLong_AsLong(PyList_GetItem(ob,i));
	  self -> data.sage_set_value(i, v);
	}
	if (not self -> data.validate()) {
	  PyErr_SetString(PyExc_AttributeError, "The chain is not valid");
	  return -1;
	}
	self -> data.initialize();
      }
      return 0;
    }
  }
  return 0;
}

PyObject* SchroederTree_layer(SchroederTreeObject* self, PyObject* args) {
  PyObject* ob = NULL;
  if(PyArg_UnpackTuple(args, "get", 1, 1, &ob)) {
    if(PyLong_CheckExact(ob)) {
      long i = PyLong_AsLong(ob);
      if (i < 0 or i >= self -> data.height()) {
	PyErr_SetString(PyExc_AttributeError, "Index out of range.");
	return NULL;
      }
      return PyLong_FromLong(self -> data.layer(i)); 
    }
    PyErr_SetString(PyExc_AttributeError, "Argument must be an integer.");
    return NULL;
  }
  PyErr_SetString(PyExc_AttributeError, "Exactly one argument is required.");
  return NULL; 
}
