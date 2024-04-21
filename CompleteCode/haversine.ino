//calculate distance between two GPS coordinates using Haversine formula which accounts for the urviture of the Earth which affects longitude.

double haversine(double lat1, double lon1, double lat2, double lon2) {
  //radius of the Earth in meters
  const double R = 6371000.0;

  //Convert latitude and longitude from degrees to radians
  lat1 *= M_PI / 180.0;
  lon1 *= M_PI / 180.0;
  lat2 *= M_PI / 180.0;
  lon2 *= M_PI / 180.0;

  //Haversine formula
  double dlat = lat2 - lat1;
  double dlon = lon2 - lon1;
  double a = sin(dlat / 2) * sin(dlat / 2) + cos(lat1) * cos(lat2) * sin(dlon / 2) * sin(dlon / 2);
  double c = 2 * atan2(sqrt(a), sqrt(1 - a));
  double distance = R * c;
  //convert distance from meters to feet
  distance *= 3.28084;
  return distance;
}
