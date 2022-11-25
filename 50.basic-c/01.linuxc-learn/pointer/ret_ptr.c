#include <string.h>
#include "ret_ptr.h"

static const char *msg[] = {
  "Sunday",
  "Monday",
  "Tuesday",
  "Wednesday",
  "Thursday",
  "Friday",
  "Saturday"
};

char *get_a_day(int index) {
  static char buf[20];

  strcpy(buf, msg[index]);

  return buf;
}
