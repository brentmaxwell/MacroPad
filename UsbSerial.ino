String commandString = "";
bool stringComplete = false;

void loopSerial() {
  while (Serial.available()) {

    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      stringComplete = true;
    } else {
      commandString += inChar;
    }
  }
  if (stringComplete) {
    if (commandString.startsWith("Date")) {
      String dateTime;
      String date;
      String time;
      String year;
      String month;
      String day;
      String hour;
      String minute;
      String second;
      get_token(commandString, dateTime, 1, ' ');
      get_token(dateTime, date, 0, 'T');
      get_token(dateTime, time, 1, 'T');
      get_token(date, year, 0, '-');
      get_token(date, month, 1, '-');
      get_token(date, day, 2, '-');
      get_token(time, hour, 0, ':');
      get_token(time, minute, 1, ':');
      get_token(time, second, 2, ':');
      if (!dateTimeSet) {
        rtc.begin(DateTime(year.toInt(), month.toInt(), day.toInt(), hour.toInt(), minute.toInt(), second.toInt()));
        dateTimeSet = true;
      } else {
        rtc.adjust(DateTime(year.toInt(), month.toInt(), day.toInt(), hour.toInt(), minute.toInt(), second.toInt()));
      }
    }
    commandString = "";
    stringComplete = false;
  }
}

bool get_token(String &from, String &to, uint8_t index, char separator) {
  uint16_t start = 0, idx = 0;
  uint8_t cur = 0;
  while (idx < from.length()) {
    if (from.charAt(idx) == separator) {
      if (cur == index) {
        to = from.substring(start, idx);
        return true;
      }
      cur++;
      while ((idx < from.length() - 1) && (from.charAt(idx + 1) == separator)) idx++;
      start = idx + 1;
    }
    idx++;
  }
  if ((cur == index) && (start < from.length())) {
    to = from.substring(start, from.length());
    return true;
  }
  return false;
}