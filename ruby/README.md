# LibOSDP for Ruby

This gem exposes the C library for OSDP devices to Ruby to enable rapid
prototyping of these devices. There are two modules exposed by this package:

- `OSDP::Sys`: A thin wrapper around the C API; this is a low level API.

- `OSDP`: A wrapper over the `OSDP::Sys` to provide Ruby-friendly API.

## Install

You can install LibOSDP from RubyGems using:

```sh
gem install libosdp
```

Or, from source:

```sh
git clone https://github.com/goToMain/libosdp --recurse-submodules
cd libosdp/ruby
gem build libosdp.gemspec
gem install libosdp-3.1.0.gem
```

## Quick Start

### Control Panel Mode

```ruby
require 'osdp'

# Create a communication channel
channel = OSDP::SerialChannel.new('/dev/ttyUSB0')

# Populate PD info
pd_info = [
  OSDP::PDInfo.new(101, channel, scbk: OSDP::KeyStore.gen_key)
]

# Create a CP device and start it
cp = OSDP::ControlPanel.new(pd_info, log_level: OSDP::LogLevel::DEBUG)
cp.start
cp.sc_wait_all

loop do
  # Check if we have an event from PD
  event = cp.get_event(pd_info[0].address)
  puts "CP: Received event #{event}" if event

  # Send LED command to PD-0
  led_cmd = {
    command: OSDP::Command::LED,
    # ... command details
  }
  cp.send_command(pd_info[0].address, led_cmd)
  
  sleep(1)
end
```

See [examples/ruby/cp_app.rb](../examples/ruby/cp_app.rb) for more details.

### Peripheral Device Mode

```ruby
require 'osdp'

# Create a communication channel
channel = OSDP::SerialChannel.new('/dev/ttyUSB0')

# Describe the PD (setting scbk=nil puts the PD in install mode)
pd_info = OSDP::PDInfo.new(101, channel, scbk: nil)

# Indicate the PD's capabilities to LibOSDP
pd_cap = OSDP::PDCapabilities.new

# Create a PD device and start it
pd = OSDP::PeripheralDevice.new(pd_info, pd_cap, log_level: OSDP::LogLevel::DEBUG)
pd.start
pd.sc_wait

loop do
  # Send a card read event to CP
  card_event = {
    event: OSDP::Event::CARD_READ,
    # ... event details
  }
  pd.notify_event(card_event)

  # Check if we have any commands from the CP
  cmd = pd.get_command
  puts "PD: Received command: #{cmd}" if cmd
  
  sleep(1)
end
```

See [examples/ruby/pd_app.rb](../examples/ruby/pd_app.rb) for more details.

## Documentation

For more information about OSDP and LibOSDP:
- [LibOSDP Documentation](https://libosdp.sidcha.dev/)
- [API Documentation](https://libosdp.sidcha.dev/api/)
- [OSDP Protocol](https://libosdp.sidcha.dev/protocol/)

## License

This software is distributed under the terms of Apache-2.0 license.
