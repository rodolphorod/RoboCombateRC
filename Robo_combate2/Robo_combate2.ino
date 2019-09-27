#include <Servo.h> //para acionar o esc


//#define MAX_SPEED             255 // max motor speed
int MAX_SPEED;
#define PULSE_WIDTH_DEADBAND   5 // pulse width difference from 1500 us (microseconds) to ignore (to compensate for control centering offset)
#define PULSE_WIDTH_RANGE     45 // pulse width difference from 1500 us to be treated as full scale input (for example, a value of 350 means
                                  //   any pulse width <= 1150 us or >= 1850 us is considered full scale)
//pino do driver
const int motorDIR = 5;
const int motorESQ = 6;
const int dirDIR = 7;
const int dirESQ = 8;
const bool frente = LOW;
const bool tras = HIGH;

int velocidadeMaxima = 240;
int velocidadeMedia = 127;
int velocidadeNula = 0;


//ARMA
const int pinoESC = 9;
int valor = 0;
Servo ESC;


//Controle

 int EixoY=0;
 int Acelerador=0;
 int EixoX=0;
 int Arma=0;

const int pinoEixoY = 10;
const int pinoAcelerador = 11;
const int pinoEixoX = 12;
const int pinoArma = 13;




void setup() 
{ 
  Serial.begin(9600);

    // configurando controle

    pinMode (pinoEixoY, INPUT);
    pinMode (pinoAcelerador, INPUT);
    pinMode (pinoEixoX, INPUT);
    pinMode (pinoArma, INPUT);

  
    // Pinos do Driver:

    pinMode(motorDIR, OUTPUT);
    pinMode(motorESQ, OUTPUT);
    pinMode(dirDIR, OUTPUT);
    pinMode(dirESQ, OUTPUT);
    pinMode(pinoESC, OUTPUT);

    // Rotina de Inicialização do ESC

    ESC.attach(pinoESC);
    ESC.writeMicroseconds(0);
    delay(500);
    ESC.writeMicroseconds(2000);
    delay(500);
    ESC.writeMicroseconds(700);
    delay(500);
    ESC.writeMicroseconds(800);




 }
 int left_speed,right_speed;

void loop() 
{
    //recebe canais

    EixoY = (pulseIn (pinoEixoY, HIGH, 100000))/10 - 150;
    Acelerador = (pulseIn (pinoAcelerador, HIGH, 100000))/10;
    EixoX = (pulseIn (pinoEixoX, HIGH, 100000))/10 - 150;
    Arma = (pulseIn (pinoArma, HIGH, 100000))/10;


    if (Arma < 150)
      ESC.writeMicroseconds(800);
    else
      ESC.writeMicroseconds(2000);

    MAX_SPEED = map(Acelerador,97,199,0,255);
    MAX_SPEED = constrain(MAX_SPEED,0,255);
    
    if(abs(EixoY)<=5)
      EixoY = 0;
    if(abs(EixoX)<=5)
      EixoX = 0;

    
    
    right_speed = ((long)EixoY * MAX_SPEED / PULSE_WIDTH_RANGE) - ((long)EixoX * MAX_SPEED / PULSE_WIDTH_RANGE);
    left_speed = ((long)EixoY * MAX_SPEED / PULSE_WIDTH_RANGE) + ((long)EixoX * MAX_SPEED / PULSE_WIDTH_RANGE);


    if(left_speed < 0){
      left_speed = abs(left_speed);
      digitalWrite(dirESQ, tras);
//      Serial.print("tras");
//      Serial.print("\t");
    }else{
      digitalWrite(dirESQ, frente);
//      Serial.print("frente");
//      Serial.print("\t");
    }

    if(right_speed < 0){
      right_speed = abs(right_speed);
      digitalWrite(dirDIR, tras);
//      Serial.print("tras");
//      Serial.print("\t");
    }else{
      digitalWrite(dirDIR, frente);
//      Serial.print("frente");
//      Serial.print("\t");
    }

    right_speed = constrain(right_speed,0,MAX_SPEED);
    left_speed = constrain(left_speed,0,MAX_SPEED);
    
    
//    Serial.print(right_speed);
//    Serial.print("\t");
//    Serial.println(left_speed);
    analogWrite(motorDIR, right_speed);
    analogWrite(motorESQ, left_speed);

    
    
    /*
    delay(3000);
    

    delay(3000);

    digitalWrite(dirDIR, frente);
    digitalWrite(dirESQ, frente);
    analogWrite(motorDIR, 240);
    analogWrite(motorESQ, 0);

    delay(3000);


    digitalWrite(dirDIR, frente);
    digitalWrite(dirESQ, frente);
    analogWrite(motorDIR, 0);
    analogWrite(motorESQ, 240);

    delay(3000);

    digitalWrite(dirDIR, tras);
    digitalWrite(dirESQ, tras);
    analogWrite(motorDIR, 240);
    analogWrite(motorESQ, 0);

    delay(3000);

    digitalWrite(dirDIR, tras);
    digitalWrite(dirESQ, tras);
    analogWrite(motorDIR, 0);
    analogWrite(motorESQ, 240);

    delay(3000);

    digitalWrite(dirDIR, tras);
    digitalWrite(dirESQ, tras);
    analogWrite(motorDIR, 0);
    analogWrite(motorESQ, 0);

    delay(3000);
    */
}
