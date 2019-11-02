/*
 * file name: RFID 
 * Date; 11/1/2019
 * modified: Christopher Diaz-Reyes
 * Description: The RFID will read a key fob that has the same address inside content.substring(1). If correct key fob is read, green LED turns on and open door; but if different fob is read, program will denied acces0s and turn on red LED. Motor will turn counterclockwise to simulate opening a door, while rotating clockwise will be closeing. 
 * All the resources for this project: https://randomnerdtutorials.com/
 * Created by FILIPEFLOP
 */
 
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
/////////////////////////////////////////////////////////////////////////////////////////////////////
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.               This block of code is connecting the motor driver to the arduino to run the motor. The motor driver 
int ledGreen = 6; //The pin the green LED is connected                         has a voltage source range from 5V-12V; the motor needs to be supplied 5V. 
int ledRed = 7;
int IN1 = 2;
int IN2 = 3;
int IN3 = 4;
int IN4 = 5;
int IN5 = 8;
int _step = 0;
boolean simDoor = false; //false = clockwise, true = counter clockwise. Found online 
int count = 0;
/////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Hader file: void setup() 
 * Date; 11/1/2019
 * Description: This function is initialize the arduinos ports: the pinouts, serial communication, initialize RFID, and asking user for card.
 * Modified by Christopher Diaz-Reyes
 */

void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Hello, Please scan card");
  Serial.println();
  pinMode(ledGreen, OUTPUT); // Green lED turn on when correct key fob is scanned.
  pinMode(ledRed, OUTPUT);  //  Red LED turn on when failed to scan appropriate kay fob. 
  pinMode(IN1, OUTPUT);             
  pinMode(IN2, OUTPUT);  
  pinMode(IN3, OUTPUT);             
  pinMode(IN4, OUTPUT);
}             
///////////////////////////////////////////////////////////////////////////////////////////////////// 

/*
 * Hader file: void setup() 
 * Date; 11/1/2019
 * Description: This block of code goes into the MFRC522.h library which allows to scan a key fob and print out the address of the key fob. 
 * Modified by Christopher Diaz-Reyes
 */

void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
//  byte letter;
  ///////////////////////////////////////////////////////////////////////////////////////////////////// 
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  
  if (content.substring(1) == "19 73 65 B9") //Can change the the amount of cards allowed to be saved in the aaray
  
  {
    Serial.println("Authorized access\n\r Welcome  ");
    Serial.println();
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
///////////////////////////////////////////////////////////////////////////////////////////////////// 

/*
 * Hader file: mtor control 
 * Date; 11/1/2019
 * Description: The motor will run when the correct key fob is scanned and will be simulating an opening door. 
 * Modified by Christopher Diaz-Reyes
 */   
    switch(_step)
    { 
      case 0: 
        digitalWrite(IN1, LOW);  //The motor is a two phase, which allows us to run the motor at one at a time using one phase at a time. 
        digitalWrite(IN2, LOW); 
        digitalWrite(IN3, LOW); 
        digitalWrite(IN4, HIGH); 
      break;  
      case 1: 
        digitalWrite(IN1, LOW);  
        digitalWrite(IN2, LOW); 
        digitalWrite(IN3, HIGH); 
        digitalWrite(IN4, HIGH); 
      break;  
      case 2: 
        digitalWrite(IN1, LOW);  
        digitalWrite(IN2, LOW); 
        digitalWrite(IN3, HIGH); 
        digitalWrite(IN4, LOW); 
      break;  
      case 3: 
        digitalWrite(IN1, LOW);  
        digitalWrite(IN2, HIGH); 
        digitalWrite(IN3, HIGH); 
        digitalWrite(IN4, LOW); 
      break;  
      case 4: 
        digitalWrite(IN1, LOW);  
        digitalWrite(IN2, HIGH); 
        digitalWrite(IN3, LOW); 
        digitalWrite(IN4, LOW); 
      break;  
      case 5: 
        digitalWrite(IN1, HIGH);  
        digitalWrite(IN2, HIGH); 
        digitalWrite(IN3, LOW); 
        digitalWrite(IN4, LOW); 
      break;  
      case 6: 
        digitalWrite(IN1, HIGH);  
        digitalWrite(IN2, LOW); 
        digitalWrite(IN3, LOW); 
        digitalWrite(IN4, LOW); 
      break;  
      case 7: 
        digitalWrite(IN1, HIGH);  
        digitalWrite(IN2, LOW); 
        digitalWrite(IN3, LOW); 
        digitalWrite(IN4, HIGH); 
      break;  
      default: 
        digitalWrite(IN1, LOW);  
        digitalWrite(IN2, LOW); 
        digitalWrite(IN3, LOW); 
        digitalWrite(IN4, LOW); 
      break;   
    }
       if(simDoor)
       { 
         _step++; 
       }
      
      else
      { 
        _step--; 
      } 
      
      if(_step>7)
      { 
        _step=0; 
      } 
      
      if(_step<0)
      { 
        _step=7; 
      } 
    delay(1); 
    
    delay(3000);
  }
 
 else   {
    
    Serial.println(" Access denied");
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, HIGH);
    delay(3000);
 }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////           
        
