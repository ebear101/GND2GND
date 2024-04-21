//Prints all GPS information each second (can be changed) and calls the speaker once.

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
