# Stopping and Starting Animations

Sometimes you might one to run one animation sequence once, do something else then start another animation sequence.


## Defining the sequences

This example sequence is for AlaLedRgb. With AlaLed you don't specify palettes.

```
AlaSeq seq1[] = 
{ 
  { ALA_OFF,            1000, 2000, alaPalNull }, 
  { ALA_ON,             1000, 2000, alaPalRgb }, 
  { ALA_SPARKLE,        1000, 9000, alaPalRgb }, 
  { ALA_CYCLECOLORS,    3000, 6000, alaPalRgb }, 
  { ALA_OFF,            1000, 1000, alaPalNull }, 
  { ALA_STOP,           1000, 1000, alaPalNull}, 
  {ALA_ENDSEQ} 
}; 
```

NOTE: ALA_STOP has a speed and duration specified. If you intend to break out of the animation sequence the values don't matter
since the break-out occurs immediately. However, if you don't break out of the animation loop ALA_STOP has the side effect of freezing the 
previous animation - which may or may not be desireable. The ALA_OFF turns the LEDs off - you can shorten the duration rather than wait 1000 ms.

## setup()


The setup() method does NOT set the initial animation sequence
```
void setup()
{
  Serial.begin(9600);
  delay(100); // some arduinos need it
  
  Serial.println("\nAnimation sequences starting.\n");

  // 24 leds driven by pin 11
  rgbStrip.initWS2812(24, 11);
  rgbStrip.setBrightness(0x444444);

}
```

## running the animation

This bare-bones method is all that is needed to run the animation sequence till it stops.

```
void doAnimation(AlaSeq seq[])
{
  rgbStrip.reset();	// clears the stoppedFlag
  rgbStrip.setAnimation(seq);

  while(1)
  {
  rgbStrip.runAnimation();
  if (rgbStrip.getStoppedFlag()) break;
  }
}
```

## loop()

In your loop() method, assuming your have 3 animation sequences (se1,seq2,seq3) you can call your animation sequences like this:-

```
void loop()
{
  doAnimation(seq1);
  
  // Do something here after seq1 has finished
  
  doAnimation(seq2);
  
  //Do something here after seq2 has finished
  
  doAnimation(seq3);
  
  //Do something here after seq3 has finished
}
```

This would allow you to change animation sequence based on some input.
