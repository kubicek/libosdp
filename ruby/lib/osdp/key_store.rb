#
#  Copyright (c) 2021-2025 Siddharth Chandrasekaran <sidcha.dev@gmail.com>
#
#  SPDX-License-Identifier: Apache-2.0
#

require 'securerandom'

module OSDP
  # Key store for managing OSDP keys
  class KeyStore
    # Generate a random key
    # @return [String] Random 16-byte key
    def self.gen_key
      SecureRandom.random_bytes(16)
    end

    # Load a key from a file
    # @param filename [String] Path to the key file
    # @return [String] The loaded key
    def self.load_key(filename)
      File.binread(filename)
    end

    # Store a key to a file
    # @param filename [String] Path to the key file
    # @param key [String] The key to store
    def self.store_key(filename, key)
      File.binwrite(filename, key)
    end
  end
end
