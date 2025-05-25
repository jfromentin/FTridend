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

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "schroeder_tree.hpp"

static PyModuleDef ftridend_kernel_module = {
  .m_base = PyModuleDef_HEAD_INIT,
  .m_name = "ftridend.kernel",
  .m_doc = "Kernel part of the ftridend module.",
  .m_size = -1,
};

PyMODINIT_FUNC
PyInit_kernel(void)
{
  PyObject *m;
  if (PyType_Ready(&SchroederTreeType) < 0) return NULL;
  
  m = PyModule_Create(&ftridend_kernel_module);
  if (m == NULL) return NULL;
  
  if (PyModule_AddObjectRef(m, "SchroederTree", (PyObject *)&SchroederTreeType) < 0) {
    Py_DECREF(m);
    return NULL;
  }
  return m;
}
