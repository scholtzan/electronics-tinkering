#basiert auf: http://www.lima-city.de/thread/makefile-fuer-avr-gcc
#CFILE.c enthaelt den Code. 
CFILE=main
#Type des AVR
AVRTYPE=attiny2313

compile:
	avr-gcc -mmcu=$(AVRTYPE) -O2 $(CFILE).c -o $(CFILE).o

write:
	avr-objcopy -j .text -j .data -O ihex $(CFILE).o $(CFILE).hex
	avrdude -V -p $(AVRTYPE) -c stk600 -P /dev/cu.SLAB_USBtoUART -U flash:w:$(CFILE).hex

clean:
	rm $(CFILE).hex $(CFILE).map $(CFILE).o $(CFILE).out