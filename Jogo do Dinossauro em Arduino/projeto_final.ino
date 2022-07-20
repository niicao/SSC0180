//pinos :
  //semaforo
int red_semaforo = 1;
int amarelo_semaforo = 2;
int verde_semaforo = 3;
  //contador
int contador1 = 4;
int contador2 = 5;
  //outros
int ledA = 0;
int butao = 6;
//variaveis de programa
int n_potencia;
int btn_state = 0;
int nrandomdelay;
int nrandomled;
int valorRed;
int jump_state,jump_timer;
int input = 0;
void contar(){
  delay(1000);
  digitalWrite(contador1, HIGH);
  delay(1000);
  digitalWrite(contador1, LOW);
  digitalWrite(contador2,HIGH);
  delay(1000);
  digitalWrite(contador1, HIGH);
  delay(1000);
  digitalWrite(contador2,LOW);
  digitalWrite(contador1, LOW);
  
}
void semi_delay(){
  for(int i = 0; i < nrandomdelay; i++){
    delay(1);
    //Serial.println(jump_timer);
    //Serial.println(input);
    if(jump_timer > 300){
      delay(300);
      input = 0;
    }else{
      if(jump_timer == 300){
        while( 0 < jump_timer){
          input = 0;
          digitalWrite(ledA,HIGH);
          //Serial.println("Azul1");
          digitalWrite(contador2,LOW);
          //Serial.println("verde0");
          //Serial.println(input);
          jump_state = 0;
          jump_timer--;
          delay(1);
        }
      }else{
        //input = 1;
        evento_btn();
      }
    }
    if(input == 1){
      digitalWrite(ledA,LOW);
      //Serial.println("Azul0");
      digitalWrite(contador2,HIGH);
      //Serial.println("Verde1");
      jump_state = 1;
    }else{
      digitalWrite(ledA,HIGH);
      //Serial.println("Azul1");
      digitalWrite(contador2,LOW);
      //Serial.println("verde0");
      jump_state = 0;
      jump_timer = 0;
   }
   if( jump_state == 1) {
    jump_timer++;
   }
   //Serial.println(jump_state);
  }
}
void derrota(){
  digitalWrite(red_semaforo,HIGH);
  digitalWrite(amarelo_semaforo,HIGH);
  digitalWrite(verde_semaforo,HIGH);
  digitalWrite(contador1,HIGH);
  digitalWrite(ledA,HIGH);
  digitalWrite(contador2,HIGH);
  delay(1000);
  digitalWrite(red_semaforo,LOW);
  digitalWrite(amarelo_semaforo,LOW);
  digitalWrite(verde_semaforo,LOW);
  digitalWrite(contador1,LOW);
  digitalWrite(ledA,LOW);
  digitalWrite(contador2,LOW);
}
void evento_btn(){
  btn_state = digitalRead(butao);
  if(btn_state != 0){
    input = 1; 
  }/*else{
    input = 0;
  }*/
  
  //Serial.println(nrandom);
  /*if(btn_state != 0){
    digitalWrite(ledA,LOW);
    digitalWrite(contador2,HIGH);
    jump_state = 1;
   }else{
    digitalWrite(ledA,HIGH);
    digitalWrite(contador2,LOW);
    jump_state = 0;
   }*/
}
void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  pinMode(ledA,OUTPUT);
  pinMode(red_semaforo,OUTPUT);
  pinMode(amarelo_semaforo,OUTPUT);
  pinMode(verde_semaforo,OUTPUT);
  pinMode(contador1,OUTPUT);
  pinMode(contador2,OUTPUT);
  pinMode(A5,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  n_potencia = analogRead(A5);
  jump_timer = 0;
  if(n_potencia < 350){
    nrandomled = random(0,2);
    nrandomdelay = random(300,1500);
    jump_state = 0;
    if(jump_state == 0){
      digitalWrite(ledA,HIGH);
      digitalWrite(contador2,LOW);
    }
    //loop semaforo:
    //verde
    digitalWrite(verde_semaforo,HIGH);//acende o verde
    semi_delay();
    digitalWrite(verde_semaforo,LOW);//apaga o verde
    evento_btn();
    //amarelo
    digitalWrite(amarelo_semaforo,HIGH);//ascende o amarelo
    semi_delay();
    digitalWrite(amarelo_semaforo,LOW);//apaga o amarelo
    evento_btn();
    
      if(nrandomled == 1){
        //ledV = 5 ; ledA = 0; cVermelho = 4
        semi_delay();
        evento_btn();
        digitalWrite(contador1,HIGH);
        evento_btn();
        semi_delay();
        if(digitalRead(contador2) == HIGH && digitalRead(contador1) == HIGH){
          derrota();
        }
        evento_btn();
        digitalWrite(contador1,LOW);
    }else{
      evento_btn();
      digitalWrite(red_semaforo,HIGH);//liga o vermelho
      valorRed = 1;
      semi_delay();
      if(digitalRead(ledA) == HIGH && valorRed == 1){
        derrota();
      }
      digitalWrite(red_semaforo,LOW);//apaga o vermelho
      valorRed = 0;
    }
    evento_btn();  
  }else{
    digitalWrite(ledA,LOW);
    //Semaforo
    digitalWrite(red_semaforo,HIGH);//liga o vermelho
    contar();
    digitalWrite(red_semaforo,LOW);//apaga o vermelho
    digitalWrite(amarelo_semaforo,HIGH);//ascende o amarelo
    contar();
    digitalWrite(amarelo_semaforo,LOW);//apaga o amarelo
    digitalWrite(verde_semaforo,HIGH);//acende o verde
    contar();
    digitalWrite(verde_semaforo,LOW);//apaga o verde
  }
}
