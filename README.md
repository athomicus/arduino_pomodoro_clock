# arduino_pomodoro_clock
   <img width="224" height="189" alt="obraz" src="https://github.com/user-attachments/assets/5efea825-89bd-4e49-8efb-27596435bd77" />




Idea was to create simple timer for counting ~30 minutes.<br>
The Pomodoro Technique is a time-management method that uses a timer to break work into intervals, 
traditionally 25 minutes in length, separated by short breaks. 
Each interval is called a "pomodoro" (the Italian word for tomato). 
The process involves identifying a task, working on it with no distractions for 25 minutes, taking a 5-minute break, and repeating this for four pomodoros
<br>

https://github.com/user-attachments/assets/8372e83a-47a1-4b83-885f-ee5969b65357

<br>


How it works ( idea for my counter)
- clock showing animation
- when you click button then using interruption function will set variable  counting_active to  <b>true</b>
```C
 ISR(PCINT1_vect)  //przerwanie
 {
  counting_active = true;
  startTime=millis();
  clear_progress();
  startTimeInterval=millis();     
  counting_active=true;
} 
```
- clock will start counting lighting up another LEDs (to make it easier I used internal arduino
  
  ![leds](https://github.com/user-attachments/assets/28c73d8a-36a1-436b-a800-9d56f5fb2bb2)
- after end of time animation will start again
  
   ![anim](https://github.com/user-attachments/assets/746fc7d6-0ad1-4c37-93d3-ff2f4c6e10fb)

<br><br>
# parts I used:
- Led Matrix 1088BS*
  
   ![matrix](https://github.com/user-attachments/assets/58eb4fb9-4a1a-4e8a-ad68-cec9e511c7f7)
- Arduino Uno
- Cables
- button
- case for Arduino
- case for battery ( 9V )
  
  ![parts](https://github.com/user-attachments/assets/918d0b44-aea4-4731-92d5-e03515346a3a)

<br><br>
# connect everything together:
I used some scheme from the web:
<br>
![projekt16](https://github.com/user-attachments/assets/893a50c4-d830-4703-b7c2-4933c5b768fa)
<br>
Important thing is to connect properly cables to selected PINs in Arduino so
if you look at the LED Matrix 8x8 ther is a signature <b>1088BS</b> so starting from left, 
- brown cable go into a Arduino PIN <b>A5</b>
- red cable go into a Arduino PIN <b>A4</b>
- orange cable go into a Arduino PIN <b>A3</b>
- yellow cable go into a Arduino PIN <b>A2</b>
- green cable go into a Arduino PIN <b>13</b>
<br>etc...

<img width="323" height="243" alt="obraz" src="https://github.com/user-attachments/assets/16c5f981-7b4e-4971-84d3-94db6b52aa9e" />
<br><br>

![conm](https://github.com/user-attachments/assets/b5d43575-6302-4c8f-85c0-3560720f18bc)



<br><BR><br><br>
  <i>*what I noticed you can buy Led Matrtix 8x8 with driver so you can use less cable connections and should be easier setup than my:
  <img width="745" height="323" alt="obraz" src="https://github.com/user-attachments/assets/1cb57faf-91a7-4a69-aec8-6ecc9c12a1b3" />
<Br> there is also an version with "A" - dont remember exactly for ie: <b> 1088AS</b> for that you need to use different scheme cable connections(opposite)
<br><br> steering this led is a little bit tricky because they are blinking always in a loop and you have the impression that they are alwayes turned on - you can see the pictures it seems that some of leds are not working</i>

<br><br>

# code:
<br>


```C

unsigned long startTime = 0, startTimeInterval = 0; //: Stores the start time of the Pomodoro and the start time of the current LED interval
unsigned long currentTime = 0, currentTimeInterval = 0; //: Tracks elapsed total time and elapsed time since last LED update
const int ButtonPin = 1; //: Pin number for the button input
const unsigned long ONE_POMODORO = 1800000; //: Duration of one Pomodoro session in milliseconds (30 minutes)
const unsigned long PART_POMODORO = 28125; //: Time interval for lighting the next LED (~0.46 minutes)
bool counting_active = false; //: Flag to indicate if the Pomodoro timer is running
const int cols[] = {5, A3, A2, 8, 12, 7, 3, 2}; //: Column pin configuration for LED matrix
const int rows[] = {9, 4, 10, 6, A5, 11, A4, 13}; //: Row pin configuration for LED matrix
int x = 0, y = 0; //: Coordinates for progress LED position

int progress[8][8] = { //: Progress pattern (1 = LED on, 0 = LED off)
    {1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},  
    {0, 0, 0, 0, 0, 0, 0, 0},  
    {0, 0, 0, 0, 0, 0, 0, 0},  
    {0, 0, 0, 0, 0, 0, 0, 0},  
    {0, 0, 0, 0, 0, 0, 0, 0},  
    {0, 0, 0, 0, 0, 0, 0, 0},  
    {0, 0, 0, 0, 0, 0, 0, 0}  
};

//: Various 8x8 LED patterns (1 = LED on, 0 = LED off)
const int big_heart[8][8] = { /* ... */ };
const int small_heart[8][8] = { /* ... */ };
const int brick[8][8] = { /* ... */ };
const int angry_robot[8][8] = { /* ... */ };
const int squares_0[8][8] = { /* ... */ };
const int squares_1[8][8] = { /* ... */ };
const int squares_2[8][8] = { /* ... */ };
const int squares_3[8][8] = { /* ... */ };
const int squares_4[8][8] = { /* ... */ };
const int smile[8][8] = { /* ... */ };
const int smile_talk[8][8] = { /* ... */ };
const int character1[8][8] = { /* ... */ };
const int cool[8][8] = { /* ... */ };
const int enemy_1[8][8] = { /* ... */ };
const int bomb[8][8] = { /* ... */ };
const int pacman[8][8] = { /* ... */ };
const int enemy_2[8][8] = { /* ... */ };
const int enemy_2a[8][8] = { /* ... */ };

void setup() {
    //: Configure A0 as input with pull-up resistor
    pinMode(A0, INPUT_PULLUP);

    //: Enable pin change interrupt for PORTC (PCINT[14:8])
    PCICR |= (1 << PCIE1);
    PCMSK1 |= (1 << PCINT8); //: Enable interrupt for pin A0

    //: Initialize LED matrix pins and turn all LEDs off
    for (int i = 0; i < 8; i++) {
        pinMode(rows[i], OUTPUT);
        pinMode(cols[i], OUTPUT);
        digitalWrite(rows[i], LOW);
        digitalWrite(cols[i], HIGH);
    }
}

//: Draws a given 8x8 pattern on the LED matrix
void draw_pattern_on_led_matrix(const int pattern[8][8]) {   
    for (int i = 0; i < 8; i++) {
        digitalWrite(rows[i], HIGH); //: Activate current row
        for (int j = 0; j < 8; j++) {
            if (pattern[i][j] == 1) {
                digitalWrite(cols[j], LOW); //: Turn LED on
            } else {
                digitalWrite(cols[j], HIGH); //: Turn LED off
            }
        }
        delay(2); //: Small delay for persistence of vision
        digitalWrite(rows[i], LOW); //: Deactivate row
    }
}

//: Resets the progress array and lights the first LED
void clear_progress() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            progress[i][j] = 0;
        }
    }
    x = 0; y = 0;
    progress[0][0] = 1; //: First LED lit
}

//: Updates the progress bar LEDs based on elapsed time
void update_progress_bar() {
    if (currentTimeInterval > PART_POMODORO) {
        if (x < 8) y++;
        if (y >= 8) { y = 0; x++; }
        if (progress[x][y] == 0) progress[x][y] = 1;
        startTimeInterval = millis(); //: Reset interval timer
    }
    draw_pattern_on_led_matrix(progress);
}

//: Interrupt Service Routine for button press
ISR(PCINT1_vect) {
    counting_active = true;
    startTime = millis();
    clear_progress();
    startTimeInterval = millis();
    counting_active = true;
}

void loop() {
    if (counting_active) { //: If Pomodoro is running
        currentTime = millis() - startTime;
        currentTimeInterval = millis() - startTimeInterval;
        if (currentTime < ONE_POMODORO) {
            update_progress_bar();
        } else {
            counting_active = false; //: End Pomodoro
        }
    } else {
        //: Display animations when timer is not running
        for (int j = 0; j <= 5; j++) {
            for (int i = 0; i < 10; i++) draw_pattern_on_led_matrix(squares_0);
            for (int i = 0; i < 10; i++) draw_pattern_on_led_matrix(squares_1);
            for (int i = 0; i < 10; i++) draw_pattern_on_led_matrix(squares_2);
            for (int i = 0; i < 10; i++) draw_pattern_on_led_matrix(squares_3);
        }
        for (int i = 0; i < 20; i++) draw_pattern_on_led_matrix(squares_4);
        for (int i = 0; i < 30; i++) draw_pattern_on_led_matrix(squares_1);
        for (int i = 0; i < 30; i++) draw_pattern_on_led_matrix(bomb);
        for (int i = 0; i < 100; i++) draw_pattern_on_led_matrix(pacman);

        for (int j = 0; j <= 4; j++) {
            for (int i = 0; i < 12; i++) draw_pattern_on_led_matrix(small_heart);
            for (int i = 0; i < 10; i++) draw_pattern_on_led_matrix(big_heart);
            for (int i = 0; i < 7; i++) draw_pattern_on_led_matrix(small_heart);
            for (int i = 0; i < 50; i++) draw_pattern_on_led_matrix(big_heart);
        }

        for (int i = 0; i < 100; i++) draw_pattern_on_led_matrix(enemy_1);
        for (int j = 0; j <= 4; j++) {
            for (int i = 0; i < 20; i++) draw_pattern_on_led_matrix(enemy_2);
            for (int i = 0; i < 20; i++) draw_pattern_on_led_matrix(enemy_2a);
        }
        for (int i = 0; i < 100; i++) draw_pattern_on_led_matrix(pacman);
        for (int i = 0; i < 100; i++) draw_pattern_on_led_matrix(smile);
    }
}

```
