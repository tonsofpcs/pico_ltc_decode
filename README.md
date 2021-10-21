# LTC Decoder
# for Raspberry Pi Pico

* Reads LTC and outputs hex right now.  I think the bit order is flipped the whole way?  Trying to decode to usable values.  ~~2021-10-21 EJA
* LTC input on pin 5 (GP3)

* I set up my toolchain following: https://shawnhymel.com/2096/how-to-set-up-raspberry-pi-pico-c-c-toolchain-on-windows-with-vs-code/ but using mingw64 instead of mingw32

* I build by opening a Windows command prompt terminal in VSCode and running the lines in .env manually, making a build folder, going into that folder and running ``cmake -G "MinGW Makefiles" ..``.  Once that's done, I run ``make`` (which runs the batch file that runs mingw32make).  
* I've noticed sometimes this gets angry at a preprocessor -- just delete the build folder, run cmake again, then run make again and it's happy. 