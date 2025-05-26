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

#include "schroeder_forest.hpp"
#include "schroeder_tree.hpp"

int SchroederForestInit(SchroederForestObject* self, PyObject* args, PyObject* Py_UNUSED(ignored)) {
  PyObject* ob = NULL;
  if (PyArg_UnpackTuple(args, "SchroederTreenInit", 0, 1, &ob)) {
    if (ob == NULL) {
      // Call empty constructor
      return 0;
    }
    PyTypeObject* type = Py_TYPE(ob);
    if(strcmp(type -> tp_name, SchroederTreeType.tp_name) == 0) {
      SchroederTreeObject* tree = (SchroederTreeObject*) ob;
      self -> data = SchroederForest(tree -> data);
      return 0;
    }
    PyErr_SetString(PyExc_AttributeError, "Argument must be a SchroederTree.");
    return -1;
  }
  PyErr_SetString(PyExc_AttributeError, "At most one argument is required.");
  return -1;
}

PyObject* SchroederForest_layer(SchroederForestObject* self, PyObject* args) {
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
