import serial
import time
import argparse
import sys

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
        cmd = input("Insert command for arduino... ")
        if (cmd == "exit"):
            sys.exit()
        arduino_serial.write(cmd.encode('ascii'));
    

if __name__ == "__main__":
    main()
