//Determines the next class period by adding a full period length (1:15) to the time

String getNextPeriod(bool letterDay, int hour, int min)//returns the period after the current period
{
 return getClassPeriod(letterDay, hour+1, min+15);
}
