# Notes 06/07

## Chip Variant Attributes

There are **6** chip variants for the NRF51**8**22 noted in the reference
manual. Furthermore, there are variants of the related NRF51**4**22.

The chip code _NRF51XXXPPVVHPYYWWLL_ is made of the following items
- **PP**: Package Code
  - **QF**: QFN Package, 48 Pins
  - **CD**: WLCSP Package, 56 Pins
  - **CE**: WLCSP Package, 62 Pins
  - **CF**: WLCSP Package, 62 Pins
  
**VV**: Variant Code

| Variant  | Flash | RAM |
| --- | --- | --- |
| AA | 256 kB | 16 kB |
| AB | 128 kB | 16 kB |
| AC | 256 kB | 32 kB |




# Notes 06/05

Pomodoros:
  - Apply peripheral stubs from julia
  - Change code to PM proposed layout
  - Add attribute for actual SOC type
  - Map all peripheral MMIO areas systematically

## GDB Muscle Memroy
  - `symbol-file` to load symbol
  - `break *0xADDRESS` to break at address
  - `monitor system_reset` to issue a `system_reset` to qemu
  - `p/t $cpsr` print status register


# Notes 06/03

- NRF51822 supports S100 SoftDevice
- Differences between nRF51822 and nRF51422
  - For nRF51422, you can flash all softdevices for BLE and/or ANT protocols (S110, S120, S130, S210, S310)
  - For nRF51822, you can flash only BLE softdevices (S110, S120, S130)


# Notes 05/31

Useful flags for debugging:
```
-singlestep -d in_asm,cpu -D /tmp/qemu.log
```

- `-d in_asm` prints address, bytecode, mnemonic and operands of the instruction being executed
- `-d cpu` prints contents of all registers after execution
- `-singlestep` evaluate debug options after each instruction
  - Affects `DisasContextBase` members `singlestep_enabled`, `singlestep`, `max_insns` in `translator.c`

Small howto how to add qmp commands: `qemu/qemu/docs/devel/writing-qmp-commands.txt`

----

## `memory_` API

- Found in `qemu/inlcude/exec/memory.h`
- Use `memory_region_init` to create a _memory container_, just map the maximal memory size (_UINT64MAX_)
  - Use `memory_region_add_subregion_overlay` to create overlay of mapped memory
    - Overlay can be given `priority`, higher priority beats lower priority
  - Use `memory_region_init_ram` to create a SRAM MemoryRegion 
  - Use `memory_region_add_subregion` to add regular subregions into a container (reference to eg. SRAM region) 
  - `memory_region_size`

### Best practices attach MMIO device to SoC (iotkit - tz-ppc)
Prerequisites:
- Peripheral device class must be inherited from TYPE\_SYS\_BUS\_DEVICE 

In Peripheral:
- Use `memory_region_init_io` to create memory region **MR** and attached MemoryRegionOps
- Use `sysbus_init_mmio` to register **MR** with sysbus device 

In the SoC:
- Use `sysbus_mmio_get_region` to get **MR** from peripheral
- Use `memory_region_add_subregion` to map MMIO to SOC container 

# Notes 05/29

Reading more code: `hw/arm/stm32f205_soc` and `hw/arm/netduino`
---

Used in machine netduino2.

- In Class:
  - Setup MemoryRegions
    - `init_ram`, `init_flash` sets SIZE
    - Set readonly flash
    - Set flash alias region
    - `add_subregion` sets mapped address

Still have not really understood QOM. 

## Reading object.h.
- Registering user creatable types
  - Dynamically regisering
  - Single-inheritance
  - Multiple inheritance of stateless interfaces

- Minimal example with `type_init`
  - `type_init` on module level --> call registering functions
  - Register new type (with name and parent name) via `TypeInfo` struct using `type_register_state`, instance size of DeviceState for device
  - Alternative register serveral types via `DEFINE_TYPES`
  - Every *type* has an *ObjectClass* associated with it
  - *ObjectClass* is dynamically instantiated *singleton*
  - *ObjectClass* contains table of function pointers with virtual methods
  - `object_new` is used to instantiate a _object_ of _class_ *ObjectClass*
  - _object_ can be casted up/down the hierachy with `object_dynamic_cast`, usually via `OBJECT_CHECK` and `OBJECT_CLASS_CHECK` macros
  - *ObjectClass* initialization
    - Lazily instantiated
    - First initialize any parent class
    - Parent class is copied into sub-class after initialization
    - After parent initialization, `TypeInfo::class_init` is called to init the current class
    - _method_: Operates on object instance, passed as first argument
    - Used callback on _stm32f205_ class, which is a `DeviceClass`:
      - _realize_: Called when `realized` property changed to true
  - `DeviceClass` objects are constructed in two stages:
    - Object instantiation via `object_initialize` (can fail)
      - Trivial field initialization
    - Device realization (may not fail and must be re-entrant)
      - All static properties must be set before this step
  - Difference between `TypeInfo::instance_init` and `DeviceClass::realize`:
    - Both gets passed the `State` object not the `DeviceClass` object
    - **1)** `TypeInfo::instance_init`:
      - Called to initialize the object
      - Class already initialized
      - Initialize 'child' objects/device and attach to sysbus as well
    - **2)** `DeviceClass:realize`:
      - Can interact with 'child' objects/devices 
      - Interconnect devices/irqs
      - Set _realized_ property in children to _true_

---

## Refine button-set-state design

- Remove microbit.json again
  - Move to more general api --> stimulate.json
- Set mapping either as `MachineClass` or `MachineState` property
  - Add property dynamically to `MachineState` for now, `MachineClass` required manual implementation of subclassed machine class
- In button-set-state, get object from tree with `object_resolve_path`
  - Attach new object to machine: `/machine/stimulate/`
  - Buttons be like: `/machine/stimulate/button-a` or `/machine/stimulate/button/a` or `/machine/stimulate/button[0]` (with name "a")
  - Other peripherals (like adcs) be like: `/machine/stimulate/analogin` etc
  - Stimulate acts as an *adapter* across the *system boundary* and translates _high level_ *machine objects* likes buttons, analog ins, analog outs, leds to `DeviceClass` level manipulations.
- Get gpio for button from mapping
- Stimulate gpio

# Notes 05/27

- Fix SuHang tests with symlink outside OOT build dist to tests
- Run hexload and boot-serial-test tests with
  - export QTEST\_LOG=1 for logging to stderr
  - make check-qtest-arm

# Notes 05/25

- Set up docker container based on `phuison/baseimage-docker` (ubuntu 16.04 LTS based)
  - Setup mbed/yotta toolchain, build microbit-dal/microbit-samples: Success!
  - Try to run qemu with elf/hex: does not work.
  - Crashes on first `ni` when gdb attached, also no code at location of reset vector

---

**Sections** of `.hex` file generated using **online** toolchain:

```
/home/pouze/Downloads/microbit.hex:     file format ihex
/home/pouze/Downloads/microbit.hex
architecture: UNKNOWN!, flags 0x00000000:

start address 0x000153ed

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .sec1         00010000  00000000  00000000  00000010  2**0
                  CONTENTS, ALLOC, LOAD
  1 .sec2         00010000  00010000  00010000  0002c020  2**0
                  CONTENTS, ALLOC, LOAD
  2 .sec3         00010000  00020000  00020000  00058030  2**0
                  CONTENTS, ALLOC, LOAD
  3 .sec4         0000b2d4  00030000  00030000  00084040  2**0
                  CONTENTS, ALLOC, LOAD
  4 .sec5         00000080  0003e000  0003e000  000a2c20  2**0
                  CONTENTS, ALLOC, LOAD
SYMBOL TABLE:
no symbols
```

Begin loading of `.text` at offset `0x0000 0000`, vector PC to `0x000153ed` on reset.


**Entries in `.hex` file**:
```
:020000040000FA  --> Following entry addreses are the most significant 16 bit of the address
:1000000000400020ED530100295401002B54010051 --> Load first entry (32 bytes) starting at offset 0x000
:1000100000000000000000000000000000000000E0
```

---

**Sections** in `.elf` file created using **offline** toolchain:

```
pouze@gouranga % arm-none-eabi-objdump -x microbit_samples_1.elf            

microbit_samples_1.elf:     file format elf32-littlearm
microbit_samples_1.elf
architecture: arm, flags 0x00000112:
EXEC_P, HAS_SYMS, D_PAGED
start address 0x0001f565

Program Header:
0x70000001 off    0x0001a21c vaddr 0x0002a21c paddr 0x0002a21c align 2**2
         filesz 0x00000008 memsz 0x00000008 flags r--
    LOAD off    0x00000000 vaddr 0x00010000 paddr 0x00010000 align 2**16
         filesz 0x0001a224 memsz 0x0001a224 flags r-x
    LOAD off    0x00022000 vaddr 0x20002000 paddr 0x0002a224 align 2**16
         filesz 0x00000214 memsz 0x00000214 flags rw-
    LOAD off    0x00022218 vaddr 0x20002218 paddr 0x0002a440 align 2**16
         filesz 0x00000000 memsz 0x00000870 flags rw-
private flags = 5000200: [Version5 EABI] [soft-float ABI]

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .text         0001221c  00018000  00018000  00008000  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  1 .ARM.exidx    00000008  0002a21c  0002a21c  0001a21c  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  2 .data         00000214  20002000  0002a224  00022000  2**2
                  CONTENTS, ALLOC, LOAD, DATA
  3 .bss          00000870  20002218  0002a440  00022218  2**3
                  ALLOC
  4 .heap         00000800  20002a88  20002a88  00022218  2**3
                  CONTENTS, READONLY
  5 .stack_dummy  00000800  20002a88  20002a88  00022a18  2**3
                  CONTENTS, READONLY
  6 .ARM.attributes 00000028  00000000  00000000  00023218  2**0
                  CONTENTS, READONLY
  7 .comment      0000007e  00000000  00000000  00023240  2**0
                  CONTENTS, READONLY
```

Here, the `.text` section is loaded to offset `0x00018000`. 
Lets try to fix this. Copy all loadable sections to `.hex` file:

```
arm-none-eabi-objcopy -O ihex input.elf output.hex:

pouze@gouranga ~/projects/gsoc/kernels (git)-[master] % arm-none-eabi-objdump -x output.hex

output.hex:     file format ihex
output.hex
architecture: UNKNOWN!, flags 0x00000000:

start address 0x0001f565

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .sec1         00008000  00018000  00018000  00000011  2**0
                  CONTENTS, ALLOC, LOAD
  1 .sec2         0000a438  00020000  00020000  00016822  2**0
                  CONTENTS, ALLOC, LOAD
SYMBOL TABLE:
no symbols
```
Lets try with corrected addresses:
```
arm-none-eabi-objcopy -O ihex --change-section-address .text=0x00 input.elf output.hex:

pouze@gouranga ~/projects/gsoc/kernels (git)-[master] % arm-none-eabi-objdump -x output.hex

output.hex:     file format ihex
output.hex
architecture: UNKNOWN!, flags 0x00000000:

start address 0x0001f565

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .sec1         00010000  00000000  00000000  00000000  2**0
                  CONTENTS, ALLOC, LOAD
  1 .sec2         0000221c  00010000  00010000  0002d011  2**0
                  CONTENTS, ALLOC, LOAD
  2 .sec3         0000021c  0002a21c  0002a21c  00033014  2**0
                  CONTENTS, ALLOC, LOAD
SYMBOL TABLE:
no symbols


pouze@gouranga ~/projects/gsoc/kernels (git)-[master] % head -n3 output.hex
:100000000040002065F50100A1F50100A3F5010005
:1000100000000000000000000000000000000000E0
:10002000000000000000000000000000A5F5010035

```

> Better use objdump -h to show section headers

Disassembly of micro_samples_1.elf (Offline file):

```
microbit_samples_1.elf:     file format elf32-littlearm


Disassembly of section .text:

00018000 <__Vectors>: --> Load .text here
   18000:       20004000       --> init SP 
   18004:       0001f565       --> Reset vector, lowest bit always set on armv6-m/armv7-m to signal thumb mode instead of arm mode 
   18008:       0001f5a1        andeq   pc, r1, r1, lsr #11
   1800c:       0001f5a3        andeq   pc, r1, r3, lsr #11

0001f564 <Reset_Handler>: --> Looks good
   1f564:   4808        ldr r0, [pc, #32]   ; (1f588 <Reset_Handler+0x24>)
   1f566:   6802        ldr r2, [r0, #0]
   1f568:   2103        movs    r1, #3
   1f56a:   430a        orrs    r2, r1
```

Disassembly of microbit.hex (online file):

```
arm-none-eabi-objdump -m arm -D ~/Downloads/microbit.hex > ~/tmp/dump_online_hex.txt

/home/pouze/Downloads/microbit.hex:     file format ihex


Disassembly of section .sec1:

00000000 <.sec1>: --> Load .text at 0x00
       0:   20004000   --> init Sp 
       4:   000153ed   --> Reset vector 0x153ec
       8:   00015429    andeq   r5, r1, r9, lsr #8
```

According to _NRF51 reference manual_:
- Code Flash Start is `0x0000 0000`
- Data Ram Start is   `0x2000 0000`

Size of Sections (according to _Nordic nRF51822-QFAA-R rev 3 datasheet_):
- Flash Size: 256KB, highest address in bytes therefore:` 0x40000`
- SRAM Size: 16KB, highest address in bytes therefore: `0x20004000`
Furthermore `.data`, `.bss`, `.stack`, `.heap` must reside in `Block1,RAM3`, which seem to be the upper half of the SRAM: `0x20002000 - 0x20004000`

```
arm-none-eabi-objcopy --change-section-address .text=0x00 -R .ARM.exidx microbit_samples_1.elf microbit_samples_1_moved.elf
```
this at least does not lead to immediate panic but all absolute addresses (vector table) still stay the same. 

The only solution is to fix the microbit-samples linker file.

I checked the https://github.com/bbcmicrobit/micropython repository now.
Building this project:
yt target bbc-microbit-classic-gcc-nosd
yt up
yt build

yields a elf file with sections allocated at the right adresses. This file can be loaded and used
for debugging right away:
```
pouze@gouranga ~ % docker cp elated_lamport:/bbcmicrobit/build/bbc-microbit-classic-gcc-nosd/source/microbit-micropython ~/tmp/micropython.elf
pouze@gouranga ~ % arm-none-eabi-objdump -h ~/tmp/micropython.elf

/home/pouze/tmp/micropython.elf:     file format elf32-littlearm

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .text         00037820  00000000  00000000  00010000  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  1 .ARM.exidx    00000008  00037820  00037820  00047820  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  2 .data         00000278  20000000  00037828  00050000  2**2
                  CONTENTS, ALLOC, LOAD, DATA
  3 .bss          00002d5c  20000278  00037aa0  00050278  2**3
                  ALLOC
  4 .heap         00000800  20002fd8  20002fd8  00050278  2**3
                  CONTENTS, READONLY
  5 .stack_dummy  00000800  20002fd8  20002fd8  00050a78  2**3
                  CONTENTS, READONLY
  6 .ARM.attributes 00000028  00000000  00000000  00051278  2**0
                  CONTENTS, READONLY
  7 .comment      0000007e  00000000  00000000  000512a0  2**0
                  CONTENTS, READONLY
  8 .debug_info   0021a5a7  00000000  00000000  0005131e  2**0
                  CONTENTS, READONLY, DEBUGGING
  9 .debug_abbrev 0002fbff  00000000  00000000  0026b8c5  2**0
                  CONTENTS, READONLY, DEBUGGING
 10 .debug_loc    00053399  00000000  00000000  0029b4c4  2**0
                  CONTENTS, READONLY, DEBUGGING
 11 .debug_aranges 00004a08  00000000  00000000  002ee860  2**3
                  CONTENTS, READONLY, DEBUGGING
 12 .debug_ranges 0000a1a8  00000000  00000000  002f3268  2**0
                  CONTENTS, READONLY, DEBUGGING
 13 .debug_line   00030f12  00000000  00000000  002fd410  2**0
                  CONTENTS, READONLY, DEBUGGING
 14 .debug_str    0003442d  00000000  00000000  0032e322  2**0
                  CONTENTS, READONLY, DEBUGGING
 15 .debug_frame  0000df28  00000000  00000000  00362750  2**2
                  CONTENTS, READONLY, DEBUGGING
 16 .stabstr      00000076  00000000  00000000  00370678  2**0
                  CONTENTS, READONLY, DEBUGGING
```
microbit-samples can also be build with the yt target bbc-microbit-classic-gcc-nosd target and this then located at the right adresses.

# Notes 05/24 
- mbed offline toolchain installiert (auf arch)
- installation of yotta does not work with pip == 10.x (breaks project-generator dependency)
- can not build microbit-samples project:
  - problem is either yotta with cmake 3.11 or with arch-maintained gcc-arm-none-eabi
     Problem: SVC calls in -mcpu=cortex-m0 / -march=armv6-m (should be ok in armv6s-m though and cortex-m0 include priviledge extension)


# Notes 05/20

QMP = QEMU maschine protocol

QAPI defintiion in qemu/qapi, insbesondere in qapi-schema.json -> describes all available commands

QMP command types:
 - regular
 - query

 QMP specification: docs/interop/qmp-sec.txt

 Generate stubs via scripts/qapi-gen.py

 Access qmp: run qemu in control mode:
  -qmp tcp:localhost:4444,server
  -qmp unix:/tmp/qmp-sock,server
```
qom-list /machine
            /unattached/
                        device[0]
                        device[1]
                        device[2]
                        device[3]
                        device[4]

qdev_init_gpio_out / qdev_init_gpio_in

QMP -> Receive -> Eval GPIO Configuration -> Struct GPIO
                                                |
                                                |
                                               MMIO
```

# Notes 05/18

OOT Build softmmu only: ./configure --target-list=arm-softmmu --enable-debug
-machine microbit
-machine help: Lists machines
-kernel: gust image
-d unimp: Long access unimplemented devices (Must be created frist via create_unimplemented_device)
-trace memory_region_ops*: Log memeory access
-cpu cortex-m3
-cpu help: lists available cpus
-S: stop execution at startup , continue with c
-s: alias for -gdb tcp::1234
-nographic: disable graphic output and send std/stderr to console
-display curses: ncurses interface
-monitor
-serial mon:stdio

## qemu command line utility
    * device_add
    * device_del
    * stop
    * cont
    * info registers -a
    * info rams
    * info status
    * system_reset
    * logfile
    * Ctrl+a x: exit emulator (QEMU character ackend multiplexer)

# Notes 05/16

## QTest
- libqtest api --> QMP
- qemu/tests, qemu/tests/libqos, qemu/tests/Makefile
- Run all test: make check
- Run single test: make tests/my-test
- make check SPEED=slow V=1" for a verbose, more thorough test run
- QTEST_LOG=1 => Print to stderr
- QTEST_STOP=1 => Stop to connect to debugger

1. Attach: `gdb --pid=$(pidof my-test)`
2. Continue: `kill -SIGCONT $(pidof qemu-system-arm)`

