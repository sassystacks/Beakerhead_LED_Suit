from simplecoremidi import send_midi
from time import sleep, clock, time
import mido
import serial


started_song = 0
t_x = 0 # created a variable to keep loops running if transmission cuts out

init_time = 0
current_time = 0
endTime = 167

while int(current_time) < endTime:
    try:
        ser = serial.Serial('/dev/cu.usbmodem1421', 9600)
        bytesToRead = ser.inWaiting()
        x = ser.readline()
    except:
        print('No Arduino detected!')
        sleep(1)
        continue
        #print(x)
        
    if int(float(x)) == 5:
        started_song = 0
        print('Song has reset')
    
    if not x:
        x = t_x

    if x:
        
        if int(float(x)) == 4 and not started_song:
            init_time = time()
            sleep(2.3)
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

        msg = mido.Message('note_on', note=59 + int(float(x)))
	
	
        #print('Sending MIDI message: ' + str(msg.note))
        send_midi(msg.bytes())
        
        currentTime = time() - init_time
        t_x = x

    if round(currentTime) % 10 == 0:
        print(currentTime)


