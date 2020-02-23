//Variáveis com valores do Arduino
int entradaDigitalSensor = 4; //Pino ligado ao D4 do sensor
int entradaAnalogicoSensor = A5; //Pino ligado ao A5 do sensor
//Sentidos do motor
int Sentido1 = 7; //Ligado ao pino 2 do L293D
int Sentido2 = 2; //Ligado ao pino 7 do L293D
int botaoDeInicioSecagem = 3;
int fimDeCursoVaralCheio = 6; // sensor q detecta se varal ta cheio
int fimDeCursoVaranda = 8; // sensor q detecta se roupa recolheu

//Variáveis declaradas
int valorDigitalSensor = 0; //Armazena o valor lido do pino digital
int valorAnalogicoSensor = 0; //Armazena o valor lido do pino analogico
bool temRoupa = false;
bool desliga = false;
int inicioSecagem = 0;
int varalComRoupa = 0;
int finalVaranda = 0;

void setup()
{
  // Define os pinos do sensor como entrada
  pinMode(entradaDigitalSensor, INPUT);
  pinMode(entradaAnalogicoSensor, INPUT);
  pinMode(botaoDeInicioSecagem, INPUT);
  pinMode(fimDeCursoVaralCheio, INPUT);
  pinMode(fimDeCursoVaranda, INPUT);
  // Define os pinos do motor como saída  
  pinMode(Sentido1, OUTPUT);
  pinMode(Sentido2, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  //Le e armazena o valor do pino digital
  valorDigitalSensor = digitalRead(entradaDigitalSensor);
  //Le e armazena o valor do pino analogico
  valorAnalogicoSensor = analogRead(entradaAnalogicoSensor);
  inicioSecagem = digitalRead(botaoDeInicioSecagem);
  varalComRoupa = digitalRead(fimDeCursoVaralCheio);
  finalVaranda = digitalRead(fimDeCursoVaranda);
 
  //Envia as informacoes para o serial monitor
  Serial.print("Valor digital : ");
  Serial.print(valorDigitalSensor);
  Serial.print(" - Valor analogico : ");
  Serial.println(valorAnalogicoSensor);

  if(inicioSecagem == 1){
    Serial.print("Inicio da secagem\n");
    Serial.print("VAI ROUPA\n");
    digitalWrite(Sentido1, LOW);
    digitalWrite(Sentido2, HIGH);
    desliga = false;
  }

  if(varalComRoupa == 0){
      temRoupa = true;
      Serial.print("TEM ROUPA NO VARAL");
      desligar_motor();
  }

  if(desliga == true){
    Serial.print("DESLIGA\n");
    desligar_motor();
  }

  if(temRoupa == true && desliga == false){
    if(valorAnalogicoSensor >= 900){
      Serial.print("SEM CHUVA\n");
    }
    if (valorAnalogicoSensor >700 && valorAnalogicoSensor <900)
    {
      Serial.print("CHUVA BAIXA\n");
      inverte();
    }
    if (valorAnalogicoSensor >400 && valorAnalogicoSensor <700)
    {
      Serial.print("CHUVA MEDIA\n");
      inverte();
    }
    if (valorAnalogicoSensor > 0 && valorAnalogicoSensor <400)
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
  digitalWrite(Sentido1, LOW);
  digitalWrite(Sentido2, LOW);
}

void inverte(){
    Serial.print("RECOLHE\n");
    digitalWrite(Sentido1, HIGH);
    digitalWrite(Sentido2, LOW);
  if(finalVaranda == 0){
    desliga = true;
    temRoupa = false;
  }
}
