// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from zed_msgs:msg/PosTrackStatus.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "zed_msgs/msg/detail/pos_track_status__rosidl_typesupport_introspection_c.h"
#include "zed_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "zed_msgs/msg/detail/pos_track_status__functions.h"
#include "zed_msgs/msg/detail/pos_track_status__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void zed_msgs__msg__PosTrackStatus__rosidl_typesupport_introspection_c__PosTrackStatus_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  zed_msgs__msg__PosTrackStatus__init(message_memory);
}

void zed_msgs__msg__PosTrackStatus__rosidl_typesupport_introspection_c__PosTrackStatus_fini_function(void * message_memory)
{
  zed_msgs__msg__PosTrackStatus__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember zed_msgs__msg__PosTrackStatus__rosidl_typesupport_introspection_c__PosTrackStatus_message_member_array[3] = {
  {
    "odometry_status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(zed_msgs__msg__PosTrackStatus, odometry_status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "spatial_memory_status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(zed_msgs__msg__PosTrackStatus, spatial_memory_status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(zed_msgs__msg__PosTrackStatus, status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers zed_msgs__msg__PosTrackStatus__rosidl_typesupport_introspection_c__PosTrackStatus_message_members = {
  "zed_msgs__msg",  // message namespace
  "PosTrackStatus",  // message name
  3,  // number of fields
  sizeof(zed_msgs__msg__PosTrackStatus),
  zed_msgs__msg__PosTrackStatus__rosidl_typesupport_introspection_c__PosTrackStatus_message_member_array,  // message members
  zed_msgs__msg__PosTrackStatus__rosidl_typesupport_introspection_c__PosTrackStatus_init_function,  // function to initialize message memory (memory has to be allocated)
  zed_msgs__msg__PosTrackStatus__rosidl_typesupport_introspection_c__PosTrackStatus_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t zed_msgs__msg__PosTrackStatus__rosidl_typesupport_introspection_c__PosTrackStatus_message_type_support_handle = {
  0,
  &zed_msgs__msg__PosTrackStatus__rosidl_typesupport_introspection_c__PosTrackStatus_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_zed_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, zed_msgs, msg, PosTrackStatus)() {
  if (!zed_msgs__msg__PosTrackStatus__rosidl_typesupport_introspection_c__PosTrackStatus_message_type_support_handle.typesupport_identifier) {
    zed_msgs__msg__PosTrackStatus__rosidl_typesupport_introspection_c__PosTrackStatus_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &zed_msgs__msg__PosTrackStatus__rosidl_typesupport_introspection_c__PosTrackStatus_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif