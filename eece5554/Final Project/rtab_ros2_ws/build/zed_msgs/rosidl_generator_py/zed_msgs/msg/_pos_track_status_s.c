// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from zed_msgs:msg/PosTrackStatus.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "zed_msgs/msg/detail/pos_track_status__struct.h"
#include "zed_msgs/msg/detail/pos_track_status__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool zed_msgs__msg__pos_track_status__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[46];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("zed_msgs.msg._pos_track_status.PosTrackStatus", full_classname_dest, 45) == 0);
  }
  zed_msgs__msg__PosTrackStatus * ros_message = _ros_message;
  {  // odometry_status
    PyObject * field = PyObject_GetAttrString(_pymsg, "odometry_status");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->odometry_status = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // spatial_memory_status
    PyObject * field = PyObject_GetAttrString(_pymsg, "spatial_memory_status");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->spatial_memory_status = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // status
    PyObject * field = PyObject_GetAttrString(_pymsg, "status");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->status = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * zed_msgs__msg__pos_track_status__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of PosTrackStatus */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("zed_msgs.msg._pos_track_status");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "PosTrackStatus");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  zed_msgs__msg__PosTrackStatus * ros_message = (zed_msgs__msg__PosTrackStatus *)raw_ros_message;
  {  // odometry_status
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->odometry_status);
    {
      int rc = PyObject_SetAttrString(_pymessage, "odometry_status", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // spatial_memory_status
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->spatial_memory_status);
    {
      int rc = PyObject_SetAttrString(_pymessage, "spatial_memory_status", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // status
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->status);
    {
      int rc = PyObject_SetAttrString(_pymessage, "status", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
