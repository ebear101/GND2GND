//Determines the wing (section of school) that the device is in based on coordinate input

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
