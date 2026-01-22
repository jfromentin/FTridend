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

#include "schroeder_tree.hpp"
#include "schroeder_forest.hpp"

//***************
//* Python type *
//***************

PyTypeObject SchroederTreeType = {
  .ob_base = PyVarObject_HEAD_INIT(NULL, 0)
  .tp_name = "ftridend.SchroederTree",
  .tp_basicsize = sizeof(SchroederTreeObject),
  .tp_itemsize = 0,
  .tp_repr = (reprfunc)SchroederTreeRepr,
  .tp_hash = (hashfunc)SchroederTreeHash,
  .tp_flags = Py_TPFLAGS_DEFAULT,
  .tp_doc = PyDoc_STR("SchroederTree"),
  .tp_methods = SchroederTreeMethods,
  .tp_init = (initproc)SchroederTreeInit,
  .tp_new = PyType_GenericNew,
};

//********************
//* Python operators *
//********************

//----------------
// Initialisation
//----------------

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

//********************
//* Member functions *
//********************

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
  PyObject* ob = NULL;
  if(PyArg_UnpackTuple(args, "left_forest", 1, 1, &ob)) {
    if(!PyLong_CheckExact(ob)) {
      PyErr_SetString(PyExc_AttributeError, "Argument must be an integer.");
      return NULL;
    }
    long i = PyLong_AsLong(ob);
    if (i < 0 or i >= self -> data.left_forests_length()) {
      PyErr_SetString(PyExc_AttributeError, "Index out of range.");
      return NULL;
    }
    SchroederForestObject* res = (SchroederForestObject*)SchroederForestType.tp_alloc(&SchroederForestType, 1);
    self -> data.set_left_comb_forest(res -> data, i);
    return (PyObject*)res;
  }
  PyErr_SetString(PyExc_AttributeError, "Exactly one argument is required.");
  return NULL; 
}

PyObject* SchroederTree_right_forest(SchroederTreeObject* self, PyObject* args) {
  PyObject* ob = NULL;
  if(PyArg_UnpackTuple(args, "left_forest", 1, 1, &ob)) {
    if(!PyLong_CheckExact(ob)) {
      PyErr_SetString(PyExc_AttributeError, "Argument must be an integer.");
      return NULL;
    }
    long i = PyLong_AsLong(ob);
    if (i < 0 or i >= self -> data.right_forests_length()) {
      PyErr_SetString(PyExc_AttributeError, "Index out of range.");
      return NULL;
    }
    SchroederForestObject* res = (SchroederForestObject*)SchroederForestType.tp_alloc(&SchroederForestType, 1);
    self -> data.set_right_comb_forest(res -> data, i);
    return (PyObject*) res;
  }
  PyErr_SetString(PyExc_AttributeError, "Exactly one argument is required.");
  return NULL; 
}
