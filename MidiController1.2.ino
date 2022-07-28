

#include <LiquidCrystal.h>

#include <Bounce2.h>


#define BUTTON_DEBOUNCE 50 

// the MIDI channel number to send messages
const int channel = 2;


const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Bounce button14 = Bounce(14, BUTTON_DEBOUNCE);
Bounce button15 = Bounce(15, BUTTON_DEBOUNCE);  
Bounce button16 = Bounce(16, BUTTON_DEBOUNCE);  
Bounce button17 = Bounce(17, BUTTON_DEBOUNCE);  
Bounce button18 = Bounce(18, BUTTON_DEBOUNCE);
Bounce button19 = Bounce(19, BUTTON_DEBOUNCE);  

int potVal = 0; //Initial pot val
int lastVal = 0;
int lastVal2 = 0;
//Terrible variable names, but these are used for voume bar
int lastVal3 = 0;
int lastVal4 = 0;

int d = 0;


  


void setup() {
  // Configure the pins for footswitch buttons as input mode = pullup resistors.
  // The pushbuttons connect from each pin to ground.  When
  // the button is pressed, the pin reads LOW because the button
  // shorts it to ground.  When released, the pin reads HIGH
  // because the pullup resistor connects to +5 volts inside
  // the chip. 
  // Teensy++ 2.0 LED, may need 1k resistor pullup
   Serial.begin(9600);

  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  pinMode(17, INPUT_PULLUP);
  pinMode(18, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);
  pinMode(23, INPUT_PULLUP);


  // Testing Variable Resistor Pullup

  //pinMode (PIN_ADC4, INPUT_PULLUP)

  
  //Maybe send serial messages if helpful

  //Serial.begin(9600);
 

   // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(0, 0);

  lcd.print("Midi Controller 1.2");
  
}

void loop() {
  // Get a reading from the button
  button14.update();
  button15.update();
  button16.update();
  button17.update();
  button18.update();
  button19.update();
 


  // Turn notes on if a button has been connected to ground

  if (button14.fallingEdge()) {
    lcd.setCursor(0, 1);
    lcd.write(1022);
    lcd.write(1022);
    lcd.write(1022);
    usbMIDI.sendNoteOn(66, 99, 3);  // 66 = F#4
  }
  if (button15.fallingEdge()) {
    lcd.setCursor(0, 1);
    lcd.write(1022);
    lcd.write(1022);
    lcd.write(1022);    usbMIDI.sendNoteOn(67, 99, channel);  // 67 = G4
  }
  if (button16.fallingEdge()) {
    lcd.setCursor(0, 1);
     lcd.write(1022);
    lcd.write(1022);
    lcd.write(1022);    usbMIDI.sendNoteOn(68, 99, channel);  // 68 = G#4
  }
  if (button17.fallingEdge()) {
    lcd.setCursor(0, 1);
    lcd.write(1022);
    lcd.write(1022);
    lcd.write(1022);    usbMIDI.sendNoteOn(69, 99, channel);  // 69 = A5
  }
  if (button18.fallingEdge()) {
    lcd.setCursor(0, 1);
    lcd.write(1022);
    lcd.write(1022);
    lcd.write(1022);    usbMIDI.sendNoteOn(70, 99, channel);  // 70 = A#5
  }
  if (button19.fallingEdge()) {
    lcd.setCursor(0, 1);
    lcd.write(1022);
    lcd.write(1022);
    lcd.write(1022);    usbMIDI.sendNoteOn(71, 99, channel);  // 71 = B5
  }
 


  // Turn notes off if a button was disconnected from ground
 
  if (button14.risingEdge()) {
    lcd.setCursor(0, 1);
    lcd.print("F#4");
    usbMIDI.sendNoteOff(66, 0, 3);  // 66 = F#4
  }
  if (button15.risingEdge()) {
    lcd.setCursor(0, 1);
    lcd.print("G4");
    usbMIDI.sendNoteOff(67, 0, channel);  // 67 = G4
  }
  if (button16.risingEdge()) {
    lcd.setCursor(0, 1);
    lcd.print("G#4");
    usbMIDI.sendNoteOff(68, 0, channel);  // 68 = G#4
  }
  if (button17.risingEdge()) {
    lcd.setCursor(0, 1);
    lcd.print("A5");
    usbMIDI.sendNoteOff(69, 0, channel);  // 69 = A5
  }
  if (button18.risingEdge()) {
    lcd.setCursor(0, 1);
    lcd.print("A#5");
    usbMIDI.sendNoteOff(70, 0, channel);  // 70 = A#5
  }
  if (button19.risingEdge()) {
    lcd.setCursor(0, 1);
    lcd.print("B5");
    usbMIDI.sendNoteOff(71, 0, channel);  // 71 = B5
  }

   //This portion is strictly for the varibale pedal

   potVal = analogRead(9); //Since this should be a 1k pot, this will put it 0-127


 

  
   if (potVal != lastVal && potVal < 350){
    //convert pot value
    //potVal = abs(250-potVal) / 2;
    // If the value changes, send message 
    //Hopefully 11 is the expression change   
    potVal = constrain(potVal, 80, 310); //This successfuly contrains the values
    
    //Now to remap input sweep, this is sick as fuck
    lastVal2 = map(potVal, 80, 310, 127, 0);
    Serial.println(lastVal2);
    Serial.print(" ");

    usbMIDI.sendControlChange(11, lastVal2, channel);
    lastVal = potVal;

    //Trying to create volume bar
    //First convert lastVal2 to 0-14
    lastVal3 = map(lastVal2, 0, 127, 0, 15);
   
    lcd.setCursor(4, 1);

    if (lastVal3 > lastVal4) { // check if the number changes to a higher number
    for (d = 0; lastVal3 >= d; d++) { // count up from 0 to 15
      lcd.setCursor(d + 4, 1); // start at the bottom left and work forward
      lcd.write(1023); // show a block
    }
  }

  if (lastVal3 <= lastVal4) { // check if the number changed to a smaller number
    for (d = 15; lastVal3 <= d; d--) { //count down from 15 to 0
      lcd.setCursor(d + 4, 1); // start at the bottom right and work back
      lcd.write(1022); // show blank
    }
  }
  

  lastVal4 = lastVal3;  
}
 
    
}
   


  
  


 
