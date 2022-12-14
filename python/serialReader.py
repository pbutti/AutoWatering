import serial
import time
import argparse

def read(device):
    data = device.readline()
    return data.decode()


def main():

    parser = argparse.ArgumentParser(
        formatter_class = argparse.ArgumentDefaultsHelpFormatter,
        description="")
    parser.add_argument('-d', '--device',default="/dev/tty.usbmodem14201",help="serial device to read from")


    args = parser.parse_args()
    
    baud = 9600
    interface = args.device # Vale's adapter
    timeout = .1
    arduino_serial = serial.Serial(port=interface, baudrate=baud, timeout=timeout)
    
    
    while True:

        #Check if incoming bythes are waiting to be read from the serial input
        if (arduino_serial.in_waiting >  0):
            value = read(arduino_serial)
            print(value)

        #Sleep 10ms to let other threads run
        time.sleep(0.01)


if __name__ == "__main__":
    main()
