# Introduction 
Plant Watering System is a DIY Automatic Micro Home Drip Irrigation Watering System.
It is a simple and cheap DIY system to automatically water a plant using 
- a Soil Moisture Sensor, to detect if soil is dry and needs watering (or not),
- a small pump, to pump water to the plant when needed,
- a transistor to boost the power to the required level for the pump
- a cheap and power efficient micro controller (MCU) to activate the pump when needed
- a (USB) power bank to power the MCU and pump
- and this small piecce of code which runs on the micro controller and with it the amount of water can be finetuned.


# Getting Started
1. Buy components
To setup such a system for yourself you need the mentioned components. 
Easiest and probably cheapest way to get most of the components in one buy is getting an 'Automatic Watering System Kit', like:
[Aliexpress](https://www.aliexpress.com/item/1005003092397460.html?spm=a2g0o.productlist.0.0.76a2273eWvJQFe&algo_pvid=e7e86a76-c40e-402d-901a-dcb389c79a8f&algo_exp_id=e7e86a76-c40e-402d-901a-dcb389c79a8f-6&pdp_ext_f=%7B%22sku_id%22%3A%2212000024031784013%22%7D&pdp_pi=-1%3B3.44%3B-1%3B-1%40salePrice%3BEUR%3Bsearch-mainSearch) or
[Amzon](https://www.amazon.com/WayinTop-Automatic-Irrigation-Watering-Capacitive/dp/B07TLRYGT1/ref=sr_1_24?crid=3L9IK859UHVNY&keywords=Automatic+Watering+System+Kit&qid=1645360150&sprefix=automatic+watering+system+kit%2Caps%2C131&sr=8-24)
I got mine for less then 2 euro on Aliexpress, but I see the prices are almost doubled now.

Additional you need:
- TO-220 NPN Transistor (or you could use a relais to power the pump)
- Micro controller, I used the power efficient NodeMCU ESP8266 wifi module

2. Setup the circuit
![Schema](/Images/Schema.png)

Connect the Moisture sensor to the signal adapter
Connect ESP8266 to the signal adapter:
- ESP8266 A0  = the analoge output of signal adapter (A0)
- ESP8266 D5  = the digital output signal adapter (D0, LOW for wet and HIGH for dry)
- ESP8266 GND = the ground of signal adapter (GND)
- ESP8266 3v3 = the power of signal adapter (VCC)

Connecet motor via T-220 transistor
- ESP8266 D6  = Output to drive the motor (true=on / false=off), connect to transistor pin 1(left)
- ESP8266 3v3 = power to transitor (pin 2, middle)
- ESP8266 GND = ground (black wire) of motor.
-               pin 3 of transistor to power (red wire) of motor

[pin layout ESP8266](https://i2.wp.com/randomnerdtutorials.com/wp-content/uploads/2019/05/ESP8266-NodeMCU-kit-12-E-pinout-gpio-pin.png?resize=817%2C542&quality=100&strip=all&ssl=1)


3.	Installation process
Download the source code in this repro and compile it using Arduino IDE


# Build and Test
Connect the ESP8266 via USB, verify the COM port and select it in Arduio IDE
Download the software and check the Serial port monitor for the output.
Fine tune code where needed.. 

# Contribute
Wishlist to improve this system:
- use less power (activate sleep mode; and wake up every 2 hours, and do a check within 30 secs and go to sleep again)
- use a solar cell to power the system (and a small battery of 2 18650 batery cells)  
- send measured moisture via WIFI to central system
- measure water level , and send also via WIFI
