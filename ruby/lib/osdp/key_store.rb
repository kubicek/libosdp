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
    # @raise [ArgumentError] if filename is invalid
    # @raise [Errno::ENOENT] if file doesn't exist
    def self.load_key(filename)
      raise ArgumentError, 'filename cannot be nil or empty' if filename.nil? || filename.empty?
      raise Errno::ENOENT, filename unless File.exist?(filename)
      File.binread(filename)
    end

    # Store a key to a file
    # @param filename [String] Path to the key file
    # @param key [String] The key to store
    # @raise [ArgumentError] if filename or key is invalid
    def self.store_key(filename, key)
      raise ArgumentError, 'filename cannot be nil or empty' if filename.nil? || filename.empty?
      raise ArgumentError, 'key cannot be nil' if key.nil?
      raise ArgumentError, 'key must be 16 bytes' if key.length != 16
      File.binwrite(filename, key)
    end
  end
end
