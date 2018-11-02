# Notes 11/1

## TWI in I2C mode
```
twi_write: 0x124 <- 0x0 [4] - Set Back Error Event
twi_write: 0x500 <- 0x0 [4] - Disable TWI (or other modes)
twi_write: 0xffc <- 0x0 [4] - Power off (obsolete?)
twi_write: 0xffc <- 0x1 [4] - Power on (obsolete?)
twi_write: 0x508 <- 0x0 [4] - PSELSCL (Pin select for SCL) to PIN0
twi_write: 0x50c <- 0x1e [4] - PSELSDA (Pin select for for SDA) to PIN30
twi_write: 0x524 <- 0x1980000 [4] - TWI Frequency to 100 kbps
twi_write: 0x500 <- 0x5 [4] - Enable TWI
nrf51_soc.io: unimplemented device write (size 4, value 0x0, offset 0x617c) - GPIOTE: Clear Event PORT
nrf51_soc.io: unimplemented device write (size 4, value 0x80000000, offset 0x6304) - GPIOTE: Enable Interrupt on event PORT
twi_write: 0x588 <- 0x1d [4] - Set Address to communicate with to 0x1d (29)
twi_write: 0x200 <- 0x0 [4] - Deactivate SHORTS 
twi_write: 0x8 <- 0x1 [4] - Start TWI Transmit sequence
twi_write: 0x51c <- 0xd [4] - TXD (transmit register) = 0xd
twi_read: 0x11c [4] = 1 - Content of TXD sent (TXDSENT)
twi_write: 0x11c <- 0x0 [4] - Clear  TXDSENT
twi_write: 0x588 <- 0x1d [4] - Set address to 0x1d
twi_write: 0x200 <- 0x1 [4] - Shortcut between BB (Byte boundary, generated before each byte that is sent or received) and SUSPEND task (suspend twi transmission)
twi_write: 0x108 <- 0x0 [4] - Clear RXDREADY event (TWI RXD byte received)
twi_write: 0x0 <- 0x1 [4] - Start TWI receive sequence
twi_write: 0x200 <- 0x2 [4] - Shortcut between BB event and STOP task (stop twi transmission)
twi_write: 0x20 <- 0x1 [4] - Resume TWI transaction
twi_read: 0x108 [4] = 1 - Check RXDREADY
twi_write: 0x108 <- 0x0 [4] - Clear RXDREADY
twi_read: 0x518 [4] = 0 - Read RXD
twi_read: 0x104 [4] = 1 - Check whether TWI is stopped 
twi_write: 0x104 <- 0x0 [4] - Stop TWi 
twi_write: 0x588 <- 0x19 [4] - Address to 0x19 (27)
twi_write: 0x200 <- 0x0 [4] - Clear Shortcuts
twi_write: 0x8 <- 0x1 [4] - Start TWI transmit sequence
twi_write: 0x51c <- 0xf [4] - Send 0xf
twi_read: 0x11c [4] = 1 - Check TXDSENT
twi_write: 0x11c <- 0x0 [4] - Clear TXD byte sent
twi_write: 0x588 <- 0x19 [4] - Address to 0x19
twi_write: 0x200 <- 0x1 [4] - Shortcut between BB event and SUSPEND task
twi_write: 0x108 <- 0x0 [4] - Clear RXDReady
twi_write: 0x0 <- 0x1 [4] - Start RX sequence
twi_write: 0x200 <- 0x2 [4] - Shortcut between BB and STOP 
twi_write: 0x20 <- 0x1 [4] - Resume TWI transaction
twi_read: 0x108 [4] = 1 - Check RXDREADY
twi_write: 0x108 <- 0x0 [4] - Clear RXDREADY
twi_read: 0x518 [4] = 0 - Read RXD
twi_read: 0x104 [4] = 1 - Check whether TWI is stopped (yes)
twi_write: 0x104 <- 0x0 [4] - Clear TWI stopped event
twi_write: 0x588 <- 0x1e [4] - Set address to 0x1e (30)
twi_write: 0x200 <- 0x0 [4] - Clear shortcuts
twi_write: 0x8 <- 0x1 [4] - Start TWI sequence
twi_write: 0x51c <- 0xd [4] - Send 0xd
twi_read: 0x11c [4] = 1 - Check if sent
twi_write: 0x11c <- 0x0 [4] - Clear sent event
twi_write: 0x588 <- 0x1e [4] - Set address to 0x1e (30)
twi_write: 0x200 <- 0x1 [4] - Shortcut between BB and SUSPEND
twi_write: 0x108 <- 0x0 [4] - Clear RXDREADY
twi_write: 0x0 <- 0x1 [4] - Start TWI receive sequence
twi_write: 0x200 <- 0x2 [4] - Shortcut between BB and STOP
twi_write: 0x20 <- 0x1 [4] - Resume TWI transaction
twi_read: 0x108 [4] = 1 - Check received
twi_write: 0x108 <- 0x0 [4] - Clear received
twi_read: 0x518 [4] = 0 - Read RXD
twi_read: 0x104 [4] = 1 - Check Stopped
twi_write: 0x104 <- 0x0 [4] - Clear stopped
```

```
pouze@gouranga ..micropython/yotta_modules/microbit-dal (git)-[master] % grep -ir "0x0d" .
./source/bluetooth/MicroBitLEDService.cpp:    0xe9,0x5d,0x0d,0x2d,0x25,0x1d,0x47,0x0a,0xa0,0x62,0xfa,0x19,0x22,0xdf,0xa9,0xa8
./inc/drivers/MicroBitAccelerometer.h:#define MMA8653_WHOAMI          0x0D
./inc/drivers/MicroBitCompass.h:#define MAG_OFF_Z_MSB 0x0D
pouze@gouranga ..micropython/yotta_modules/microbit-dal (git)-[master] %
```

e10a4ff to current master (40e9291):

```
pouze@gouranga ..yotta_modules/microbit-dal/inc/drivers (git)-[master] % git diff --stat e10a5ff 40e9291
 ....
 source/microbit/main.cpp                  |   53 ++--
 source/microbit/microbitaccelerometer.cpp |   34 ++-
 source/microbit/microbitcompass.cpp       |   57 ++--
 ...
 42 files changed, 1944 insertions(+), 260 deletions(-)
```

Main now uses "autoDetect" of Accelormeter and Compass.
Need to update included modules using yotta (or check out microbit-dal repo).
Interesting changes are mostly in the drivers that are part of the microbit-dal

```
@@ -126,15 +140,20 @@ typedef struct _appended_script_t {
 #define APPENDED_SCRIPT ((const appended_script_t*)microbit_mp_appended_script())

 int main(void) {
+    // Configure the soft reset button
+    gpio_init_in(&reset_button_gpio, MICROBIT_PIN_BUTTON_RESET);
+    gpio_mode(&reset_button_gpio, PullUp);
+    gpio_irq_init(&reset_button_gpio_irq, MICROBIT_PIN_BUTTON_RESET, &reset_button_handler, 1 /* dummy, must be non-zero */);
+    gpio_irq_set(&reset_button_gpio_irq, IRQ_FALL, 1);
+
+    // Create dynamically-allocated DAL components
+    ubit_accelerometer = &MicroBitAccelerometer::autoDetect(ubit_i2c);
+    ubit_compass = &MicroBitCompass::autoDetect(ubit_i2c);
+    ubit_compass_calibrator = new MicroBitCompassCalibrator(*ubit_compass, *ubit_accelerometer, ubit_display);
+
```

MicroBitAccelerometer probes which Accelerometer is installed on the MicroBit
and creates an instance of the driver (so its basically some kind of factory):

https://github.com/lancaster-university/microbit-dal/blob/9164922a519aa213a565cbf2abaa2cf4debf4977/source/drivers/MicroBitAccelerometer.cpp#L79
https://github.com/lancaster-university/microbit-dal/blob/9164922a519aa213a565cbf2abaa2cf4debf4977/source/drivers/MicroBitCompass.cpp#L101


# Notes 10/28

- Revised patches are located in microbit-shenki branch (tracking upstream origin/microbit-shenki)
- Brought master to state of current qemu/master (reset, fetch, merge --ff-only): 179f9ac887
- Change master to track upstream qemu/master
- Two possibilities to transplant the changeset from microbit-shenki to master:
  - Cherry-picking
  - rebase --onto
- Lets try cherry-picking: 36fe8c6a92 - 4653dcbdbe:
  - git cherry-pick 36fe8c6a92~1..4653dcbdbe

# Notes 07/22

## GDB Muscle Memory

```
set substitute-path from to ; Subsistute search path, also see directory
save breakpoints path ; Save breakpoints of session

```

# Notes 07/21

## Timer maths

```python
f = 16e6
# Arguments: nanoseconds, prescaler
ns_to_ticks = lambda x,p: (x * f)/(1e9 * (1 << p))
ticks_to_ns = lambda x,p: (x * (1 << p) * 1e9) / f
```

# Notes 07/18

## State of micropython kernel peripheral usage

Create a list of unimplemented peripheral device access:

```bash
qemu.. -machine .. -kernel .. -d unimp 2> /tmp/unimp.txt
```

Prepare the log using `sort | uniq`.

Remove all non-unimp items from the log. 

Sort the list by offset address:

```python
data = open('/tmp/unimp_uniq_clean.txt').readlines()
data.sort(key=lambda l: int(l.split(' ')[-1][:-2] ,16))
open('/tmp/unimp_sorted.txt', 'w').writelines(data)
```

Annotated list for `microbit-micropython-e10a5ff` can be found [here](unimp_micropython.md)

## Investigation into `microbitdisplay.cpp`

MicrobitDisplay does not show a single pixel at the moment.

Calling `display.clear()` hangs/crashes. Reason: Call for [wait_for_events](https://github.com/bbcmicrobit/micropython/blob/e10a5ffdbaf1cc40a82a665d79343c7b6b78d13b/source/microbit/microbitdisplay.cpp#L492) will call `__WFI` which stalls because nothing causes the CPU to return from this call at the moment. Needs investigation.

Display is not driven because the framebuffer is drawn by [callback](https://github.com/bbcmicrobit/micropython/blob/0185d0bf99ded455b64929f2489a76bb21bf406f/source/microbit/microbitdisplay.cpp#L357), which is [driven by](https://github.com/bbcmicrobit/micropython/blob/0185d0bf99ded455b64929f2489a76bb21bf406f/source/microbit/microbitdisplay.cpp#L463) the "ticker" which is driven by [TIMER0](https://github.com/bbcmicrobit/micropython/blob/e26d7c89d4a96de0fa0a1dd5aec024b31fc4816e/source/lib/ticker.c#L30)

# Notes 07/16

## GSOC Meet-Up

* LED Mapping
  * https://github.com/groklearning/microbit-simulated-dal/blob/master/source/Hardware.cpp#L520
* Microbit-dal Display Rendering
  * https://github.com/bbcmicrobit/micropython/blob/master/source/microbit/display_readme.md
* UART v2 Patch
  * https://github.com/jusual/qemu/commit/498ba4f4ebb50016154991895739d57fd3545c0a
* Microsoft Javascript Runtime PXT
  * https://github.com/Microsoft/pxt-microbit/blob/v0.13.52/libs/core/pxt.cpp#L742
  * https://github.com/Microsoft/pxt-microbit/blob/master/README.md

# Notes 07/15

## Test GPIO

```python
import machine
base = 0x50000000
r = lambda x: hex(machine.mem32[base + x])
def w(off, value):
    machine.mem32[base + off] = value
```

## LEDs in QEMU

* `hw/display/jazz_led.c`
  * 7-Segment color LED display
  * http://qemu.11.n7.nabble.com/PATCH-Add-a-7-segments-led-display-td43432.html
  * Used with MIPS PICA 61
  * https://www.linux-mips.org/wiki/QEMU
  * To be used with `qemu-system-mips -M pica61`
* `hw/display/ssd0303.c`, `hw/display/ssd0323.c`
  * I2C display, interesting

# Notes 07/13

## Run / Test migration

```
12:29 < stefanha> $ qemu ...options... -incoming tcp::1234
12:29 < stefanha> Now you have two QEMUs with identical options, except the -incoming option.
12:30 < stefanha> The second QEMU doesn't run, it's just waiting for an incoming migration connection.
12:30 < stefanha> In the first QEMU:
12:30 < stefanha> (qemu) migrate tcp:127.0.0.1:1234
12:36 < stefanha> For more background, see docs/devel/migration.rst.
```

## GPIOs in QEMU

* `gpio_key.c` - Key pass through
  * Used toggle an _outgoing_ (qemu) gpio line after some time out after receiving a pulse on an incoming gpio line
  * Used in `hw/arm/virt.c` for the power button
* `pl0651.c` - pl061 Arm PrimeCell PL061 General Purpose
  * MMIO interface
  * IRQ interface
  * GPIO exposes via qemu gpios
* `omap_gpio.c` - TI OMAP processors GPIO emulation
  * Same architecture as `pl0651`
* `zaurus.c`
* `puv3_gpio.c`
  * Very basic with exposed GPIOs via qemu gpios
* `mpc8xxx.c` - Freescale SoCs
  * Very basic with exposed GPIOs via qemu gpios
* `imx_gpio.c` - i.MX processors GPIO emulation.
  * Basic with exposed GPIOs 

# Notes 07/04

## Run microbit tests

From `dist` run:
```bash
make -j9
make tests/microbit-test 
QTEST_LOG=1 QTEST_QEMU_BINARY=arm-softmmu/qemu-system-arm gtester -k --verbose tests/microbit-test
```

GDB can not easily be attached, because gtester forks and runs the target binary (in this case `qemu-system-arm`). It is easier to let `gtester` run gdb instead:

```bash
QTEST_QEMU_BINARY="xterm -e gdb --tty $(tty) --args arm-softmmu/qemu-system-arm" gtester -k --verbose tests/microbit-test
```

## pyOCD + DAPLINK 

### Change udev rules 

`/etc/udev/rules.d/90-usb-microbit.rules is owned by mu-editor 1:0.9.13-1`

change line 

`SUBSYSTEM=="tty", ATTRS{idVendor}=="0d28", ATTRS{idProduct}=="0204", MODE="0666"`

to 

`SUBSYSTEM=="usb", ATTRS{idVendor}=="0d28", ATTRS{idProduct}=="0204", MODE="0666"`

for non-root access on CMSIS-DAP HID endpoint.

```
pouze@gouranga ~/projects/gsoc/dist (git)-[master] % pyocd-tool list
0 => Microbit [nrf51] boardId => 9900000043114e4500549001000000490000000097969901
```

### Attach pyOCD to DAPLINK

TBD

## Access micropython repl

Micropython must be in REPL mode, which means there can not
be any piggybacked python file attached to the hex file.

I flashed the `microbit-micropython-e10a5ffdbaf1.hex` file to 
get access the the REPL.

The Freescale KL26Z exposes three interfaces to the microbit via USB:
* Mass Storage Device to drop & flash firmware (in intel hex format)
* CDC UART Pass through from the nRF51 to the host
* CMSIS-DAP (HID) debug interface. Can be used with pyOCD gdbserver for SWD debugging.

If the micropython firmware is flashed, the micropython REPL will be exposed on UART. Baudrate is 115200 Baud.

Screen can be used as a serial terminal:

`screen /dev/ttyACM1 115200`

Exit screen with `^A+k`.

## Access memory from micropython

Micropython provides an interface to the SOC memory via the
`machine` module.

```python
import machine

# Print init address of SP
print(hex(machine.mem32[0x00000000]))
```

## Test NVMC behavior out of micropython repl

Access to the SOCs raw memory is provided by micropython
through the `machine` modules `mem8`, `mem16` and `mem32` properties. The implementation
can be found in the micropython sources in `extmod/machine_mem.c`.

```python
import machine

page_size = 1024
target_page = 254

# Set NVMC CONFIG.EEN
machine.mem32[0x4001E504] = 0x02

# Delete target page
machine.mem32[0x4001E508] = target_page * page_size

# Reset NVMC CONFIG
machine.mem32[0x4001E504] = 0x00

# Verify page erased
for word in range(0, page_size, 4):
    # mem32 returns signed integers, so we test for -1 instead of 0xFFFFFFFF
    if machine.mem32[target_page * page_size + word] != -1:
        print("Bad word")
        print(target_page * page_size + word)
        
# Set NVMC CONFIG.WEN
machine.mem32[0x4001E504] = 0x01
machine.mem32[target_page * page_size] = 123456789
# Reset NVMC CONFIG.WEN
machine.mem32[0x4001E504] = 0x00
if machine.mem32[target_page * page_size] != 123456789:
    print('Write did not succeed')

# Try to write another word without setting write enabled
machine.mem32[target_page * page_size + 4] = 123456789
if machine.mem32[target_page * page_size + 4] != 123456789:
    print('Write did not succeed')
```

From the tests, it was determined that writes without `CONFIG.WEN` will simply not change the value.
Writes to unaligned addresses (using `mem8`) will cause a hard fault.

# Notes 06/26

## Git Muscle Memory

* Show diff of commit compared with parent
  * `git diff $COMMITID^!`

# Notes 06/23

## Git Muscle Memory

### Prepare patch

* Checkout new branch on lastest commit/change 
  that should be in the patch `git checkout -b branchname COMMITID`.
* `git rebase -i HEAD^ or HEAD~NUMBER` to adjust history within the branch
  * Make sure `prefix: ` is added to email titles
* Before sending the patch with `git send-email -#INCLUDECOMMITS`, create a patch with `git format-patch -#INCLUDECOMMITS` and run `scripts/checkpatch.pl patch-file` on it
* `git send-email --subject-prefix "RFC" --cc "Stefan Hajnoczi <stefanha@gmail.com>" --cc "Joel Stanley <joel@jms.id.au>" --cc "Jim Mussared <jim@groklearning.com>" --cc "Julia Suvorova <jusual@mail.ru>" -1`

# Notes 06/22

- NVMC
    - ERASEPCR0 can only be accessed by code running in code region 0. This ids enforced by the MPU 

# Notes 06/21

- Instead of mapping a MMIO device just to read
the FICR data, it would also be possible map a fixed data memory region as ram using `memory_region_init_ram_ptr` (the function does not copy but maps the data passed by `ptr`). Then `memory_region_set_readonly` can be used to make the region readonly.

- Use hmp command `info mtree` to generate a nice memory tree with all the mapped regions

- NRF51 SDK NVMC driver: `vim yotta_modules/nrf51-sdk/source/nordic_sdk/components/drivers_nrf/hal/nrf_nvmc.c`

- SSI Bus API QEMU Synchronous Serial Interface support

- Implementation of a I2C device see `hw/nvram/eeprom_at24c.c` for example

## NVMC

- Write can be conducted word-by-word to CODE or UICR sections.
- Can only be written if it was erased before
- Erasing is conducted on a per-page basis
  - Erasing can be conducted by `address_space_read/write` primitives
- The driver code in `nrf_nvmc.c` checks/pends on the READY / BUSY bits. They need to be implemented.

# Notes 06/20

## Docker

```
docker container ls -- List containers
docker container start microbit_dal -- Start container
docker container attach microbit_dal -- Attach container
docker container stop microbit_dal -- Stop container
docker cp microbit_dal:/bbcmicrobit/build/bbc-microbit-classic-gcc-nosd/source/microbit-micropython . -- Copy from container to host
```


# Notes 06/10

## Copy eclipse cdt project

- Project copy does not work (nullpointer exception)
- Copy project manually in workspace
  - Copy & paste `gpio` project to `newname`
  - `find . -type f -exec sed -i 's/blinky/newname/g' {} +`
  
## Attach serial monitor to stdio
Use the `-serial backend` option to allocate a new 
serial handle (see `serial_parse`, `serial_hd`) and connects 
it to _backend_. The first serial handle allocated will be handle 0.

The NRF51 SOC connects the _UART0_ peripheral instance to the
serial handle 0.  

There are many backends (see `qemu_chr_parse_compat`), including:
- _null_
- _chardev_
- _stdio_
- _pty_

There are also "modifier" (?):
- _mon:_
  - Used together `stdio` will mux this serial handle with the
  monitor
  - Control characters will also be send to the guest, to terminate
  qemu press `Ctrl+a, Ctrl+x`
  
### Examples

Full example running NRF51 UART Loopback example:
```
mqemu -machine microbit -nodefaults -nographic -d unimp \
-kernel /home/pouze/projects/gsoc/test_firmware/uart/_build/fw.out \
-serial mon:stdio
```

## Set up character device

`-chardev socket,path=/tmp/foo.sock,server,nowait,id=foo -device myi2c,chardev=foo`

- Allocate a new character device, connect to _socket_ backend
with parameters `server,nowait` and set id to `foo`
- Allocate a new device of type `myi2c` and set parameter `chardev` to `foo`

## Use of timers

Timers are found in `include/qemu/timers.h`.

`timer_new_ns(QEMU_CLOCK_VIRTUAL, gptm_tick, &s->opaque[0]);`

Important: Thread context of the timer interrupt.
"in icount mode, %QEMU_CLOCK_VIRTUAL timers are run in the vCPU thread. "

=> Important... but i don't know what icount mode is or how to get in there. I just suppose this is true and cross fingers for now.

Timer Control:
- timer_mod
- timer_del

Timer seem to be always one-shot (from reading aspeed/stelaris code).

Examples of usage of timers:
- `hw/timer/aspeed_timer.c`
- `hw/arm/stellaris.c`


## Random

- Use of custom trace event in `trace_aspeed_timer_ctrl_enable(t->id, enable);`

# Notes 06/07

## Chip Variant Attributes

There are **6** chip variants for the NRF51**8**22 noted in the reference
manual. Furthermore, there are variants of the related NRF51**4**22.

The chip code _NRF51XXXPPVVHPYYWWLL_ is made of the following items
### **PP**: Package Code
- **QF**: QFN Package, 48 Pins
- **CD**: WLCSP Package, 56 Pins
- **CE**: WLCSP Package, 62 Pins
- **CF**: WLCSP Package, 62 Pins
  
### **VV**: Variant Code

| Variant  | Flash | RAM | RAM Blocks | RAM Sections |
| --- | --- | --- | --- | --- |
| AA | 256 kB | 16 kB | 2 | 4 |
| AB | 128 kB | 16 kB | 2 | 4 |
| AC | 256 kB | 32 kB | 4 | 8 |

The RAM region is divided into _blocks_. Each block of 8 kB can be indiviual 
powered down by the power managment to save energy.

Each _block_ is made up of two _sections_. Each section of 4 kB has an dedicated 
AHB slave.

Some care should be taken to separate sections used by peripherals and 
allocation of CODE, heap and stack to allow for parallel memory access.




# Notes 06/05

Pomodoros:
  - Apply peripheral stubs from julia
  - Change code to PM proposed layout
  - Add attribute for actual SOC type
  - Map all peripheral MMIO areas systematically

## GDB Muscle Memory
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
```
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
```

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

