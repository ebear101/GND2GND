# GND2GND GPStick documentation can be found [here](https://docs.google.com/document/d/1__1h7gW_0Egsf5SJsRBOKp1m6WEZ-hCyr1FRJ5fe9_U/edit?usp=sharing)
## Background
  The GPStick is designed to use an [Arduino Uno Rev3](https://store.arduino.cc/products/arduino-uno-rev3) to take input from the [Adafruit Ultimate GPS Breakout](https://www.adafruit.com/product/746) and output GPS directions with a [DFPlayer Mini](https://wiki.dfrobot.com/DFPlayer_Mini_SKU_DFR0299) and TF Card connected to a 3W 8Ohm speaker. It is all encapsulated into a custom-made laser-cut wooden box to be attached to a walking stick. Read more about the design in the [documentation](https://docs.google.com/document/d/1__1h7gW_0Egsf5SJsRBOKp1m6WEZ-hCyr1FRJ5fe9_U/edit?usp=sharing).
# Features
**Audio**
- Plays the first audio file in the TF Card in DFPlayer
- Capable of parsing through sound files in TF Card for a given duration for each file
**GPS**
- Prints time in Eastern Time
- Prints the accurate date
- Prints whether the satellite receives a fix (receiving adequate location data)
- Prints the fix quality
- Prints the present number of satellites\
\
**If there is a satellite fix...**
- Prints location coordinates in Google Maps format
- Prints the calculated speed in MPH of the device
- Determines if the location is in the school with method `inSchool(lat,lon)`
- Calculates the distance from school with `haversine(lat1,lon1,lat2,lon2)` _...more on that later_
- Determines the next class based on time/schedule
- Generates and prints directions to the next class, including calculated distances from the next turn (checkpoint)
- Determines the "wing" (section of school) that the device is in
- Determines the closest room based on coordinate input
- Calculates the day of the week based on date
