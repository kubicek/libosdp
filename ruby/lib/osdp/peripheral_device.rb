#
#  Copyright (c) 2021-2025 Siddharth Chandrasekaran <sidcha.dev@gmail.com>
#
#  SPDX-License-Identifier: Apache-2.0
#

module OSDP
  # OSDP Peripheral Device
  class PeripheralDevice
    def initialize(pd_info, pd_cap, log_level: LogLevel::INFO)
      @pd_info = pd_info
      @pd_cap = pd_cap
      @log_level = log_level
      # Native initialization would happen here
    end

    # Start the peripheral device
    def start
      # Start the refresh thread
    end

    # Stop the peripheral device
    def stop
      # Stop the refresh thread
    end

    # Wait for secure channel establishment
    def sc_wait(timeout: 30)
      # Wait for secure channel
      sleep(timeout)
    end

    # Notify an event to the CP
    # @param event [Hash] Event hash
    def notify_event(event)
      # Notify event to CP
    end

    # Get a command from the CP
    # @return [Hash, nil] Command hash or nil
    def get_command
      # Get command from CP
      nil
    end

    # Check if secure channel is active
    # @return [Boolean] True if secure channel is active
    def sc_active?
      # Check secure channel status
      false
    end
  end
end
