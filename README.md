# mcs-net

Network code shared by ESP32 MaltBee Control System projects. This is the Stage 0 skeleton: it declares its dependency on `mcs-core` and contains no code yet.

Planned contents, one stage at a time:
- Stage 1: `MqttTransport` and `MdnsResolver` ports, `MqttLink`, `WiFiLink`, `EspMdnsResolver`, `BrokerAddressResolver`, and exported test fakes.
- Stage 2: the Loco2MQTT turnout contract (`TopicScheme`, `PayloadCodec`, `Loco2MqttFeedbackSource`).
- Stage 3: presence and identity.

The Mega 2560 does not use this library, so STL types are allowed here.
