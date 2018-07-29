// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: single_user_online.proto

#ifndef PROTOBUF_single_5fuser_5fonline_2eproto__INCLUDED
#define PROTOBUF_single_5fuser_5fonline_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3005001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace protobuf_single_5fuser_5fonline_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[2];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
void InitDefaultsLoginInfoImpl();
void InitDefaultsLoginInfo();
void InitDefaultsResultInfoImpl();
void InitDefaultsResultInfo();
inline void InitDefaults() {
  InitDefaultsLoginInfo();
  InitDefaultsResultInfo();
}
}  // namespace protobuf_single_5fuser_5fonline_2eproto
namespace singleuseronline {
class LoginInfo;
class LoginInfoDefaultTypeInternal;
extern LoginInfoDefaultTypeInternal _LoginInfo_default_instance_;
class ResultInfo;
class ResultInfoDefaultTypeInternal;
extern ResultInfoDefaultTypeInternal _ResultInfo_default_instance_;
}  // namespace singleuseronline
namespace singleuseronline {

// ===================================================================

class LoginInfo : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:singleuseronline.LoginInfo) */ {
 public:
  LoginInfo();
  virtual ~LoginInfo();

  LoginInfo(const LoginInfo& from);

  inline LoginInfo& operator=(const LoginInfo& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  LoginInfo(LoginInfo&& from) noexcept
    : LoginInfo() {
    *this = ::std::move(from);
  }

  inline LoginInfo& operator=(LoginInfo&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const LoginInfo& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const LoginInfo* internal_default_instance() {
    return reinterpret_cast<const LoginInfo*>(
               &_LoginInfo_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(LoginInfo* other);
  friend void swap(LoginInfo& a, LoginInfo& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline LoginInfo* New() const PROTOBUF_FINAL { return New(NULL); }

  LoginInfo* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const LoginInfo& from);
  void MergeFrom(const LoginInfo& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(LoginInfo* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string userid = 1;
  void clear_userid();
  static const int kUseridFieldNumber = 1;
  const ::std::string& userid() const;
  void set_userid(const ::std::string& value);
  #if LANG_CXX11
  void set_userid(::std::string&& value);
  #endif
  void set_userid(const char* value);
  void set_userid(const char* value, size_t size);
  ::std::string* mutable_userid();
  ::std::string* release_userid();
  void set_allocated_userid(::std::string* userid);

  // string passwordEncoded = 2;
  void clear_passwordencoded();
  static const int kPasswordEncodedFieldNumber = 2;
  const ::std::string& passwordencoded() const;
  void set_passwordencoded(const ::std::string& value);
  #if LANG_CXX11
  void set_passwordencoded(::std::string&& value);
  #endif
  void set_passwordencoded(const char* value);
  void set_passwordencoded(const char* value, size_t size);
  ::std::string* mutable_passwordencoded();
  ::std::string* release_passwordencoded();
  void set_allocated_passwordencoded(::std::string* passwordencoded);

  // string deviceid = 4;
  void clear_deviceid();
  static const int kDeviceidFieldNumber = 4;
  const ::std::string& deviceid() const;
  void set_deviceid(const ::std::string& value);
  #if LANG_CXX11
  void set_deviceid(::std::string&& value);
  #endif
  void set_deviceid(const char* value);
  void set_deviceid(const char* value, size_t size);
  ::std::string* mutable_deviceid();
  ::std::string* release_deviceid();
  void set_allocated_deviceid(::std::string* deviceid);

  // int64 timestamp = 3;
  void clear_timestamp();
  static const int kTimestampFieldNumber = 3;
  ::google::protobuf::int64 timestamp() const;
  void set_timestamp(::google::protobuf::int64 value);

  // int32 status = 5;
  void clear_status();
  static const int kStatusFieldNumber = 5;
  ::google::protobuf::int32 status() const;
  void set_status(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:singleuseronline.LoginInfo)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr userid_;
  ::google::protobuf::internal::ArenaStringPtr passwordencoded_;
  ::google::protobuf::internal::ArenaStringPtr deviceid_;
  ::google::protobuf::int64 timestamp_;
  ::google::protobuf::int32 status_;
  mutable int _cached_size_;
  friend struct ::protobuf_single_5fuser_5fonline_2eproto::TableStruct;
  friend void ::protobuf_single_5fuser_5fonline_2eproto::InitDefaultsLoginInfoImpl();
};
// -------------------------------------------------------------------

class ResultInfo : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:singleuseronline.ResultInfo) */ {
 public:
  ResultInfo();
  virtual ~ResultInfo();

  ResultInfo(const ResultInfo& from);

  inline ResultInfo& operator=(const ResultInfo& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  ResultInfo(ResultInfo&& from) noexcept
    : ResultInfo() {
    *this = ::std::move(from);
  }

  inline ResultInfo& operator=(ResultInfo&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const ResultInfo& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const ResultInfo* internal_default_instance() {
    return reinterpret_cast<const ResultInfo*>(
               &_ResultInfo_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    1;

  void Swap(ResultInfo* other);
  friend void swap(ResultInfo& a, ResultInfo& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline ResultInfo* New() const PROTOBUF_FINAL { return New(NULL); }

  ResultInfo* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const ResultInfo& from);
  void MergeFrom(const ResultInfo& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(ResultInfo* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string resultMsg = 2;
  void clear_resultmsg();
  static const int kResultMsgFieldNumber = 2;
  const ::std::string& resultmsg() const;
  void set_resultmsg(const ::std::string& value);
  #if LANG_CXX11
  void set_resultmsg(::std::string&& value);
  #endif
  void set_resultmsg(const char* value);
  void set_resultmsg(const char* value, size_t size);
  ::std::string* mutable_resultmsg();
  ::std::string* release_resultmsg();
  void set_allocated_resultmsg(::std::string* resultmsg);

  // int32 resultCode = 1;
  void clear_resultcode();
  static const int kResultCodeFieldNumber = 1;
  ::google::protobuf::int32 resultcode() const;
  void set_resultcode(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:singleuseronline.ResultInfo)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr resultmsg_;
  ::google::protobuf::int32 resultcode_;
  mutable int _cached_size_;
  friend struct ::protobuf_single_5fuser_5fonline_2eproto::TableStruct;
  friend void ::protobuf_single_5fuser_5fonline_2eproto::InitDefaultsResultInfoImpl();
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// LoginInfo

// string userid = 1;
inline void LoginInfo::clear_userid() {
  userid_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& LoginInfo::userid() const {
  // @@protoc_insertion_point(field_get:singleuseronline.LoginInfo.userid)
  return userid_.GetNoArena();
}
inline void LoginInfo::set_userid(const ::std::string& value) {
  
  userid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:singleuseronline.LoginInfo.userid)
}
#if LANG_CXX11
inline void LoginInfo::set_userid(::std::string&& value) {
  
  userid_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:singleuseronline.LoginInfo.userid)
}
#endif
inline void LoginInfo::set_userid(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  userid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:singleuseronline.LoginInfo.userid)
}
inline void LoginInfo::set_userid(const char* value, size_t size) {
  
  userid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:singleuseronline.LoginInfo.userid)
}
inline ::std::string* LoginInfo::mutable_userid() {
  
  // @@protoc_insertion_point(field_mutable:singleuseronline.LoginInfo.userid)
  return userid_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* LoginInfo::release_userid() {
  // @@protoc_insertion_point(field_release:singleuseronline.LoginInfo.userid)
  
  return userid_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void LoginInfo::set_allocated_userid(::std::string* userid) {
  if (userid != NULL) {
    
  } else {
    
  }
  userid_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), userid);
  // @@protoc_insertion_point(field_set_allocated:singleuseronline.LoginInfo.userid)
}

// string passwordEncoded = 2;
inline void LoginInfo::clear_passwordencoded() {
  passwordencoded_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& LoginInfo::passwordencoded() const {
  // @@protoc_insertion_point(field_get:singleuseronline.LoginInfo.passwordEncoded)
  return passwordencoded_.GetNoArena();
}
inline void LoginInfo::set_passwordencoded(const ::std::string& value) {
  
  passwordencoded_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:singleuseronline.LoginInfo.passwordEncoded)
}
#if LANG_CXX11
inline void LoginInfo::set_passwordencoded(::std::string&& value) {
  
  passwordencoded_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:singleuseronline.LoginInfo.passwordEncoded)
}
#endif
inline void LoginInfo::set_passwordencoded(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  passwordencoded_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:singleuseronline.LoginInfo.passwordEncoded)
}
inline void LoginInfo::set_passwordencoded(const char* value, size_t size) {
  
  passwordencoded_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:singleuseronline.LoginInfo.passwordEncoded)
}
inline ::std::string* LoginInfo::mutable_passwordencoded() {
  
  // @@protoc_insertion_point(field_mutable:singleuseronline.LoginInfo.passwordEncoded)
  return passwordencoded_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* LoginInfo::release_passwordencoded() {
  // @@protoc_insertion_point(field_release:singleuseronline.LoginInfo.passwordEncoded)
  
  return passwordencoded_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void LoginInfo::set_allocated_passwordencoded(::std::string* passwordencoded) {
  if (passwordencoded != NULL) {
    
  } else {
    
  }
  passwordencoded_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), passwordencoded);
  // @@protoc_insertion_point(field_set_allocated:singleuseronline.LoginInfo.passwordEncoded)
}

// int64 timestamp = 3;
inline void LoginInfo::clear_timestamp() {
  timestamp_ = GOOGLE_LONGLONG(0);
}
inline ::google::protobuf::int64 LoginInfo::timestamp() const {
  // @@protoc_insertion_point(field_get:singleuseronline.LoginInfo.timestamp)
  return timestamp_;
}
inline void LoginInfo::set_timestamp(::google::protobuf::int64 value) {
  
  timestamp_ = value;
  // @@protoc_insertion_point(field_set:singleuseronline.LoginInfo.timestamp)
}

// string deviceid = 4;
inline void LoginInfo::clear_deviceid() {
  deviceid_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& LoginInfo::deviceid() const {
  // @@protoc_insertion_point(field_get:singleuseronline.LoginInfo.deviceid)
  return deviceid_.GetNoArena();
}
inline void LoginInfo::set_deviceid(const ::std::string& value) {
  
  deviceid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:singleuseronline.LoginInfo.deviceid)
}
#if LANG_CXX11
inline void LoginInfo::set_deviceid(::std::string&& value) {
  
  deviceid_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:singleuseronline.LoginInfo.deviceid)
}
#endif
inline void LoginInfo::set_deviceid(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  deviceid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:singleuseronline.LoginInfo.deviceid)
}
inline void LoginInfo::set_deviceid(const char* value, size_t size) {
  
  deviceid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:singleuseronline.LoginInfo.deviceid)
}
inline ::std::string* LoginInfo::mutable_deviceid() {
  
  // @@protoc_insertion_point(field_mutable:singleuseronline.LoginInfo.deviceid)
  return deviceid_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* LoginInfo::release_deviceid() {
  // @@protoc_insertion_point(field_release:singleuseronline.LoginInfo.deviceid)
  
  return deviceid_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void LoginInfo::set_allocated_deviceid(::std::string* deviceid) {
  if (deviceid != NULL) {
    
  } else {
    
  }
  deviceid_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), deviceid);
  // @@protoc_insertion_point(field_set_allocated:singleuseronline.LoginInfo.deviceid)
}

// int32 status = 5;
inline void LoginInfo::clear_status() {
  status_ = 0;
}
inline ::google::protobuf::int32 LoginInfo::status() const {
  // @@protoc_insertion_point(field_get:singleuseronline.LoginInfo.status)
  return status_;
}
inline void LoginInfo::set_status(::google::protobuf::int32 value) {
  
  status_ = value;
  // @@protoc_insertion_point(field_set:singleuseronline.LoginInfo.status)
}

// -------------------------------------------------------------------

// ResultInfo

// int32 resultCode = 1;
inline void ResultInfo::clear_resultcode() {
  resultcode_ = 0;
}
inline ::google::protobuf::int32 ResultInfo::resultcode() const {
  // @@protoc_insertion_point(field_get:singleuseronline.ResultInfo.resultCode)
  return resultcode_;
}
inline void ResultInfo::set_resultcode(::google::protobuf::int32 value) {
  
  resultcode_ = value;
  // @@protoc_insertion_point(field_set:singleuseronline.ResultInfo.resultCode)
}

// string resultMsg = 2;
inline void ResultInfo::clear_resultmsg() {
  resultmsg_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& ResultInfo::resultmsg() const {
  // @@protoc_insertion_point(field_get:singleuseronline.ResultInfo.resultMsg)
  return resultmsg_.GetNoArena();
}
inline void ResultInfo::set_resultmsg(const ::std::string& value) {
  
  resultmsg_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:singleuseronline.ResultInfo.resultMsg)
}
#if LANG_CXX11
inline void ResultInfo::set_resultmsg(::std::string&& value) {
  
  resultmsg_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:singleuseronline.ResultInfo.resultMsg)
}
#endif
inline void ResultInfo::set_resultmsg(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  resultmsg_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:singleuseronline.ResultInfo.resultMsg)
}
inline void ResultInfo::set_resultmsg(const char* value, size_t size) {
  
  resultmsg_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:singleuseronline.ResultInfo.resultMsg)
}
inline ::std::string* ResultInfo::mutable_resultmsg() {
  
  // @@protoc_insertion_point(field_mutable:singleuseronline.ResultInfo.resultMsg)
  return resultmsg_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* ResultInfo::release_resultmsg() {
  // @@protoc_insertion_point(field_release:singleuseronline.ResultInfo.resultMsg)
  
  return resultmsg_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ResultInfo::set_allocated_resultmsg(::std::string* resultmsg) {
  if (resultmsg != NULL) {
    
  } else {
    
  }
  resultmsg_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), resultmsg);
  // @@protoc_insertion_point(field_set_allocated:singleuseronline.ResultInfo.resultMsg)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace singleuseronline

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_single_5fuser_5fonline_2eproto__INCLUDED
