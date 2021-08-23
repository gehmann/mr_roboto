#include <Adafruit_PWMServoDriver.h>

#include <Wire.h>

#include <TimerThree.h>

#include <PololuLedStrip.h>

#define SCROLL 0
#define PULSE 1
#define RANDOMCOLORS 2
#define FLASH 3
#define FLASHTIME 4
#define BLINKINTERVAL 1
#define SAFETYDANCE 2
#define MRROBOTO 1
#define GETTOCLASS 2
#define LAUGH 3
#define SERVOMIN 150
#define SERVOMAX 600
#define HANDMAX 450
#define HANDMIN 250
#define LEFTSHOULDERMIN 230
#define RIGHTSHOULDERMAX 430
#define HTMAX 500
#define HTMIN 180
#define REVERSE true
#define DANCEARRAYLENGTH 180
#define LEDARRAYLENGTH 15


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
Pololu::rgb_color off;

int switch1 = HIGH, switch2 = HIGH, switch3 = HIGH, switch4 = HIGH, switch5 = HIGH, switch6 = HIGH, switch7 = HIGH, timerCounter = 0, I2CVal;
boolean timerExp = false, arduinoControl = false, hundredMillis = false, I2C = false, dancing = false, whichDance = true;

void sendI2C()
{
  Wire.beginTransmission(8);
  Wire.write(I2CVal);
  Wire.endTransmission();
}

void doI2C(int x)
{
  I2C = true;
  I2CVal = x;
}

template<unsigned char pin, unsigned char l> class leds : public PololuLedStrip<pin>
{
  private: rgb_color color;
  private: rgb_color colors[l];
    int Length, scrollCount = 0, scrollCountPrevious, scrollCounter = 0, pulseCounter = 0, randomCounter = 0, flashTime = 0, flashCounter = 0;
    int pulseCount = 1;
    boolean scrollDirection = false ;
    boolean ON = true;
    boolean pulseDirection = true;
    int count = 0;
    int red = 0, green = 0, blue = 0;
    int inter, numberLeds;
    boolean scrollVar = false, pulseVar = false, flashVar = false, randomColorVar = false, flashTimeVar = false;
  public:
    leds()
    {
      //rgb_color c[l];

      Length = l;
      scrollCount = 0; scrollCountPrevious = 1;
      for (int i = 0; i < l; i++) {
        colors[i].red = off.red;
        colors[i].green = off.green;
        colors[i].blue = off.blue;
      }
      //colors = c;
      PololuLedStripBase::interruptFriendly = false;
    }

    void updateLeds()
    {
      if (scrollVar)
      {
        this->scroll(inter, numberLeds);
      }
      else if (pulseVar)
      {
        this->pulse(inter);
      }
      else if (randomColorVar)
      {
        this->randomColors(inter);
      }
      else if (flashVar)
      {
        this->flash(inter);
      }
      else if (flashTimeVar)
      {
        this->flash(inter, flashTime);
      }
    }


    void doLeds(int n)
    {
      if (n == 0)
      {
        scrollVar = true;
        pulseVar = false;
        randomColorVar = false;
        flashVar = false;
      }
      else if (n == 1)
      {
        pulseVar = true;
        scrollVar = false;
        randomColorVar = false;
        flashVar = false;
      }
      else if (n == 2)
      {
        randomColorVar = true;
        scrollVar = false;
        pulseVar = false;
        flashVar = false;
      }
      else if (n == 3)
      {
        flashVar = true;
        scrollVar = false;
        pulseVar = false;
        randomColorVar = false;
      }
      else
      {
        scrollVar = false;
        pulseVar = false;
        randomColorVar = false;
        flashVar = false;
      }

    }

    void doLeds(int n, int interval)
    {
      if (n == 0)
      {
        scrollVar = true;
        pulseVar = false;
        randomColorVar = false;
        flashVar = false;
      }
      else if (n == 1)
      {
        pulseVar = true;
        scrollVar = false;
        randomColorVar = false;
        flashVar = false;
      }
      else if (n == 2)
      {
        randomColorVar = true;
        scrollVar = false;
        pulseVar = false;
        flashVar = false;
      }
      else if (n == 3)
      {
        flashVar = true;
        scrollVar = false;
        pulseVar = false;
        randomColorVar = false;
      }
      else
      {
        scrollVar = false;
        pulseVar = false;
        randomColorVar = false;
        flashVar = false;
      }

      inter = interval;
    }

    void doLeds(int n, int interval, int numLeds)
    {
      Serial.println("doLeds");
      Serial.println(n, DEC);
      Serial.println(interval, DEC);
      Serial.println(numLeds, DEC);
      if (n == 0)
      {
        scrollVar = true;
        pulseVar = false;
        randomColorVar = false;
        flashVar = false;
      }
      else if (n == 1)
      {
        pulseVar = true;
        scrollVar = false;
        randomColorVar = false;
        flashVar = false;
      }
      else if (n == 2)
      {
        randomColorVar = true;
        scrollVar = false;
        pulseVar = false;
        flashVar = false;
      }
      else if (n == 3)
      {
        flashVar = true;
        scrollVar = false;
        pulseVar = false;
        randomColorVar = false;
      }
      else
      {
        scrollVar = false;
        pulseVar = false;
        randomColorVar = false;
        flashVar = false;
      }
      
      if (interval > 0) {
        inter = interval;
      } 
      else
      {
        inter = 5;
      }
      
      if (numLeds > 0)
      {
        numberLeds = numLeds;
      } 
      else 
      {
        numberLeds = 1;
      }
    }
    
    void doLeds(int n, int interval, int numLeds, int time)
    {
      Serial.println("doLeds");
      Serial.println(n, DEC);
      Serial.println(interval, DEC);
      Serial.println(numLeds, DEC);
      if (n == 0)
      {
        flashTimeVar = false;
        scrollVar = true;
        pulseVar = false;
        randomColorVar = false;
        flashVar = false;
      }
      else if (n == 1)
      {
        flashTimeVar = false;
        pulseVar = true;
        scrollVar = false;
        randomColorVar = false;
        flashVar = false;
      }
      else if (n == 2)
      {
        flashTimeVar = false;
        randomColorVar = true;
        scrollVar = false;
        pulseVar = false;
        flashVar = false;
      }
      else if (n == 3)
      {
        flashTimeVar = false;
        flashVar = true;
        scrollVar = false;
        pulseVar = false;
        randomColorVar = false;
      }
      else if (n == 4)
      {
        flashTimeVar = true;
        scrollVar = false;
        pulseVar = false;
        randomColorVar = false;
        flashVar = false;
      }
      else
      {
        flashTimeVar = false;
        scrollVar = false;
        pulseVar = false;
        randomColorVar = false;
        flashVar = false;
      }
      
      if (interval > 0) {
        inter = interval;
      } 
      else
      {
        inter = 50;
      }
      
      if (numLeds > 0)
      {
        numberLeds = numLeds;
      } 
      else 
      {
        numberLeds = 1;
      }
      flashTime = time;
    }

    void setColor(int r, int g, int b)
    {
      Serial.println("set Color");
      Serial.println(r, DEC);
      Serial.println(g, DEC);
      Serial.println(b, DEC);
      if(r == -1)
      {
      }
      else
      {
        red = r;
        green = g;
        blue = b;
        color.red = red;
        color.green = green;
        color.blue = blue;
      }
      
    }

    void scroll(int interval, int numLeds)
    {
      if (scrollCounter == interval)
      {

        if (scrollDirection)
          scrollCountPrevious = scrollCount - numLeds;
        else
          scrollCountPrevious = scrollCount + numLeds;

        colors[scrollCount] = color;
        colors[scrollCountPrevious] = off;

        if ((scrollDirection) && scrollCount <= Length)
        {
          if (scrollCount == Length - 1 )
          {
            scrollDirection = false;
            scrollCount = scrollCount - numLeds;
          }
          else
          {
            scrollCount++;
          }
        }

        else if (!(scrollDirection) && scrollCount >= 0)
        {
          if (scrollCount == 0)
          {
            scrollDirection = true;
            scrollCount = numLeds;

          }
          else
          {
            scrollCount--;
          }
        }
        this->write(colors, Length);
        scrollCounter = 0;
      }
      else
      {
        scrollCounter++;
      }
    }
    void on(int r, int g, int b)
    {
      red = r;
      green = g;
      blue = b;
      color.red = red;
      color.green = green;
      color.blue = blue;
      for (int i = 0; i < Length; i++)
        colors[i] = color;
      this->write(colors, Length);
    }
    void onIndex(int indexStart, int indexEnd)
    {
      color.red = red;
      color.green = green;
      color.blue = blue;
      for (int i = 0; i < Length; i++)
      {
        if (i > indexStart && i < indexEnd)
        {
          colors[i] = color;
        }
        else
        {
          colors[i] = off;
        }
      }
      this->write(colors, Length);
    }

    void OFF()
    {
      for (int i = 0; i < Length; i++)
        colors[i] = off;
      this->write(colors, Length);
    }

    void flash(int interval)
    {
      if (count == interval / 10 && !ON)
      {
        count = 0;
        ON = true;
        for (int i = 0; i < Length; i++)
          colors[i] = color;
        this->write(colors, Length);
      }
      else if (count == interval / 10 && ON)
      {
        for (int i = 0; i < Length; i++)
          colors[i] = off;
        this->write(colors, Length);
        count = 0;
        ON = false;
      }
      else
      {
        count++;
      }
    }
    
    void flash(int interval, int time)
    {
      if(flashCounter <= time)
      {
        if (count == interval / 10 && !ON)
        {
          count = 0;
          ON = true;
          for (int i = 0; i < Length; i++)
            colors[i] = color;
          this->write(colors, Length);
        }
        else if (count == interval / 10 && ON)
        {
          for (int i = 0; i < Length; i++)
            colors[i] = off;
          this->write(colors, Length);
          count = 0;
          ON = false;
        }
        else
        {
          count++;
        }
        flashCounter++;
        
        if(flashCounter == time)
        {
          flashTimeVar = false;
          flashCounter = 0;
          idleLeds();
        }
      }
    }

    void pulse(int interval)
    {
      
      if (pulseCounter == interval * 10)
      {
        pulseCounter = 0;
        if (pulseDirection)
        {
          Serial.println(interval, DEC);
          color.red = ((int)(red / pulseCount));
          color.blue = ((int)(blue / pulseCount));
          color.green = ((int)(green / pulseCount));
          pulseCount++;
          if (pulseCount == 16)
          {
            pulseDirection = false;
            pulseCount = 16;
          }
        }
        else
        {

          color.red = ((int)(red / pulseCount));
          color.blue = ((int)(blue / pulseCount));
          color.green = ((int)(green / pulseCount));
          pulseCount--;

          if (pulseCount == 1)
          {
            pulseDirection = true;
            pulseCount = 1;
          }

        }
        for (int i = 0; i < Length; i++)
        {
          colors[i] = color;
          // Serial.print(color.red, DEC);
        }

        this->write(colors, Length);
      }
      else
      {
        pulseCounter++;
      }
      //Serial.print(pulseCounter, DEC);
    }

    void randomColors(int interval)
    {
      if (randomCounter == interval)
      {
        color.red = random(255);
        color.green = random(255);
        color.blue = random(255);
        for (int i = 0; i < Length; i++)
          colors[i] = color;
        this->write(colors, Length);
        randomCounter = 0;
      }
      else
      {
        randomCounter++;
      }
    }
};



// leds<pin, length> name
leds<10, 12> rightArmLed;
leds<40, 12> leftArmLed;
leds<13, 17> rearBumper;
leds<18, 17> frontBumper;
leds<37, 17> topBar;
leds<41, 22> leftFront;
leds<19, 22> rightFront;
leds<4, 37> leftLeg;
leds<5, 37> rightLeg;
leds<2, 4> mouthMiddle;
leds<3, 2> mouthTop;
leds<11, 2> mouthBottom;
leds<12, 2> rightEye;
leds<39, 2> leftEye;

class Mouth
{
  public:
    rgb_color mouth2[2];
    rgb_color mouth4[4];
    rgb_color color;
    int red, green, blue;
    void smile(int r, int g, int b)
    {
      if(r == 1)
      {
        color.red = red;
        color.green = green;
        color.blue = blue;
      }
      else
      {
        color.red = r;
        color.green = g;
        color.blue = b;
      }
      mouth2[0] = off;
      mouth2[1] = off;
      mouthTop.write(mouth2, 2);
      mouth2[0] = color;
      mouth2[1] = color;
      mouthBottom.write(mouth2, 2);
      mouth4[0] = color;
      mouth4[1] = off;
      mouth4[2] = off;
      mouth4[3] = color;
      mouthMiddle.write(mouth4, 4);
    }

    void frown(int r, int g, int b)
    {
      if(r == 1)
      {
        color.red = red;
        color.green = green;
        color.blue = blue;
      }
      else
      {
        color.red = r;
        color.green = g;
        color.blue = b;
      }
      mouth2[0] = off;
      mouth2[1] = off;
      mouthBottom.write(mouth2, 2);
      mouth2[0] = color;
      mouth2[1] = color;
      mouthTop.write(mouth2, 2);
      mouth4[0] = color;
      mouth4[1] = off;
      mouth4[2] = off;
      mouth4[3] = color;
      mouthMiddle.write(mouth4, 4);
    }
    void mOpen(int r, int g, int b)
    {
      if(r == 1)
      {
        color.red = red;
        color.green = green;
        color.blue = blue;
      }
      else
      {
        color.red = r;
        color.green = g;
        color.blue = b;
      }
      mouth4[0] = color;
      mouth4[1] = off;
      mouth4[2] = off;
      mouth4[3] = color;
      mouth2[0] = color;
      mouth2[1] = color;
      mouthBottom.write(mouth2, 2);
      mouthTop.write(mouth2, 2);
      mouthMiddle.write(mouth4, 4);
    }

    void straight(int r, int g, int b)
    {
      if(r == 1)
      {
        color.red = red;
        color.green = green;
        color.blue = blue;
      }
      else
      {
        color.red = r;
        color.green = g;
        color.blue = b;
      }
      mouth2[0] = off;
      mouth2[1] = off;
      mouthBottom.write(mouth2, 2);
      mouthTop.write(mouth2, 2);
      for (int i = 0; i < 4; i++)
        mouth4[i] = color;
      mouthMiddle.write(mouth4, 4);
    }
};

class eye
{
  public:
    rgb_color color;
    rgb_color colors[2];
    rgb_color leftEyeColors[2];
    rgb_color rightEyeColors[2];
    int blinkCounter, red = 1, green = 1, blue = 1;

    void on(int r, int g, int b)
    {
      if(r == 1)
      {
        this->on();
      }
      else
      {
        red = r;
        green = g;
        blue = b;
        color.red = r;
        color.green = g;
        color.blue = b;
        rightEye.on(r, g, b);
        leftEye.on(r, g, b);
        colors[1] = color;
        colors[0] = color;
      }
    }
    void on()
    {
      color.red = red;
      color.green = green;
      color.blue = blue;
      for (int i = 0; i < 2; i++)
        colors[i] = color;
      rightEye.write(colors, 2);
      leftEye.write(colors, 2);
    }

    void OFF()
    {
      rightEye.OFF();
      leftEye.OFF();
    }

    void Blink(int interval)
    {
      if (blinkCounter == interval * 50)
      {
        this->OFF();
        blinkCounter++;
      }
      else if (blinkCounter == ((interval * 500) + 10))
      {
        this->on(red, green, blue);
        blinkCounter = 0;
      }
      else
      {
        blinkCounter++;
      }
    }

    void lookLeft()
    {
      rightEyeColors[1] = color;
      rightEyeColors[0] = off;
      leftEyeColors[1] = off;
      leftEyeColors[0] = color;
      rightEye.write(rightEyeColors, 2);
      leftEye.write(leftEyeColors, 2);
    }

    void lookRight()
    {
      rightEyeColors[0] = color;
      rightEyeColors[1] = off;
      leftEyeColors[0] = off;
      leftEyeColors[1] = color;
      rightEye.write(rightEyeColors, 2);
      leftEye.write(leftEyeColors, 2);

    }
};

eye eyes;
Mouth mouth;

class servo
{
    int pin, servoMax, servoMin, degs, lastPosition, servoCounter = 0, servoTime, tempLastPosition;
    double mapDegs, servoVal, servoDegrees;
    boolean servoUpdate = false, rev = false;
  public:
    servo(int p, int sMax, int sMin, boolean r)
    {
      servoMin = sMin;
      servoMax = sMax;
      pin  = p;
      rev = r;
    }
    servo(int p, int sMax, int sMin)
    {
      servoMin = sMin;
      servoMax = sMax;
      pin  = p;
    }

    void goToPosition (int d)
    {
      lastPosition = d;
      mapDegs = d;
      reverse();
      mapDegs = map(mapDegs, 0, 180, servoMin, servoMax);
      pwm.setPWM(pin, 0, mapDegs);
    }

    void goToPosition (int d, int t)
    {
      if (t != 0)
      {
        servoUpdate = true;
        servoDegrees = d;
        tempLastPosition = d;
        servoTime = t;
        servoCounter = 0;
      }
      else
      {
        lastPosition = d;
        mapDegs = d;
        reverse();
        mapDegs = map(mapDegs, 0, 180, servoMin, servoMax);
        pwm.setPWM(pin, 0, mapDegs);
      }
    }

    void positionUpdate()
    {
      if (servoCounter == 0)
      {
        servoDegrees = (servoDegrees - lastPosition);
        servoDegrees = abs(servoDegrees);
        servoDegrees =  servoDegrees / servoTime;
        servoCounter++;
      }

      if (servoCounter <= servoTime)
      {

        mapDegs = servoDegrees * servoCounter;
        mapDegs = mapDegs - lastPosition;
        mapDegs = abs(mapDegs);
        reverse();
        servoVal = map(mapDegs, 0, 180, servoMin, servoMax);
        pwm.setPWM(pin, 0, servoVal);
        servoCounter++;
      }

      if (servoCounter == servoTime)
      {
        servoUpdate = false;
        lastPosition = tempLastPosition;
      }

    }

    void update()
    {
      if (servoUpdate)
      {
        this->positionUpdate();
      }
    }

    void reverse()
    {
      if (rev)
      {
        mapDegs = mapDegs - 180;
        mapDegs = abs(mapDegs);
      }
    }

};

servo headServo(3, 400, 200);
servo rightElbow(4, HTMAX, HTMIN, REVERSE);
servo rightShoulder(7, RIGHTSHOULDERMAX, SERVOMIN, REVERSE);
servo leftShoulder(12, SERVOMAX, LEFTSHOULDERMIN);
servo leftElbow(13, HTMAX, HTMIN);
servo leftHand(14, HANDMAX, HANDMIN);
servo rightHand(2, HANDMAX, HANDMIN);


class trck
{
    int pin, servoMax, servoMin, Speed;
  public:
    trck(int p)
    {
      pin = p;
    }

    void stopTrack()
    {
      pwm.setPWM(pin, 0, 320);
    }

    void moveTrack(int s)
    {
      if (s == -4)
      {
        Speed = 440;
      }
      else if (s == -3)
      {
        Speed = 410;
      }
      else if (s == -2)
      {
        Speed = 380;
      }
      else if (s == -1)
      {
        Speed = 350;
      }
      else if (s == 0)
      {
        Speed = 320;
      }
      else if (s == 1)
      {
        Speed = 290;
      }
      else if (s == 2)
      {
        Speed = 260;
      }
      else if (s == 3)
      {
        Speed = 230;
      }
      else if (s == 4)
      {
        Speed = 200;
      }

      pwm.setPWM(pin, 0, Speed);
    }

};

trck leftTrack(5);
trck rightTrack(6);

class trcks
{
    int trackTime;
    int trackCounter;

  public:

    void forward(int s, int t)
    {
      trackTime = t;
      trackCounter = 0;
      leftTrack.moveTrack(s);
      rightTrack.moveTrack(s);
    }

    void updateTracks()
    {
      if (trackCounter = trackTime)
      {
        leftTrack.stopTrack();
        rightTrack.stopTrack();
      }
      else
      {
        trackCounter++;
      }
    }

    void turnTracks(int left, int right, int t)
    {
      trackTime = t;
      trackCounter = 0;
      leftTrack.moveTrack(left);
      rightTrack.moveTrack(right);
    }

};

trcks tracks;

class Arm
{
    servo *shoulder;
    servo *elbow;
    servo *hand;
    char positionNum[DANCEARRAYLENGTH];
    int timer[DANCEARRAYLENGTH];
    char servoTime[DANCEARRAYLENGTH];
    int danceCounter = 0;
    int timerCounter = 0;
    boolean danceRun = false;

  public:
    void setServos(servo *s, servo *e, servo *h)
    {
      shoulder = s;
      elbow = e;
      hand = h;
    }

    void startDance()
    {
      danceCounter = 0;
      timerCounter = 0;
      danceRun = true;
    }
    void setDance(int i, int p, int t, int s)
    {
      positionNum[i] = p;
      timer[i] = t;
      servoTime[i] = s;
    }
    
    void stopDance()
    {
      danceRun = false;
      danceCounter = 0;
      timerCounter = 0;
    }

    void update()
    {

      if (danceRun)
      {
        if (timer[danceCounter] == timerCounter)
        {
          switch (positionNum[danceCounter])
          {
            case 0:
              shoulder->goToPosition(0, servoTime[danceCounter]);
              elbow->goToPosition(0, servoTime[danceCounter]);
              hand->goToPosition(0, servoTime[danceCounter]);
              break;

            case 1:
              shoulder->goToPosition(180, servoTime[danceCounter]);
              elbow->goToPosition(0, servoTime[danceCounter]);
              hand->goToPosition(0, servoTime[danceCounter]);
              break;

            case 2:
              shoulder->goToPosition(180, servoTime[danceCounter]);
              elbow->goToPosition(90, servoTime[danceCounter]);
              hand->goToPosition(0, servoTime[danceCounter]);
              break;

            case 3:
              shoulder->goToPosition(180, servoTime[danceCounter]);
              elbow->goToPosition(180, servoTime[danceCounter]);
              hand->goToPosition(0, servoTime[danceCounter]);
              break;

            case 4:
              shoulder->goToPosition(90, servoTime[danceCounter]);
              elbow->goToPosition(180, servoTime[danceCounter]);
              hand->goToPosition(0, servoTime[danceCounter]);
              break;

            case 5:
              shoulder->goToPosition(0, servoTime[danceCounter]);
              elbow->goToPosition(120, servoTime[danceCounter]);
              hand->goToPosition(0, servoTime[danceCounter]);
              break;

            case 6:
              shoulder->goToPosition(0, servoTime[danceCounter]);
              elbow->goToPosition(140, servoTime[danceCounter]);
              hand->goToPosition(180, servoTime[danceCounter]);
              break;

            case 7:
              shoulder->goToPosition(180, servoTime[danceCounter]);
              elbow->goToPosition(180, servoTime[danceCounter]);
              hand->goToPosition(180, servoTime[danceCounter]);
              break;
          }
          if (positionNum[danceCounter] == -1)
          {
            danceRun = false;
            Serial.println("End");
          }
          danceCounter++;
        }
        else
        {
          timerCounter++;
        }

        shoulder->update();
        elbow->update();
        hand->update();
      }
    }


};



class Head
{
    servo *headS;
    Mouth *mouthD;
    eye *eyesD;
    char positionNum[DANCEARRAYLENGTH];
    char servoTime[DANCEARRAYLENGTH];
    unsigned int timer[DANCEARRAYLENGTH];
    char mouthPosition[DANCEARRAYLENGTH];
    char eyePosition[DANCEARRAYLENGTH];
    unsigned char mouthRed[DANCEARRAYLENGTH];
    unsigned char mouthGreen[DANCEARRAYLENGTH];
    unsigned char mouthBlue[DANCEARRAYLENGTH];
    unsigned char eyeRed[DANCEARRAYLENGTH];
    unsigned char eyeGreen[DANCEARRAYLENGTH];
    unsigned char eyeBlue[DANCEARRAYLENGTH];
    int danceCounter = 0;
    int timerCounter = 0;
    boolean danceRun = false;

  public:
    Head()
    {
    
    }
    
    
    void setServos(servo *h, Mouth *m, eye *e)
    {
      headS = h;
      mouthD = m;
      eyesD = e;
    }
    
    void startDance()
    {
      danceCounter = 0;
      timerCounter = 0;
      danceRun = true;
    }
    
    void setDance(int i, int p, unsigned int t, int s, int m, unsigned char eR, unsigned char eG, unsigned char eB, unsigned char mR, unsigned char mG, unsigned char mB)
    {
      positionNum[i] = p;
      servoTime[i] = s;
      timer[i] = t;
      mouthPosition[i] = m;
      eyeRed[i] = eR;
      eyeGreen[i] = eG;
      eyeBlue[i] = eB;
      mouthRed[i] = mR;
      mouthGreen[i] = mG;
      mouthBlue[i] = mB;
    }
    
    void stopDance()
    {
      danceRun = false;
      danceCounter = 0;
      timerCounter = 0;
      
    }
    
    void update()
    {
      if(danceRun)
      {
        if(timer[danceCounter] == timerCounter)
        {
          headS->goToPosition(positionNum[danceCounter], servoTime[danceCounter]);
          
          if(positionNum[danceCounter] > 150)
          {
            eyePosition[danceCounter] = 4;
          }
          else if(positionNum[danceCounter] < 30)
          {
            eyePosition[danceCounter] = 3;
          }
          else
          {
            eyePosition[danceCounter] = 1;
          }
          
          switch(mouthPosition[danceCounter])
          {
            case 1:
            mouth.mOpen(mouthRed[danceCounter], mouthGreen[danceCounter], mouthBlue[danceCounter]);
            break;
            
            case 2:
            mouth.straight(mouthRed[danceCounter], mouthGreen[danceCounter], mouthBlue[danceCounter]);
            break;
            
            case 3:
            mouth.frown(mouthRed[danceCounter], mouthGreen[danceCounter], mouthBlue[danceCounter]);
            break;
            
            case 4:
            mouth.smile(mouthRed[danceCounter], mouthGreen[danceCounter], mouthBlue[danceCounter]);
            break;
          }
          
          switch(eyePosition[danceCounter])
          {
            case 1:
            eyes.on(eyeRed[danceCounter], eyeGreen[danceCounter], eyeBlue[danceCounter]);
            break;
            
            case 2:
            eyes.OFF();
            break;
            
            case 3: 
            eyes.lookLeft();
            break;
            
            case 4:
            eyes.lookRight();
            break;
          }
        
        danceCounter++;
        }
        else
        {
          timerCounter++;
        }
        if(positionNum[danceCounter] == -1)
        {
          this->stopDance();
          dancing = false;
        }
        headServo.update();
      }
    }

};

class Legs
{

    trcks *tracks;
    boolean danceRun = false;
    int danceCounter = 0;
    int timerCounter = 0;
    int leftPosition[DANCEARRAYLENGTH];
    int rightPosition[DANCEARRAYLENGTH];
    int timer[DANCEARRAYLENGTH];
    int trackTime[DANCEARRAYLENGTH];
  public:
    Legs()
    {
    
    }
    
    void setServos(trcks *t)
    {
      tracks = t;
    }
    
    void startDance()
    {
      danceRun = true;
      danceCounter = 0;
      timerCounter = 0;
    }
    
    void setDance(int i, int l, int r, int t, int tt)
    {
      leftPosition[i] = l;
      rightPosition[i] = r;
      timer[i] = t;
      trackTime[i] = tt;
    }
    
    void stopDance()
    {
      danceRun = false;
      danceCounter = 0;
      timerCounter = 0;
    }
    
    void update()
    {
      if(danceRun)
      {
        if(timer[danceCounter] == timerCounter)
        {
          tracks->turnTracks(leftPosition[danceCounter], rightPosition[danceCounter], trackTime[danceCounter]);
          danceCounter++;
        }
        else
        {
          timerCounter++;
        }
        if(leftPosition[danceCounter] == -1)
        {
          this->stopDance();
        }
      }
      tracks->updateTracks();
    }
};

class DanceLeds
{
  int timer[LEDARRAYLENGTH];
  unsigned char legRed[LEDARRAYLENGTH];
  unsigned char legGreen[LEDARRAYLENGTH];
  unsigned char legBlue[LEDARRAYLENGTH];
  unsigned char armRed[LEDARRAYLENGTH];
  unsigned char armGreen[LEDARRAYLENGTH];
  unsigned char armBlue[LEDARRAYLENGTH];
  unsigned char frontRed[LEDARRAYLENGTH];
  unsigned char frontGreen[LEDARRAYLENGTH];
  unsigned char frontBlue[LEDARRAYLENGTH];
  unsigned char topBarRed[LEDARRAYLENGTH];
  unsigned char topBarGreen[LEDARRAYLENGTH];
  unsigned char topBarBlue[LEDARRAYLENGTH];
  unsigned char frontBumperRed[LEDARRAYLENGTH];
  unsigned char frontBumperGreen[LEDARRAYLENGTH];
  unsigned char frontBumperBlue[LEDARRAYLENGTH];
  unsigned char rearBumperRed[LEDARRAYLENGTH];
  unsigned char rearBumperGreen[LEDARRAYLENGTH];
  unsigned char rearBumperBlue[LEDARRAYLENGTH];
  unsigned char legPattern[LEDARRAYLENGTH];
  unsigned char armPattern[LEDARRAYLENGTH];
  unsigned char topBarPattern[LEDARRAYLENGTH];
  unsigned char frontBumperPattern[LEDARRAYLENGTH];
  unsigned char rearBumperPattern[LEDARRAYLENGTH];
  unsigned char frontPattern[LEDARRAYLENGTH];
  unsigned char legInterval[LEDARRAYLENGTH];
  unsigned char armInterval[LEDARRAYLENGTH];
  unsigned char topBarInterval[LEDARRAYLENGTH];
  unsigned char frontBumperInterval[LEDARRAYLENGTH];
  unsigned char rearBumperInterval[LEDARRAYLENGTH];
  unsigned char frontInterval[LEDARRAYLENGTH];
  unsigned char legNumLeds[LEDARRAYLENGTH];
  unsigned char armNumLeds[LEDARRAYLENGTH];
  unsigned char topBarNumLeds[LEDARRAYLENGTH];
  unsigned char frontBumperNumLeds[LEDARRAYLENGTH];
  unsigned char rearBumperNumLeds[LEDARRAYLENGTH];
  unsigned char frontNumLeds[LEDARRAYLENGTH];
  int timerCounter = 0;
  int danceCounter = 0;
  boolean danceRun = false;

  
  

  public:
    DanceLeds()
    {

    }
    
    void startDance()
    {
      danceRun = true;
      danceCounter = 0;
      timerCounter = 0;
    }
    
    void setDance(int i, int t, unsigned char lR, unsigned char lG, unsigned char lB, unsigned char aR, unsigned char aG, unsigned char aB, unsigned char fR, unsigned char fG, unsigned char fB, unsigned char tBR, unsigned char tBG, unsigned char tBB, unsigned char fBR, unsigned char fBG, unsigned char fBB, unsigned char rBR, unsigned char rBG, unsigned char rBB, char lP, char aP, char tBP, char fBP, char rBP, char fP, unsigned char lI, unsigned char aI, unsigned char tBI, unsigned char fBI, unsigned char rBI, unsigned char fI, char lN, char aN, char tBN, char fBN, char rBN, char fN)
    {
      timer[i] = t;
      legRed[i] = lR;
      legGreen[i] = lG;
      legBlue[i] = lB;
      armRed[i] = aR;
      armGreen[i] = aG;
      armBlue[i] = aB;
      frontRed[i] = fR;
      frontBlue[i] = fB;
      frontGreen[i] = fG;
      topBarRed[i] = tBR;
      topBarGreen[i] = tBG;
      topBarBlue[i] = tBB;
      frontBumperRed[i] = fBR;
      frontBumperGreen[i] = fBG;
      frontBumperBlue[i] = fBB;
      rearBumperRed[i] = rBR;
      rearBumperGreen[i] = rBG;
      rearBumperBlue[i] = rBB;
      legPattern[i] = lP;
      armPattern[i] = aP;
      topBarPattern[i] = tBP;
      frontBumperPattern[i] = fBP;
      rearBumperPattern[i] = rBP;
      frontPattern[i] = fP;
      legInterval[i] = lI;
      armInterval[i] = aI;
      topBarInterval[i] = tBI;
      frontBumperInterval[i] = fBI;
      rearBumperInterval[i] = rBI;
      frontInterval[i] = fI;
      legNumLeds[i] = lN;
      armNumLeds[i] = aN;
      topBarNumLeds[i] = tBN;
      frontBumperNumLeds[i] = fBN;
      rearBumperNumLeds[i] = rBN;
      frontNumLeds[i] = fN;
    }
    
    void stopDance()
    {
      danceRun = false;
      danceCounter = 0;
      timerCounter = 0;
    }

    void update()
    {
      if(danceRun)
      {
        if(timer[danceCounter] == timerCounter)
        {
          leftLeg.setColor(legRed[danceCounter], legGreen[danceCounter], legBlue[danceCounter]);
          rightLeg.setColor(legRed[danceCounter], legGreen[danceCounter], legBlue[danceCounter]);
          leftLeg.doLeds(legPattern[danceCounter], legInterval[danceCounter], legNumLeds[danceCounter]);
          rightLeg.doLeds(legPattern[danceCounter], legInterval[danceCounter], legNumLeds[danceCounter]);
          
          leftArmLed.setColor(armRed[danceCounter], armGreen[danceCounter], armBlue[danceCounter]);
          rightArmLed.setColor(armRed[danceCounter], armGreen[danceCounter], armBlue[danceCounter]);
          leftArmLed.doLeds(armPattern[danceCounter], armInterval[danceCounter], armNumLeds[danceCounter]);
          rightArmLed.doLeds(armPattern[danceCounter], armInterval[danceCounter], armNumLeds[danceCounter]);
          
          topBar.setColor(topBarRed[danceCounter], topBarGreen[danceCounter], topBarBlue[danceCounter]);
          topBar.doLeds(topBarPattern[danceCounter], topBarInterval[danceCounter], topBarNumLeds[danceCounter]);
          
          frontBumper.setColor(frontBumperRed[danceCounter], frontBumperGreen[danceCounter], frontBumperBlue[danceCounter]);
          frontBumper.doLeds(frontBumperPattern[danceCounter], frontBumperGreen[danceCounter], frontBumperBlue[danceCounter]);
          
          rearBumper.setColor(rearBumperRed[danceCounter], rearBumperGreen[danceCounter], rearBumperBlue[danceCounter]);
          rearBumper.doLeds(rearBumperPattern[danceCounter], rearBumperInterval[danceCounter], rearBumperNumLeds[danceCounter]);
          
          leftFront.setColor(frontRed[danceCounter], frontGreen[danceCounter], frontBlue[danceCounter]);
          rightFront.setColor(frontRed[danceCounter], frontGreen[danceCounter], frontBlue[danceCounter]);
          leftFront.doLeds(frontPattern[danceCounter], frontInterval[danceCounter], frontNumLeds[danceCounter]);
          rightFront.doLeds(frontPattern[danceCounter], frontInterval[danceCounter], frontNumLeds[danceCounter]);
          
          danceCounter++;   
        }
        else
        {
          timerCounter++;
        }
      }
    }
};

Arm leftArm;
Arm rightArm;
Head head;
Legs legs;
DanceLeds danceLeds;


  
class Dance
{
    int danceCounter = 0 ;
    int song;

  public:
    Dance()
    {
    }

    void startDance()
    {
      rightArm.startDance();
      leftArm.startDance();
      head.startDance();
      legs.startDance();
      danceLeds.startDance();
      doI2C(song);
      dancing = true;
    }
    
    void setSong(int s)
    {
      song = s;
    }
    
    void stopDance()
    {
      rightArm.stopDance();
      leftArm.stopDance();
      head.stopDance();
      legs.stopDance();
      danceLeds.stopDance();
      doI2C(0);
      dancing = false;
    }

    void updateDance()
    {
      if(!dancing)
      {
        this->stopDance();
      }
      leftArm.update();
      rightArm.update();
      head.update();
      legs.update();
      danceLeds.update();
    }
};


Dance dance;



void setup() {
  // put your setup code here, to run once:
  pinMode(52, INPUT);
  pinMode(50, INPUT);
  pinMode(48, INPUT);
  pinMode(46, INPUT);
  pinMode(14, INPUT);
  pinMode(15, INPUT);
  pinMode(16, INPUT);
  pinMode(53, OUTPUT);
  digitalWrite(53, HIGH);
  digitalWrite(52, HIGH);
  digitalWrite(50, HIGH);
  digitalWrite(48, HIGH);
  digitalWrite(46, HIGH);
  digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);
  digitalWrite(16, HIGH);
  Wire.begin();
  pwm.begin();
  pwm.setPWMFreq(60);
  off.red = 0; 
  off.green = 0;
  off.blue = 0;
  Serial.begin(9600);
  Timer3.initialize(10000);
  Timer3.attachInterrupt(timer);
  leftArm.setServos(&leftShoulder, &leftElbow, &leftHand);
  rightArm.setServos(&rightShoulder, &rightElbow, &rightHand);
  head.setServos(&headServo, &mouth, &eyes);
  legs.setServos(&tracks);
  rearBumper.setColor(255, 255, 255);
  rearBumper.doLeds(SCROLL, 4, 5);
  doI2C(0);
  idleLeds();
}

void timer()
{
  timerExp = true;
  if (timerCounter == 10)
  {
    hundredMillis = true;
    timerCounter = 0;
  }
  else
  {
    timerCounter++;
  }
}

void readInputs()
{
  if (switch1 != digitalRead(46))
  {
    doSwitch1();
  }
  if (switch2 != digitalRead(48))
  {
    doSwitch2();
  }
  if (switch3 != digitalRead(50))
  {
    doSwitch3();
  }
  if (switch4 != digitalRead(52))
  {
    doSwitch4();
  }
  if(switch5 != digitalRead(14))
  {
    doSwitch5();
  }
  if(switch6 != digitalRead(15))
  {
    doSwitch6();
  }
  if(switch7 != digitalRead(16))
  {
    doSwitch7();
  }
  switch1 = digitalRead(46);
  switch2 = digitalRead(48);
  switch3 = digitalRead(50);
  switch4 = digitalRead(52);
  switch5 = digitalRead(14);
  switch6 = digitalRead(15);
  switch7 = digitalRead(16);
}

void doSwitch1()
{
  if (switch1 == HIGH)
  {
    digitalWrite(53, HIGH);
    dancing = false;
    arduinoControl = false;
    idleLeds();
  }
  else
  {
    digitalWrite(53, LOW);
    dancing = false;
    arduinoControl = true;
    idleLeds();
  }
}

void doSwitch2()
{
  if(switch2 == LOW && arduinoControl)
  {
    if(whichDance)
    {
      setMrRoboto();
      whichDance = !whichDance;
    }
    else
    {
      setSafetyDance();
      whichDance = !whichDance;
    }
  }
  
  if(switch2 == HIGH)
  {
    dance.stopDance();
    idleLeds();
  }
}

void doSwitch3()
{
  if(!dancing)
  {
    if(switch3 == HIGH)
    {
      rightArmLed.on(255, 0, 0);
      leftArmLed.on(255, 0, 0);
      rearBumper.on(255, 0, 0);
      frontBumper.on(255, 0, 0);
      topBar.on(255, 0, 0);
      leftFront.on(255, 0, 0);
      rightFront.on(255, 0, 0);
      leftLeg.on(255, 0, 0);
      rightLeg.on(255, 0, 0);
      
      rightArmLed.doLeds(-1, 50, 10);
      leftArmLed.doLeds(-1, 50, 10);
      rearBumper.doLeds(-1, 50, 10);
      frontBumper.doLeds(-1, 50, 10);
      topBar.doLeds(-1, 50, 10);
      leftFront.doLeds(-1, 50, 10);
      rightFront.doLeds(-1, 50, 10);
      leftLeg.doLeds(-1, 50, 10);
      rightLeg.doLeds(-1, 50, 10);
      
      headServo.goToPosition(180, 20);
      
      mouth.frown(255, 0, 0);
      eyes.on(255, 0, 0);
    }
    else
    {
      rightArmLed.on(150, 150, 150);
      leftArmLed.on(150, 150, 150);
      rearBumper.on(150, 150, 150);
      frontBumper.on(150, 150, 150);
      topBar.on(150, 150, 150);
      leftFront.on(150, 150, 150);
      rightFront.on(150, 150, 150);
      leftLeg.on(150, 150, 150);
      rightLeg.on(150, 150, 150);
      
      rightArmLed.doLeds(-1, 50, 10);
      leftArmLed.doLeds(-1, 50, 10);
      rearBumper.doLeds(SCROLL, 10, 5);
      frontBumper.doLeds(SCROLL, 10, 5);
      topBar.doLeds(-1, 50, 10);
      leftFront.doLeds(-1, 50, 10);
      rightFront.doLeds(-1, 50, 10);
      leftLeg.doLeds(-1, 50, 10);
      rightLeg.doLeds(-1, 50, 10);
      
      headServo.goToPosition(0, 20);
      
      mouth.smile(150, 150, 150);
      eyes.on(150, 150, 150);
    }
  }
  
}

void doSwitch4()
{
  if(!dancing)
  {
    if(switch4 == HIGH)
    {
      doI2C(GETTOCLASS);
      rightArmLed.setColor(255, 0, 0);
      leftArmLed.setColor(255, 0, 0);
      rearBumper.setColor(255, 0, 0);
      frontBumper.setColor(255, 0, 0);
      topBar.setColor(255, 0, 0);
      leftFront.setColor(255, 0, 0);
      rightFront.setColor(255, 0, 0);
      leftLeg.setColor(255, 0, 0);
      rightLeg.setColor(255, 0, 0);
    
      rightArmLed.doLeds(FLASHTIME, 1, 50, 10);
      leftArmLed.doLeds(FLASHTIME, 1, 50, 10);
      rearBumper.doLeds(FLASHTIME, 1, 50, 10);
      frontBumper.doLeds(FLASHTIME, 1, 50, 10);
      topBar.doLeds(FLASHTIME, 1, 50, 10);
      leftFront.doLeds(FLASHTIME, 1, 50, 10);
      rightFront.doLeds(FLASHTIME, 1, 50, 10);
      leftLeg.doLeds(FLASHTIME, 1, 50, 10);
      rightLeg.doLeds(FLASHTIME, 1, 50, 10);
      
      mouth.frown(255, 0, 0);
      eyes.on(255, 0, 0);
    }
  }
}

void doSwitch5()
{
  if(arduinoControl)
  {
    if(switch6 == LOW)
    {
      dance.stopDance();
    }
    Serial.println("Stop");
  }
}

void doSwitch6()
{
  if(!dancing && switch6 == LOW)
  {
    doI2C(LAUGH);
    rightArmLed.setColor(255, 0, 0);
    leftArmLed.setColor(255, 0, 0);
    rearBumper.setColor(255, 0, 0);
    frontBumper.setColor(255, 0, 0);
    topBar.setColor(255, 0, 0);
    leftFront.setColor(255, 0, 0);
    rightFront.setColor(255, 0, 0);
    leftLeg.setColor(255, 0, 0);
    rightLeg.setColor(255, 0, 0);
    
    rightArmLed.doLeds(FLASHTIME, 10, 50, 100);
    leftArmLed.doLeds(FLASHTIME, 10, 50, 100);
    rearBumper.doLeds(FLASHTIME, 50, 100);
    frontBumper.doLeds(FLASHTIME, 50, 100);
    topBar.doLeds(FLASHTIME, 50, 100);
    leftFront.doLeds(FLASHTIME, 50, 100);
    rightFront.doLeds(FLASHTIME, 50, 100);
    leftLeg.doLeds(FLASHTIME, 50, 100);
    rightLeg.doLeds(FLASHTIME, 50, 100);
    
    mouth.mOpen(150, 150, 150);
    eyes.on(150, 150, 150);
  }
}

void doSwitch7()
{
  if(arduinoControl)
  {
    if(switch7 == LOW)
    {
      if(whichDance)
      {
        setMrRoboto();
        whichDance = !whichDance;
      }
      else
      {  
        setSafetyDance();
        whichDance = !whichDance;
      }
    }
  }
}

void stopMusic ()
{
  doI2C(0);
}

void idleLeds()
{
  rightArmLed.on(150, 150, 150);
  leftArmLed.on(150, 150, 150);
  rearBumper.on(150, 150, 150);
  frontBumper.on(150, 150, 150);
  topBar.on(150, 150, 150);
  leftFront.on(150, 150, 150);
  rightFront.on(150, 150, 150);
  leftLeg.on(150, 150, 150);
  rightLeg.on(150, 150, 150);
      
  rightArmLed.doLeds(-1, 50, 10);
  leftArmLed.doLeds(-1, 50, 10);
  rearBumper.doLeds(SCROLL, 10, 5);
  frontBumper.doLeds(SCROLL, 10, 5);
  topBar.doLeds(-1, 50, 10);
  leftFront.doLeds(-1, 50, 10);
  rightFront.doLeds(-1, 50, 10);
  leftLeg.doLeds(-1, 50, 10);
  rightLeg.doLeds(-1, 50, 10);
      
  headServo.goToPosition(0, 20);
      
  mouth.smile(150, 150, 150);
  eyes.on(150, 150, 150);
}

void setMrRoboto()
{
  
  dance.setSong(MRROBOTO);
  setRandomArmsSame(3300, 20);
  danceLeds.setDance(0, 10, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, FLASH, FLASH, FLASH, FLASH, FLASH, FLASH, 200, 200, 200, 200, 200, 200, 4, 1, 2, 2, 1, 1);
  danceLeds.setDance(1, 200, 200, 0, 0, 200, 0, 0, 200, 0, 0, 200, 0, 0, 200, 0, 0, 200, 0, 0, SCROLL, SCROLL, SCROLL, SCROLL, SCROLL, SCROLL, 10, 10, 5, 5, 10, 10, 4, 2, 2, 2, 2, 2);
  danceLeds.setDance(2, 800, 0, 0, 200, 0, 0, 200, 0, 0, 200, 0, 0, 200, 0, 0, 200, 0, 0, 200, FLASH, FLASH, FLASH, FLASH, FLASH, FLASH, 100, 100, 500, 500, 100, 100, 4, 2, 2, 2, 2, 2);
  danceLeds.setDance(3, 1100, 0, 200, 0, 0, 200, 0, 0, 200, 0, 0, 200, 0, 0, 200, 0, 0, 200, 0, FLASH, FLASH, FLASH, FLASH, FLASH, FLASH, 200, 200, 50, 50, 150, 150, 4, 2, 2, 2, 2, 2);
  danceLeds.setDance(4, 1700, 255, 0, 200, 255, 0, 200, 0, 200, 255, 0, 0, 200, 255, 200, 0, 255, 200, 0, SCROLL, SCROLL, SCROLL, SCROLL, SCROLL, SCROLL, 10, 10, 5, 5, 10, 10, 4, 2, 2, 2, 2, 2);
  danceLeds.setDance(5, 2200, 200, 0, 200, 200, 0, 200, 0, 200, 200, 0, 0, 200, 200, 200, 0, 200, 200, 0, FLASH, FLASH, FLASH, FLASH, FLASH, FLASH, 100, 100, 50, 50, 100, 100, 4, 2, 2, 2, 2, 2);
  danceLeds.setDance(6, 2700, 200, 99, 150, 250, 25, 250, 0, 200, 250, 0, 50, 200, 120, 200, 37, 100, 200, 78, SCROLL, SCROLL, SCROLL, SCROLL, SCROLL, SCROLL, 10, 10, 5, 5, 10, 10, 4, 2, 2, 2, 2, 2);
  danceLeds.setDance(7, 3200, 78, 70, 47, 47, 167, 86, 196, 158, 233, 253, 0, 120, 200, 212, 231, 200, 212, 0, FLASH, FLASH, FLASH, FLASH, FLASH, FLASH, 1000, 1000, 500, 500, 1000, 1000, 4, 2, 2, 2, 2, 2);
  danceLeds.setDance(8, 4300, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, SCROLL, SCROLL, SCROLL, SCROLL, SCROLL, SCROLL, 100, 100, 50, 50, 100, 100, 4, 2, 2, 2, 2, 2);
  
  head.setDance(0, 180, 0, 20, 1, 0, 0, 255, 255, 255, 255);
  head.setDance(1, 0, 50, 20, 2, 1, 0, 0, 1, 0, 0);
  head.setDance(2, 180, 60, 20, 2, 1, 0, 0, 1, 0, 0);
  dance.startDance();
}

void setSafetyDance()
{
  dance.setSong(SAFETYDANCE);
  setRandomArms(3000);
  danceLeds.setDance(0, 10, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, SCROLL, SCROLL, SCROLL, SCROLL, SCROLL, SCROLL, 1000, 1000, 500, 500, 1000, 1000, 4, 1, 2, 2, 1, 1);
  danceLeds.setDance(1, 200, 200, 0, 0, 200, 0, 0, 200, 0, 0, 200, 0, 0, 200, 0, 0, 200, 0, 0, SCROLL, SCROLL, SCROLL, SCROLL, SCROLL, SCROLL, 10, 10, 5, 5, 10, 10, 4, 2, 2, 2, 2, 2);
  danceLeds.setDance(2, 800, 0, 0, 200, 0, 0, 200, 0, 0, 200, 0, 0, 200, 0, 0, 200, 0, 0, 200, FLASH, FLASH, FLASH, FLASH, FLASH, FLASH, 100, 100, 500, 500, 100, 100, 4, 2, 2, 2, 2, 2);
  danceLeds.setDance(3, 1200, 0, 200, 0, 0, 200, 0, 0, 200, 0, 0, 200, 0, 0, 200, 0, 0, 200, 0, FLASH, FLASH, FLASH, FLASH, FLASH, FLASH, 200, 200, 50, 50, 150, 150, 4, 2, 2, 2, 2, 2);
  danceLeds.setDance(4, 1600, 255, 0, 200, 255, 0, 200, 0, 200, 255, 0, 0, 200, 255, 200, 0, 255, 200, 0, SCROLL, SCROLL, SCROLL, SCROLL, SCROLL, SCROLL, 10, 10, 5, 5, 10, 10, 4, 2, 2, 2, 2, 2);
  danceLeds.setDance(5, 2000, 200, 0, 200, 200, 0, 200, 0, 200, 200, 0, 0, 200, 200, 200, 0, 200, 200, 0, FLASH, FLASH, FLASH, FLASH, FLASH, FLASH, 100, 100, 50, 50, 100, 100, 4, 2, 2, 2, 2, 2);
  danceLeds.setDance(6, 2400, 200, 99, 150, 250, 25, 250, 0, 200, 250, 0, 50, 200, 120, 200, 37, 100, 200, 78, SCROLL, SCROLL, SCROLL, SCROLL, SCROLL, SCROLL, 10, 10, 5, 5, 10, 10, 4, 2, 2, 2, 2, 2);
  danceLeds.setDance(7, 2800, 78, 70, 47, 47, 167, 86, 196, 158, 233, 253, 0, 120, 200, 212, 231, 200, 212, 0, FLASH, FLASH, FLASH, FLASH, FLASH, FLASH, 1000, 1000, 500, 500, 1000, 1000, 4, 2, 2, 2, 2, 2);
  danceLeds.setDance(8, 3200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, SCROLL, SCROLL, SCROLL, SCROLL, SCROLL, SCROLL, 100, 100, 50, 50, 100, 100, 4, 2, 2, 2, 2, 2);
  
  head.setDance(0, 180, 10, 20, 1, 0, 0, 255, 255, 255, 255);
  head.setDance(1, 0, 50, 20, 2, 1, 0, 0, 1, 0, 0);
  head.setDance(2, 180, 60, 20, 2, 1, 0, 0, 1, 0, 0);
  dance.startDance();
}

void setRandomArms(int danceTime)
{
  int positionNum;
  int time = 0;
  int servoTime;
  int temp;
  boolean c = true;
  for(int i = 0; i < DANCEARRAYLENGTH; i = i + 0)
  {
   positionNum = random(7);
   do
   {
      temp = random(1, 10);
      servoTime = random(10);
   }while(temp < servoTime);
   
   time = time + temp;
   Serial.println(time, DEC);
   
   if(c)
   {
    rightArm.setDance(i, positionNum, time, servoTime);
    c = false;
   }
   else
   {
     leftArm.setDance(i, positionNum, time, servoTime);
     c = true;
     i++;
   }
   
   if(time >= danceTime)
   {
     rightArm.setDance((i+1), -1, 1, 1);
     leftArm.setDance((i+1), -1, 1, 1);
     break;
   }
  }
}

void setRandomArmsSameRandomInterval(int danceTime)
{
  int positionNum;
  int time;
  int servoTime;
  int temp;
  boolean c = true;
  for(int i = 0; i < DANCEARRAYLENGTH; i++)
  {
   positionNum = random(7);
   do
   {
      temp = random(5, 20);
      servoTime = random(15);
   }while(temp < servoTime);
   
   time = time + temp;
   Serial.println(time, DEC);
   rightArm.setDance(i, positionNum, time, servoTime);
   leftArm.setDance(i, positionNum, time, servoTime);
   
   if(time >= danceTime)
   {
     rightArm.setDance((i+1), -1, 1, 1);
     leftArm.setDance((i+1), -1, 1, 1);
     break;
   }
  }
}

void setRandomArmsSame(int danceTime, int interval)
{
  int positionNum;
  int time = 0;
  int servoTime;
  int temp;
  boolean c = true;
  for(int i = 0; i < DANCEARRAYLENGTH; i++)
  {
    positionNum = random(7);
    servoTime = random(interval);
    time = time + interval;
    Serial.println(time, DEC);
    Serial.println(i, DEC);
    rightArm.setDance(i, positionNum, time, servoTime);
    leftArm.setDance(i, positionNum, time, servoTime);
   
   if(time >= danceTime)
   {
     rightArm.setDance((i+1), -1, 1, 1);
     leftArm.setDance((i+1), -1, 1, 1);
     break;
   }
  }
}


void loop() {
  // put your main code here, to run repeatedly:

  if (timerExp)
  {
    readInputs();
    leftLeg.updateLeds();
    rightLeg.updateLeds();
    leftArmLed.updateLeds();
    rightArmLed.updateLeds();
    topBar.updateLeds();
    frontBumper.updateLeds();
    rearBumper.updateLeds();
    leftFront.updateLeds();
    rightFront.updateLeds();    
    timerExp = false;
    eyes.Blink(BLINKINTERVAL);
  }
  if (hundredMillis)
  {
    
    dance.updateDance();
    //headServo.update();
    hundredMillis = false; 
  }
  if(I2C)
  {
    sendI2C();
    I2C = false;
  }
}