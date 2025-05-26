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
#include "schroeder_forest.hpp"

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
	return 0;
      }
      PyErr_SetString(PyExc_AttributeError, "A list of integer is required");
      return -1;
    }
  }
  PyErr_SetString(PyExc_AttributeError, "At most one argument is required");
  return -1;
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

PyObject* SchroederTree_left_forest(SchroederTreeObject* self, PyObject* args) {
  PyObject* ob1 = NULL;
  PyObject* ob2 = NULL;
  if(PyArg_UnpackTuple(args, "left_forest", 2, 2, &ob1, &ob2)) {
    PyTypeObject* type = Py_TYPE(ob1);
    if(strcmp(type -> tp_name, SchroederForestType.tp_name) != 0) {
      PyErr_SetString(PyExc_AttributeError, "First argument must be a SchroederForest.");
      return NULL;
    }
    if(! PyLong_CheckExact(ob2)) {
      PyErr_SetString(PyExc_AttributeError, "Second argument must be an integr.");
      return NULL;
    }
    SchroederForestObject* forest = (SchroederForestObject*)ob1;
    long i = PyLong_AsLong(ob2);
    if (i < 0 or i >= self -> data.left_forests_length()) {
      PyErr_SetString(PyExc_AttributeError, "Index out of range.");
      return NULL;
    }
    self -> data.set_left_comb_forest(forest -> data, i);
    return Py_None;
  }
  PyErr_SetString(PyExc_AttributeError, "Exactly two arguments are required.");
  return NULL; 
}

PyObject* SchroederTree_right_forest(SchroederTreeObject* self, PyObject* args) {
  PyObject* ob1 = NULL;
  PyObject* ob2 = NULL;
  if(PyArg_UnpackTuple(args, "right_forest", 2, 2, &ob1, &ob2)) {
    PyTypeObject* type = Py_TYPE(ob1);
    if(strcmp(type -> tp_name, SchroederForestType.tp_name) != 0) {
      PyErr_SetString(PyExc_AttributeError, "First argument must be a SchroederForest.");
      return NULL;
    }
    if(! PyLong_CheckExact(ob2)) {
      PyErr_SetString(PyExc_AttributeError, "Second argument must be an integr.");
      return NULL;
    }
    SchroederForestObject* forest = (SchroederForestObject*)ob1;
    long i = PyLong_AsLong(ob2);
    if (i < 0 or i >= self -> data.right_forests_length()) {
      PyErr_SetString(PyExc_AttributeError, "Index out of range.");
      return NULL;
    }
    self -> data.set_right_comb_forest(forest -> data, i);
    return Py_None;
  }
  PyErr_SetString(PyExc_AttributeError, "Exactly two arguments are required.");
  return NULL; 
}

PyObject* SchroederTree_left_forest_info(SchroederTreeObject* self, PyObject* args) {
  PyObject* ob = NULL;
  if(PyArg_UnpackTuple(args, "left_forest_info", 1, 1, &ob)) {
    if(PyLong_CheckExact(ob)) {
      long i = PyLong_AsLong(ob);
      if (i < 0 or i >= self -> data.left_forests_length()) {
	PyErr_SetString(PyExc_AttributeError, "Index out of range.");
	return NULL;
      }
      const ForestInfo& info = self -> data.get_left_forest_info(i);
      PyObject* res = PyList_New(3);
      PyList_SetItem(res, 0, PyLong_FromLong(info.h));
      PyList_SetItem(res, 1, PyLong_FromLong(info.n));
      PyList_SetItem(res, 2, PyLong_FromLong(info.a));
      return res;
    }
    PyErr_SetString(PyExc_AttributeError, "Argument must be an integer.");
    return NULL;
  }
  PyErr_SetString(PyExc_AttributeError, "Exactly one argument is required.");
  return NULL; 
}

PyObject* SchroederTree_right_forest_info(SchroederTreeObject* self, PyObject* args) {
  PyObject* ob = NULL;
  if(PyArg_UnpackTuple(args, "right_forest_info", 1, 1, &ob)) {
    if(PyLong_CheckExact(ob)) {
      long i = PyLong_AsLong(ob);
      if (i < 0 or i >= self -> data.right_forests_length()) {
	PyErr_SetString(PyExc_AttributeError, "Index out of range.");
	return NULL;
      }
      const ForestInfo& info = self -> data.get_right_forest_info(i);
      PyObject* res = PyList_New(3);
      PyList_SetItem(res, 0, PyLong_FromLong(info.h));
      PyList_SetItem(res, 1, PyLong_FromLong(info.n));
      PyList_SetItem(res, 2, PyLong_FromLong(info.a));
      return res;
    }
    PyErr_SetString(PyExc_AttributeError, "Argument must be an integer.");
    return NULL;
  }
  PyErr_SetString(PyExc_AttributeError, "Exactly one argument is required.");
  return NULL; 
}
