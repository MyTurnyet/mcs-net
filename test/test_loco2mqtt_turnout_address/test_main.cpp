#include <catch2/catch_test_macros.hpp>

#include "domain/Loco2MqttTurnoutAddress.h"

TEST_CASE("state topic is where Loco2MQTT publishes the turnout's state")
{
    REQUIRE(Loco2MqttTurnoutAddress(5).stateTopic() == "loconet/turnout/5/state");
}

TEST_CASE("command topic is where Loco2MQTT listens for the turnout's commands")
{
    REQUIRE(Loco2MqttTurnoutAddress(5).commandTopic() == "loconet/turnout/5/set");
}

TEST_CASE("the highest LocoNet address forms a topic")
{
    REQUIRE(Loco2MqttTurnoutAddress(2048).stateTopic() == "loconet/turnout/2048/state");
}

TEST_CASE("state and command topics differ for the same address")
{
    const Loco2MqttTurnoutAddress address(17);

    REQUIRE(address.stateTopic() != address.commandTopic());
}
