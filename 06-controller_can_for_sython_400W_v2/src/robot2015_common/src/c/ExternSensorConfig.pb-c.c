/* Generated by the protocol buffer compiler.  DO NOT EDIT! */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C_NO_DEPRECATED
#define PROTOBUF_C_NO_DEPRECATED
#endif

#include "ExternSensorConfig.pb-c.h"
void   extern_sensor_config__config__mode_fan__init
                     (ExternSensorConfig__ConfigModeFan         *message)
{
  static ExternSensorConfig__ConfigModeFan init_value = EXTERN_SENSOR_CONFIG__CONFIG__MODE_FAN__INIT;
  *message = init_value;
}
void   extern_sensor_config__init
                     (ExternSensorConfig         *message)
{
  static ExternSensorConfig init_value = EXTERN_SENSOR_CONFIG__INIT;
  *message = init_value;
}
size_t extern_sensor_config__get_packed_size
                     (const ExternSensorConfig *message)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &extern_sensor_config__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t extern_sensor_config__pack
                     (const ExternSensorConfig *message,
                      uint8_t       *out)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &extern_sensor_config__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t extern_sensor_config__pack_to_buffer
                     (const ExternSensorConfig *message,
                      ProtobufCBuffer *buffer)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &extern_sensor_config__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
ExternSensorConfig *
       extern_sensor_config__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (ExternSensorConfig *)
     protobuf_c_message_unpack (&extern_sensor_config__descriptor,
                                allocator, len, data);
}
void   extern_sensor_config__free_unpacked
                     (ExternSensorConfig *message,
                      ProtobufCAllocator *allocator)
{
  PROTOBUF_C_ASSERT (message->base.descriptor == &extern_sensor_config__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor extern_sensor_config__config__mode_fan__field_descriptors[5] =
{
  {
    "fan_ID",
    1,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT32,
    PROTOBUF_C_OFFSETOF(ExternSensorConfig__ConfigModeFan, has_fan_id),
    PROTOBUF_C_OFFSETOF(ExternSensorConfig__ConfigModeFan, fan_id),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "fan_enable",
    2,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT32,
    PROTOBUF_C_OFFSETOF(ExternSensorConfig__ConfigModeFan, has_fan_enable),
    PROTOBUF_C_OFFSETOF(ExternSensorConfig__ConfigModeFan, fan_enable),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "vaule_open",
    3,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_FLOAT,
    PROTOBUF_C_OFFSETOF(ExternSensorConfig__ConfigModeFan, has_vaule_open),
    PROTOBUF_C_OFFSETOF(ExternSensorConfig__ConfigModeFan, vaule_open),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "vaule_close",
    4,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_FLOAT,
    PROTOBUF_C_OFFSETOF(ExternSensorConfig__ConfigModeFan, has_vaule_close),
    PROTOBUF_C_OFFSETOF(ExternSensorConfig__ConfigModeFan, vaule_close),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "Ctrl_switch",
    5,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_FLOAT,
    PROTOBUF_C_OFFSETOF(ExternSensorConfig__ConfigModeFan, has_ctrl_switch),
    PROTOBUF_C_OFFSETOF(ExternSensorConfig__ConfigModeFan, ctrl_switch),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned extern_sensor_config__config__mode_fan__field_indices_by_name[] = {
  4,   /* field[4] = Ctrl_switch */
  0,   /* field[0] = fan_ID */
  1,   /* field[1] = fan_enable */
  3,   /* field[3] = vaule_close */
  2,   /* field[2] = vaule_open */
};
static const ProtobufCIntRange extern_sensor_config__config__mode_fan__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 5 }
};
const ProtobufCMessageDescriptor extern_sensor_config__config__mode_fan__descriptor =
{
  PROTOBUF_C_MESSAGE_DESCRIPTOR_MAGIC,
  "ExternSensorConfig.Config_Mode_fan",
  "ConfigModeFan",
  "ExternSensorConfig__ConfigModeFan",
  "",
  sizeof(ExternSensorConfig__ConfigModeFan),
  5,
  extern_sensor_config__config__mode_fan__field_descriptors,
  extern_sensor_config__config__mode_fan__field_indices_by_name,
  1,  extern_sensor_config__config__mode_fan__number_ranges,
  (ProtobufCMessageInit) extern_sensor_config__config__mode_fan__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor extern_sensor_config__field_descriptors[3] =
{
  {
    "Led_Color",
    1,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT32,
    PROTOBUF_C_OFFSETOF(ExternSensorConfig, has_led_color),
    PROTOBUF_C_OFFSETOF(ExternSensorConfig, led_color),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "Config_fan_Msg",
    2,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_MESSAGE,
    PROTOBUF_C_OFFSETOF(ExternSensorConfig, n_config_fan_msg),
    PROTOBUF_C_OFFSETOF(ExternSensorConfig, config_fan_msg),
    &extern_sensor_config__config__mode_fan__descriptor,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "Led_Flight",
    3,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT32,
    PROTOBUF_C_OFFSETOF(ExternSensorConfig, has_led_flight),
    PROTOBUF_C_OFFSETOF(ExternSensorConfig, led_flight),
    NULL,
    NULL,
    0,            /* packed */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned extern_sensor_config__field_indices_by_name[] = {
  1,   /* field[1] = Config_fan_Msg */
  0,   /* field[0] = Led_Color */
  2,   /* field[2] = Led_Flight */
};
static const ProtobufCIntRange extern_sensor_config__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 3 }
};
const ProtobufCMessageDescriptor extern_sensor_config__descriptor =
{
  PROTOBUF_C_MESSAGE_DESCRIPTOR_MAGIC,
  "ExternSensorConfig",
  "ExternSensorConfig",
  "ExternSensorConfig",
  "",
  sizeof(ExternSensorConfig),
  3,
  extern_sensor_config__field_descriptors,
  extern_sensor_config__field_indices_by_name,
  1,  extern_sensor_config__number_ranges,
  (ProtobufCMessageInit) extern_sensor_config__init,
  NULL,NULL,NULL    /* reserved[123] */
};
