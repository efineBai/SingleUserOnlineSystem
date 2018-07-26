// GENERATED CODE -- DO NOT EDIT!

'use strict';
var grpc = require('grpc');
var single_user_online_pb = require('./single_user_online_pb.js');

function serialize_singleuseronline_LoginInfo(arg) {
  if (!(arg instanceof single_user_online_pb.LoginInfo)) {
    throw new Error('Expected argument of type singleuseronline.LoginInfo');
  }
  return new Buffer(arg.serializeBinary());
}

function deserialize_singleuseronline_LoginInfo(buffer_arg) {
  return single_user_online_pb.LoginInfo.deserializeBinary(new Uint8Array(buffer_arg));
}

function serialize_singleuseronline_ResultInfo(arg) {
  if (!(arg instanceof single_user_online_pb.ResultInfo)) {
    throw new Error('Expected argument of type singleuseronline.ResultInfo');
  }
  return new Buffer(arg.serializeBinary());
}

function deserialize_singleuseronline_ResultInfo(buffer_arg) {
  return single_user_online_pb.ResultInfo.deserializeBinary(new Uint8Array(buffer_arg));
}


var SingleUserOnlineService = exports.SingleUserOnlineService = {
  // sign up a new account
  signUp: {
    path: '/singleuseronline.SingleUserOnline/signUp',
    requestStream: false,
    responseStream: false,
    requestType: single_user_online_pb.LoginInfo,
    responseType: single_user_online_pb.ResultInfo,
    requestSerialize: serialize_singleuseronline_LoginInfo,
    requestDeserialize: deserialize_singleuseronline_LoginInfo,
    responseSerialize: serialize_singleuseronline_ResultInfo,
    responseDeserialize: deserialize_singleuseronline_ResultInfo,
  },
  // live-statue, stream to stream； use status to logout or login
  keepAliveStream: {
    path: '/singleuseronline.SingleUserOnline/keepAliveStream',
    requestStream: true,
    responseStream: true,
    requestType: single_user_online_pb.LoginInfo,
    responseType: single_user_online_pb.LoginInfo,
    requestSerialize: serialize_singleuseronline_LoginInfo,
    requestDeserialize: deserialize_singleuseronline_LoginInfo,
    responseSerialize: serialize_singleuseronline_LoginInfo,
    responseDeserialize: deserialize_singleuseronline_LoginInfo,
  },
  // live-statue, short connection
  keepAliveShort: {
    path: '/singleuseronline.SingleUserOnline/keepAliveShort',
    requestStream: false,
    responseStream: false,
    requestType: single_user_online_pb.LoginInfo,
    responseType: single_user_online_pb.ResultInfo,
    requestSerialize: serialize_singleuseronline_LoginInfo,
    requestDeserialize: deserialize_singleuseronline_LoginInfo,
    responseSerialize: serialize_singleuseronline_ResultInfo,
    responseDeserialize: deserialize_singleuseronline_ResultInfo,
  },
};

exports.SingleUserOnlineClient = grpc.makeGenericClientConstructor(SingleUserOnlineService);
