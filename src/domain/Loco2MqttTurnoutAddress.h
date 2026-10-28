#pragma once

#include <string>

class Loco2MqttTurnoutAddress
{
public:
    explicit Loco2MqttTurnoutAddress(const int address) : address_(address)
    {
    }

    [[nodiscard]] std::string stateTopic() const
    {
        return topicWithSuffix("/state");
    }

    [[nodiscard]] std::string commandTopic() const
    {
        return topicWithSuffix("/set");
    }

private:
    [[nodiscard]] std::string topicWithSuffix(const std::string& suffix) const
    {
        return "loconet/turnout/" + std::to_string(address_) + suffix;
    }

    int address_;
};
