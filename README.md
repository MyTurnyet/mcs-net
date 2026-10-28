# mcs-net

Network code shared by ESP32 MaltBee Control System projects. Depends on [`mcs-core`](https://github.com/MyTurnyet/mcs-core) (`Clock`). The Mega 2560 does not use this library, so STL types are allowed here.

## Contents (v0.1.0, Stage 1)

| Path | What it is |
| --- | --- |
| `ports/MqttTransport.h`, `ports/MdnsResolver.h` | Ports (pure interfaces) |
| `application/BrokerAddressResolver.{h,cpp}` | mDNS lookup throttled to one blocking query per interval, with fallback host |
| `adapters/MqttLink`, `WiFiLink`, `EspMdnsResolver` | ESP32 adapters, compiled only when `ARDUINO` is defined |
| `testing/FakeClock.h`, `FakeMqttTransport.h`, `FakeMdnsResolver.h` | Hand-written fakes for consumers' native tests |

## Using it

1. Add `https://github.com/MyTurnyet/mcs-net.git#v0.1.0` to `lib_deps` of each ESP32 and native environment.
2. Add `knolleary/PubSubClient@^2.8` to `lib_deps` of each ESP32 environment. It is deliberately not a declared dependency of this library, because it would break native builds.
3. Include headers by their library-rooted path, for example `#include "ports/MqttTransport.h"`.

## Running this library's own tests

Run `pio test -e native` from the repository root.

## Planned

- Stage 2: the Loco2MQTT turnout contract (`Loco2MqttFeedbackSource`).
- Stage 3: presence and identity.
