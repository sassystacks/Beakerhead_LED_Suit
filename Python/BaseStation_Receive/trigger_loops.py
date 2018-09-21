from simplecoremidi import send_midi
from time import sleep
import mido
import serial


while 1:
    ser = serial.Serial('/dev/cu.usbmodem1411', 9600)
    bytesToRead = ser.inWaiting()
    x = ser.readline()

    print(x)


    if x:


        msg = mido.Message('note_on', note=59 + int(float(x )))

        print('Sending MIDI message: ' + str(msg.note))
        send_midi(msg.bytes())
