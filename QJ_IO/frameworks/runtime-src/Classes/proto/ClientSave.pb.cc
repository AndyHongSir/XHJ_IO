// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ClientSave.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "ClientSave.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
// @@protoc_insertion_point(includes)

namespace jynetwork {
namespace proto {

void protobuf_ShutdownFile_ClientSave_2eproto() {
  delete CSAuthSave::default_instance_;
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
void protobuf_AddDesc_ClientSave_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#else
void protobuf_AddDesc_ClientSave_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#endif
  CSAuthSave::default_instance_ = new CSAuthSave();
  CSAuthSave::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_ClientSave_2eproto);
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_ClientSave_2eproto_once_);
void protobuf_AddDesc_ClientSave_2eproto() {
  ::google::protobuf::::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_ClientSave_2eproto_once_,
                 &protobuf_AddDesc_ClientSave_2eproto_impl);
}
#else
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_ClientSave_2eproto {
  StaticDescriptorInitializer_ClientSave_2eproto() {
    protobuf_AddDesc_ClientSave_2eproto();
  }
} static_descriptor_initializer_ClientSave_2eproto_;
#endif

// ===================================================================

#ifndef _MSC_VER
const int CSAuthSave::kServerIdFieldNumber;
const int CSAuthSave::kUdidFieldNumber;
#endif  // !_MSC_VER

CSAuthSave::CSAuthSave()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void CSAuthSave::InitAsDefaultInstance() {
}

CSAuthSave::CSAuthSave(const CSAuthSave& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void CSAuthSave::SharedCtor() {
  _cached_size_ = 0;
  server_id_ = 0u;
  udid_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

CSAuthSave::~CSAuthSave() {
  SharedDtor();
}

void CSAuthSave::SharedDtor() {
  if (udid_ != &::google::protobuf::internal::kEmptyString) {
    delete udid_;
  }
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
  }
}

void CSAuthSave::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const CSAuthSave& CSAuthSave::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_ClientSave_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_ClientSave_2eproto();
#endif
  return *default_instance_;
}

CSAuthSave* CSAuthSave::default_instance_ = NULL;

CSAuthSave* CSAuthSave::New() const {
  return new CSAuthSave;
}

void CSAuthSave::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    server_id_ = 0u;
    if (has_udid()) {
      if (udid_ != &::google::protobuf::internal::kEmptyString) {
        udid_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool CSAuthSave::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint32 server_id = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &server_id_)));
          set_has_server_id();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_udid;
        break;
      }

      // optional string udid = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_udid:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_udid()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void CSAuthSave::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional uint32 server_id = 1;
  if (has_server_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->server_id(), output);
  }

  // optional string udid = 2;
  if (has_udid()) {
    ::google::protobuf::internal::WireFormatLite::WriteString(
      2, this->udid(), output);
  }

}

int CSAuthSave::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional uint32 server_id = 1;
    if (has_server_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->server_id());
    }

    // optional string udid = 2;
    if (has_udid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->udid());
    }

  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void CSAuthSave::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const CSAuthSave*>(&from));
}

void CSAuthSave::MergeFrom(const CSAuthSave& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_server_id()) {
      set_server_id(from.server_id());
    }
    if (from.has_udid()) {
      set_udid(from.udid());
    }
  }
}

void CSAuthSave::CopyFrom(const CSAuthSave& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool CSAuthSave::IsInitialized() const {

  return true;
}

void CSAuthSave::Swap(CSAuthSave* other) {
  if (other != this) {
    std::swap(server_id_, other->server_id_);
    std::swap(udid_, other->udid_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string CSAuthSave::GetTypeName() const {
  return "jynetwork.proto.CSAuthSave";
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace proto
}  // namespace jynetwork

// @@protoc_insertion_point(global_scope)
