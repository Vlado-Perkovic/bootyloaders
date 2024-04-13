# KRAKEN HUNT

## Table of Contents
- [Introduction](#introduction)
- [Installation](#installation)
- [Doxygen](#doxygen-docs) 
- [Usage](#usage)

## Introduction
Hello! This is repository for a game Kraken Hunt. It's made for BL DevKit with esp32 microcontroller.

## Installation

Build and run

Clone this project and run `git submodule update --init --recursive`.
Apply the patch for lvgl_esp32_drivers submodule to update it to LVGL 8.3. by positioning yourself in the 
components/lvgl_esp32_drivers directory and running `git apply ../lvgl_esp32_drivers_8-3.patch`.

Configure the project:

If you are using the Byte Lab Development Kit, copy sdkconfig.defaults over sdkconfigs (`cp sdkconfig.defaults sdkconfig`).

Set up required environmental variables using the `. $HOME/esp/esp-idf/export.sh` command.
Build the project with `idf.py build`.
Flash the project with `idf.py flash /dev/ttyUSB0`. Make sure to use the appropriate USB path. 

❗  If the Byte Lab Development Kit is used, TCH_IRQ switch on the peripheral module must be OFF.

Monitor the projects output with `idf.py monitor /dev/ttyUSB0`.

## Doxygen docs
The repo provides a Doxyfile for generating the documentation. You need to install doxygen and run `doxygen Doxyfile`. This will create a directory docs/ with html and latex documentation of the project.


## Usage

Once the game is loaded your typical startup would be to:
1) Plug in your DevKit.
2) After bootup you should PROVISION your device onto your network of choice. That is done by clicking the *CHANGE NETWORK* option.
3) Once the device is provisioned, the status in the top left corner of the screen should say "WIFI CONNECTED" and you are ready to start the game.
4) After this point when you reboot the network credentials should be available which will be signaled by the status "WIFI AVAILABLE". In that case you should just click on the *CONNECT* button to connect to the network.
5) You can always reprovision to another network if you choose so, note that the game cannot be started without wifi connection.


Playing the game:
The goal is to kill the kraken without getting too close, otherwise the kraken eats you.
In the main screen you can move freely with the joystick in 8 directions and monitor your position change with the coordinates
displayed on the screen. You can bring up the map with __BUTTON 3__ and see the positions of your submarine and the kraken but note that when you do that, you cannot move or use weapons. Speaking of weapons, in the main screen you choose between torpedos, nets and lights with __BUTTON 2__ and __BUTTON 4__. 

When you come within the 10 m range, you can fire a net which traps the kraken and ensures that the torpedo will land, otherwise its roughly a 30% chance of hitting the torpedo. By the way, torpedos have a range of only about 8 m. If you come too close tho, for example, closer than 6 m, you get eaten.

On game end you will get a notification of the result. Pressing any of the buttons restarts the game. Also, on the top left of the screen there is a red button which you can press that takes you back to the starting screen.

__HAPPY HUNTING!__
