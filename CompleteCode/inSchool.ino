//Determines whether a given set of coordinates is within the bounds of the school.

bool inSchool(double latitude, double longitude) {
  // Check if the input coordinates fall within the school's range
  if (latitude >= 39.86626 && latitude <= 39.86817 &&
      longitude >= -75.50442 && longitude <= -75.50132) {
      return true; // Location is within the school's range
  } else {
      return false; // Location is outside the school's range
  }
}
