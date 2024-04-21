//Determine the day of the week based on the date

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
