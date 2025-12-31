# LibOSDP Ruby Examples

This directory contains example Ruby applications demonstrating how to use LibOSDP.

## Examples

### Control Panel (CP) Application

`cp_app.rb` - Demonstrates how to create a Control Panel that can communicate with one or more Peripheral Devices.

Usage:
```bash
ruby cp_app.rb /dev/ttyUSB0 --baudrate 115200 --log-level 6
```

### Peripheral Device (PD) Application

`pd_app.rb` - Demonstrates how to create a Peripheral Device that can communicate with a Control Panel.

Usage:
```bash
ruby pd_app.rb /dev/ttyUSB0 --baudrate 115200 --log-level 6
```

## Running the Examples

1. Install the libosdp gem:
   ```bash
   cd ../../ruby
   gem build libosdp.gemspec
   gem install libosdp-3.1.0.gem
   ```

2. Connect your OSDP devices via serial port

3. Run the examples as shown above

## Notes

- The examples use a placeholder serial channel implementation. For real hardware, you'll need to implement proper serial communication using a gem like `serialport`.
- Make sure you have the necessary permissions to access the serial device (you may need to add your user to the `dialout` group on Linux).
- The examples demonstrate the basic structure and API usage. You'll need to adapt them for your specific use case.

## See Also

- [LibOSDP Documentation](https://libosdp.sidcha.dev/)
- [Python Examples](../python/) for more comprehensive examples
- [C Examples](../c/) for the original C implementation examples
