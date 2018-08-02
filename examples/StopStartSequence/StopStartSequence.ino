///////////////////////////////////////////////////////////////////////////////////////////
//
// Using ALA_STOP animation to terminate a sequence.
//
// Example to demonstrate how to play an animation sequence, stop it, do something else
// start a new sequence and so on.
//
// ALA_STOP is (normally) added to the end of a sequence. Although you can specify a speed, duration and palette
// these are ignored. ALA_STOP immediately sets a stoppedFlag which can be tested (getStoppedFlag())and used
// to terminate the animation loop. If you don't break out of the loop the animation will continue to run for
// the specified duration. Meanwhile the LEDs will be frozen in their last state before ALA_STOP and the sequence 
// will then loop as normal.
//
//
// Brian N. Norman
//
///////////////////////////////////////////////////////////////////////////////////////////

#include <AlaLedRgb.h>

AlaLedRgb rgbStrip;

// define the sequences to use

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

AlaSeq seq2[]=
{
  { ALA_FADECOLORSLOOP, 3000, 6000, alaPalRgb },
  { ALA_SPARKLE2,       1000, 6000, alaPalRgb },
  { ALA_OFF,            1000, 1000, alaPalNull },
  { ALA_SPARKLE2,       1000, 6000, alaPalFire },
  { ALA_PIXELSMOOTHSHIFTRIGHT, 6000, 2000, alaPalRgb },
  { ALA_OFF,            1000, 1000, alaPalNull },
  { ALA_MOVINGBARS,     3000, 6000, alaPalRgb },
  { ALA_COMET,          3000, 6000, alaPalRgb },
  { ALA_COMETCOL,       3000, 6000, alaPalRgb },
  { ALA_OFF,            1000, 1000, alaPalNull },
  { ALA_STOP,           1000, 1000, alaPalNull},
  { ALA_ENDSEQ }
};

AlaSeq seq3[]=
{
  { ALA_GLOW,           3000, 6000, alaPalRgb },
  { ALA_OFF,            1000, 1000, alaPalNull },
  { ALA_FIRE,           1000, 6000, alaPalFire },
  { ALA_OFF,            1000, 1000, alaPalNull },
  { ALA_BOUNCINGBALLS,  1000, 6000, alaPalRgb },
  { ALA_OFF,            1000, 1000, alaPalNull },
  { ALA_BUBBLES,        1000, 6000, alaPalRainbow },
  { ALA_STOP,           1000, 1000, alaPalNull},
  { ALA_ENDSEQ }
};


void setup()
{
  Serial.begin(9600);
  delay(100); // some arduinos need it
  
  Serial.println("\nAnimation sequences starting.\n");

  // 24 leds driven by pin 11
  rgbStrip.initWS2812(24, 11);
  rgbStrip.setBrightness(0x444444);

}

void doAnimation(AlaSeq seq[],String which)
{
  // run the specified animation sequence
  // the parameter 'which' is for debugging only
  
  Serial.print("Starting sequence ");
  Serial.println(which);

  // reset the animation code
  // to ensure it starts at the beginning
  
  rgbStrip.reset();

  // set the new animation sequence
  rgbStrip.setAnimation(seq);

  // this loop runs the animation till ALA_STOP is executed.
  while(1)
  {
  rgbStrip.runAnimation();
  
  // if ALA_STOP is executed we break out of the loop immediately
  // and return to the main loop() code
  
  if (rgbStrip.getStoppedFlag()) 
    {
      Serial.print("Sequence ");
      Serial.print(which);
      Serial.println(" stopped.");
      break;
    }
  }
}


void loop()
{
  doAnimation(seq1,"1");
  Serial.println("Do something here after seq1 has finished");
  doAnimation(seq2,"2");
  Serial.println("Do something here after seq2 has finished");
  doAnimation(seq3,"3");
  Serial.println("Do something here after seq3 has finished");
}

