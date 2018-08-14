<?php
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: src/proto/grpc/testing/messages.proto

namespace Grpc\Testing;

use Google\Protobuf\Internal\GPBType;
use Google\Protobuf\Internal\RepeatedField;
use Google\Protobuf\Internal\GPBUtil;

/**
 * Client-streaming request.
 *
 * Generated from protobuf message <code>grpc.testing.StreamingInputCallRequest</code>
 */
class StreamingInputCallRequest extends \Google\Protobuf\Internal\Message
{
    /**
     * Optional input payload sent along with the request.
     *
     * Generated from protobuf field <code>.grpc.testing.Payload payload = 1;</code>
     */
    private $payload = null;
    /**
     * Whether the server should expect this request to be compressed. This field
     * is "nullable" in order to interoperate seamlessly with servers not able to
     * implement the full compression tests by introspecting the call to verify
     * the request's compression status.
     *
     * Generated from protobuf field <code>.grpc.testing.BoolValue expect_compressed = 2;</code>
     */
    private $expect_compressed = null;

    public function __construct() {
        \GPBMetadata\Src\Proto\Grpc\Testing\Messages::initOnce();
        parent::__construct();
    }

    /**
     * Optional input payload sent along with the request.
     *
     * Generated from protobuf field <code>.grpc.testing.Payload payload = 1;</code>
     * @return \Grpc\Testing\Payload
     */
    public function getPayload()
    {
        return $this->payload;
    }

    /**
     * Optional input payload sent along with the request.
     *
     * Generated from protobuf field <code>.grpc.testing.Payload payload = 1;</code>
     * @param \Grpc\Testing\Payload $var
     * @return $this
     */
    public function setPayload($var)
    {
        GPBUtil::checkMessage($var, \Grpc\Testing\Payload::class);
        $this->payload = $var;

        return $this;
    }

    /**
     * Whether the server should expect this request to be compressed. This field
     * is "nullable" in order to interoperate seamlessly with servers not able to
     * implement the full compression tests by introspecting the call to verify
     * the request's compression status.
     *
     * Generated from protobuf field <code>.grpc.testing.BoolValue expect_compressed = 2;</code>
     * @return \Grpc\Testing\BoolValue
     */
    public function getExpectCompressed()
    {
        return $this->expect_compressed;
    }

    /**
     * Whether the server should expect this request to be compressed. This field
     * is "nullable" in order to interoperate seamlessly with servers not able to
     * implement the full compression tests by introspecting the call to verify
     * the request's compression status.
     *
     * Generated from protobuf field <code>.grpc.testing.BoolValue expect_compressed = 2;</code>
     * @param \Grpc\Testing\BoolValue $var
     * @return $this
     */
    public function setExpectCompressed($var)
    {
        GPBUtil::checkMessage($var, \Grpc\Testing\BoolValue::class);
        $this->expect_compressed = $var;

        return $this;
    }

}

