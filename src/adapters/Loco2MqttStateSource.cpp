#include "adapters/Loco2MqttStateSource.h"

#include "domain/Loco2MqttTurnoutAddress.h"

template <int N>
BasicLoco2MqttStateSource<N>::BasicLoco2MqttStateSource(
    MqttTransport& transport, const std::array<int, N>& channelTurnoutAddresses)
{
    for (int i = 0; i < N; ++i)
    {
        subscribeChannel(transport, i + 1, channelTurnoutAddresses[i]);
    }
}

template <int N>
void BasicLoco2MqttStateSource<N>::subscribeChannel(MqttTransport& transport, const int channel, const int turnoutAddress)
{
    if (turnoutAddress == 0)
    {
        return;
    }
    transport.subscribe(Loco2MqttTurnoutAddress(turnoutAddress).stateTopic(),
                        [this, channel](const std::string& payload) { accept(channel, payload); });
}

template <int N>
void BasicLoco2MqttStateSource<N>::accept(const int channel, const std::string& payload)
{
    const auto position = codec_.decode(payload);
    if (position.has_value())
    {
        pending_.push_back(Loco2MqttStateUpdate{channel, *position});
    }
}

template <int N>
bool BasicLoco2MqttStateSource<N>::poll(Loco2MqttStateUpdate& outUpdate)
{
    if (pending_.empty())
    {
        return false;
    }
    outUpdate = pending_.front();
    pending_.pop_front();
    return true;
}

template class BasicLoco2MqttStateSource<12>;
template class BasicLoco2MqttStateSource<8>;
template class BasicLoco2MqttStateSource<4>;
