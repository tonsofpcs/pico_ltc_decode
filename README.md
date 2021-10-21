# LTC Decoder
# for Raspberry Pi Pico

* Reads LTC and outputs hex right now.  I think the bit order is flipped the whole way?  Trying to decode to usable values.  ~~2021-10-21 EJA

* I set up my toolchain following: https://shawnhymel.com/2096/how-to-set-up-raspberry-pi-pico-c-c-toolchain-on-windows-with-vs-code/ but using mingw64 instead of mingw32

* I build by opening a Windows command prompt terminal in VSCode and running the lines in .env manually, making a build folder, going into that folder and running ``cmake -G "MinGW Makefiles" ..``.  Once that's done, I run ``make`` (which runs the batch file that runs mingw32make).  
* I've noticed sometimes this gets angry at a preprocessor -- just delete the build folder, run cmake again, then run make again and it's happy. 

# To install and run
* Hold down the button when plugging the Pi Pico into your computer.  
* Copy the uf2 file over.  It will start running immediately.  On first run your (windows) computer may install some USB drivers.  
* To start the program running over, unplug and replug USB without holding the button. 
* Connect with Putty (or other serial terminal software) to the serial port added in device manager at 115200 bps.  If you connect within the first 10 seconds you will see "Hello..." a few times (once per second).  
* Feed LTC into pin 5 using some method to drive input +3v3/0.  I built a comparator circuit using an LM393.  

# Comparator Circuit
* Feed 3v3 from Pi Pico to pin 8 of LM393
* Connect Ground from Pi Pico to pin 4 of LM393
* Connect LTC+ (or unbalanced) to pin 3 of LM393
* Connect signal ground (and LTC-) to pin 4 of LM393. 
* Connect pin 4 and pin 2 of LM393 (pin 2 to ground)
* // Tie unused inputs pins to ground per LM393 spec sheet //
* Connect pin 1 of LM393 to pin 5 (GP3) of Pi Pico