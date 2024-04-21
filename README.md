# GND2GND GPStick | Beaver Works [MIT Beaver Works CRE[AT]E Challenge](https://sites.google.com/view/beaver-works-assistive-tech/create-challenge/the-challenge)
## Full documentation for our project can be found [here](https://docs.google.com/document/d/1__1h7gW_0Egsf5SJsRBOKp1m6WEZ-hCyr1FRJ5fe9_U/edit?usp=sharing)
# Background
  The GPStick is designed to use an [Arduino Uno Rev3](https://store.arduino.cc/products/arduino-uno-rev3) to take input from the [Adafruit Ultimate GPS Breakout](https://www.adafruit.com/product/746) and output GPS directions with a [DFPlayer Mini](https://wiki.dfrobot.com/DFPlayer_Mini_SKU_DFR0299) and TF Card connected to a 3W 8Ohm speaker. It is all encapsulated into a custom-made laser-cut wooden box to be attached to a walking stick. Read more about the design in the [documentation](https://docs.google.com/document/d/1__1h7gW_0Egsf5SJsRBOKp1m6WEZ-hCyr1FRJ5fe9_U/edit?usp=sharing).
# Features
## Audio
- Plays the first audio file in the TF Card in DFPlayer
- Capable of parsing through sound files in TF Card for a given duration for each file\
\
## GPS
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

# Files
## CompleteCode Functions
- audioDistance _In progress... prints the appropriate file for a given distance rounded to 5 feet_
- closestRoom _Function to determine the closest room from a given set of coordinates_
- getClassPeriod _Given the time/date, determines the current class period according to schedule_
- getDayOfWeek _Determine the day of the week based on the date_
- getNextPeriod _Determines the next class period by adding a full period length (1:15) to the time_
- haversine _Calculates distance between two GPS coordinates using Haversine formula which accounts for the urviture of the Earth which affects longitude._
- inSchool _Determines whether a given set of coordinates is within the bounds of the school_
- wing _Determines the wing (section of school) that the device is in based on coordinate input_

## TestingData Explanation
This folder contains the raw data acquired from testing the capabilities of the GPS device.

NMEA_DATA contains all NMEA sentences from a jaunt on the road. 
We calculated and interpreted the data accordingly to conclude that the data was accurate to the correct side of the road 88% of the time. 
Coordinates toward the end are 100% precise, though on the incorrect side of the road. 
On a typical 12 ft lane road, the GPS can adequately determine the proper side and is thus effectively 88% precise to 12 feet.
In addition to the NMEA sentences, the spreadsheet contains the time it took for the GPS to properly output the date, time, and coordinates.

- PrecisionData lists 29 tests of the GPS device with 5-7 coordinates taken each time. Coordinates were taken and compared to a known location. The average precision for the 29 trials was calculated to be 3.35 meters or 11.0 feet.

- RoomAndCheckpoint_Coordinates lists the coordinates of each of the desired rooms and coordinates

- RoomToRoom_withCheckpoints lists the simplistic route from checkpoint to locations

- WingCoordinates lists the bounds of each of the wings from the top left to top right

## Audio Explanation
- All audio files used in the device have been uploaded into the folder "Audio"
- An Audacity project (.aup) has been added to view annotations on audio and explore sound data
- Files are meant to be used by a future function to interpret date and time
- Audio should be uploaded in the order listed, as it will be read and parsed by the DFPlayer in that particular order
