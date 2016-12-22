/*
 * Lora's New Years Eve Dress
 * 
 * Lights react to sound. Louder and more intense sounds make
 * dress light up brighter colors and flash more frequently.
 * 
 * v0.1 Base version
 * 
 */

#include <Adafruit_NeoPixel.h>
#include <math.h>
 
#define N_PIXELS  10  // Number of pixels in strand
#define MIC_PIN   A0  // Microphone is attached to this analog pin
#define LED_PIN    4  // NeoPixel LED strand is connected to this pin
#define SAMPLE_WINDOW   10  // Sample window for average level
#define INPUT_FLOOR 10 //Lower range of analogRead input
#define INPUT_CEILING 300 //Max range of analogRead input, the lower the value the more sensitive (1023 = max)

unsigned int sample;
 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {

  Serial.begin(38400);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

}

void loop() {

  unsigned long startMillis= millis();  // Start of sample window
  float peakToPeak = 0;   // peak-to-peak level
 
  unsigned int signalMax = 0;
  unsigned int signalMin = 1023;
  unsigned int c, y;
 
 
  // collect data for length of sample window (in mS)
  while (millis() - startMillis < SAMPLE_WINDOW)
  {
    sample = analogRead(MIC_PIN);
    if (sample < 1024)  // toss out spurious readings
    {
      if (sample > signalMax)
      {
        signalMax = sample;  // save just the max levels
      }
      else if (sample < signalMin)
      {
        signalMin = sample;  // save just the min levels
      }
    }
  }
  peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
 
  Serial.println(peakToPeak);

}
