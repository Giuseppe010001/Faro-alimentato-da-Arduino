/*
  Progetto: Faro alimentato da Arduino;
  Descrizione: lo scopo del software e' quello di permettere il funzionamento di un faro per edilizia;
  Cognome Nome: Carlino Giuseppe;
  Data: 02/06/2023.
*/


// Dichiarazione dei pin analogici
#define RegolatoreA1 1
#define SensLumA0 0

// Dichiarazione dei pin digitali
#define Pulsante1 1
#define Pulsante2 2
#define DisplayINA 3
#define DisplayINB 4
#define DisplayINC 5
#define DisplayIND 6
#define DisplayINE 7
#define DisplayINF 8
#define DisplayING 9
#define Motore10 10
#define LEDBianco11 11
#define LEDBianco12 12
#define LEDBianco13 13


// Dichiarazione variabili globali
int luminosita, pot;
unsigned long tempo_trascorso;
bool intermittenza0, intermittenza1, vero_falso = false;


// Dichiarazione prototipi di funzioni e/o procedure
void display_7();
void motore();
void intermittenza();
void spegnimento();


// Dichiarazione della procedura setup contenente le istruzioni da eseguire solo una volta
void setup() {
  
  // Settare i pin di input
  pinMode(Pulsante1, INPUT_PULLUP);
  pinMode(Pulsante2, INPUT_PULLUP);
  
  // Settare i pin di output
  pinMode(DisplayINA, OUTPUT);
  pinMode(DisplayINB, OUTPUT);
  pinMode(DisplayINC, OUTPUT);
  pinMode(DisplayIND, OUTPUT);
  pinMode(DisplayINE, OUTPUT);
  pinMode(DisplayINF, OUTPUT);
  pinMode(DisplayING, OUTPUT);
  pinMode(Motore10, OUTPUT);
  pinMode(LEDBianco11, OUTPUT);
  pinMode(LEDBianco12, OUTPUT);
  pinMode(LEDBianco13, OUTPUT);
  
  // Memorizzare il tempo trascorso in millisecondi dall'accensione di Arduino
  tempo_trascorso = millis();
}

// Dichiarazione della procedura loop contenente le istruzioni da eseguire ciclicamente, per tutta la durata dell'esecuzione del software
void loop() {
  
  // Leggere il valore di luminosita' dell'ambiente circostante con il fotoresistore e assegnarlo a luminosita
  luminosita = analogRead(SensLumA0);
  
  // Se il valore di luminosita' letto dal fotoresistore e' minore o uguale a 150
  if (luminosita <= 150) {
    
    // Leggere il valore del potenziometro ed assegnarlo a pot
    pot = analogRead(RegolatoreA1);
    
    // Richiamare la procedura display
    display_7();
    
    // Richiamare la procedura motore
    motore();
    
    // Leggere il valore dei pulsanti ed assegnarlo a intermittenza0 e a intermittenza1
    intermittenza0 = digitalRead(Pulsante1);
    intermittenza1 = digitalRead(Pulsante2);
    
    // Richiamare la procedura intermittenza
    intermittenza();
  
  // Altrimenti
  } else {
    
    // Richiamare la procedura spegnimento
    spegnimento();
  }
}


// Procedura che accende il display a sette segmenti
void display_7() {
  // Se il valore del potenziometro e' posto a 0
  if (pot == 0) {
      
    // Scrivere il numero 0 sul display
    digitalWrite(DisplayINA, LOW);
    digitalWrite(DisplayINB, LOW);
    digitalWrite(DisplayINC, LOW);
    digitalWrite(DisplayIND, LOW);
    digitalWrite(DisplayINE, LOW);
    digitalWrite(DisplayINF, LOW);
    digitalWrite(DisplayING, HIGH);
    
  // Seconda alternativa
  } else if (pot > 0 && pot <= 300) {
      
    // Scrivere il numero 1 sul display
    digitalWrite(DisplayINA, HIGH);
    digitalWrite(DisplayINB, LOW);
    digitalWrite(DisplayINC, LOW);
    digitalWrite(DisplayIND, HIGH);
    digitalWrite(DisplayINE, HIGH);
    digitalWrite(DisplayINF, HIGH);
    digitalWrite(DisplayING, HIGH);
      
  // Terza alternativa
  } else if (pot > 300 && pot <= 600) {
      
    // Scrivere il numero 2 sul display
    digitalWrite(DisplayINA, LOW);
    digitalWrite(DisplayINB, LOW);
    digitalWrite(DisplayINC, HIGH);
    digitalWrite(DisplayIND, LOW);
    digitalWrite(DisplayINE, LOW);
    digitalWrite(DisplayINF, HIGH);
    digitalWrite(DisplayING, LOW);
      
  // Quarta alternativa
  } else if (pot > 600 && pot <= 900) {
      
    // Scrivere il numero 3 sul display
    digitalWrite(DisplayINA, LOW);
    digitalWrite(DisplayINB, LOW);
    digitalWrite(DisplayINC, LOW);
    digitalWrite(DisplayIND, LOW);
    digitalWrite(DisplayINE, HIGH);
    digitalWrite(DisplayINF, HIGH);
    digitalWrite(DisplayING, LOW);
      
  // Altrimenti
  } else {
      
    // Scrivere il numero 4 sul display
    digitalWrite(DisplayINA, HIGH);
    digitalWrite(DisplayINB, LOW);
    digitalWrite(DisplayINC, LOW);
    digitalWrite(DisplayIND, HIGH);
    digitalWrite(DisplayINE, HIGH);
    digitalWrite(DisplayINF, LOW);
    digitalWrite(DisplayING, LOW);
  } 
}

// Procedura che accende il motore
void motore() {
  
  // Rimappare i valori di pot
  pot = map(pot, 0, 1023, 0, 255);
  
  // Fornire al motore un valore di potenza pari a quello fornito dal potenziometro
  analogWrite(Motore10, pot);
}

// Procedura che gestisce l'intermittenza dei LED
void intermittenza() {
  
  // Se il primo pulsante viene premuto e il secondo no
  if (!intermittenza0 && intermittenza1) {
      
    // Assegnare a vero_falso il valore false
    vero_falso = false;
  } else {
    
    // Nel caso contrario
    if (intermittenza0 && !intermittenza1) {
      
      // Assegnare a vero_falso il valore true
      vero_falso = true;
    }
  }
        
  // Se vero_falso assume valore true
  if (vero_falso) {
      
    // Attivare la luce intermittente nei LED
    if (millis() - tempo_trascorso >= 100) {
      
      // Questo codice fornisce un funzionamento piu' ottimizzato rispetto a quello dato dalla funzione delay(), che causa lo spreco di molto tempo utile per Arduino
      digitalWrite(LEDBianco11, !digitalRead(LEDBianco11));
      digitalWrite(LEDBianco12, !digitalRead(LEDBianco12));
      digitalWrite(LEDBianco13, !digitalRead(LEDBianco13));
      
      tempo_trascorso = millis();
    }  
    
  // Altrimenti
  } else {
      
    // Tenerli semplicemente accesi
    digitalWrite(LEDBianco11, HIGH);
    digitalWrite(LEDBianco12, HIGH);
    digitalWrite(LEDBianco13, HIGH);
  }
}

// Procedura che gestisce lo spegnimento del faro
void spegnimento() {
  
  // Spegnere il display
  digitalWrite(DisplayINA, HIGH);
  digitalWrite(DisplayINB, HIGH);
  digitalWrite(DisplayINC, HIGH);
  digitalWrite(DisplayIND, HIGH);
  digitalWrite(DisplayINE, HIGH);
  digitalWrite(DisplayINF, HIGH);
  digitalWrite(DisplayING, HIGH);
    
  // Spegnere il motore
  analogWrite(Motore10, LOW);
    
  // Spegnere i LED
  digitalWrite(LEDBianco11, LOW);
  digitalWrite(LEDBianco12, LOW);
  digitalWrite(LEDBianco13, LOW);
}
