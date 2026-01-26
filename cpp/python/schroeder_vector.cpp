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
#include "schroeder_vector.hpp"

//***************
//* Python type *
//***************

PyTypeObject SchroederVectorType = {
  .ob_base = PyVarObject_HEAD_INIT(NULL, 0)
  .tp_name = "ftridend.SchroederVector",
  .tp_basicsize = sizeof(SchroederVectorObject),
  .tp_itemsize = 0,
  .tp_repr = (reprfunc)SchroederVectorRepr,
  .tp_hash = (hashfunc)SchroederVectorHash,
  .tp_flags = Py_TPFLAGS_DEFAULT,
  .tp_doc = PyDoc_STR("SchroederVector"),
  .tp_methods = SchroederVectorMethods,
  .tp_init = (initproc)SchroederVectorInit,
  .tp_new = PyType_GenericNew,
};

//********************
//* Python operators *
//********************

//----------------
// Initialisation
//----------------

int SchroederVectorInit(SchroederVectorObject* self, PyObject* args, PyObject* Py_UNUSED(ignored)) {
  PyObject* ob = NULL;
  if (PyArg_UnpackTuple(args, "SchroederVectorInit", 0, 1, &ob)) {
    if (ob == NULL) {
      self -> data = SchroederVector<int>();
      return 0;
    }
    else {
      PyTypeObject* type = Py_TYPE(ob);
      if(strcmp(type -> tp_name, "ftridend.SchroederTree") == 0) {
	SchroederTreeObject* tree = (SchroederTreeObject*)ob;
	self -> data = SchroederVector<int>(tree -> data);
	return 0;
      }
      PyErr_SetString(PyExc_AttributeError, "A SchroederTree is  required");
      return -1;
    }
  }
  PyErr_SetString(PyExc_AttributeError, "At most one argument is required");
  return -1;
}

//********************
//* Member functions *
//********************

PyObject* SchroederVector_add(SchroederVectorObject* self, PyObject* args) {
  PyObject* ob1 = NULL;
  PyObject* ob2 = NULL;
  if(PyArg_UnpackTuple(args, "SchroederVector.add", 1, 2, &ob1, &ob2)) {
    PyTypeObject* type = Py_TYPE(ob1);
    if(strcmp(type -> tp_name, "ftridend.SchroederTree") != 0 and
       strcmp(type -> tp_name, "ftridend.SchroederVector") != 0) {
      PyErr_SetString(PyExc_AttributeError, "First argument must be a SchroederTree or a SchroederVector.");
      return NULL; 
    }
    long coeff = 1;
    if(ob2 != NULL) {
      if(not PyLong_CheckExact(ob2)) {
	PyErr_SetString(PyExc_AttributeError, "Second argument must be an integer.");
	return NULL;
      }
      coeff = PyLong_AsLong(ob2);
    }
    if(strcmp(type -> tp_name, "ftridend.SchroederTree") == 0) {
      SchroederTreeObject* tree = (SchroederTreeObject*)ob1;
      self -> data.add(tree -> data, coeff);
      return Py_None;
    }
    SchroederVectorObject* vector = (SchroederVectorObject*)ob1;
    self -> data.add(vector -> data, coeff);
    return Py_None;
  }
  PyErr_SetString(PyExc_AttributeError, "One or two arguments are required.");
  return NULL; 
}
