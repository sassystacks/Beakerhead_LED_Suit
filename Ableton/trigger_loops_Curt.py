from simplecoremidi import send_midi
from time import sleep
import mido
import serial


started_song = 0
while 1:
    try:
        ser = serial.Serial('/dev/cu.usbmodem1421', 9600)
        bytesToRead = ser.inWaiting()
        x = ser.readline()
    except:
        print('No Arduino detected!')
        sleep(1)
        continue
        #print(x)

    if x:
        if int(float(x)) == 4 and not started_song:
            started_song = 1
            print('Playing song!!')
        elif int(float(x)) == 4 and started_song:
            x = 0
            print('Song already started...')
        elif int(float(x)) == 0 and not started_song:
            print('No message received.')
        elif int(float(x)) == 0 and started_song:
            print('Song is playing...')
        else:
            print('Triggering loop number', int(x))

        msg = mido.Message('note_on', note=59 + int(float(x )))
	
	
        #print('Sending MIDI message: ' + str(msg.note))
        send_midi(msg.bytes())
