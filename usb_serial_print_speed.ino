// Simple test of Serial.print() speed.  How many lines/sec can your
// Arduino board print to the serial monitor?

// This combination of printing text and numbers is meant to test the
// most common way Serial printing is used with Arduino.

// On true serial boards, this test measures how much of the bandwidth
// of a high baud rate can really be used.  Efficiency copying bytes
// into the transmit buffer, and the serial transmit interrupt, are
// the main factors.

// On native USB boards, this test measures how well the USB stack can
// utilize the USB bandwidth.  USB is fast but complex protocol.  This
// test tends to measure how well optimized the USB code is.  For
// 12 Mbit/sec (full speed) USB, 36848 is the theoretical maximum
// lines/sec.  For 480 Mbit/sec (high speed) USB, 1521371 is the
// theoretical maximum lines/sec speed.  Unlike ordinary serial, your
// operating system and its drivers, the type of USB port, whether a
// USB hub is used, and CPU load on your computer can affect the speed.

uint32_t count, prior_count;
uint32_t prior_msec;
uint32_t count_per_second;

// Uncomment this for boards where "SerialUSB" needed for native port
//#define Serial SerialUSB

void setup() {
  Serial.begin(1000000); // edit for highest baud your board can use
  while (!Serial) ;
  count = 10000000; // starting with 8 digits gives consistent chars/line
  prior_count = count;
  count_per_second = 0;
  prior_msec = millis();
}

void loop() {
  Serial.print("count=");
  Serial.print(count);
  Serial.print(", lines/sec=");
  Serial.println(count_per_second);
  count = count + 1;
  uint32_t msec = millis();
  if (msec - prior_msec > 1000) {
    // when 1 second as elapsed, update the lines/sec count
    prior_msec = prior_msec + 1000;
    count_per_second = count - prior_count;
    prior_count = count;
  }
}

