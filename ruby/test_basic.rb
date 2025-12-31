#!/usr/bin/env ruby
#
#  Copyright (c) 2020-2025 Siddharth Chandrasekaran <sidcha.dev@gmail.com>
#
#  SPDX-License-Identifier: Apache-2.0
#

# Simple test to verify Ruby bindings are working

require 'osdp'

puts "Testing LibOSDP Ruby Bindings"
puts "=" * 50

# Test constants
puts "\nTesting Constants:"
puts "  LogLevel::DEBUG = #{OSDP::LogLevel::DEBUG}"
puts "  Command::LED = #{OSDP::Command::LED}"
puts "  Event::CARD_READ = #{OSDP::Event::CARD_READ}"
puts "  CommandLEDColor::RED = #{OSDP::CommandLEDColor::RED}"
puts "  Capability::LED_CONTROL = #{OSDP::Capability::LED_CONTROL}"

# Test key generation
puts "\nTesting KeyStore:"
key = OSDP::KeyStore.gen_key
puts "  Generated key length: #{key.length} bytes"
puts "  Key (hex): #{key.unpack1('H*')}"

# Test classes
puts "\nTesting Classes:"
puts "  ControlPanel class exists: #{defined?(OSDP::ControlPanel) ? 'yes' : 'no'}"
puts "  PeripheralDevice class exists: #{defined?(OSDP::PeripheralDevice) ? 'yes' : 'no'}"
puts "  Channel class exists: #{defined?(OSDP::Channel) ? 'yes' : 'no'}"
puts "  PDInfo class exists: #{defined?(OSDP::PDInfo) ? 'yes' : 'no'}"
puts "  PDCapabilities class exists: #{defined?(OSDP::PDCapabilities) ? 'yes' : 'no'}"

# Test PDInfo
puts "\nTesting PDInfo:"
channel = OSDP::SerialChannel.new('/dev/null', baud_rate: 9600)
pd_info = OSDP::PDInfo.new(101, channel, scbk: key)
puts "  Created PDInfo with address: #{pd_info.address}"

# Test PDCapabilities
puts "\nTesting PDCapabilities:"
pd_cap = OSDP::PDCapabilities.new
pd_cap.add_capability(OSDP::Capability::LED_CONTROL, 1, 1)
puts "  Created PDCapabilities with #{pd_cap.capabilities.size} capabilities"

puts "\n" + "=" * 50
puts "All tests passed!"
