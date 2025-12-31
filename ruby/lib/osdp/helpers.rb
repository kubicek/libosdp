#
#  Copyright (c) 2021-2025 Siddharth Chandrasekaran <sidcha.dev@gmail.com>
#
#  SPDX-License-Identifier: Apache-2.0
#

module OSDP
  # PD identification information
  class PdId
    attr_accessor :version, :model, :vendor_code, :serial_number, :firmware_version

    def initialize(version: 0, model: 0, vendor_code: 0, serial_number: 0, firmware_version: 0)
      @version = version
      @model = model
      @vendor_code = vendor_code
      @serial_number = serial_number
      @firmware_version = firmware_version
    end
  end

  # PD information structure
  class PDInfo
    attr_accessor :address, :channel, :scbk, :flags

    def initialize(address, channel, scbk: nil, flags: 0)
      @address = address
      @channel = channel
      @scbk = scbk
      @flags = flags
    end
  end

  # PD capabilities structure
  class PDCapabilities
    attr_accessor :capabilities

    def initialize
      @capabilities = {}
    end

    def add_capability(function_code, compliance, num_items)
      @capabilities[function_code] = {
        compliance: compliance,
        num_items: num_items
      }
    end
  end
end
