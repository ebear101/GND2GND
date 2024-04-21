//ALL CODE IS CONTAINED IN THIS FILE. TO EXPLORE SPECIFIC METHODS, VIEW THE "GND2GND" FOLDER.

#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <math.h>
#include <DFRobotDFPlayerMini.h>

//for GPS
SoftwareSerial mySerial(3, 2); //TX, RX
Adafruit_GPS GPS(&mySerial);

//for speaker
SoftwareSerial mySoftwareSerial(10, 11); //RX, TX
DFRobotDFPlayerMini speaker;

//Define checkpoints (aka turning points)
float checkpoint[][2] = {
{39.867059, -75.503591}, //A
{39.866748, -75.503305}, //B
{39.866951, -75.502873}, //C
{39.866512, -75.502394}, //D
{39.867016, -75.502925}  //E
};

// Define the coordinates of the rooms (where classes are held)
float roomCoordinates[][2] = {
{39.867353, -75.503725},  //A133
{39.86642, -75.503156},    //Chorus
{39.86756, -75.503601},    //A137
{39.867336, -75.502451},   //C131
{39.867059, -75.5024},     //Wrestling Gym
{39.867228, -75.503816}    //A109
};

char c;

void setup() {
  //gps
Serial.begin(9600);
GPS.begin(9600);

GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
delay(1000);

//speaker
mySoftwareSerial.begin(9600);
  Serial.begin(115200);

  if (!speaker.begin(mySoftwareSerial)) {
    Serial.println(F("DFPlayer Mini not found."));
    while (true);
  }

  speaker.volume(1);  // Set volume level (0~30).
  speaker.playMp3Folder(1); // Play the audio file "TestAudio.mp3" in the root directory.
}

/*************************************************************************************************************************/

/*************************************************************************************************************************/

void loop() {

  clearGPS();
  
//speaker.play(3);//for whatever reason, the 2 does not work and it just skips over that index

speaker.play(1);
//Plays 27 files in TF Card
for (int num = 1; num <= 27; num++) {
    speaker.play(num);
    delay(8000);//set the timer to 8 seconds (play a new file every 8 seconds)
}


//Reads GPS
while (!GPS.newNMEAreceived()) {
  c = GPS.read();
}

bool letterDay = false; //G-Day is true and V-Day is false
//At Garnet Valley, there are two "letter days" which determines the schedule. G-Days are different from V-Days and the day alternates from the previous day. 

GPS.parse(GPS.lastNMEA());

int hour = GPS.hour;
//calculate hour from GMT to Eastern Time

if(GPS.hour<=4)//if the time is before 4 AM, add it to 20 (EST is GMT-4)
  hour = 20+GPS.hour;
int min = GPS.minute;
Serial.print(F("Time: "));
Serial.print(hour, DEC);//convert to eastern time
Serial.print(':');
Serial.print(GPS.minute, DEC);
Serial.print(':');
Serial.print(GPS.seconds, DEC);
Serial.print('.');
Serial.println(GPS.milliseconds);
Serial.println(getClassPeriod(letterDay, hour, min));



//Calculates the proper day of the week
if(hour<0)//if eastern time is less than 0 (before midnight) then it's still the previous day
{
  if(GPS.day>1)//if it's the first of the month then the month needs to go down
  {
    int day = GPS.day;
    int month = GPS.month;
    int year = GPS.year;
  }
  else if(GPS.day<1 && GPS.month>1)
  {
    int month = GPS.month-1;
    if(month==1||month==3||month==5||month==7||month==8||month==10||month==12)
      int day = 31;//then you gotta figure out how many days in the month
    else if(month==2)
      int day = 28;
    else
      int day = 30;
    int year = GPS.year;
  }
  else if(GPS.day==1 && month>1)
  {
    int day = GPS.day;
    int month = GPS.month;
    int year = GPS.year;
  }

}
else
{
  int day = GPS.day;
  int month = GPS.month;
  int year = GPS.year;
}

int day = GPS.day;
int month = GPS.month;
int year = GPS.year;

//Prints the date
Serial.print(F("Date: "));
Serial.print(month);
Serial.print(F("/"));
Serial.print(day);
Serial.print(F("/20"));
Serial.println(year);

//String dayOfWeek = getDayOfWeek(GPS.day, GPS.month, GPS.year);
//Serial.println(dayOfWeek); //gets the day of the week using the function that does not currently work


Serial.print("Fix: ");
Serial.print(GPS.fix);
Serial.print(" quality: ");
Serial.println(GPS.fixquality);
Serial.print(F("Satellites: "));
Serial.println(GPS.satellites);




if (GPS.fix) {
  /*Serial.print("Location: ");
  Serial.print(GPS.latitude, 5);
  Serial.print(GPS.lat);
  Serial.print(", ");
  Serial.print(GPS.longitude, 5);
  Serial.println(GPS.lon);*/
  Serial.print(F("Google Maps location: "));
  Serial.print(GPS.latitudeDegrees, 6);
  Serial.print(F(", "));
  Serial.println(GPS.longitudeDegrees, 6);

  Serial.print(F("Speed (MPH): "));
  Serial.println(GPS.speed*1.15078);
  Serial.print(F("Heading: "));
  Serial.println(GPS.angle);
  Serial.print(F("Altitude: "));
  Serial.println(GPS.altitude);

  float lat = GPS.latitudeDegrees;
  float lon = GPS.longitudeDegrees;

  //Determine if the GPS is in the school
  if(inSchool(lat,lon))
    Serial.println(F("In school"));
  else
    Serial.println(F("Not in school"));

  Serial.print(F("Distance from school: "));
  Serial.println(haversine(39.86714, -75.50295, lat, lon));//distance from center of school

  //Serial.println("Wing: "+wing(lat,lon));
  Serial.println("Closest Room: " + closestRoom(lat,lon));

 bool go = true; //user input for the user to verify whether they want directions
 const double d = 15.0;//minimum distance before new direction in feet (remember to account for GPS deviation)
  //Generate directions:
 if(go){
  if(letterDay)
  {//for G-Days
   if(getClassPeriod(letterDay, hour, min)=="Advisory")
   {
     Serial.println(F("The next destination is Concert Choir"));
     Serial.println(F("Turn right and continue for 100 ft"));
     while(haversine(lat,lon,checkpoint[0][0],checkpoint[0][1])>d)//Advisory to A
     {
       Serial.print(F("Continue forwards for "));//Maybe add the audio for distance??
       Serial.print(haversine(lat,lon,checkpoint[0][0],checkpoint[0][1]));
       Serial.println(F(" feet"));
     }
     Serial.println("Turn right and continue for 10 feet");//A to "A"
     Serial.println("Turn left and continue for 150 feet");
     while(haversine(lat,lon,checkpoint[1][0],checkpoint[1][1])>d)//A to B
     {
       Serial.println("Continue forwards for ");//get a timer to repeat this every ~5 seconds
       Serial.print(haversine(lat,lon,checkpoint[1][0],checkpoint[1][1]));
       Serial.println(" feet");
     }
     Serial.println("Turn left and continue for 140 feet");
     while(haversine(lat,lon,checkpoint[2][0],checkpoint[2][1])>d) //B to C
     {
       Serial.println("Continue forwards for ");//get a timer to repeat this every ~5 seconds
       Serial.print(haversine(lat,lon,checkpoint[2][0],checkpoint[2][1]));
       Serial.println(" feet");
     }
     Serial.println("Turn left and continue for 200 feet");
     while(haversine(lat,lon,checkpoint[3][0],checkpoint[3][1])>d) //C to D
     {
       Serial.println("Continue forwards for ");//get a timer to repeat this every ~5 seconds
       Serial.print(haversine(lat,lon,checkpoint[3][0],checkpoint[3][1]));
       Serial.println(" feet");
     }
     Serial.println("Turn right and continue for 180 feet");
     while(haversine(lat,lon,roomCoordinates[1][0],roomCoordinates[1][1]>d)) //D to Chorus
     {
       Serial.println("Continue forwards for ");//get a timer to repeat this every ~5 seconds
       Serial.print(haversine(lat,lon,roomCoordinates[1][0],roomCoordinates[1][1]));
       Serial.println(" feet");
     }
      Serial.println("You have arrived at Concert Choir");
   }
   else if(getClassPeriod(letterDay, hour, min)=="Concert Choir")
   {
     Serial.println("The next destination is Appreciation of Physical Science");
     while(haversine(lat,lon,checkpoint[3][0],checkpoint[3][1])) //Chorus to D
     {
       Serial.println("Continue forwards for ");//get a timer to repeat this every ~5 seconds
       Serial.print(haversine(lat,lon,checkpoint[3][0],checkpoint[3][1]));
       Serial.println(" feet");
     }
     Serial.println("Turn left and continue for 250 feet");
     while(haversine(lat,lon,checkpoint[4][0],checkpoint[4][1])) //D to E
     {
       Serial.println("Continue forwards for ");//get a timer to repeat this every ~5 seconds
       Serial.print(haversine(lat,lon,checkpoint[4][0],checkpoint[4][1]));
       Serial.println(" feet");
     }
     Serial.println("Turn right and continue until C131");
     while(haversine(lat,lon,checkpoint[3][0],checkpoint[3][1])) //E to destination
     {
       Serial.println("Continue forwards for ");//get a timer to repeat this every ~5 seconds
       Serial.print(haversine(lat,lon,roomCoordinates[3][0],roomCoordinates[3][1]));
       Serial.println(" feet");
     }
     Serial.println("You have arrived at C131");
   }


  }
  else//v day
  {
     if(getClassPeriod(letterDay, hour, min)=="Advisory")//go to art
     {
       Serial.println("The next destination is Concert Choir");
       Serial.println("Turn left and continue for 50 feet");
       while(haversine(lat,lon,roomCoordinates[2][0],roomCoordinates[2][1]>d))//Advisory to A137
       {
         Serial.print("Continue forwards for ");//Maybe add the audio for distance??
         Serial.print(haversine(lat,lon,roomCoordinates[2][0],roomCoordinates[2][1]));
         Serial.println(" feet");
       }
       Serial.println("You have arrived at A137");
     }
     else if(getClassPeriod(letterDay, hour, min)=="Intro to Art")//art to Adapted Physical Education
     {
       Serial.println("The next destination is Adapted Physical Education");
       Serial.println("Turn left and continue for 120 feet");
       while(haversine(lat,lon,checkpoint[0][0],checkpoint[0][1])>d)
       {
         Serial.print("Continue forwards for ");
         Serial.print(haversine(lat,lon,checkpoint[0][0],checkpoint[0][1]));
         Serial.println(" feet");
       }
       Serial.println("Turn right and continue for 10 feet");//A to "A"
       Serial.println("Turn left and continue for 150 feet");
       while(haversine(lat,lon,checkpoint[1][0],checkpoint[1][1])>d)//A to B
       {
         Serial.println("Continue forwards for ");//get a timer to repeat this every ~5 seconds
         Serial.print(haversine(lat,lon,checkpoint[1][0],checkpoint[1][1]));
         Serial.println(" feet");
       }
       Serial.println("Turn left and continue for 140 feet");
       while(haversine(lat,lon,checkpoint[2][0],checkpoint[2][1])>d) //B to C
       {
         Serial.println("Continue forwards for ");//get a timer to repeat this every ~5 seconds
         Serial.print(haversine(lat,lon,checkpoint[2][0],checkpoint[2][1]));
         Serial.println(" feet");
       }
       Serial.println("Turn left and continue for 200 feet");
       while(haversine(lat,lon,checkpoint[3][0],checkpoint[3][1])>d) //C to D
       {
         Serial.println("Continue forwards for ");//get a timer to repeat this every ~5 seconds
         Serial.print(haversine(lat,lon,checkpoint[3][0],checkpoint[3][1]));
         Serial.println(" feet");
       }
       Serial.println("Turn left and continue for 120 feet");
       while(haversine(lat,lon,roomCoordinates[4][0], roomCoordinates[4][1])) //C to D
       {
         Serial.println("Continue forwards for ");//get a timer to repeat this every ~5 seconds
         Serial.print(haversine(lat,lon,roomCoordinates[4][0], roomCoordinates[4][1]));
         Serial.println(" feet");
       }
       //Serial.println("You have arrived at the Wrestling Gym");
     }
    
  }
 }

Serial.println("-------------------------------------");
}

void audioDistance(double num)
{
  //plays the appropriate number on speaker based on input.
  //Will say something like "in 150 feet".
  //round to the nearest 5 ft because the GPS is only that precise
  int use = round(num / 5.0) * 5;//number to use
  speaker.play(1); //"in..."

  //as long as they're all in order
  int filesBefore = 1;
  if(use<300)
    speaker.play((use/5)+filesBefore);//record fifty files from  0-300
  else
    speaker.play(60+filesBefore);
}


void clearGPS() {
while (!GPS.newNMEAreceived()) {
  c = GPS.read();
}
GPS.parse(GPS.lastNMEA());




while (!GPS.newNMEAreceived()) {
  c = GPS.read();
}
GPS.parse(GPS.lastNMEA());
}



char wing(float latitude, float longitude) {//returns whichever wing it is in
if ((latitude >= 39.867672 && latitude <= 39.867281) && (longitude >= -75.504065 && longitude <= -75.503424)) {
  return 'A';
} else if ((latitude >= 39.867295 && latitude <= 39.866822) && (longitude >= -75.504019 && longitude <= -75.503341)) {
  return 'A';
} else if ((latitude >= 39.868156 && latitude <= 39.867867) && (longitude >= -75.503161 && longitude <= -75.502458)) {
  return 'B';
} else if ((latitude >= 39.868016 && latitude <= 39.867732) && (longitude >= -75.50366 && longitude <= -75.502834)) {
  return 'B';
} else if ((latitude >= 39.867645 && latitude <= 39.867209) && (longitude >= -75.50344 && longitude <= -75.502998)) {
  return 'B';
} else if ((latitude >= 39.867618 && latitude <= 39.867349) && (longitude >= -75.502987 && longitude <= -75.502644)) {
  return 'C';
} else if ((latitude >= 39.867781 && latitude <= 39.867322) && (longitude >= -75.502885 && longitude <= -75.502051)) {
  return 'C';
} else if ((latitude >= 39.867252 && latitude <= 39.867087) && (longitude >= -75.503046 && longitude <= -75.502485)) {
  return 'C';
} else if ((latitude >= 39.867238 && latitude <= 39.866974) && (longitude >= -75.502477 && longitude <= -75.501756)) {
  return 'D';
} else if ((latitude >= 39.86703 && latitude <= 39.86696) && (longitude >= -75.502863 && longitude <= -75.501769)) {
  return 'D';
} else if ((latitude >= 39.866885 && latitude <= 39.866618) && (longitude >= -75.502166 && longitude <= -75.501622)) {
  return 'D';
} else if ((latitude >= 39.866682 && latitude <= 39.866196) && (longitude >= -75.503542 && longitude <= -75.50244)) {
  return 'M';//music
} else if ((latitude >= 39.866805 && latitude <= 39.866527) && (longitude >= -75.502692 && longitude <= -75.502131)) {
  return 'C';//cafeteria
} else {
  return '?';
}
}




bool inSchool(double latitude, double longitude) {
  // Define the school's latitude and longitude range
  /*
  double schoolLatMin = 39.86626;
  double schoolLatMax = 39.86817;
  double schoolLonMin = -75.50442;
  double schoolLonMax = -75.50132;
*/

  // Check if the input coordinates fall within the school's range
  if (latitude >= 39.86626 && latitude <= 39.86817 &&
      longitude >= -75.50442 && longitude <= -75.50132) {
      return true; // Location is within the school's range
  } else {
      return false; // Location is outside the school's range
  }
}


// Function to determine the closest room
String closestRoom(double latitude, double longitude) {
double minDistance = 999999;  // Initialize with a large value
int closestRoomIndex = -1;

for (int i = 0; i < 6; i++) {
  double distance = sqrt(pow(latitude - roomCoordinates[i][0], 2) + pow(longitude - roomCoordinates[i][1], 2));
  if (distance < minDistance) {
    minDistance = distance;
    closestRoomIndex = i;
  }
}

// Return the closest room name
switch (closestRoomIndex) {
  case 0:
    return "A133";
  case 1:
    return "Chorus";
  case 2:
    return "A137";
  case 3:
    return "C131";
  case 4:
    return "Wrestling Gym";
  case 5:
    return "A109";
  default:
    return "Unknown Room";
}
}


String getNextPeriod(bool letterDay, int hour, int min)//returns the period after the current period
{
 return getClassPeriod(letterDay, hour+1, min+15);
}


String getClassPeriod(bool letterDay, int hour, int min)
{
if(letterDay)//G Day
{
  if(hour==8&&min<=30)
  {//daily
    return "Advisory";
  }
  else if(hour==8&&min>=35)
  {
    return "Concert Choir";
  }
  else if(hour==9&&min<=45)
  {
    return "Concert Choir";
  }
  else if(hour==9&&min>=50)
  {
    return "Appreciation of Physical Science";
  }
  else if(hour==10)
  {
    return "Appreciation of Physical Science";
  }
  else if(hour==11&&min<=35)
  {
    return "Lunch";
  }
  else if(hour==11&&min>35)
  {
    return "Learn";
  }
  else if(hour==12&&min<=10)
  {
    return "Learn";
  }
  else if(hour==12&&min>10)
  {
    return "Reading";
  }
      else if(hour==13&&min<=20)
  {
   return "Reading";
  }
  else if(hour==13&&min>=25)
  {
   return "Math";
  }
  else if(hour==14&&min<=35)
  {
    return "Math";
  }
  else if(hour>8&&hour<15)
  {
    return "Between periods";
  }
  else
  {
   return "Not during school hours";
  }
}




if(!letterDay)//V Day
{
  if(hour==8&&min<30)
  {//daily
    return "Advisory";
  }
  else if(hour==8&&min>=35)
  {
    return "Intro to Art";
  }
  else if(hour==9&&min<=45)
  {
    return "Intro to Art";
  }
  else if(hour==9&&min>=50)
  {
    return "Adapted Physical Education";
  }
  else if(hour==10)
  {
    return "Adapted Physical Education";
  }
  else if(hour==11&&min<=35)
  {
    return "Lunch";
  }
  else if(hour==11&&min>35)
  {
    return "Learn";
  }
  else if(hour==12&&min<=10)
  {
    return "Learn";
  }
  else if(hour==12&&min>10)
  {
    return "Appreciation of Pa";
  }
  else if(hour==13&&min<=20)
  {
   return "Appreciation of Pa";
  }
  else if(hour==13&&min>=25)
  {
    return "Career Readiness";
  }
  else if(hour==14&&min<=35)
  {
    return "Between periods";
  }
  else
  {
    return "Not during school hours";
  }
}
}



String getDayOfWeek(int day, int month, int year) {
tmElements_t tm;
tm.Year = CalendarYrToTm(year);
tm.Month = month;
tm.Day = day;
tm.Hour = 0;
tm.Minute = 0;
tm.Second = 0;
if (makeTime(tm) && weekday() != 0) {
  switch (weekday()) {
    case 1:
      return "Sunday";
    case 2:
      return "Monday";
    case 3:
      return "Tuesday";
    case 4:
      return "Wednesday";
    case 5:
      return "Thursday";
    case 6:
      return "Friday";
    case 7:
      return "Saturday";
    default:
      return "Invalid Day";
  }
} else {
  return "Invalid Date";
}
}

//calculate distance between two GPS coordinates using Haversine formula
double haversine(double lat1, double lon1, double lat2, double lon2) {
  //radius of the Earth in meters
  const double R = 6371000.0;

  // Convert latitude and longitude from degrees to radians
  lat1 *= M_PI / 180.0;
  lon1 *= M_PI / 180.0;
  lat2 *= M_PI / 180.0;
  lon2 *= M_PI / 180.0;

  // Haversine formula
  double dlat = lat2 - lat1;
  double dlon = lon2 - lon1;
  double a = sin(dlat / 2) * sin(dlat / 2) + cos(lat1) * cos(lat2) * sin(dlon / 2) * sin(dlon / 2);
  double c = 2 * atan2(sqrt(a), sqrt(1 - a));
  double distance = R * c;
  // Convert distance from meters to feet
  distance *= 3.28084;
  return distance;
}
