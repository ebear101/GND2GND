//Given the time/date, determines the current class period according to schedule

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

