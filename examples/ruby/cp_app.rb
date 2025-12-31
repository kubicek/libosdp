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
  opts.banner = "Usage: cp_app.rb DEVICE [options]"

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
  puts "Usage: cp_app.rb DEVICE [options]"
  exit 1
end

device = ARGV[0]

# Describe the PD (setting scbk=nil puts the PD in install mode)
channel = SerialChannel.new(device, options[:baudrate])
pd_info = [
  OSDP::PDInfo.new(101, channel, scbk: OSDP::KeyStore.gen_key)
]

# Create a CP device and kick-off the handler thread
cp = OSDP::ControlPanel.new(pd_info, log_level: options[:log_level])
cp.start
cp.sc_wait_all

# Create a LED command to be used later
led_cmd = {
  command: OSDP::Command::LED,
  reader: 1,
  led_number: 0,
  control_code: 1,
  on_count: 10,
  off_count: 10,
  on_color: OSDP::CommandLEDColor::RED,
  off_color: OSDP::CommandLEDColor::BLACK,
  timer_count: 10,
  temporary: true
}

count = 0
while count < 5
  # Send LED command to PD-0
  cp.send_command(pd_info[0].address, led_cmd)

  # Check if we have an event from PD
  event = cp.get_event(pd_info[0].address)
  puts "PD-0 Sent Event #{event}" if event

  count += 1
  sleep(2)
end

cp.stop
