# arduino_pomodoro_clock
<img width="224" height="189" alt="obraz" src="https://github.com/user-attachments/assets/5efea825-89bd-4e49-8efb-27596435bd77" />

Idea was to create simple timer for counting ~30 minutes.<br>
The Pomodoro Technique is a time-management method that uses a timer to break work into intervals, 
traditionally 25 minutes in length, separated by short breaks. 
Each interval is called a "pomodoro" (the Italian word for tomato). 
The process involves identifying a task, working on it with no distractions for 25 minutes, taking a 5-minute break, and repeating this for four pomodoros

How it works
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
