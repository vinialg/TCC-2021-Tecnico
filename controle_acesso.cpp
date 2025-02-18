#include <SPI.h>		// Carrega a biblioteca "SPI"
#include <MFRC522.h>	// Carrega a biblioteca "MFRC522"

#define RST_PIN		9		// Definir o pino reset do RFID
#define SS_PIN		10 		// Definir o pino SDA do RFID
#define BUZZER		8		// Definir o pino do Buzzer
#define RED_LED		3		// Definir o pino LED vermelho
#define SOLENOIDE	4		// Definir o pino do Solenoide
#define GREEN_LED	2	          // Definir o pino do LED verde
MFRC522 mfrc522(SS_PIN, RST_PIN); 
#define NOTE_G4 392         		// Definir a nota G4
#define NOTE_C5 523        		 // Definir a nota C5
#define NOTE_G5 784         		// Definir a nota G5
#define NOTE_C6 1047        		// Definir a nota C6
int Melodia[] = {NOTE_G5, NOTE_C6};	// Define a melodia de entrada
int TempoMelodia[] = {12,8};		// Define o tempo da melodia
int FalsaMelodia[] = {NOTE_C6, NOTE_G5};	// Define a melodia de acesso negado
int FalsoTempoMelodia[] = {12,8};			// Define o tempo da melodia de acesso negado
#define playMelodia() playMelody(Melodia, TempoMelodia, 2) 	//Define o inicio da melodia
#define playFalsaMelodia() playMelody(FalsaMelodia, FalsoTempoMelodia, 2)	// Define o inicio da melodia de acesso engado

// Configuração Inicial
void setup() {
  Serial.begin(9600); 	// Inicializa a comunicação serial
  while (!Serial);		// Fazer enquanto não tiver nenhuma porta serial aberta
  SPI.begin();			// Inicia SPI bus
  mfrc522.PCD_Init(); 	// Inicia MFRC522
  Serial.println("Por favor coloque seu cartão no leitor RFID");  //Imprime no monitor serial o pedido de leitura
  pinMode(RED_LED,OUTPUT);		// Define o LED vermelho como saída
  pinMode(GREEN_LED,OUTPUT);	// Define o LED verde como saída
  pinMode(SOLENOIDE,OUTPUT);	// Define o solenoide como saída
  pinMode(BUZZER,OUTPUT);		// Define o Buzzer como saída
  digitalWrite(RED_LED,HIGH);		// Define o LED vermelho com sinal lógico alto
}
// Sistema principal
void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  Serial.print("UID tag :");
  String RFIDtag ="";
  byte letter;
  for(byte i = 0; i< mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    RFIDtag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    RFIDtag.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

Serial.println();
Serial.print("Message : ");
RFIDtag.toUpperCase();

if(RFIDtag.substring(1) == "09 48 EB 8B")	// Condição para permitir o acesso
{
  Serial.println("Acesso garantido");	// Imprime no monitor serial a permissão de acesso
  playMelodia();				// Toca a melodia de acesso
  digitalWrite(SOLENOIDE,HIGH); 	// Aciona o solenoide 
  digitalWrite(RED_LED,LOW); 		// Desliga o LED vermelho
  digitalWrite(GREEN_LED,HIGH); 	// Liga o LED verde
  delay(3000); 				// Aguarda 3 segundos
  digitalWrite(GREEN_LED,LOW); 	// Desliga o LED verde
  digitalWrite(SOLENOIDE,LOW); 	// Desliga solenoide
  digitalWrite(RED_LED, HIGH); 		// Liga o LED vermelho
Serial.println("Por favor coloque seu cartão no leitor RFID");
// Imprime a pergunta de leitura
}
else						// Condição de acesso negado
  {
    Serial.println("Acesso negado");	// Imprime no monitor serial que o acesso foi negado
    playFalsaMelodia();			// Toca a melodia de acesso negado
    digitalWrite(GREEN_LED,LOW); 	// Desliga o LED verde
    digitalWrite(SOLENOIDE,LOW); 	// Desliga solenoide
    digitalWrite(RED_LED, HIGH);    	// Liga o LED vermelho
    delay(1000); 				// Aguarda 1 segundo
      Serial.println("Por favor coloque seu cartão no leitor RFID");
// Imprime no monitor serial que o acesso foi negado
  }
}
// Função das melodias
void playMelody(int *melody, int *noteDurations, int notesLength)
{
  pinMode(BUZZER, OUTPUT);
  for(int thisNote = 0; thisNote < notesLength; thisNote++){
    int noteDuration = 1000/ noteDurations[thisNote];
    tone(BUZZER, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration *1.30;
    delay(pauseBetweenNotes);
    noTone(BUZZER);
  }
}

