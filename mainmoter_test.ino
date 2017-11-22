int PositionInput = 0;
int RPWM_Output = 5; // Arduino PWM output pin 5; connect to IBT-2 pin 1 (RPWM)
int LPWM_Output = 6; // Arduino PWM output pin 6; connect to IBT-2 pin 2 (LPWM)
bool Pstop = true;
bool DirN = false;
bool DirB = false;
String inString = "";
void setup() {
    Serial.begin(9600);
    Serial.println("Hello !!!");
    pinMode(RPWM_Output, OUTPUT);
    pinMode(LPWM_Output, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    digitalWrite(7,1);
    digitalWrite(8,1);
}
 
void loop() {
     //Serial.println(analogRead(A2));
     if (Serial.available() > 0) {
         inString = Serial.readString();
         PositionInput = inString.toInt();
         Pstop = true;
         while(Pstop)
         {
            if(PositionInput > analogRead(A2))
            {
              if(DirB == true)
              {
                DirB = false;
                Pstop = false;
              }
              else
              {
                DirN = true;
                analogWrite(RPWM_Output,20);
                analogWrite(LPWM_Output,0);
              }
            }
            else if(PositionInput < analogRead(A2))
            {
              if(DirN == true)
              {
                DirN = false;
                Pstop = false;
              }
              else
              {
                DirB = true;
                analogWrite(RPWM_Output,0);
                analogWrite(LPWM_Output,20);
              }
            }
            Serial.println(analogRead(A2));
         }
         analogWrite(RPWM_Output,0);
         analogWrite(LPWM_Output,0);
     }
}
