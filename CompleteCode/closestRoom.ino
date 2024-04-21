//Function to determine the closest room from a given set of coordinates
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
