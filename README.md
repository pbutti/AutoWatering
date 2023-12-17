# AutoWatering


# Connecting the relay

## Led Side
On the led side you have 3 pins marked as "S" "+" and "-". 

1) Connect S to the GPIO / DIGITAL pin for controlling the relay circuit.
2) Connect "+" to 5V and "-" to GND.

## Output side
3) Connect the center pin to voltage (in my case 5V)
5) Connect the pin on the same side as the "-" pin to the pump. 

```
EXAMPLE
GPIO ===> S  |_____| ===> FREE
5V   ===> +  |Relay| ===> V
GND  ===> -  |_____| ===> PUMP +DC
```
