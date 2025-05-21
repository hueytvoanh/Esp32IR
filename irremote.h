/*
//choose your protocol
#define EXCLUDE_UNIVERSAL_PROTOCOLS
#define DECODE_DENON        // Includes Sharp
#define DECODE_JVC
#define DECODE_KASEIKYO
#define DECODE_PANASONIC    // alias for DECODE_KASEIKYO
#define DECODE_LG
#define DECODE_NEC          // Includes Apple and Onkyo
#define DECODE_SAMSUNG
#define DECODE_SONY
#define DECODE_RC5
#define DECODE_RC6
*/


#define EXCLUDE_EXOTIC_PROTOCOLS
#define DECODE_STRICT_CHECKS                             //helps with false readings
#define RECORD_GAP_MICROS 10000                          //helps with false readings
#define TOLERANCE_FOR_DECODERS_MARK_OR_SPACE_MATCHING 5  //helps with false readings


//for LED blip output (optional)
#define IR_FEEDBACK_LED_PIN 32
#define FEEDBACK_LED_IS_ACTIVE_LOW


#include <IRremote.hpp>


//pin for IR receiver
#define RECEIVER_PIN_1 19


//used for noise detection
#define MIN_BIT_LENGTH 32




void IR_setup() {


  IrReceiver.begin(RECEIVER_PIN_1, ENABLE_LED_FEEDBACK);


  Serial.print("code version 1-8-2024");
  Serial.print("\nReady to receive remote IR signals ");
  Serial.print("at pin ");
  Serial.println(RECEIVER_PIN_1);  //declares digital pin to receive IR signal
}


//clear out last IR readings
void IR_flush() {
  while (IrReceiver.decode())  //flush out IR buffer
    IrReceiver.resume();  //start receiving new IR commands
}


//call this function if a person pushes mute/unmute too fast on the remote, etc.
void IR_debounce() {
  //debounce
  delay(650);
  IR_flush();
}


void IR_loop() {
volatile uint32_t receivedHex = 0;


  //start decoding IR command
  if (IrReceiver.decode()) {


    //get rid of noise/junk
    if (IrReceiver.decodedIRData.numberOfBits < MIN_BIT_LENGTH) {
      IrReceiver.resume();  // Ignore short or invalid signals
      return;
    }


    receivedHex = IrReceiver.decodedIRData.decodedRawData;
    Serial.print("\n\n");
    IrReceiver.printIRResultShort(&Serial);  //print data to Serial Monitor to help with debugging


    //if signal has multiple repeats, do something
    //uncomment 'return' if you want to ignore repeat signals
    if (IrReceiver.decodedIRData.flags & (IRDATA_FLAGS_IS_REPEAT)) {
      Serial.print("\nrepeated command, re-using last hex value");
      IrReceiver.resume();
      //return;
    }


    //if command X received, then do Y
    switch (receivedHex) {
      case 0xFD020707:
        Serial.print("\npower toggle: Universal Remote");
        break;
      case 0xF8070707:
        Serial.print("\nvolume up");
break;
      case 0xF40B0707:
        Serial.print("\nvolume down");
        break;
      case 0xF00F0707:
        Serial.print("\nmute / vol push");  //volume push on main remote
        break;
      case 0xED120707:
        Serial.print("\nchannel up - universal");
        break;
      case 0xEF100707:
        Serial.print("\nchannel down - universal");
        break;
      case 0xE0E0D629:
        Serial.print("\nchannel list - Universal #2");
        break;
      case 0x946B0707:
        Serial.print("\nchannel list");
        break;
      case 0x9F600707:
        Serial.print("\nup - Universal");
        break;
      case 0x9E610707:
        Serial.print("\ndown - Universal");
        break;
      case 0x9A650707:
        Serial.print("\nleft - Universal");
        break;
      case 0x9D620707:
        Serial.print("\nright - Universal");
 break;
      case 0xFB040707:
        Serial.print("\ndigital 1");
        break;
      case 0xFA050707:
        Serial.print("\ndigital 2");
        break;
      case 0xF9060707:
        Serial.print("\ndigital 3");
        break;
      case 0xF7080707:
        Serial.print("\ndigital 4");
        break;
      case 0xF6090707:
        Serial.print("\ndigital 5");
        break;
      case 0xF50A0707:
        Serial.print("\ndigital 6");
        break;
      case 0xF30C0707:
        Serial.print("\ndigital 7");
        break;
      case 0xF20D0707:
        Serial.print("\ndigital 8");
        break;
      case 0xF10E0707:
        Serial.print("\ndigital 9");
        break;
      case 0xEE110707:
        Serial.print("\ndigital 0");
        break;
case 0x66990707:
        Serial.print("\nTV - universal");
        break;
      case 0xE51A0707:
        Serial.print("\nmenu - universal");
        break;
      case 0xE01F0707:
        Serial.print("\ninfo/options - universal");
        break;
      case 0xD22D0707:
        Serial.print("\nexit - universal");
        break;
      case 0xBA450707:
        Serial.print("\nrewind - universal");
        break;
      case 0xB8470707:
        Serial.print("\nplay - universal");
        break;
      case 0xB7480707:
        Serial.print("\nfast forward - universal");
        break;
      case 0xB54A0707:
        Serial.print("\npause - universal");
        break;
      case 0xB6490707:
        Serial.print("\nrecord - universal");
        break;
      case 0xDC230707:
        Serial.print("\n-hyphen");
        break;
      case 0xE0E0C43B:
        Serial.print("\n-hyphen");
        break;
      case 0xE0E0FC03:
        Serial.print("\nE-Manual");
        break;
      case 0xC03F0707:
        Serial.print("\nE-Manual");
        break;
      case 0xE0E0C03F:
        Serial.print("\nSleep");
        break;
      case 0xFC030707:
        Serial.print("\nSleep");
        break;
      case 0xE0E07C83:
        Serial.print("\npic size");
        break;
      case 0xC13E0707:
        Serial.print("\npic size");
        break;
      case 0xE0E0A45B:
        Serial.print("\nCC/VD");
        break;
      case 0xDA250707:
        Serial.print("\nCC/VD");
        break;
      case 0xB9460707:
        Serial.print("\nstop - universal");
        break;
      case 0x97680707:
        Serial.print("\nok / enter - universal");
        break;
      case 0x86790707:
        Serial.print("\nhome");
        break;
      case 0xEC130707:
        Serial.print("\nreturn / go back - universal");
        break;
      case 0xA7580707:
        Serial.print("\nreturn / go back");
        break;
      case 0xFE010707:
        Serial.print("\ninput - universal");
        break;
      case 0x936C0707:
        Serial.print("\nred - universal");
        break;
      case 0xEB140707:
        Serial.print("\ngreen - universal");
        break;
      case 0xEA150707:
        Serial.print("\nyellow - universal");
        break;
      case 0xE9160707:
        Serial.print("\nblue - universal");
        break;
    }
  }
  IrReceiver.resume();  // Receive the next value
}