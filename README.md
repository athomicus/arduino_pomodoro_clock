# arduino_pomodoro_clock
   <img width="224" height="189" alt="obraz" src="https://github.com/user-attachments/assets/5efea825-89bd-4e49-8efb-27596435bd77" />

Idea was to create simple timer for counting ~30 minutes.<br>
The Pomodoro Technique is a time-management method that uses a timer to break work into intervals, 
traditionally 25 minutes in length, separated by short breaks. 
Each interval is called a "pomodoro" (the Italian word for tomato). 
The process involves identifying a task, working on it with no distractions for 25 minutes, taking a 5-minute break, and repeating this for four pomodoros

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
- clock will start counting lighting up another LEDs
  
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

![projekt16](https://github.com/user-attachments/assets/893a50c4-d830-4703-b7c2-4933c5b768fa)

Important thing is to connect properly cables to selected PINs in Arduino so
if you look at the LED Matrix 8x8 ther is a signature <b>1088BS</b> so starting from left, brown cable should go into a PIN A5

<img width="323" height="243" alt="obraz" src="https://github.com/user-attachments/assets/16c5f981-7b4e-4971-84d3-94db6b52aa9e" />


![conm](https://github.com/user-attachments/assets/b5d43575-6302-4c8f-85c0-3560720f18bc)




  *what I notice you can buy Led Matrtix 8x8 with driver so you can use less cable connection and should be easier than my:
  <img width="745" height="323" alt="obraz" src="https://github.com/user-attachments/assets/1cb57faf-91a7-4a69-aec8-6ecc9c12a1b3" />

