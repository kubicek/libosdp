#
#  Copyright (c) 2021-2025 Siddharth Chandrasekaran <sidcha.dev@gmail.com>
#
#  SPDX-License-Identifier: Apache-2.0
#

module OSDP
  # Base class for OSDP communication channels
  class Channel
    # Send data over the channel
    # @param data [String] Data to send
    # @return [Integer] Number of bytes sent
    def send(data)
      raise NotImplementedError, "Subclasses must implement #send"
    end

    # Receive data from the channel
    # @param max_len [Integer] Maximum number of bytes to receive
    # @return [String, nil] Received data or nil if no data available
    def recv(max_len)
      raise NotImplementedError, "Subclasses must implement #recv"
    end

    # Flush the channel
    def flush
      # Default implementation - can be overridden
    end
  end

  # Serial channel implementation for OSDP
  class SerialChannel < Channel
    def initialize(device, baud_rate: 9600)
      raise ArgumentError, 'device cannot be nil or empty' if device.nil? || device.empty?
      raise ArgumentError, 'baud_rate must be a positive integer' unless baud_rate.is_a?(Integer) && baud_rate > 0
      
      @device = device
      @baud_rate = baud_rate
      # Actual serial implementation would go here
    end

    def send(data)
      # Placeholder implementation
      data.length
    end

    def recv(max_len)
      # Placeholder implementation
      nil
    end

    def flush
      # Placeholder implementation
    end
  end
end
