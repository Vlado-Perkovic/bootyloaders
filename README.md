# BOOTYLOADERS 

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


