## HW requirements

- nrf52833
- nrf52840 dongle



## SW requirements

### SDK & SoftDevice

- nRF5_SDK_17.0.0_9d13099
- s140_nrf52_7.0.1_softdevice
  - nRF5_SDK_17.0.0_9d13099\components\softdevice\s140

### IDE & Tools

- Segger Embedded Studio 5.30 windows x64
- J-Link utility
- GNU Arm Embeddd Toolchain 9-2019-q4-major
- nRF connect for desktop
- nRF command line tools



## Development architecture

- Application
  - nRF5_SDK_17.0.0_9d13099\examples\ble_peripheral\ble_app_template\pca10056\s140
- bootloader
  - nRF5_SDK_17.0.0_9d13099\examples\dfu\secure_bootloader\pca10100_s140_ble
- Code from SDK in a local directory
  - absolute path , SEGGER options global macros (NORDIC_SDK_PATH)

### Directory structure

- Application
  - src
  - inc
  - build
    - armgcc
    - config
    - ses
- Bootloader
  - src
- common
  - dfu