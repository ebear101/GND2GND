//In progress... prints the appropriate file for a given distance rounded to 5 feet

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
