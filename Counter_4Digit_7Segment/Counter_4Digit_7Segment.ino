#define aPin 2  //        
#define bPin 3  //      _____
#define cPin 4  //     |  A  |
#define dPin 5  //   F |_____| B
#define ePin 6  //     |  G  |
#define fPin 7  //   E |_____| C
#define gPin 8  //        D     O dot

#define c1Pin 9  // Common pin for digit 1
#define c2Pin 10 // Common pin for digit 2
#define c3Pin 11 // Common pin for digit 3
#define c4Pin 12 // Common pin for digit 4

#define bt_up     A0
#define bt_down   A1
#define bt_reset  A2

#define buzzer 13

long Counter=0;

int flag1=0, flag2=0, timer=0;

int Common = 1; //<Common=1; for Common anode> <Common=0; for Common cathode>
int On, Off, Off_C; 
int DTime = 4; // Display timer

void setup(){ // put your setup code here, to run once  
 
 pinMode(bt_up,    INPUT_PULLUP);
 pinMode(bt_down,  INPUT_PULLUP);
 pinMode(bt_reset, INPUT_PULLUP);

 pinMode(aPin, OUTPUT);
 pinMode(bPin, OUTPUT);
 pinMode(cPin, OUTPUT);
 pinMode(dPin, OUTPUT);
 pinMode(ePin, OUTPUT); 
 pinMode(fPin, OUTPUT);
 pinMode(gPin, OUTPUT);

 pinMode(c1Pin, OUTPUT);
 pinMode(c2Pin, OUTPUT);
 pinMode(c3Pin, OUTPUT);
 pinMode(c4Pin, OUTPUT);

 pinMode(buzzer, OUTPUT);

 if(Common==1){On=0, Off=1, Off_C=0;} //for Common anode
          else{On=1, Off=0, Off_C=1;} //for Common cathode

 // Indicate that system is ready
 for (int i = 9; i >=0; i--) {
 showNumber(i);
 digitalWrite(c1Pin, Common);
 digitalWrite(c2Pin, Common);
 digitalWrite(c3Pin, Common);
 digitalWrite(c4Pin, Common);
 delay(1000); 
 } 
}

void loop(){  

if(digitalRead (bt_up) == 0){ 
if(flag1==0){ flag1=1;
digitalWrite(buzzer, HIGH);
Counter = Counter+1;
if(Counter>9999){Counter=0;} 
 }
}else{flag1=0;}

if(digitalRead (bt_down) == 0){ 
if(flag2==0){ flag2=1;
digitalWrite(buzzer, HIGH);
Counter = Counter-1;
if(Counter<0){Counter=9999;} 
 }  
}else{flag2=0;}

if(digitalRead (bt_reset) == 0){ 
digitalWrite(buzzer, HIGH);
if(timer<200){timer=timer+1;}
if(timer==200){
Counter=0;
}   
}else{timer=0;}


showNumber((Counter/1000)%10);
digitalWrite(c1Pin, Common);
delay(DTime);
digitalWrite(c1Pin, Off_C);

showNumber((Counter/100)%10);
digitalWrite(c2Pin, Common);
delay(DTime);
digitalWrite(c2Pin, Off_C);

showNumber((Counter/10)%10);
digitalWrite(c3Pin, Common);
delay(DTime);
digitalWrite(c3Pin, Off_C);

showNumber(Counter%10);
digitalWrite(c4Pin, Common);
delay(DTime);
digitalWrite(c4Pin, Off_C);

digitalWrite(buzzer, LOW);
}


void showNumber(int x){
  
   switch(x){
     case 1: one();   break;
     case 2: two();   break;
     case 3: three(); break;
     case 4: four();  break;
     case 5: five();  break;
     case 6: six();   break;
     case 7: seven(); break;
     case 8: eight(); break;
     case 9: nine();  break;
     default: zero(); break;
   }
}

void one(){
  digitalWrite( aPin, Off); //      
  digitalWrite( bPin, On);  //      |
  digitalWrite( cPin, On);  //      |
  digitalWrite( dPin, Off); //      |
  digitalWrite( ePin, Off); //      |
  digitalWrite( fPin, Off);
  digitalWrite( gPin, Off);
}

void two(){
  digitalWrite( aPin, On);  //  ____
  digitalWrite( bPin, On);  //      | 
  digitalWrite( cPin, Off); //  ____|
  digitalWrite( dPin, On);  // |     
  digitalWrite( ePin, On);  // |____
  digitalWrite( fPin, Off);
  digitalWrite( gPin, On);
}

void three(){
  digitalWrite( aPin, On);  //  ____
  digitalWrite( bPin, On);  //      |
  digitalWrite( cPin, On);  //  ____|
  digitalWrite( dPin, On);  //      |
  digitalWrite( ePin, Off); //  ____|
  digitalWrite( fPin, Off); 
  digitalWrite( gPin, On);
}

void four(){
  digitalWrite( aPin, Off); //  
  digitalWrite( bPin, On);  // |    |
  digitalWrite( cPin, On);  // |____|
  digitalWrite( dPin, Off); //      |
  digitalWrite( ePin, Off); //      |
  digitalWrite( fPin, On);
  digitalWrite( gPin, On);
}

void five(){
  digitalWrite( aPin, On);  //  ____
  digitalWrite( bPin, Off); // |
  digitalWrite( cPin, On);  // |____
  digitalWrite( dPin, On);  //      |
  digitalWrite( ePin, Off); //  ____|
  digitalWrite( fPin, On);  
  digitalWrite( gPin, On);
}

void six(){
  digitalWrite( aPin, On);  //  ____
  digitalWrite( bPin, Off); // |
  digitalWrite( cPin, On);  // |____
  digitalWrite( dPin, On);  // |    |
  digitalWrite( ePin, On);  // |____|
  digitalWrite( fPin, On);
  digitalWrite( gPin, On);
}

void seven(){
  digitalWrite( aPin, On);  //  ____
  digitalWrite( bPin, On);  //      |
  digitalWrite( cPin, On);  //      |
  digitalWrite( dPin, Off); //      |
  digitalWrite( ePin, Off); //      |
  digitalWrite( fPin, Off);
  digitalWrite( gPin, Off);
}

void eight(){
  digitalWrite( aPin, On); //  ____
  digitalWrite( bPin, On); // |    |
  digitalWrite( cPin, On); // |____|
  digitalWrite( dPin, On); // |    |
  digitalWrite( ePin, On); // |____|
  digitalWrite( fPin, On); 
  digitalWrite( gPin, On); 
}

void nine(){
  digitalWrite( aPin, On);  //  ____
  digitalWrite( bPin, On);  // |    |
  digitalWrite( cPin, On);  // |____|
  digitalWrite( dPin, On);  //      |
  digitalWrite( ePin, Off); //  ____|
  digitalWrite( fPin, On); 
  digitalWrite( gPin, On);
}

void zero(){                 
  digitalWrite( aPin, On); //  ____
  digitalWrite( bPin, On); // |    |
  digitalWrite( cPin, On); // |    |
  digitalWrite( dPin, On); // |    |
  digitalWrite( ePin, On); // |____|
  digitalWrite( fPin, On); 
  digitalWrite( gPin, Off);   
}
