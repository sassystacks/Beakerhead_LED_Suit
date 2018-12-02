# import libraries
import RPi.GPIO as GPIO
import time
import os
from stream_fuckedWith import list_muses, stream
import pygatt

# Set the mode to board (see raspberry pi pinout)
GPIO.setmode(GPIO.BOARD)

# Set the button pin
buttonPin = 16

# initialize the button pin, use the internal resistor for a pull up/ pulldown resistor
GPIO.setup(buttonPin, GPIO.IN, pull_up_down=GPIO.PUD_UP)

# initialize button state
buttonState = True

# test counter
count = 0
# wait for the button to be pressed
while buttonState == True:

    # Check the state of the button
    buttonState = GPIO.input(buttonPin)


print("Starting main loop")


# send start command from RPI
os.system('python3 ~/MyProjects/Beakerhead/rpi-rf/scripts/rpi-rf_send 5')
os.system('python3 ~/MyProjects/Beakerhead/rpi-rf/scripts/rpi-rf_send 4')

startSongTime = time.time()

# look for muse
muses = list_muses()

# if a muse is found connect to it
if muses:
    addrs = muses[0]['address']

# connect to muse and wait until the part of song to transmit
stream(addrs, (startSongTime))

# End song maybe a timer?
os.system('python3 ~/MyProjects/Beakerhead/rpi-rf/scripts/rpi-rf_send 7')
