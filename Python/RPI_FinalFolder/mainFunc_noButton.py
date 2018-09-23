# import libraries
import time
import os
from stream_fuckedWith import list_muses, stream
import pygatt


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
