import RPi.GPIO as GPIO
from lib_nrf24 import NRF24
import time
import spidev
import pdb

GPIO.setmode(GPIO.BCM)

pipes = [[0xE8, 0xE8, 0xF0, 0xF0, 0xE1], [0xF0, 0xF0, 0xF0, 0xF0, 0xE1]]

radio = NRF24(GPIO, spidev.SpiDev())
radio.begin(0, 17)

radio.setPayloadSize(32)
radio.setChannel(0x76)
radio.setDataRate(NRF24.BR_1MBPS)
radio.setPALevel(NRF24.PA_MIN)

radio.setAutoAck(True)
radio.enableDynamicPayloads()
radio.enableAckPayload()

radio.openReadingPipe(1, pipes[1])
radio.printDetails()
radio.startListening()

'''Initialization'''
imu_data = []
dataread_interval = 5
curent_time = time.time()

while(1):
    # ackPL = [1]
    while not radio.available(0):
        time.sleep(1 / 100)
    receivedMessage = []
    radio.read(receivedMessage, radio.getDynamicPayloadSize())
    print("Received: {}".format(receivedMessage))

    #adding data to the dictionary
    if(time.time()-curent_time>=dataread_interval):
        curent_time = time.time()
        accel_x = (float(receivedMessage[1])*256+float(receivedMessage[0]))/100
        accel_y = (float(receivedMessage[3]) * 256 + float(receivedMessage[2])) / 100
        accel_z = (float(receivedMessage[5]) * 256 + float(receivedMessage[4])) / 100
        imu_data.append([curent_time, accel_x, accel_y, accel_z])
        print("data saved in imu_data:")
        print([curent_time, accel_x, accel_y, accel_z])