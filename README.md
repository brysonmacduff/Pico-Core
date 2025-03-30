* Description
    - This project contains c++ libraries that wrap around the Raspberry Pi Pico SDK.
* Build Instructions
    - cmake -S . -B build
    - cd build
    - make
* Install Instructions
    - cmake --install build
* Runing Test Firmware
    - This project builds test firmware that runs on the Pico for testing libraries in this project.
    - Transfer uf2 file from build directory to Raspberry Pi Pico W drive.
* Reading Test Firmware USB Serial Output
    - Manual
        - Identify serial port
            - sudo dmesg | tail
        - View USB serial output
            - Example: sudo screen /dev/ttyACM0 115200
        - Exit USB serial output
            - Enter keyboard commands: Ctrl+A, k, y
    - Automatic
        - Before loading firmware to the pico:
            - sudo ./record_serial_logs.sh
            - tail -f serial_log.txt
