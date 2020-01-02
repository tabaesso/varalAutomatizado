int pino_d = 4; //Pino ligado ao D4 do sensor
int pino_a = A5; //Pino ligado ao A5 do sensor
int val_d = 0; //Armazena o valor lido do pino digital
int val_a = 0; //Armazena o valor lido do pino analogico
bool temRoupa = false;
bool desliga = false;

//Sentidos do motor
int Sentido1 = 9; //Ligado ao pino 2 do L293D - 9
int Sentido2 = 11; //Ligado ao pino 7 do L293D - 11

//Inicio da secagem
int pino_is = 3;
int pino_fs = 6; // sensor q detecta se varal ta cheio
int pino_fsv = 8; // sensor q detecta se roupa recolheu
//int pino_pwm = 9;
//int btn_recolhe = 11;
int inicio_sec = 0;
int final_sec = 0;
int final_var = 0;
//int botao_recolhe = 0;
int valor_pwm = 0;

void setup()
{
  // Define os pinos do sensor como entrada
  pinMode(pino_d, INPUT);
  pinMode(pino_a, INPUT);
  pinMode(pino_is, INPUT);
  pinMode(pino_fs, INPUT);
  pinMode(pino_fsv, INPUT);
  //pinMode(btn_recolhe, INPUT);
  // Define pino pwm
  //pinMode(pino_pwm, OUTPUT);
  // Define os pinos do motor como saída  
  pinMode(Sentido1, OUTPUT);
  pinMode(Sentido2, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  // Define velocidade inicial do pwm
  //valor_pwm = 128;
  //analogWrite(pino_pwm, valor_pwm);
  //Le e armazena o valor do pino digital
  val_d = digitalRead(pino_d);
  //Le e armazena o valor do pino analogico
  val_a = analogRead(pino_a);
  inicio_sec = digitalRead(pino_is);
  final_sec = digitalRead(pino_fs);
  final_var = digitalRead(pino_fsv);
  //botao_recolhe = digitalRead(btn_recolhe);
 
  //Envia as informacoes para o serial monitor
  Serial.print("Valor digital : ");
  Serial.print(val_d);
  Serial.print(" - Valor analogico : ");
  Serial.println(val_a);

  if(inicio_sec == 1){
    Serial.print("Inicio da secagem\n");
    Serial.print("VAI ROUPA\n");
    //digitalWrite(Sentido1, LOW);
    analogWrite(Sentido1, 0);
    analogWrite(Sentido2, 51);
    //digitalWrite(Sentido2, HIGH);
    desliga = false;
  }

  if(final_sec == 0){ //APERTA GATILHO 6
      temRoupa = true;
      Serial.print("TEM ROUPA NO VARAL");
      desligar_motor();
  }

  if(desliga == true){
    Serial.print("DESLIGA\n");
    desligar_motor();
  }

  if(temRoupa == true && desliga == false){
    if(val_a >= 900){
      Serial.print("SEM CHUVA\n");
//      verificaBotaoRecolhe(botao_recolhe);
    }
    if (val_a >700 && val_a <900)
    {
      Serial.print("CHUVA BAIXA\n");
      inverte();
    }
    if (val_a >400 && val_a <700)
    {
      Serial.print("CHUVA MEDIA\n");
      inverte();
    }
    if (val_a > 0 && val_a <400)
    {
      Serial.print("CHUVA ALTA\n");
      inverte();
    }
    delay(1000);
  }
}

void desligar_motor()
{
  Serial.print("DESLIGA\n");
  //digitalWrite(Sentido1, LOW);
  //digitalWrite(Sentido2, LOW);
  analogWrite(Sentido1, 0);
  analogWrite(Sentido2, 0);
}

void inverte(){
    Serial.print("RECOLHE\n");
    //digitalWrite(Sentido1, HIGH);
    //digitalWrite(Sentido2, LOW);
    analogWrite(Sentido1, 128);
    analogWrite(Sentido2, 0);
  if(final_var == 0){
    desliga = true;
    temRoupa = false;
  }
}

//void verificaBotaoRecolhe(int botao_recolhe)
//{
//  Serial.println("CHAMOU");
//  //if
//  if(botao_recolhe <= 0){
////    Serial.println("ENTROU");
////    inverte();
//    exit;
//  } else if(botao_recolhe == 1){
//     Serial.println("ENTROU");
//    inverte();
//  }
//}