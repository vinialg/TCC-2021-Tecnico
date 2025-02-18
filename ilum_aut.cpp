const int LDR = 0;		//Define o sensor LDR no pino anal�gico 0
const int Led = 10;		//Define o Led no pino digital 10
int valorLido = 0;		//Declara a variavel valorLido
// Configura��o operacional inicial
void setup() {
 pinMode (Led, OUTPUT);		//Define o Led como sa�da
 Serial.begin(9600);			// Inicia o monitor serial
}
// Sistema operacional principal
void loop() {
 valorLido = analogRead(LDR);	 //Define a variavel igual aos valores medidos do sensor
 Serial.println(valorLido);		 // Imprime a intensidade de ilumina��o
 if(valorLido>750) { 			//Condi��o para acionar o Led
 const int DUTY = 200; 		// Define o DUTY, sendo que quanto maior o valor maior a intensidade
 analogWrite(Led, DUTY);		//Define o Led em fun��o do DUTY
}
  else if(valorLido>700){		//Condi��o para acionar o Led em menor intensidade
 const int DUTY = 100;		// Define o DUTY, sendo que quanto maior o valor maior a intensidade
 analogWrite(Led, DUTY);		//Define o Led em fun��o do DUTY
  }
  else {                       		 //Condi��o para desligar o Led
 digitalWrite(Led, LOW);        	//Desligar o Led
}
}















