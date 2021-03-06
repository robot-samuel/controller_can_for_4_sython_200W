// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ErrorMessage.proto

#ifndef PROTOBUF_ErrorMessage_2eproto__INCLUDED
#define PROTOBUF_ErrorMessage_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ErrorMessage_2eproto();
void protobuf_AssignDesc_ErrorMessage_2eproto();
void protobuf_ShutdownFile_ErrorMessage_2eproto();

class ErrorMessage;

// ===================================================================

class ErrorMessage : public ::google::protobuf::Message {
 public:
  ErrorMessage();
  virtual ~ErrorMessage();

  ErrorMessage(const ErrorMessage& from);

  inline ErrorMessage& operator=(const ErrorMessage& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ErrorMessage& default_instance();

  void Swap(ErrorMessage* other);

  // implements Message ----------------------------------------------

  ErrorMessage* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ErrorMessage& from);
  void MergeFrom(const ErrorMessage& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional bool CarLeftFDriverError = 1;
  inline bool has_carleftfdrivererror() const;
  inline void clear_carleftfdrivererror();
  static const int kCarLeftFDriverErrorFieldNumber = 1;
  inline bool carleftfdrivererror() const;
  inline void set_carleftfdrivererror(bool value);

  // optional bool CarRightFDriverError = 2;
  inline bool has_carrightfdrivererror() const;
  inline void clear_carrightfdrivererror();
  static const int kCarRightFDriverErrorFieldNumber = 2;
  inline bool carrightfdrivererror() const;
  inline void set_carrightfdrivererror(bool value);

  // optional bool CarLeftBDriverError = 3;
  inline bool has_carleftbdrivererror() const;
  inline void clear_carleftbdrivererror();
  static const int kCarLeftBDriverErrorFieldNumber = 3;
  inline bool carleftbdrivererror() const;
  inline void set_carleftbdrivererror(bool value);

  // optional bool CarRightBDriverError = 4;
  inline bool has_carrightbdrivererror() const;
  inline void clear_carrightbdrivererror();
  static const int kCarRightBDriverErrorFieldNumber = 4;
  inline bool carrightbdrivererror() const;
  inline void set_carrightbdrivererror(bool value);

  // optional bool LeftFDriverComError = 5;
  inline bool has_leftfdrivercomerror() const;
  inline void clear_leftfdrivercomerror();
  static const int kLeftFDriverComErrorFieldNumber = 5;
  inline bool leftfdrivercomerror() const;
  inline void set_leftfdrivercomerror(bool value);

  // optional bool RightFDriverComError = 6;
  inline bool has_rightfdrivercomerror() const;
  inline void clear_rightfdrivercomerror();
  static const int kRightFDriverComErrorFieldNumber = 6;
  inline bool rightfdrivercomerror() const;
  inline void set_rightfdrivercomerror(bool value);

  // optional bool LeftBDriverComError = 7;
  inline bool has_leftbdrivercomerror() const;
  inline void clear_leftbdrivercomerror();
  static const int kLeftBDriverComErrorFieldNumber = 7;
  inline bool leftbdrivercomerror() const;
  inline void set_leftbdrivercomerror(bool value);

  // optional bool RightBDriverComError = 8;
  inline bool has_rightbdrivercomerror() const;
  inline void clear_rightbdrivercomerror();
  static const int kRightBDriverComErrorFieldNumber = 8;
  inline bool rightbdrivercomerror() const;
  inline void set_rightbdrivercomerror(bool value);

  // optional bool ExternComDevError = 9;
  inline bool has_externcomdeverror() const;
  inline void clear_externcomdeverror();
  static const int kExternComDevErrorFieldNumber = 9;
  inline bool externcomdeverror() const;
  inline void set_externcomdeverror(bool value);

  // optional bool BMSSysError = 10;
  inline bool has_bmssyserror() const;
  inline void clear_bmssyserror();
  static const int kBMSSysErrorFieldNumber = 10;
  inline bool bmssyserror() const;
  inline void set_bmssyserror(bool value);

  // optional bool ObstacleStopError = 11;
  inline bool has_obstaclestoperror() const;
  inline void clear_obstaclestoperror();
  static const int kObstacleStopErrorFieldNumber = 11;
  inline bool obstaclestoperror() const;
  inline void set_obstaclestoperror(bool value);

  // optional bool CashSwitchStopError = 12;
  inline bool has_cashswitchstoperror() const;
  inline void clear_cashswitchstoperror();
  static const int kCashSwitchStopErrorFieldNumber = 12;
  inline bool cashswitchstoperror() const;
  inline void set_cashswitchstoperror(bool value);

  // optional bool CurrentOverloadError = 13;
  inline bool has_currentoverloaderror() const;
  inline void clear_currentoverloaderror();
  static const int kCurrentOverloadErrorFieldNumber = 13;
  inline bool currentoverloaderror() const;
  inline void set_currentoverloaderror(bool value);

  // optional bool DriverLeftFNodeOFF = 14;
  inline bool has_driverleftfnodeoff() const;
  inline void clear_driverleftfnodeoff();
  static const int kDriverLeftFNodeOFFFieldNumber = 14;
  inline bool driverleftfnodeoff() const;
  inline void set_driverleftfnodeoff(bool value);

  // optional bool DriverLeftBNodeOFF = 15;
  inline bool has_driverleftbnodeoff() const;
  inline void clear_driverleftbnodeoff();
  static const int kDriverLeftBNodeOFFFieldNumber = 15;
  inline bool driverleftbnodeoff() const;
  inline void set_driverleftbnodeoff(bool value);

  // optional bool DriverRightFNodeOFF = 16;
  inline bool has_driverrightfnodeoff() const;
  inline void clear_driverrightfnodeoff();
  static const int kDriverRightFNodeOFFFieldNumber = 16;
  inline bool driverrightfnodeoff() const;
  inline void set_driverrightfnodeoff(bool value);

  // optional bool DriverRightBNodeOFF = 17;
  inline bool has_driverrightbnodeoff() const;
  inline void clear_driverrightbnodeoff();
  static const int kDriverRightBNodeOFFFieldNumber = 17;
  inline bool driverrightbnodeoff() const;
  inline void set_driverrightbnodeoff(bool value);

  // optional bool BObstacleStopError = 18;
  inline bool has_bobstaclestoperror() const;
  inline void clear_bobstaclestoperror();
  static const int kBObstacleStopErrorFieldNumber = 18;
  inline bool bobstaclestoperror() const;
  inline void set_bobstaclestoperror(bool value);

  // optional bool DropStopError = 19;
  inline bool has_dropstoperror() const;
  inline void clear_dropstoperror();
  static const int kDropStopErrorFieldNumber = 19;
  inline bool dropstoperror() const;
  inline void set_dropstoperror(bool value);

  // @@protoc_insertion_point(class_scope:ErrorMessage)
 private:
  inline void set_has_carleftfdrivererror();
  inline void clear_has_carleftfdrivererror();
  inline void set_has_carrightfdrivererror();
  inline void clear_has_carrightfdrivererror();
  inline void set_has_carleftbdrivererror();
  inline void clear_has_carleftbdrivererror();
  inline void set_has_carrightbdrivererror();
  inline void clear_has_carrightbdrivererror();
  inline void set_has_leftfdrivercomerror();
  inline void clear_has_leftfdrivercomerror();
  inline void set_has_rightfdrivercomerror();
  inline void clear_has_rightfdrivercomerror();
  inline void set_has_leftbdrivercomerror();
  inline void clear_has_leftbdrivercomerror();
  inline void set_has_rightbdrivercomerror();
  inline void clear_has_rightbdrivercomerror();
  inline void set_has_externcomdeverror();
  inline void clear_has_externcomdeverror();
  inline void set_has_bmssyserror();
  inline void clear_has_bmssyserror();
  inline void set_has_obstaclestoperror();
  inline void clear_has_obstaclestoperror();
  inline void set_has_cashswitchstoperror();
  inline void clear_has_cashswitchstoperror();
  inline void set_has_currentoverloaderror();
  inline void clear_has_currentoverloaderror();
  inline void set_has_driverleftfnodeoff();
  inline void clear_has_driverleftfnodeoff();
  inline void set_has_driverleftbnodeoff();
  inline void clear_has_driverleftbnodeoff();
  inline void set_has_driverrightfnodeoff();
  inline void clear_has_driverrightfnodeoff();
  inline void set_has_driverrightbnodeoff();
  inline void clear_has_driverrightbnodeoff();
  inline void set_has_bobstaclestoperror();
  inline void clear_has_bobstaclestoperror();
  inline void set_has_dropstoperror();
  inline void clear_has_dropstoperror();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  bool carleftfdrivererror_;
  bool carrightfdrivererror_;
  bool carleftbdrivererror_;
  bool carrightbdrivererror_;
  bool leftfdrivercomerror_;
  bool rightfdrivercomerror_;
  bool leftbdrivercomerror_;
  bool rightbdrivercomerror_;
  bool externcomdeverror_;
  bool bmssyserror_;
  bool obstaclestoperror_;
  bool cashswitchstoperror_;
  bool currentoverloaderror_;
  bool driverleftfnodeoff_;
  bool driverleftbnodeoff_;
  bool driverrightfnodeoff_;
  bool driverrightbnodeoff_;
  bool bobstaclestoperror_;
  bool dropstoperror_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(19 + 31) / 32];

  friend void  protobuf_AddDesc_ErrorMessage_2eproto();
  friend void protobuf_AssignDesc_ErrorMessage_2eproto();
  friend void protobuf_ShutdownFile_ErrorMessage_2eproto();

  void InitAsDefaultInstance();
  static ErrorMessage* default_instance_;
};
// ===================================================================


// ===================================================================

// ErrorMessage

// optional bool CarLeftFDriverError = 1;
inline bool ErrorMessage::has_carleftfdrivererror() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ErrorMessage::set_has_carleftfdrivererror() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ErrorMessage::clear_has_carleftfdrivererror() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ErrorMessage::clear_carleftfdrivererror() {
  carleftfdrivererror_ = false;
  clear_has_carleftfdrivererror();
}
inline bool ErrorMessage::carleftfdrivererror() const {
  return carleftfdrivererror_;
}
inline void ErrorMessage::set_carleftfdrivererror(bool value) {
  set_has_carleftfdrivererror();
  carleftfdrivererror_ = value;
}

// optional bool CarRightFDriverError = 2;
inline bool ErrorMessage::has_carrightfdrivererror() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ErrorMessage::set_has_carrightfdrivererror() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ErrorMessage::clear_has_carrightfdrivererror() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ErrorMessage::clear_carrightfdrivererror() {
  carrightfdrivererror_ = false;
  clear_has_carrightfdrivererror();
}
inline bool ErrorMessage::carrightfdrivererror() const {
  return carrightfdrivererror_;
}
inline void ErrorMessage::set_carrightfdrivererror(bool value) {
  set_has_carrightfdrivererror();
  carrightfdrivererror_ = value;
}

// optional bool CarLeftBDriverError = 3;
inline bool ErrorMessage::has_carleftbdrivererror() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ErrorMessage::set_has_carleftbdrivererror() {
  _has_bits_[0] |= 0x00000004u;
}
inline void ErrorMessage::clear_has_carleftbdrivererror() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void ErrorMessage::clear_carleftbdrivererror() {
  carleftbdrivererror_ = false;
  clear_has_carleftbdrivererror();
}
inline bool ErrorMessage::carleftbdrivererror() const {
  return carleftbdrivererror_;
}
inline void ErrorMessage::set_carleftbdrivererror(bool value) {
  set_has_carleftbdrivererror();
  carleftbdrivererror_ = value;
}

// optional bool CarRightBDriverError = 4;
inline bool ErrorMessage::has_carrightbdrivererror() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void ErrorMessage::set_has_carrightbdrivererror() {
  _has_bits_[0] |= 0x00000008u;
}
inline void ErrorMessage::clear_has_carrightbdrivererror() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void ErrorMessage::clear_carrightbdrivererror() {
  carrightbdrivererror_ = false;
  clear_has_carrightbdrivererror();
}
inline bool ErrorMessage::carrightbdrivererror() const {
  return carrightbdrivererror_;
}
inline void ErrorMessage::set_carrightbdrivererror(bool value) {
  set_has_carrightbdrivererror();
  carrightbdrivererror_ = value;
}

// optional bool LeftFDriverComError = 5;
inline bool ErrorMessage::has_leftfdrivercomerror() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void ErrorMessage::set_has_leftfdrivercomerror() {
  _has_bits_[0] |= 0x00000010u;
}
inline void ErrorMessage::clear_has_leftfdrivercomerror() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void ErrorMessage::clear_leftfdrivercomerror() {
  leftfdrivercomerror_ = false;
  clear_has_leftfdrivercomerror();
}
inline bool ErrorMessage::leftfdrivercomerror() const {
  return leftfdrivercomerror_;
}
inline void ErrorMessage::set_leftfdrivercomerror(bool value) {
  set_has_leftfdrivercomerror();
  leftfdrivercomerror_ = value;
}

// optional bool RightFDriverComError = 6;
inline bool ErrorMessage::has_rightfdrivercomerror() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void ErrorMessage::set_has_rightfdrivercomerror() {
  _has_bits_[0] |= 0x00000020u;
}
inline void ErrorMessage::clear_has_rightfdrivercomerror() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void ErrorMessage::clear_rightfdrivercomerror() {
  rightfdrivercomerror_ = false;
  clear_has_rightfdrivercomerror();
}
inline bool ErrorMessage::rightfdrivercomerror() const {
  return rightfdrivercomerror_;
}
inline void ErrorMessage::set_rightfdrivercomerror(bool value) {
  set_has_rightfdrivercomerror();
  rightfdrivercomerror_ = value;
}

// optional bool LeftBDriverComError = 7;
inline bool ErrorMessage::has_leftbdrivercomerror() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void ErrorMessage::set_has_leftbdrivercomerror() {
  _has_bits_[0] |= 0x00000040u;
}
inline void ErrorMessage::clear_has_leftbdrivercomerror() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void ErrorMessage::clear_leftbdrivercomerror() {
  leftbdrivercomerror_ = false;
  clear_has_leftbdrivercomerror();
}
inline bool ErrorMessage::leftbdrivercomerror() const {
  return leftbdrivercomerror_;
}
inline void ErrorMessage::set_leftbdrivercomerror(bool value) {
  set_has_leftbdrivercomerror();
  leftbdrivercomerror_ = value;
}

// optional bool RightBDriverComError = 8;
inline bool ErrorMessage::has_rightbdrivercomerror() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void ErrorMessage::set_has_rightbdrivercomerror() {
  _has_bits_[0] |= 0x00000080u;
}
inline void ErrorMessage::clear_has_rightbdrivercomerror() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void ErrorMessage::clear_rightbdrivercomerror() {
  rightbdrivercomerror_ = false;
  clear_has_rightbdrivercomerror();
}
inline bool ErrorMessage::rightbdrivercomerror() const {
  return rightbdrivercomerror_;
}
inline void ErrorMessage::set_rightbdrivercomerror(bool value) {
  set_has_rightbdrivercomerror();
  rightbdrivercomerror_ = value;
}

// optional bool ExternComDevError = 9;
inline bool ErrorMessage::has_externcomdeverror() const {
  return (_has_bits_[0] & 0x00000100u) != 0;
}
inline void ErrorMessage::set_has_externcomdeverror() {
  _has_bits_[0] |= 0x00000100u;
}
inline void ErrorMessage::clear_has_externcomdeverror() {
  _has_bits_[0] &= ~0x00000100u;
}
inline void ErrorMessage::clear_externcomdeverror() {
  externcomdeverror_ = false;
  clear_has_externcomdeverror();
}
inline bool ErrorMessage::externcomdeverror() const {
  return externcomdeverror_;
}
inline void ErrorMessage::set_externcomdeverror(bool value) {
  set_has_externcomdeverror();
  externcomdeverror_ = value;
}

// optional bool BMSSysError = 10;
inline bool ErrorMessage::has_bmssyserror() const {
  return (_has_bits_[0] & 0x00000200u) != 0;
}
inline void ErrorMessage::set_has_bmssyserror() {
  _has_bits_[0] |= 0x00000200u;
}
inline void ErrorMessage::clear_has_bmssyserror() {
  _has_bits_[0] &= ~0x00000200u;
}
inline void ErrorMessage::clear_bmssyserror() {
  bmssyserror_ = false;
  clear_has_bmssyserror();
}
inline bool ErrorMessage::bmssyserror() const {
  return bmssyserror_;
}
inline void ErrorMessage::set_bmssyserror(bool value) {
  set_has_bmssyserror();
  bmssyserror_ = value;
}

// optional bool ObstacleStopError = 11;
inline bool ErrorMessage::has_obstaclestoperror() const {
  return (_has_bits_[0] & 0x00000400u) != 0;
}
inline void ErrorMessage::set_has_obstaclestoperror() {
  _has_bits_[0] |= 0x00000400u;
}
inline void ErrorMessage::clear_has_obstaclestoperror() {
  _has_bits_[0] &= ~0x00000400u;
}
inline void ErrorMessage::clear_obstaclestoperror() {
  obstaclestoperror_ = false;
  clear_has_obstaclestoperror();
}
inline bool ErrorMessage::obstaclestoperror() const {
  return obstaclestoperror_;
}
inline void ErrorMessage::set_obstaclestoperror(bool value) {
  set_has_obstaclestoperror();
  obstaclestoperror_ = value;
}

// optional bool CashSwitchStopError = 12;
inline bool ErrorMessage::has_cashswitchstoperror() const {
  return (_has_bits_[0] & 0x00000800u) != 0;
}
inline void ErrorMessage::set_has_cashswitchstoperror() {
  _has_bits_[0] |= 0x00000800u;
}
inline void ErrorMessage::clear_has_cashswitchstoperror() {
  _has_bits_[0] &= ~0x00000800u;
}
inline void ErrorMessage::clear_cashswitchstoperror() {
  cashswitchstoperror_ = false;
  clear_has_cashswitchstoperror();
}
inline bool ErrorMessage::cashswitchstoperror() const {
  return cashswitchstoperror_;
}
inline void ErrorMessage::set_cashswitchstoperror(bool value) {
  set_has_cashswitchstoperror();
  cashswitchstoperror_ = value;
}

// optional bool CurrentOverloadError = 13;
inline bool ErrorMessage::has_currentoverloaderror() const {
  return (_has_bits_[0] & 0x00001000u) != 0;
}
inline void ErrorMessage::set_has_currentoverloaderror() {
  _has_bits_[0] |= 0x00001000u;
}
inline void ErrorMessage::clear_has_currentoverloaderror() {
  _has_bits_[0] &= ~0x00001000u;
}
inline void ErrorMessage::clear_currentoverloaderror() {
  currentoverloaderror_ = false;
  clear_has_currentoverloaderror();
}
inline bool ErrorMessage::currentoverloaderror() const {
  return currentoverloaderror_;
}
inline void ErrorMessage::set_currentoverloaderror(bool value) {
  set_has_currentoverloaderror();
  currentoverloaderror_ = value;
}

// optional bool DriverLeftFNodeOFF = 14;
inline bool ErrorMessage::has_driverleftfnodeoff() const {
  return (_has_bits_[0] & 0x00002000u) != 0;
}
inline void ErrorMessage::set_has_driverleftfnodeoff() {
  _has_bits_[0] |= 0x00002000u;
}
inline void ErrorMessage::clear_has_driverleftfnodeoff() {
  _has_bits_[0] &= ~0x00002000u;
}
inline void ErrorMessage::clear_driverleftfnodeoff() {
  driverleftfnodeoff_ = false;
  clear_has_driverleftfnodeoff();
}
inline bool ErrorMessage::driverleftfnodeoff() const {
  return driverleftfnodeoff_;
}
inline void ErrorMessage::set_driverleftfnodeoff(bool value) {
  set_has_driverleftfnodeoff();
  driverleftfnodeoff_ = value;
}

// optional bool DriverLeftBNodeOFF = 15;
inline bool ErrorMessage::has_driverleftbnodeoff() const {
  return (_has_bits_[0] & 0x00004000u) != 0;
}
inline void ErrorMessage::set_has_driverleftbnodeoff() {
  _has_bits_[0] |= 0x00004000u;
}
inline void ErrorMessage::clear_has_driverleftbnodeoff() {
  _has_bits_[0] &= ~0x00004000u;
}
inline void ErrorMessage::clear_driverleftbnodeoff() {
  driverleftbnodeoff_ = false;
  clear_has_driverleftbnodeoff();
}
inline bool ErrorMessage::driverleftbnodeoff() const {
  return driverleftbnodeoff_;
}
inline void ErrorMessage::set_driverleftbnodeoff(bool value) {
  set_has_driverleftbnodeoff();
  driverleftbnodeoff_ = value;
}

// optional bool DriverRightFNodeOFF = 16;
inline bool ErrorMessage::has_driverrightfnodeoff() const {
  return (_has_bits_[0] & 0x00008000u) != 0;
}
inline void ErrorMessage::set_has_driverrightfnodeoff() {
  _has_bits_[0] |= 0x00008000u;
}
inline void ErrorMessage::clear_has_driverrightfnodeoff() {
  _has_bits_[0] &= ~0x00008000u;
}
inline void ErrorMessage::clear_driverrightfnodeoff() {
  driverrightfnodeoff_ = false;
  clear_has_driverrightfnodeoff();
}
inline bool ErrorMessage::driverrightfnodeoff() const {
  return driverrightfnodeoff_;
}
inline void ErrorMessage::set_driverrightfnodeoff(bool value) {
  set_has_driverrightfnodeoff();
  driverrightfnodeoff_ = value;
}

// optional bool DriverRightBNodeOFF = 17;
inline bool ErrorMessage::has_driverrightbnodeoff() const {
  return (_has_bits_[0] & 0x00010000u) != 0;
}
inline void ErrorMessage::set_has_driverrightbnodeoff() {
  _has_bits_[0] |= 0x00010000u;
}
inline void ErrorMessage::clear_has_driverrightbnodeoff() {
  _has_bits_[0] &= ~0x00010000u;
}
inline void ErrorMessage::clear_driverrightbnodeoff() {
  driverrightbnodeoff_ = false;
  clear_has_driverrightbnodeoff();
}
inline bool ErrorMessage::driverrightbnodeoff() const {
  return driverrightbnodeoff_;
}
inline void ErrorMessage::set_driverrightbnodeoff(bool value) {
  set_has_driverrightbnodeoff();
  driverrightbnodeoff_ = value;
}

// optional bool BObstacleStopError = 18;
inline bool ErrorMessage::has_bobstaclestoperror() const {
  return (_has_bits_[0] & 0x00020000u) != 0;
}
inline void ErrorMessage::set_has_bobstaclestoperror() {
  _has_bits_[0] |= 0x00020000u;
}
inline void ErrorMessage::clear_has_bobstaclestoperror() {
  _has_bits_[0] &= ~0x00020000u;
}
inline void ErrorMessage::clear_bobstaclestoperror() {
  bobstaclestoperror_ = false;
  clear_has_bobstaclestoperror();
}
inline bool ErrorMessage::bobstaclestoperror() const {
  return bobstaclestoperror_;
}
inline void ErrorMessage::set_bobstaclestoperror(bool value) {
  set_has_bobstaclestoperror();
  bobstaclestoperror_ = value;
}

// optional bool DropStopError = 19;
inline bool ErrorMessage::has_dropstoperror() const {
  return (_has_bits_[0] & 0x00040000u) != 0;
}
inline void ErrorMessage::set_has_dropstoperror() {
  _has_bits_[0] |= 0x00040000u;
}
inline void ErrorMessage::clear_has_dropstoperror() {
  _has_bits_[0] &= ~0x00040000u;
}
inline void ErrorMessage::clear_dropstoperror() {
  dropstoperror_ = false;
  clear_has_dropstoperror();
}
inline bool ErrorMessage::dropstoperror() const {
  return dropstoperror_;
}
inline void ErrorMessage::set_dropstoperror(bool value) {
  set_has_dropstoperror();
  dropstoperror_ = value;
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ErrorMessage_2eproto__INCLUDED
