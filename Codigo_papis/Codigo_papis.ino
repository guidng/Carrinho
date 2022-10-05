#define PWM1 A5  //pios utilizados pelo RC
#define PWM2 A4
#define PWM3 A3
#define PWM4 A2
#define PWM5 A1
#define PWM6 A0

#define phDf 9 //pindos de ponte H do motor da direita, se precisar mudar os pinos
#define phDt 10

#define phEf 5 //pindos de ponte H do motor da esquerda, se precisar mudar os pinos
#define phEt 6

#define ledD 2        // leds idicadores
#define ledE 3
#define Bat A6        //monitor de bateria

int ch1, ch2, ch3, ch4, ch5, ch6;   //variaveis dos canais
int flag, pwmD, pwmE, pwmMax;
float var_bat; //variavél de tensão da bateria

void setup() {
  pinMode(PWM1, INPUT);pinMode(PWM2, INPUT);pinMode(PWM3, INPUT);pinMode(PWM4, INPUT);pinMode(PWM5, INPUT);pinMode(PWM6, INPUT);
  pinMode(phDf, OUTPUT);pinMode(phDt, OUTPUT);
  pinMode(phEf, OUTPUT);pinMode(phEt, OUTPUT);
  pinMode(ledD, OUTPUT);pinMode(ledE, OUTPUT);pinMode(Bat, INPUT);

  //Serial.begin(9600);

  //animação dos leds ao ligar o tank
  digitalWrite(ledD,HIGH);delay(200);
  digitalWrite(ledD,LOW);digitalWrite(ledE,HIGH);delay(200);
  digitalWrite(ledE,LOW);delay(100);
  digitalWrite(ledE,HIGH);digitalWrite(ledD,HIGH);delay(300);
  digitalWrite(ledD,LOW);digitalWrite(ledE,LOW);

  pwmMax = 255;
}

void loop() {
  Bat_protecao();
  Modo();
  modoFrente();
  modoReh();
  modoTank();


  //rotinas de configuração e calibragem
  //LeituraTotal_rc();
  //Printa_rc();
  //Leitura_calibri_rc();
}
void modoTank(){
  if(flag == 1){
    ch1 = constrain( map( ((pulseIn(PWM1, HIGH, 25000))- 1000), 100, 887, (pwmMax*-1), pwmMax),(pwmMax*-1),pwmMax);
    ch2 = constrain( map( ((pulseIn(PWM2, HIGH, 25000))- 1000), 90, 904, pwmMax,(pwmMax*-1)),(pwmMax*-1),pwmMax);

    if( (ch2 > 20) && (ch1 >= -30) && (ch1 <= 30) ){        //movendo para frente

      pwmD = map(ch2,0,pwmMax,0,(pwmMax-150));
      pwmE = map(ch2,0,pwmMax,20,pwmMax);
     
      analogWrite(phDf,pwmD);digitalWrite(phDt,LOW);
      analogWrite(phEf,pwmE);digitalWrite(phEt,LOW);
       
    }

    else if( (ch2 < -20) && (ch1 >= -30) && (ch1 <=30) ){    //movendo para trás

      pwmD = map(ch2,0,(pwmMax*-1),0,(pwmMax-150));
      pwmE = map(ch2,0,(pwmMax*-1),20,pwmMax);
     
      analogWrite(phDt,pwmD);digitalWrite(phDf,LOW);
      analogWrite(phEt,pwmE);digitalWrite(phEf,LOW);
       
    }

    else if(ch1 > 30){                               // movendo para direita

      pwmD = map(ch1,0,pwmMax,0,(pwmMax-150));
      pwmE = map(ch1,0,pwmMax,20,pwmMax);
       
      analogWrite(phDt,pwmD);digitalWrite(phDf,LOW);
      analogWrite(phEf,pwmE);digitalWrite(phEt,LOW);
       
    }

    else if(ch1 < -30){                               // movendo para esquerda

      pwmD = map (ch1,(pwmMax*-1),0,(pwmMax-150),0);
      pwmE = map (ch1,(pwmMax*-1),0,pwmMax,20);
       
      analogWrite(phDf,pwmD);digitalWrite(phDt,LOW);
      analogWrite(phEt,pwmE);digitalWrite(phEf,LOW);
       
    }

    else{
      digitalWrite(phDf,LOW);digitalWrite(phDt,LOW);
      digitalWrite(phEf,LOW);digitalWrite(phEt,LOW);
    }
   
     
 
  }  
}

void modoFrente(){
  if(flag == 3){
    ch3 = constrain( map( ((pulseIn(PWM3, HIGH, 25000))- 1000), 90, 850, pwmMax, 0),0,pwmMax);
    ch1 = constrain( map( ((pulseIn(PWM1, HIGH, 25000))- 1000), 100, 887, (pwmMax*-1), pwmMax),(pwmMax*-1),pwmMax);

    pwmD = map(ch3,0,pwmMax,0,(pwmMax-150));
    pwmE = map(ch3,0,pwmMax,20,pwmMax);

    if(ch1 > 20){                              // virar para direita
        pwmD = constrain (pwmD - ch1,0,pwmMax);  //desaceleradno o motor da diretita  
        pwmE = constrain (pwmE + ch1,0,pwmMax);  //acelera o motor da esquerda
      }

      if(ch1 < -20){                             // virar para esquerda
        pwmE = constrain (pwmE + ch1,0,pwmMax);    //desaceleradno o motor da esquerda
        pwmD = constrain (pwmD - ch1,0,pwmMax);    //acelera o motor da direita
      }

 
   
    analogWrite(phDf,pwmD);digitalWrite(phDt,LOW);
    analogWrite(phEf,pwmE);digitalWrite(phEt,LOW);
  }
}

void modoReh(){
  if(flag == 2){
    ch3 = constrain( map( ((pulseIn(PWM3, HIGH, 25000))- 1000), 90, 850, pwmMax, 0),0,pwmMax);
    ch1 = constrain( map( ((pulseIn(PWM1, HIGH, 25000))- 1000), 100, 887, (pwmMax*-1), pwmMax),(pwmMax*-1),pwmMax);

    pwmD = map(ch3,0,pwmMax,0,(pwmMax-50));
    pwmE = map(ch3,0,pwmMax,20,pwmMax);

    if(ch1 > 20){                              // virar para direita
        pwmD = constrain (pwmD - ch1,0,pwmMax);  //desaceleradno o motor da diretita  
        pwmE = constrain (pwmE + ch1,0,pwmMax);  //acelera o motor da esquerda
      }

      if(ch1 < -20){                             // virar para esquerda
        pwmE = constrain (pwmE + ch1,0,pwmMax);    //desaceleradno o motor da esquerda
        pwmD = constrain (pwmD - ch1,0,pwmMax);    //acelera o motor da direita
      }

    analogWrite(phDt,pwmD);digitalWrite(phDf,LOW);
    analogWrite(phEt,pwmE);digitalWrite(phEf,LOW);      // ao invez de alterar a saida da variavél, experiemente alterar os limites para equeilibrar os motores
  }
}

void Modo(){
  //nessa rotina vericamos a posição do SWE e encaminha e seta a variavél de controle
  ch5 = constrain( map( ((pulseIn(PWM5, HIGH, 25000))- 1000), -61, 1043, 1000, 0),0,1000);
  ch4 = constrain( map( ((pulseIn(PWM4, HIGH, 25000))- 1000), 80, 902, 0, 1000),0,1000);
  //ch6 = constrain( map( ((pulseIn(PWM6, HIGH, 25000))- 1000), -61, 1043, 0, 255),0,255);
  //pwmMax = ch6;

  if (ch5 >= 900) flag = 3;
  if (ch5 <= 100) flag = 2;
  if ((ch5 < 900) && (ch5 > 100)) flag = 1;


    // controle de ligar e deligar o faról
      if (ch4 >= 900){
        digitalWrite(ledE,HIGH);digitalWrite(ledD,HIGH);
      }
     
      if (ch4 <= 100){
        digitalWrite(ledE,LOW);digitalWrite(ledD,LOW);
      }

     

 
}

void Bat_protecao(){
  var_bat = analogRead(Bat);
  var_bat = (var_bat*15)/1023;

  if(var_bat < 6.7){
    digitalWrite(ledE,LOW);digitalWrite(ledD,HIGH);delay(30);
    digitalWrite(ledD,LOW);digitalWrite(ledE,HIGH);delay(30);
    digitalWrite(ledE,LOW);
  }

}

void LeituraTotal_rc(){
  ch1 = constrain( map( ((pulseIn(PWM1, HIGH, 25000))- 1000), 72, 887, 0, 1000),0,1000);
  ch2 = constrain( map( ((pulseIn(PWM2, HIGH, 25000))- 1000), 90, 904, 255, -255),-255,255);
  ch3 = constrain( map( ((pulseIn(PWM3, HIGH, 25000))- 1000), 90, 850, 255, 0),0,255);
  ch4 = constrain( map( ((pulseIn(PWM4, HIGH, 25000))- 1000), 80, 902, 0, 1000),0,1000);
  ch5 = constrain( map( ((pulseIn(PWM5, HIGH, 25000))- 1000), -61, 1043, 1000, 0),0,1000);
  ch6 = constrain( map( ((pulseIn(PWM6, HIGH, 25000))- 1000), -61, 1043, 0, 255),0,255);

}

void Printa_rc(){
  Serial.print(ch1);  Serial.print("   ");  
  Serial.print(ch2);  Serial.print("   ");
  Serial.print(ch3);  Serial.print("   ");
  Serial.print(ch4);  Serial.print("   ");
  Serial.print(ch5);  Serial.print("   ");
  Serial.print(ch6);  Serial.print("   ");
  Serial.print("   Bat:");Serial.print(var_bat);
  Serial.print("   Modo:");Serial.println(flag);

  //delay(30);
}

void Leitura_calibri_rc(){
  ch1 = (pulseIn(PWM1, HIGH, 25000))- 1000;
  ch2 = (pulseIn(PWM2, HIGH, 25000))- 1000;
  ch3 = (pulseIn(PWM3, HIGH, 25000))- 1000;
  ch4 = (pulseIn(PWM4, HIGH, 25000))- 1000;
  ch5 = (pulseIn(PWM5, HIGH, 25000))- 1000;
  ch6 = (pulseIn(PWM6, HIGH, 25000))- 1000;
}
