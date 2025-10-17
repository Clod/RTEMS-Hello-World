# RTEMS-Hello-World


Senses the blue pushbutton of the board and sends a string through UART when it is pressed.

Ae the project uses rtems_waf submodule you can either clone if with:

% git clone --recurse-submodules https://github.com/Clod/RTEMS-Hello-World.git

or clone it as usual with:

% git clone https://github.com/Clod/RTEMS-Hello-World.git

and then update submodule with:

% cd RTEMS-Hello-World
% git submodule update --init

To build the project do:

$ ./waf configure --rtems=/opt/rtems/6.1 --rtems-bsp=arm/nucleo-h743zi

and then:

$ ./waf

Then copy the exe file to the host computer to flash the test board.

% cp build/arm-rtems6-nucleo-h743zi/hello.exe /out/hello.elf

Note: /out is automagically maped to users $HOME/rtems-out folder in the host computer.
If it does not exist, it gets created.

In MAC in order to check UART output use screen command:

Example:

% screen /dev/tty.usbmodem11303 115200