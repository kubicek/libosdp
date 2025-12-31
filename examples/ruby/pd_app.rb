#!/usr/bin/env ruby
#
#  Copyright (c) 2020-2025 Siddharth Chandrasekaran <sidcha.dev@gmail.com>
#
#  SPDX-License-Identifier: Apache-2.0
#

require 'optparse'
require 'osdp'

# Example serial channel implementation
class SerialChannel < OSDP::Channel
  def initialize(device, speed)
    @device = device
    @speed = speed
    # In a real implementation, you would open the serial port here
    # For example, using the 'serialport' gem:
    # require 'serialport'
    # @port = SerialPort.new(device, speed)
  end

  def send(data)
    # Send data over serial port
    # @port.write(data)
    data.length
  end

  def recv(max_len)
    # Receive data from serial port
    # data = @port.read(max_len)
    # return data if data && !data.empty?
    nil
  end

  def flush
    # Flush the serial port
    # @port.flush
  end
end

options = {
  baudrate: 115200,
  log_level: OSDP::LogLevel::INFO
}

OptionParser.new do |opts|
  opts.banner = "Usage: pd_app.rb DEVICE [options]"

  opts.on("-b", "--baudrate RATE", Integer, "Serial port baud rate (default: 115200)") do |b|
    options[:baudrate] = b
  end

  opts.on("-l", "--log-level LEVEL", Integer, "LibOSDP log level 0-7 (default: 6)") do |l|
    options[:log_level] = l
  end

  opts.on("-h", "--help", "Prints this help") do
    puts opts
    exit
  end
end.parse!

if ARGV.empty?
  puts "Error: DEVICE path required"
  puts "Usage: pd_app.rb DEVICE [options]"
  exit 1
end

device = ARGV[0]

# Describe the PD (setting scbk=nil puts the PD in install mode)
channel = SerialChannel.new(device, options[:baudrate])
pd_info = OSDP::PDInfo.new(101, channel, scbk: nil)

# Indicate the PD's capabilities to LibOSDP
pd_cap = OSDP::PDCapabilities.new
pd_cap.add_capability(OSDP::Capability::OUTPUT_CONTROL, 1, 1)
pd_cap.add_capability(OSDP::Capability::LED_CONTROL, 1, 1)
pd_cap.add_capability(OSDP::Capability::AUDIBLE_CONTROL, 1, 1)
pd_cap.add_capability(OSDP::Capability::COMMUNICATION_SECURITY, 1, 1)

# Create a PD device and kick-off the handler thread
pd = OSDP::PeripheralDevice.new(pd_info, pd_cap, log_level: options[:log_level])
pd.start
pd.sc_wait

# Create a card read event to be used later
card_event = {
  event: OSDP::Event::CARD_READ,
  reader_no: 1,
  format: OSDP::CardFormat::WIEGAND,
  direction: 1,
  length: 32,
  data: "\x55\xaa\x55\xaa"
}

count = 0
while count < 5
  # Send a card read event to CP
  pd.notify_event(card_event)

  # Check if we have any commands from the CP
  cmd = pd.get_command
  puts "PD: Received command: #{cmd}" if cmd

  count += 1
  sleep(2)
end

pd.stop
