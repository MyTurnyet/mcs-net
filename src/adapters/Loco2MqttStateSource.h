#pragma once

#include <array>
#include <deque>

#include "domain/Loco2MqttPayloadCodec.h"
#include "domain/Loco2MqttStateUpdate.h"
#include "ports/MqttTransport.h"

// Listens for Loco2MQTT's published turnout states. Channel numbers are
// 1-based array positions; a turnout address of 0 means "unconfigured".
// Every message is delivered, including the periodic re-publishes of an
// unchanged state - consumers decide whether a repeat needs any action.
template <int N>
class BasicLoco2MqttStateSource
{
public:
    BasicLoco2MqttStateSource(MqttTransport& transport, const std::array<int, N>& channelTurnoutAddresses);
    BasicLoco2MqttStateSource(const BasicLoco2MqttStateSource&) = delete;
    BasicLoco2MqttStateSource& operator=(const BasicLoco2MqttStateSource&) = delete;

    bool poll(Loco2MqttStateUpdate& outUpdate);

private:
    void subscribeChannel(MqttTransport& transport, int channel, int turnoutAddress);
    void accept(int channel, const std::string& payload);

    Loco2MqttPayloadCodec codec_;
    std::deque<Loco2MqttStateUpdate> pending_;
};

using Loco2MqttStateSource12 = BasicLoco2MqttStateSource<12>;
using Loco2MqttStateSource8 = BasicLoco2MqttStateSource<8>;
using Loco2MqttStateSource4 = BasicLoco2MqttStateSource<4>;
