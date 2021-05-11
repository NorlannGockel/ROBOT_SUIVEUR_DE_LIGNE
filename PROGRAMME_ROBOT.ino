#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//----- Adressage matériel -----
// En cas de non fonctionnement, mettez la ligne 8 en
// commentaire et retirez le commentaire à la ligne 9.
LiquidCrystal_I2C lcd(0x27, 20, 4);
//LiquidCrystal_I2C lcd(0x3F,20,4);
int pinNO=12;
int pinN1=13;
int pinMoteurD1 = 2; //on initialise nos pins
int pinMoteurD2 = 4;
int pinMoteurDPWM = 5;
int pinMoteurG1 = 7;
int pinMoteurG2 = 8;
int pinMoteurGPWM =6;
int v=0;
const int btnPin  = A3; 
const int btnPinA  = A2; 
//int etatbouton = 0; // variable qui servira à mémoriser la position du bouton.

// Définition des numéros de port
const int trigPin = 11;  // Trigger (emission)
const int echoPin = 10;  // Echo    (réception)

// Variables utiles
long duree;   // durée de l'echo
int distance; // distance
bool etatbouton;


void setup() {
  int btnVal  = 0; 
  pinMode(pinNO, INPUT);
  pinMode(pinN1, INPUT);
  pinMode(pinMoteurD1,OUTPUT);
  pinMode(pinMoteurD2,OUTPUT);
pinMode(btnPin,INPUT_PULLUP); 
pinMode(btnPinA,INPUT_PULLUP); 
  pinMode(pinMoteurDPWM,OUTPUT); // on dit si ils recoivent ou envoient des valeurs
   pinMode(pinMoteurG1,OUTPUT);
  pinMode(pinMoteurG2,OUTPUT);
  pinMode(pinMoteurGPWM,OUTPUT);
  int v=0;
  Serial.begin(9600);
   lcd.init(); // initialisation de l'afficheur
  pinMode(trigPin, OUTPUT); // Configuration du port du Trigger comme une SORTIE
pinMode(echoPin, INPUT);  // Configuration du port de l'Echo  comme une ENTREE





}

void vitmot(int x, int y)
{
  analogWrite(pinMoteurDPWM, x); //Moteur1
  digitalWrite(pinMoteurD1,HIGH);
  digitalWrite(pinMoteurD2,LOW);
  analogWrite(pinMoteurGPWM, y); //Moteur1
  digitalWrite(pinMoteurD1,HIGH);
  digitalWrite(pinMoteurD2,LOW);
}
void calcul_mesures()
{
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

    // Écoute de l'écho 
  duree = pulseIn(echoPin, HIGH);

  // Calcul de la distance
  distance = duree*0.034/2;
if (distance > 100)
{
   //Serial.print("Distance : ");
 //Serial.print(" erreur");
 //Serial.println("cm");
}
else
{
 //Serial.print("Distance : ");
 //Serial.print(distance);
 //Serial.println("cm");
}
}


void loop() 
{
  v=0;
  lcd.setCursor(0, 0);
  lcd.print(" On est         ");
  lcd.setCursor(0, 1);
  lcd.print("Arrete ");

  boolean etatpinNO = digitalRead(pinNO);
  boolean etatpinN1 = digitalRead(pinN1);
  analogWrite(pinMoteurDPWM, 0); //Moteur1
  digitalWrite(pinMoteurD1,HIGH);
  digitalWrite(pinMoteurD2,LOW);
  analogWrite(pinMoteurGPWM, 0); //Moteur1
  digitalWrite(pinMoteurD1,HIGH);
  digitalWrite(pinMoteurD2,LOW);
  int x=0;
  lcd.backlight();
  
  int btnVal=analogRead(btnPin); 
  if(btnVal<200)
    {
      v=1;     
      Serial.println(v);
    }
    
  while (v==1)
  {
  
  boolean etatpinNO = digitalRead(pinNO);
  boolean etatpinN1 = digitalRead(pinN1);
  int btnVal2=analogRead(btnPinA);
  
  if(btnVal2<200)
  { 
  v=0;
  }
      analogWrite(pinMoteurDPWM, 250); //Moteur1
          analogWrite(pinMoteurGPWM, 250); //Moteur1
  calcul_mesures();
  while (distance < 20)
  {
    Serial.println("Coucou");
    analogWrite(pinMoteurDPWM, 0); //Moteur1
    digitalWrite(pinMoteurD1,LOW);
    digitalWrite(pinMoteurD2,LOW);
    analogWrite(pinMoteurGPWM, 0); //Moteur1
    digitalWrite(pinMoteurD1,LOW);
    digitalWrite(pinMoteurD2,LOW);
    lcd.setCursor(0, 0);
    lcd.print(" Obstacle :       ");
    lcd.setCursor(0, 1);
    lcd.print(distance);
    lcd.print("cm");
    calcul_mesures();
    }
    
    lcd.backlight();
    if (etatpinN1==1 && etatpinNO==1) //Les 2 capteurs détectent une ligne donc ça met erreur
    {
    Serial.println("erreur");
    analogWrite(pinMoteurDPWM, 150); //Moteur1
    digitalWrite(pinMoteurD1,HIGH);
    digitalWrite(pinMoteurD2,LOW);
    analogWrite(pinMoteurGPWM, 150); //Moteur1
    digitalWrite(pinMoteurD1,HIGH);
    digitalWrite(pinMoteurD2,LOW);
    lcd.setCursor(0, 0);
    lcd.print(" Erreur !       ");
    lcd.setCursor(0, 1);
    lcd.print("                 ");
    x=1;
    }
    if (etatpinNO==1 && x==0)     // si jamais le capteur droit détecte un obstacle
    {
    Serial.println("On tourne a droite");
    analogWrite(pinMoteurDPWM, 255); //Moteur1
    digitalWrite(pinMoteurD1,HIGH);
    digitalWrite(pinMoteurD2,LOW);
    analogWrite(pinMoteurGPWM, 0); //Moteur2
    digitalWrite(pinMoteurG1,HIGH);
    digitalWrite(pinMoteurG2,LOW);
    lcd.setCursor(0, 0);
    lcd.print(" Je tourne");
    lcd.setCursor(0,1);
    lcd.print("A droite");
    }
    if (etatpinN1==1 && x==0) //si jamais le capteur gauche détecte un obstacle
    {
    Serial.println("On tourne a gauche");
    analogWrite(pinMoteurDPWM, 0); //Moteur1
    digitalWrite(pinMoteurD1,HIGH);
    digitalWrite(pinMoteurD2,LOW);
    analogWrite(pinMoteurGPWM, 150); //Moteur2
    digitalWrite(pinMoteurG1,HIGH);
    digitalWrite(pinMoteurG2,LOW);
    lcd.setCursor(0, 0);
    lcd.print(" Je tourne");
    lcd.setCursor(0,1);
    lcd.print("A Gauche");
    }
    if (etatpinN1==0 && etatpinNO==0)  //si les capteurs détectent rien
    {
    analogWrite(pinMoteurDPWM, 150); //Moteur1
    digitalWrite(pinMoteurD1,HIGH);
    digitalWrite(pinMoteurD2,LOW);
    analogWrite(pinMoteurGPWM, 150); //Moteur2
    digitalWrite(pinMoteurG1,HIGH);
    digitalWrite(pinMoteurG2,LOW);
    lcd.setCursor(0, 0);
    lcd.print("On Avance           ");
    lcd.setCursor(0, 1);
    lcd.print("                 ");
  }
  delay(10);
  }
}
