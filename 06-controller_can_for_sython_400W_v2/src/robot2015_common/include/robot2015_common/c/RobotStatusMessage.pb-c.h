/* Generated by the protocol buffer compiler.  DO NOT EDIT! */

#ifndef PROTOBUF_C_RobotStatusMessage_2eproto__INCLUDED
#define PROTOBUF_C_RobotStatusMessage_2eproto__INCLUDED

#include <google/protobuf-c/protobuf-c.h>

PROTOBUF_C_BEGIN_DECLS

#include "ControllerMessage.pb-c.h"

typedef struct _RobotStatusMessage RobotStatusMessage;
typedef struct _RobotStatusMessage__CameraServiceMessage RobotStatusMessage__CameraServiceMessage;
typedef struct _RobotStatusMessage__ImageRecognitionMessage RobotStatusMessage__ImageRecognitionMessage;
typedef struct _RobotStatusMessage__OnlineMessage RobotStatusMessage__OnlineMessage;
typedef struct _RobotStatusMessage__RoutePlanNaviMessage RobotStatusMessage__RoutePlanNaviMessage;
typedef struct _RobotStatusMessage__PanTiltCtrlMessage RobotStatusMessage__PanTiltCtrlMessage;
typedef struct _RobotStatusMessage__ManagementSystemMessage RobotStatusMessage__ManagementSystemMessage;


/* --- enums --- */


/* --- messages --- */

struct  _RobotStatusMessage__CameraServiceMessage
{
  ProtobufCMessage base;
  protobuf_c_boolean has_infraredcameraonline;
  int32_t infraredcameraonline;
  protobuf_c_boolean has_normalcameraonline;
  int32_t normalcameraonline;
  protobuf_c_boolean has_infraredcamerafocus;
  int32_t infraredcamerafocus;
};
#define ROBOT_STATUS_MESSAGE__CAMERA_SERVICE_MESSAGE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&robot_status_message__camera_service_message__descriptor) \
    , 0,0, 0,0, 0,0 }


struct  _RobotStatusMessage__ImageRecognitionMessage
{
  ProtobufCMessage base;
  protobuf_c_boolean has_taskid;
  int32_t taskid;
  protobuf_c_boolean has_tasksavepath;
  int32_t tasksavepath;
};
#define ROBOT_STATUS_MESSAGE__IMAGE_RECOGNITION_MESSAGE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&robot_status_message__image_recognition_message__descriptor) \
    , 0,0, 0,0 }


struct  _RobotStatusMessage__OnlineMessage
{
  ProtobufCMessage base;
  protobuf_c_boolean has_cameraserviceonline;
  int32_t cameraserviceonline;
  protobuf_c_boolean has_routeplannavionline;
  int32_t routeplannavionline;
  protobuf_c_boolean has_pantiltctrlonline;
  int32_t pantiltctrlonline;
  protobuf_c_boolean has_imagerecognitiononline;
  int32_t imagerecognitiononline;
  protobuf_c_boolean has_driverctrlonline;
  int32_t driverctrlonline;
  protobuf_c_boolean has_a310cameraonline;
  int32_t a310cameraonline;
  protobuf_c_boolean has_normalcameraonline;
  int32_t normalcameraonline;
};
#define ROBOT_STATUS_MESSAGE__ONLINE_MESSAGE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&robot_status_message__online_message__descriptor) \
    , 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0 }


struct  _RobotStatusMessage__RoutePlanNaviMessage
{
  ProtobufCMessage base;
  protobuf_c_boolean has_currentposition;
  int32_t currentposition;
  protobuf_c_boolean has_currentline;
  int32_t currentline;
  protobuf_c_boolean has_positionfinish;
  int32_t positionfinish;
  protobuf_c_boolean has_currenttaskendid;
  int32_t currenttaskendid;
};
#define ROBOT_STATUS_MESSAGE__ROUTE_PLAN_NAVI_MESSAGE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&robot_status_message__route_plan_navi_message__descriptor) \
    , 0,0, 0,0, 0,0, 0,0 }


struct  _RobotStatusMessage__PanTiltCtrlMessage
{
  ProtobufCMessage base;
  protobuf_c_boolean has_pantiltdevcomo;
  int32_t pantiltdevcomo;
  protobuf_c_boolean has_panpos;
  int32_t panpos;
  protobuf_c_boolean has_tlitpos;
  int32_t tlitpos;
  protobuf_c_boolean has_zoompos;
  int32_t zoompos;
  protobuf_c_boolean has_focuspos;
  int32_t focuspos;
  protobuf_c_boolean has_wiperstauts;
  int32_t wiperstauts;
  protobuf_c_boolean has_focusstauts;
  int32_t focusstauts;
};
#define ROBOT_STATUS_MESSAGE__PAN_TILT_CTRL_MESSAGE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&robot_status_message__pan_tilt_ctrl_message__descriptor) \
    , 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0 }


struct  _RobotStatusMessage__ManagementSystemMessage
{
  ProtobufCMessage base;
  char *taskid;
  char *taskname;
  char *meterpointid;
  char *meterpointname;
  char *stoppointid;
};
#define ROBOT_STATUS_MESSAGE__MANAGEMENT_SYSTEM_MESSAGE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&robot_status_message__management_system_message__descriptor) \
    , NULL, NULL, NULL, NULL, NULL }


struct  _RobotStatusMessage
{
  ProtobufCMessage base;
  protobuf_c_boolean has_stat;
  int32_t stat;
  ControllerMessage *controller;
  RobotStatusMessage__CameraServiceMessage *cameraservice;
  RobotStatusMessage__OnlineMessage *onlinemsg;
  RobotStatusMessage__RoutePlanNaviMessage *routeplannavi;
  RobotStatusMessage__ImageRecognitionMessage *imagerecognition;
  RobotStatusMessage__ManagementSystemMessage *managementsystem;
  RobotStatusMessage__PanTiltCtrlMessage *pantiltctrl;
};
#define ROBOT_STATUS_MESSAGE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&robot_status_message__descriptor) \
    , 0,0, NULL, NULL, NULL, NULL, NULL, NULL, NULL }


/* RobotStatusMessage__CameraServiceMessage methods */
void   robot_status_message__camera_service_message__init
                     (RobotStatusMessage__CameraServiceMessage         *message);
/* RobotStatusMessage__ImageRecognitionMessage methods */
void   robot_status_message__image_recognition_message__init
                     (RobotStatusMessage__ImageRecognitionMessage         *message);
/* RobotStatusMessage__OnlineMessage methods */
void   robot_status_message__online_message__init
                     (RobotStatusMessage__OnlineMessage         *message);
/* RobotStatusMessage__RoutePlanNaviMessage methods */
void   robot_status_message__route_plan_navi_message__init
                     (RobotStatusMessage__RoutePlanNaviMessage         *message);
/* RobotStatusMessage__PanTiltCtrlMessage methods */
void   robot_status_message__pan_tilt_ctrl_message__init
                     (RobotStatusMessage__PanTiltCtrlMessage         *message);
/* RobotStatusMessage__ManagementSystemMessage methods */
void   robot_status_message__management_system_message__init
                     (RobotStatusMessage__ManagementSystemMessage         *message);
/* RobotStatusMessage methods */
void   robot_status_message__init
                     (RobotStatusMessage         *message);
size_t robot_status_message__get_packed_size
                     (const RobotStatusMessage   *message);
size_t robot_status_message__pack
                     (const RobotStatusMessage   *message,
                      uint8_t             *out);
size_t robot_status_message__pack_to_buffer
                     (const RobotStatusMessage   *message,
                      ProtobufCBuffer     *buffer);
RobotStatusMessage *
       robot_status_message__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   robot_status_message__free_unpacked
                     (RobotStatusMessage *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*RobotStatusMessage__CameraServiceMessage_Closure)
                 (const RobotStatusMessage__CameraServiceMessage *message,
                  void *closure_data);
typedef void (*RobotStatusMessage__ImageRecognitionMessage_Closure)
                 (const RobotStatusMessage__ImageRecognitionMessage *message,
                  void *closure_data);
typedef void (*RobotStatusMessage__OnlineMessage_Closure)
                 (const RobotStatusMessage__OnlineMessage *message,
                  void *closure_data);
typedef void (*RobotStatusMessage__RoutePlanNaviMessage_Closure)
                 (const RobotStatusMessage__RoutePlanNaviMessage *message,
                  void *closure_data);
typedef void (*RobotStatusMessage__PanTiltCtrlMessage_Closure)
                 (const RobotStatusMessage__PanTiltCtrlMessage *message,
                  void *closure_data);
typedef void (*RobotStatusMessage__ManagementSystemMessage_Closure)
                 (const RobotStatusMessage__ManagementSystemMessage *message,
                  void *closure_data);
typedef void (*RobotStatusMessage_Closure)
                 (const RobotStatusMessage *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor robot_status_message__descriptor;
extern const ProtobufCMessageDescriptor robot_status_message__camera_service_message__descriptor;
extern const ProtobufCMessageDescriptor robot_status_message__image_recognition_message__descriptor;
extern const ProtobufCMessageDescriptor robot_status_message__online_message__descriptor;
extern const ProtobufCMessageDescriptor robot_status_message__route_plan_navi_message__descriptor;
extern const ProtobufCMessageDescriptor robot_status_message__pan_tilt_ctrl_message__descriptor;
extern const ProtobufCMessageDescriptor robot_status_message__management_system_message__descriptor;

PROTOBUF_C_END_DECLS


#endif  /* PROTOBUF_RobotStatusMessage_2eproto__INCLUDED */
