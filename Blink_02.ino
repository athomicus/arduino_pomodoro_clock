 
 
unsigned long startTime=0, startTimeInterval=0; // Interval czas do zapalenia diody progressu 
unsigned long currentTime=0,currentTimeInterval=0; // liczniek do liczenia ile juz uplynelo czasu od startu liczenia
const int ButtonPin = 1;
const unsigned long ONE_POMODORO = 1800000; //30minut
const unsigned long PART_POMODORO = 28125; //~ 0.46 minuty 1 lamka powinna sie zapalic
bool counting_active = false;
const int cols[] = {5, A3, A2, 8, 12, 7, 3, 2};   //konfiguracja piny - podlaczenie - sterowanie
const int rows[] = {9, 4, 10, 6, A5, 11, A4, 13};
int x=0,y=0;

int progress[8][8]= { // progress jest struktura zer z czasem zmienia sie dodajc 1 po okreslonym czxasie(zapala sie lampka)
    {1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},  
    {0, 0, 0, 0, 0, 0, 0, 0},  
    {0, 0, 0, 0, 0, 0, 0, 0},  
    {0, 0, 0, 0, 0, 0, 0, 0},  
    {0, 0, 0, 0, 0, 0, 0, 0},  
    {0, 0, 0, 0, 0, 0, 0, 0},  
    {0, 0, 0, 0, 0, 0, 0, 0}  
};

const int big_heart[8][8] = {  
  0,0,0,0,0,0,0,0,  
  0,1,1,0,0,1,1,0,  
  1,1,1,1,1,1,1,1,  
  1,1,1,1,1,1,1,1,  
  1,1,1,1,1,1,1,1,  
  0,1,1,1,1,1,1,0,  
  0,0,1,1,1,1,0,0,  
  0,0,0,1,1,0,0,0,  
};

const int small_heart[8][8] = {  
  0,0,0,0,0,0,0,0,  
  0,0,0,0,0,0,0,0,  
  0,0,1,0,0,1,0,0,  
  0,1,1,1,1,1,1,0,  
  0,1,1,1,1,1,1,0,  
  0,0,1,1,1,1,0,0,  
  0,0,0,1,1,0,0,0,  
  0,0,0,0,0,0,0,0,  
};  
const int brick[8][8] = {
  {1,0,1,0,1,0,1,0},
  {0,1,0,1,0,1,0,1},
  {1,0,1,0,1,0,1,0},
  {0,1,0,1,0,1,0,1},
  {1,0,1,0,1,0,1,0},
  {0,1,0,1,0,1,0,1},
  {1,0,1,0,1,0,1,0},
  {0,1,0,1,0,1,0,1}
};

// angry robot
const int angry_robot[8][8] = {
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 0, 1, 1, 1, 1, 0, 1},
   {1, 0, 0, 1, 1, 0, 0, 1},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 0, 1, 1, 0, 1, 1},
   {1, 0, 0, 0, 0, 0, 0, 1},
   {1, 1, 1, 0, 0, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1}
 };

//squares
const int squares_0[8][8] = {
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 0, 0, 0, 0, 0, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 1},
   {1, 1, 1, 1, 1, 1, 1, 1}
 };

const int squares_1[8][8] = {
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 0, 0, 0, 0, 0, 0, 1},
   {1, 0, 1, 1, 1, 1, 0, 1},
   {1, 0, 1, 0, 0, 1, 0, 1},
   {1, 0, 1, 0, 0, 1, 0, 1},
   {1, 0, 1, 1, 1, 1, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 1},
   {1, 1, 1, 1, 1, 1, 1, 1}
 };
const int squares_2[8][8] = {
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 1, 1, 1, 1, 1, 1, 0},
   {0, 1, 0, 0, 0, 0, 1, 0},
   {0, 1, 0, 1, 1, 0, 1, 0},
   {0, 1, 0, 1, 1, 0, 1, 0},
   {0, 1, 0, 0, 0, 0, 1, 0},
   {0, 1, 1, 1, 1, 1, 1, 0},
   {0, 0, 0, 0, 0, 0, 0, 0}
 };

 const int squares_3[8][8] = {
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 1, 1, 0, 0, 0},
   {0, 0, 0, 1, 1, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0}
 };

const int squares_4[8][8] = {
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 1, 1, 1, 1, 1, 1, 0},
   {0, 1, 0, 0, 0, 0, 1, 0},
   {0, 1, 0, 1, 1, 0, 1, 0},
   {0, 1, 0, 1, 1, 0, 1, 0},
   {0, 1, 0, 0, 0, 0, 1, 0},
   {0, 1, 1, 1, 1, 1, 1, 0},
   {0, 0, 0, 0, 0, 0, 0, 0}
 };

const int smile[8][8] = {
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 1, 1, 0, 0, 1, 1, 0},
   {0, 1, 1, 0, 0, 1, 1, 0},
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 1, 0, 0, 0, 0, 1, 0},
   {0, 0, 1, 1, 1, 1, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0}
 };

 const int smile_talk[8][8] = {
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 1, 1, 0, 0, 1, 1, 0},
   {0, 1, 1, 0, 0, 1, 1, 0},
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 1, 1, 0, 0, 0},
   {0, 1, 1, 1, 1, 1, 1, 0},
   {0, 0, 1, 1, 1, 1, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0}
 };
 
 const int character1[8][8] = {
   {0, 0, 1, 1, 1, 1, 0, 0},
   {0, 1, 1, 1, 1, 1, 1, 0},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 0, 1, 1, 1, 0, 1},
   {1, 0, 0, 1, 1, 0, 0, 1},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 0, 1, 0, 0, 1, 0, 1}
 };

 const int cool[8][8] = {
  {0, 1, 1, 0, 0, 1, 1, 0},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 0, 1, 1, 0, 1, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 1, 1, 1, 1, 0, 1},
  {1, 0, 1, 0, 0, 1, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {0, 1, 1, 1, 1, 1, 1, 0}
};
const int enemy_1[8][8] = {
  {0,0,1,1,1,1,1,0},
  {0,1,1,1,1,1,1,1},
  {0,1,0,0,1,0,0,1},
  {0,1,1,0,1,1,0,1},
  {0,1,1,1,1,1,1,1},
  {0,1,1,1,1,1,1,1},
  {0,1,1,1,1,1,1,1},
  {0,1,0,1,0,1,0,1}
};
const int bomb[8][8] = {
  {0,0,0,1,1,0,0,0},
  {0,0,1,1,1,1,0,0},
  {0,1,1,1,1,1,1,0},
  {1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1},
  {0,1,1,1,1,1,1,0},
  {0,0,1,1,1,1,0,0},
  {0,0,0,1,1,0,0,0}
};

const int pacman[8][8] = {
  {0,0,1,1,1,1,0,0},
  {0,1,1,0,1,1,1,0},
  {1,1,0,0,1,1,1,1},
  {1,1,1,1,1,1,1,1},
  {1,1,1,1,0,0,0,0},
  {1,1,1,1,1,1,1,1},
  {0,1,1,1,1,1,1,0},
  {0,0,1,1,1,1,0,0}
};

const int enemy_2[8][8] = {
  {0,0,0,1,1,0,0,0},
  {0,0,1,1,1,1,0,0},
  {0,1,1,1,1,1,1,0},
  {1,1,0,1,1,0,1,1},
  {1,1,1,1,1,1,1,1},
  {0,0,1,0,0,1,0,0},
  {0,1,0,1,1,0,1,0},
  {1,0,1,0,0,1,0,1}  
};
const int enemy_2a[8][8] = {
  {0,0,0,1,1,0,0,0},
  {0,0,1,1,1,1,0,0},
  {0,1,1,1,1,1,1,0},
  {1,1,0,1,1,0,1,1},
  {1,1,1,1,1,1,1,1},
  {0,0,1,0,0,1,0,0},
  {0,1,0,1,1,0,1,0},
  {0,1,0,0,0,0,1,0}  
};

void setup() {
//  pinMode(1, INPUT_PULLUP); //Przycisk jako wejście
 // attachInterrupt(digitalPinToInterrupt(1), handleInterrupt, FALLING);
 pinMode(A0, INPUT_PULLUP); // Ustaw A0 jako wejście z podciąganiem
  PCICR |= (1 << PCIE1);     // Włącz przerwania dla grupy PCINT[14:8] (PORTC)
  PCMSK1 |= (1 << PCINT8);   // Włącz przerwanie dla konkretnego pinu A0



  //startTime=millis();
  //startTimeInterval = millis();
  
   //wygas wszystkie diody przygotuj pod rysowanie
 for (int i = 0; i< 8; i++) {
 
        pinMode(rows[i], OUTPUT); 
        pinMode(cols[i], OUTPUT); 
        digitalWrite(rows[i], LOW); 
        digitalWrite(cols[i], HIGH); 
    }
    //Serial.begin(9600);
}

void draw_pattern_on_led_matrix(const int pattern[8][8])
{   
  for (int i = 0; i < 8; i++) {
 
        digitalWrite(rows[i], HIGH);  // Włącz wiersz
 
        for (int j = 0; j < 8; j++) {
 
            if (pattern[i][j] == 1) {
 
                digitalWrite(cols[j], LOW);  // Włącz diodę
 
            } else {
 
                digitalWrite(cols[j], HIGH);  // Wyłącz diodę
 
            }
 
        }
 
        delay(2);
 
        digitalWrite(rows[i], LOW);  // Wyłącz wiersz
 
    }
}

 
void clear_progress()
{
for (int i = 0 ;i < 8; i++ )
{
  for (int j = 0 ;j < 8; j++ )
   {
    progress[i][j] = 0;
   }
}   
x=0;y=0;
progress[0][0] = 1; //wstaw 1 lampke progressu do zapalenia
} 

void update_progress_bar()
{
  if (currentTimeInterval > PART_POMODORO)
     {
        //idz po rzedach i rysuj progress
      if(x<8) y++;
      if (y>=8) {y=0;x++;}
      if (progress[x][y] == 0) progress[x][y]  = 1; //zapisuj tablice pogress na nowo 1
      startTimeInterval=millis(); //licz kolejny odstep czasu do zapalenia sie diody
      }   
      draw_pattern_on_led_matrix(progress);
}

ISR(PCINT1_vect)  //przerwanie
 {
  counting_active = true;
  startTime=millis();
  clear_progress();
  startTimeInterval=millis();     
  counting_active=true;
}

void loop() 
{
 
/*
 if(digitalRead(ButtonPin) == LOW)
  {
      //wcisniecie buttona:  
      startTime=millis();
      clear_progress();
      startTimeInterval=millis();     
      counting_active=true;
  }
 */
  if(counting_active) //start rendering progress
  {
    currentTime = millis() - startTime;
    currentTimeInterval = millis() - startTimeInterval;
    if(currentTime < ONE_POMODORO)   {   update_progress_bar();  }    else { counting_active=false;}
  } else {
   
   for(int j=0; j<=5;j++)
   {
    for(int i=0; i<10;i++)      {draw_pattern_on_led_matrix(squares_0);} //wyswietl serce 100 razy
    for(int i=0; i<10;i++)      {draw_pattern_on_led_matrix(squares_1);}
    for(int i=0; i<10;i++)      {draw_pattern_on_led_matrix(squares_2);}
    for(int i=0; i<10;i++)      {draw_pattern_on_led_matrix(squares_3);}
   }
    for(int i=0; i<20;i++)      {draw_pattern_on_led_matrix(squares_4);}
    for(int i=0; i<30;i++)      {draw_pattern_on_led_matrix(squares_1);}
    for(int i=0; i<30;i++)      {draw_pattern_on_led_matrix(bomb);}
  
    
   for(int i=0; i<100;i++)      {draw_pattern_on_led_matrix(pacman);}
   for(int j=0; j<=4;j++)
   {    
    for(int i=0; i<12;i++)      {draw_pattern_on_led_matrix(small_heart);}
    for(int i=0; i<10;i++)      {draw_pattern_on_led_matrix(big_heart);} 
    for(int i=0; i<7;i++)      {draw_pattern_on_led_matrix(small_heart);}
    for(int i=0; i<50;i++)      {draw_pattern_on_led_matrix(big_heart);} //wyswietl serce 100 razy
   }
    for(int i=0; i<100;i++)      {draw_pattern_on_led_matrix(enemy_1);}
  for(int j=0; j<=4;j++)
    {
      for(int i=0; i<20;i++)      {draw_pattern_on_led_matrix(enemy_2);}
        for(int i=0; i<20;i++)      {draw_pattern_on_led_matrix(enemy_2a);}
    }
    for(int i=0; i<100;i++)      {draw_pattern_on_led_matrix(pacman);}
    for(int i=0; i<100;i++)      {draw_pattern_on_led_matrix(smile);}
    
    
     
  }
       


  
}