#include <LiquidCrystal.h>        		//Carrega a biblioteca "LiquidCrystal"
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 	//Define os pinos do LCD
const int pinFan = 13;			// Declara o o ventilador no pino digital 13
const int LM35 = 0;				// Declara o sensor LM35 no pino analígico 0 
float temperatura;				// Declara a variável temperatura

// Configuração operacional inicial
void setup() {
  lcd.begin(16, 2);			// Define o display com 16 colunas e 2 linhas
  lcd.clear();				// Deixa a tela do display "limpa"
  Serial.begin(9600);		//Inicia o monitor serial
  pinMode(pinFan, OUTPUT);	//Define o ventilador como saída
  pinMode(LM35, INPUT);		//Declara o sensor de temperatura como entrada
}
//Sistema operacional principal
void loop() {
//Conversão da temperatura para celsius
temperatura = ((float(analogRead(LM35))*5/(1023))/0.01)-1;  
Serial.print("Temperatura: ");	//Imprime no monitor serial o que será medido
Serial.print(temperatura);		 //Imprime no monitor serial o valor da temperatura
Serial.println(" C");			//Imprime no monitor serial a letra "C" representando a unidade celsius

  if (temperatura > 29) {		// Condição para acionamento do ventilador
    lcd.setCursor(0, 1);		// Define a coluna 0 e linha 1 do LCD como a posição onde será impresso os dados
    lcd.write("Fan ligado !");		// Imprime no LCD que o ventilador ligou
    digitalWrite(pinFan, LOW);	// Liga o ventilador
  } 
  else if (temperatura <28.85) {	// Condição para desligar oo ventilador
    lcd.setCursor(0, 1);		// Define a coluna 0 e linha 1 do LCD como a posição onde será impresso os dados
    lcd.write("Fan desligado !"); 	// Imprime no LCD que o ventilador desligou
    digitalWrite(pinFan, HIGH);	// Desliga o ventilador
  }
  else					// Condição para nenhum dos dois casos anteriores
  {
    lcd.setCursor(0, 1);		// Define a coluna 0 e linha 1 do LCD como a posição onde será impresso os dados
    lcd.write("Fan desligado !");	 // Imprime no LCD que o ventilador desligou
  }

  delay(1000);			// Aguarda 1 segundo
  // Exibição do valor da temperatura no display LCD
  lcd.clear();				// Limpa o display do LCD
  lcd.print("Temp.: ");		// Imprime no LCD o que será medido
  lcd.print(temperatura); 		// Imprime no LCD o valor da temperatura
  lcd.print(" C");			// Imprime no LCD a letra "C" representando a unidade celsius
}









