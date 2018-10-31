# Google Summer of Code '18 QEMU Cortex-M0 / BBC:Microbit Final Report

## Scope and goals of the project

The goal of the project was to provide a working bbc:microbit emulation to the Quick Emulator (QEMU).
The bbc:microbit is a one board educational computer comprising a Nordic Semiconductor nRF51822 System-on-Chip (SOC) microcontroller based around a ARM Cortex-M0 CPU. The board contains buttons, an 2D dot matrix LED display, a radio and various sensors. 
Prior to the project, QEMU had no support for the process architecture, the processor, the SOC and the peripheral board.
Support for the processor architecture (ARMv6-M) and the Cortex-M0 processor was added by Julia Suvorova as part of her Outreachy project.

### Scope and goals of my work during the project

My goals for the project were to work on the bbc:microbit board and nRF51822 peripheral model implementation to be 
able to at least successfully run the bbc:microbit micropython and microsoft pxt (javascript) kernels. Furthermore a user interface was to be added to provide means of interaction with the firmware.

### What is done

The following contributions were provided and are in the process of being reviewed & merged:

* Implementation of the nRF51 Random Number Generator Peripheral
* Implementation of the nRF51 General Purpose I/O Peripheral
* Implementation of the nRF51 Timer
* Implementation of the nRF51 Non-volatile Memories and Memory Controller
* Implementation of a 2D Dot Matrix Demultiplexer & Display
* Tests for the devices mentioned above
* Implementation/extension of the nRF51822 SOC 
* Implementation/extension of the Microbit Board

With the devices mentioned above and the contributions of Julia Suvorova a user can successfully run and interact with the micropython and microsoft pxt firmwares.

### Todo

* Provide QMP command & event handling for LED matrix and buttons
* Implement a web-based interface based on these QMP buttons & events
* Implement missing SOC/board level devices (see QEMU Feature Wiki)

### Links

* [Patch Series with nRF51/Microbit devices](https://lists.gnu.org/archive/html/qemu-devel/2018-08/msg00604.html)
* [Patch Series with SOC/Board extension](https://lists.gnu.org/archive/html/qemu-devel/2018-08/msg01913.html)
* [Microbit Website](http://microbit.org/)
* [Microbit QEMU Fork](https://github.com/douzepouze/qemu/)
* [Open Issues in completed code](https://github.com/douzepouze/qemu/issues)
* [QEMU Feature Wiki Microbit](https://wiki.qemu.org/Features/MicroBit)
* [QMP Command Stimulate](https://github.com/douzepouze/qemu/tree/feature-stimulate)
* [Project Notebook](https://github.com/douzepouze/gsoc18-qemu/blob/master/notes.md)
* [Repository with collected documents, datasheets etc.](https://github.com/douzepouze/gsoc18-qemu)
