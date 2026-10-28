#include <catch2/catch_test_macros.hpp>

#include "adapters/Loco2MqttStateSource.h"
#include "testing/FakeMqttTransport.h"

namespace
{
    constexpr int kN = 12;

    std::array<int, kN> addressesWithChannel(const int channel, const int address)
    {
        std::array<int, kN> addresses{};
        addresses[channel - 1] = address;
        return addresses;
    }
}

TEST_CASE("construction subscribes only the configured channels' state topics (N=12)")
{
    FakeMqttTransport transport;
    const auto addresses = addressesWithChannel(1, 5);

    BasicLoco2MqttStateSource<kN> source(transport, addresses);

    REQUIRE(transport.subscribedTopics.size() == 1);
    REQUIRE(transport.subscribedTopics[0] == "loconet/turnout/5/state");
}

TEST_CASE("construction subscribes each configured channel's state topic among several (N=12)")
{
    FakeMqttTransport transport;
    auto addresses = addressesWithChannel(1, 5);
    addresses[kN - 1] = 17;

    BasicLoco2MqttStateSource<kN> source(transport, addresses);

    REQUIRE(transport.subscribedTopics.size() == 2);
}

TEST_CASE("a valid incoming payload becomes a pollable update for its channel (N=12)")
{
    FakeMqttTransport transport;
    const auto addresses = addressesWithChannel(kN, 9);
    BasicLoco2MqttStateSource<kN> source(transport, addresses);

    transport.deliver("loconet/turnout/9/state", "THROWN");

    Loco2MqttStateUpdate update{};
    REQUIRE(source.poll(update));
    REQUIRE(update.channel == kN);
    REQUIRE(update.position == Loco2MqttPosition::Thrown);
}

TEST_CASE("an unrecognized payload produces nothing (N=12)")
{
    FakeMqttTransport transport;
    const auto addresses = addressesWithChannel(1, 5);
    BasicLoco2MqttStateSource<kN> source(transport, addresses);

    transport.deliver("loconet/turnout/5/state", "GARBAGE");

    Loco2MqttStateUpdate update{};
    REQUIRE_FALSE(source.poll(update));
}

TEST_CASE("a message on the command topic is not picked up (N=12)")
{
    FakeMqttTransport transport;
    const auto addresses = addressesWithChannel(1, 5);
    BasicLoco2MqttStateSource<kN> source(transport, addresses);

    transport.deliver("loconet/turnout/5/set", "THROWN");

    Loco2MqttStateUpdate update{};
    REQUIRE_FALSE(source.poll(update));
}

TEST_CASE("poll returns false once the queue is drained (N=12)")
{
    FakeMqttTransport transport;
    const auto addresses = addressesWithChannel(1, 5);
    BasicLoco2MqttStateSource<kN> source(transport, addresses);
    transport.deliver("loconet/turnout/5/state", "CLOSED");

    Loco2MqttStateUpdate update{};
    REQUIRE(source.poll(update));
    REQUIRE_FALSE(source.poll(update));
}

TEST_CASE("queued updates drain in FIFO order (N=12)")
{
    FakeMqttTransport transport;
    const auto addresses = addressesWithChannel(1, 5);
    BasicLoco2MqttStateSource<kN> source(transport, addresses);
    transport.deliver("loconet/turnout/5/state", "CLOSED");
    transport.deliver("loconet/turnout/5/state", "THROWN");

    Loco2MqttStateUpdate first{};
    Loco2MqttStateUpdate second{};
    REQUIRE(source.poll(first));
    REQUIRE(source.poll(second));
    REQUIRE(first.position == Loco2MqttPosition::Closed);
    REQUIRE(second.position == Loco2MqttPosition::Thrown);
}

TEST_CASE("a repeated, unchanged state is delivered every time (N=12)")
{
    FakeMqttTransport transport;
    const auto addresses = addressesWithChannel(1, 5);
    BasicLoco2MqttStateSource<kN> source(transport, addresses);
    transport.deliver("loconet/turnout/5/state", "THROWN");
    transport.deliver("loconet/turnout/5/state", "THROWN");

    Loco2MqttStateUpdate update{};
    REQUIRE(source.poll(update));
    REQUIRE(source.poll(update));
    REQUIRE_FALSE(source.poll(update));
}

TEST_CASE("an unconfigured channel (address 0) subscribes nothing (N=12)")
{
    FakeMqttTransport transport;
    const std::array<int, kN> addresses{};

    BasicLoco2MqttStateSource<kN> source(transport, addresses);

    REQUIRE(transport.subscribedTopics.empty());
}
