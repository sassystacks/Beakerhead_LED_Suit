# import libraries
import RPi.GPIO as GPIO
import time
import os
#from muselsl import list_muses
from stream_fuckedWith import list_muses, stream
import pygatt

# Set the mode to board (see raspberry pi pinout)
GPIO.setmode(GPIO.BOARD)

# Set the button pin
buttonPin = 16

# initialize the button pin, use the internal resistor for a pull up/ pulldown resistor
GPIO.setup(buttonPin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

# initialize button state
buttonState = False

# test counter
count = 0
# wait for the button to be pressed
while buttonState == False and count < 10:

    # Check the state of the button
    buttonState = GPIO.input(buttonPin)

    print " Checked button"

    # if the button is pressed break loop
    if buttonState == True:
        break
    count = count + 1


# send start command from RPI
os.system('python3 ~/MyProjects/Beakerhead/rpi-rf/scripts/rpi-rf_send 4')


# look for muse
muses = list_muses()

# if a muse is found connect to it
if muses:
    addrs = muses[0]['address']
import pdb
pdb.set_trace()

# connect to muse and wait until the part of song to transmit
stream(addrs, 10)

# End song maybe a timer?
