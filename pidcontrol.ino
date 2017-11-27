class PID{
public:
    double error;
    double sample;
    double lastSample;
    double kP, kI, kD;
    double P, I, D;
    double PIDvalue;
    double setPoint;
    long lastProcess;

    PID(double _kP, double _kI, double _kD){
        kP = _kP;
        kI = _kI;
        kD = _kD;
    }

    void addNewSample(double _sample){
        sample = _sample;
    }

    void setSetPoint(double _setPoint){
        setPoint = _setPoint;
    }

    double process(){
        error = setPoint - sample;
        float deltaTime = (millis() - lastProcess)/1000.0;
        lastProcess = millis();
        P = error * kP;
        I += (error * kI) * deltaTime;
        D = (lastSample - sample) * kD * deltaTime;
        lastSample = sample;

        PIDvalue = P + I + D;

        return PIDvalue;
    }
};

#define pSENSOR     A1
#define pCONTROLE   3

PID muePID(1.0, 0, 0);

void setup(){
    Serial.begin(9600);

    pinMode(pSENSOR, INPUT);
    pinMode(pCONTROLE, OUTPUT);
}

int controlPwm = 50;
float position;
void loop(){

    position = map(analogRead(pSENSOR),0,1023,0,100);

    muePID.addNewSample(position);

    controlPwm = (muePID.process() + 50);

    analogWrite(pCONTROLE, controlPwm);
}
