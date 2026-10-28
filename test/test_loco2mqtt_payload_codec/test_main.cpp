#include <catch2/catch_test_macros.hpp>

#include "domain/Loco2MqttPayloadCodec.h"

TEST_CASE("encode writes CLOSED for the closed position")
{
    REQUIRE(Loco2MqttPayloadCodec().encode(Loco2MqttPosition::Closed) == "CLOSED");
}

TEST_CASE("encode writes THROWN for the thrown position")
{
    REQUIRE(Loco2MqttPayloadCodec().encode(Loco2MqttPosition::Thrown) == "THROWN");
}

TEST_CASE("decode reads CLOSED")
{
    const auto position = Loco2MqttPayloadCodec().decode("CLOSED");

    REQUIRE(position.has_value());
    REQUIRE(*position == Loco2MqttPosition::Closed);
}

TEST_CASE("decode reads THROWN")
{
    const auto position = Loco2MqttPayloadCodec().decode("THROWN");

    REQUIRE(position.has_value());
    REQUIRE(*position == Loco2MqttPosition::Thrown);
}

TEST_CASE("decode rejects anything else, including a different case")
{
    REQUIRE_FALSE(Loco2MqttPayloadCodec().decode("GARBAGE").has_value());
    REQUIRE_FALSE(Loco2MqttPayloadCodec().decode("closed").has_value());
    REQUIRE_FALSE(Loco2MqttPayloadCodec().decode("").has_value());
}
