//IR REMOTE SERVICE SAMSUNG
//Filippo Fondi
//https://jucetize.weebly.com/uploads/3/7/2/0/37200949/samsung_service_remote.ino

////////////////////////INCLUDI LIBRERIE//////////////////////

#include <IRremote.h>
#include <NewTone.h>

///////////////////////DEFINIZIONE PIN////////////////////////

#define LEDPIN 13  //LED integrato al pin 13
#define BUZZER 2   //Buzzer
#define LEDRCV A3  //Receptor IR

//------------------Pulsanti-------------------
#define BT1 4  //Service Menu Extended  //Menú DVBT: menú DVBT especial atenuado en algunos Samsung antiguos (para realizar la sintonización del decodificador incorporado)
#define BT2 5  //Service Menu from off  //Menú de servicio desactivado: acceda al menú de servicio desde el televisor apagado
#define BT3 6  //Digital Menu           //Menú de servicio activado: accede al menú de servicio desde el televisor encendido
#define BT4 8  //Down
#define BT5 9  //Up
#define BT6 10 //Left
#define BT7 11 //Right
#define BT8 12 //Exit
#define BT9 A0 //Power

/////////////////INICIALIZA LIBRERIA///////////////////

IRsend irsend;              //Inicializa libreria ir trasm (pin trasmittente di default collegato al pin digitale PWM D3
IRrecv irrecv(LEDRCV);      //Inicializa libreria ir recept
decode_results results;

//////////////////////SETUP/////////////////////////

void setup()
{

   pinMode(LEDPIN, OUTPUT);
   pinMode(LEDRCV, INPUT);
   pinMode(BUZZER, OUTPUT);
   pinMode(BT1, INPUT_PULLUP);
   pinMode(BT2, INPUT_PULLUP);
   pinMode(BT3, INPUT_PULLUP);
   pinMode(BT4, INPUT_PULLUP);
   pinMode(BT5, INPUT_PULLUP);
   pinMode(BT6, INPUT_PULLUP);
   pinMode(BT7, INPUT_PULLUP);
   pinMode(BT8, INPUT_PULLUP);
   pinMode(BT9, INPUT_PULLUP);
   Serial.begin(9600);
   irrecv.enableIRIn();    //Inizializza ricevitore infrarossi

   NewTone(BUZZER, 700, 500);
   digitalWrite(LEDPIN, HIGH);
   delay(600);
   digitalWrite(LEDPIN, LOW);
   NewTone(BUZZER, 900, 500);
   delay(200);
   digitalWrite(LEDPIN, HIGH);
   NewTone(BUZZER, 500, 500);
   delay(300);
   digitalWrite(LEDPIN, LOW);
   NewTone(BUZZER, 700, 800);
}
 
void loop()
{

///////////////////////////////RICEZIONE CODICI///////////////////////////////

  if (irrecv.decode(&results)) 
  {
    Serial.println(results.value, HEX);
    irrecv.resume();   //Ricevi valore successivo
  }

///////////////////////////////TRASMISSIONE CODICI///////////////////////////////

//--------------------------Pulsante 1----------------------

  if(digitalRead(BT1) == LOW)
  {
    digitalWrite(BUZZER,HIGH);
    delay(50);
    digitalWrite(BUZZER,LOW);
    digitalWrite(LEDPIN, HIGH);
    delay(200);
    digitalWrite(LEDPIN,LOW);
    Serial.println("SERVICE MENU");
    
    irsend.sendSAMSUNG(0xE0E0F807, 32);  //INFO
    delay(200);
    irsend.sendSAMSUNG(0xE0E0DC23, 32);  //FACTORY
    delay(200);
    irsend.sendSAMSUNG(0xE0E03CC3, 32);  //3SPEED
  }

//--------------------------Pulsante 2----------------------
  
  else if (digitalRead(BT2) == LOW)
  {
    digitalWrite(BUZZER,HIGH);
    delay(50);
    digitalWrite(BUZZER,LOW);
    digitalWrite(LEDPIN, HIGH);
    delay(200);
    digitalWrite(LEDPIN,LOW);
    Serial.println("3SPEED");
 
    irsend.sendSAMSUNG(0xE0E0F807, 32);  //INFO
    delay(200);
    irsend.sendSAMSUNG(0xE0E058A7, 32);  //MENU
    delay(200);
    irsend.sendSAMSUNG(0xE0E0F00F, 32);  //MUTE
    delay(200);
    irsend.sendSAMSUNG(0xE0E040BF, 32);  //POWER   
  }

//--------------------------Pulsante 3----------------------
  
  else if (digitalRead(BT3) == LOW)
  {
    digitalWrite(BUZZER,HIGH);
    delay(50);
    digitalWrite(BUZZER,LOW);
    digitalWrite(LEDPIN, HIGH);
    delay(200);
    digitalWrite(LEDPIN,LOW);
    Serial.println("POWER"); 

    irsend.sendSAMSUNG(0xE0E0718E, 32);  //DIGITAL MENU (Menu sintonizzatore su tv oscurati) 
  }

//--------------------------Pulsante 4----------------------

  else if (digitalRead(BT4) == LOW)
  {
    digitalWrite(BUZZER,HIGH);
    delay(50);
    digitalWrite(BUZZER,LOW);
    digitalWrite(LEDPIN, HIGH);
    delay(200);
    digitalWrite(LEDPIN,LOW);
    Serial.println("DOWN"); 

    irsend.sendSAMSUNG(0xE0E08679, 32);  //DOWN
  }

//--------------------------Pulsante 5----------------------
  
  else if (digitalRead(BT5) == LOW)
  {
    digitalWrite(BUZZER,HIGH);
    delay(50);
    digitalWrite(BUZZER,LOW);
    digitalWrite(LEDPIN, HIGH);
    delay(200);
    digitalWrite(LEDPIN,LOW);
    Serial.println("UP"); 

    irsend.sendSAMSUNG(0xE0E006F9, 32);  //UP
  }

//--------------------------Pulsante 6----------------------
  
  else if (digitalRead(BT6) == LOW)
  {
    digitalWrite(BUZZER,HIGH);
    delay(50);
    digitalWrite(BUZZER,LOW);
    digitalWrite(LEDPIN, HIGH);
    delay(200);
    digitalWrite(LEDPIN,LOW);
    Serial.println("LEFT"); 

    irsend.sendSAMSUNG(0xE0E0A659, 32);  //LEFT
  }

//--------------------------Pulsante 7----------------------

  else if (digitalRead(BT7) == LOW)
  {
    digitalWrite(BUZZER,HIGH);
    delay(50);
    digitalWrite(BUZZER,LOW);
    digitalWrite(LEDPIN, HIGH);
    delay(200);
    digitalWrite(LEDPIN,LOW);
    Serial.println("RIGHT");

    irsend.sendSAMSUNG(0xE0E046B9, 32);  //RIGHT
  }

//--------------------------Pulsante 8----------------------

  else if (digitalRead(BT8) == LOW)
  {
    digitalWrite(BUZZER,HIGH);
    delay(50);
    digitalWrite(BUZZER,LOW);
    digitalWrite(LEDPIN, HIGH);
    delay(200);
    digitalWrite(LEDPIN,LOW);
    Serial.println("EXIT - RETURN"); 

    irsend.sendSAMSUNG(0xE0E0B44B, 32);  //EXIT
    delay(200);
    irsend.sendSAMSUNG(0xE0E01AE5, 32);  //RETURN
  }

//--------------------------Pulsante 3----------------------
  
  else if (digitalRead(BT9) == LOW)
  {
    digitalWrite(BUZZER,HIGH);
    delay(50);
    digitalWrite(BUZZER,LOW);
    digitalWrite(LEDPIN, HIGH);
    delay(200);
    digitalWrite(LEDPIN,LOW);
    Serial.println("POWER"); 

    irsend.sendSAMSUNG(0xE0E040BF, 32);  //POWER 
  }

//----------------------------------------------------------

} //Void Loop
