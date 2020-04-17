/*
Respirador UN
Fecha : 4 / 4 / 2020
Colaboladores: Johan Ramirez
Version : 0.01
Descripcion: En el contexto de la pandemia de covid-19 la universidad nacional de colombia, tiene como motivavion construir
             Respiradores mecanicos para ayudar a mitigar las muertes asociadas a fallas respiratorias, por lo se construye
             el control de los respiradores mecanicos basado en arduino
*/

// importacion de librerias
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <AccelStepper.h>
#include <avr/wdt.h>
#include "Movimiento.h"
#include  "Paciente.h"                          // se usara para configurar las variables del paciente
#include  "entrada.h"                           // se usa para configurar los botones
#include "system.h"
#include "Control.h"

// se crea objetos de interfaz, paciente
Paciente unico;
Entrada Poteciometro_volumen(A0);
Entrada Poteciometro_frecuencia(A1);
Entrada Poteciometro_presion(A2);
Entrada boton_modo_operacion(4,1);
Entrada boton_confirmacion(5,1);
movimiento cicloRespiratorio;
//Control control;

AccelStepper stepper = AccelStepper(1, 3, 2); // pin 3 : step, pin 2 : dir ; 1 indica que es driver

// se crea el lcd
LiquidCrystal_I2C MyLCD(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);


// prototipos
void imprimirLCD();
void limpiar_lcd();
void configurar_parametros();

byte ciclo = 1;
double tiempo = 0;

void setup_wdt(){
  cli();
  wdt_reset();
  WDTCSR= (1<<WDIE)|(1<<WDP0);
  sei();
}

ISR(WDT_vect)
{
  // Rutina para medir Variables y crear alertas, hacerlo lo mas corto posible
  // Definir como se va a medir y demas.

  //control.calculateU();

}

void setup() {
  wdt_disable();

  // Setup de perifericos
  MyLCD.begin(16, 2);
  stepper.setCurrentPosition(0);
  pinMode(ENABLE, OUTPUT);

  // se configuran los parametros del motor inicial
  stepper.setMaxSpeed(6000);
  stepper.setAcceleration(2800);

  // Se habilita el motor para funcionar
  Serial.begin(9600);

  wdt_enable(WDTO_32MS);
}

void loop() {
  if(boton_modo_operacion.medir_valor()){
    if(boton_confirmacion.medir_valor()){
      configurar_parametros();
      cicloRespiratorio.SetParametros(Poteciometro_frecuencia.medir_valor(), Poteciometro_volumen.medir_valor(), Poteciometro_presion.medir_valor());
      }
    else Impresion_lcd_configurando();
    delay(200);
  }
  else {
    if(ciclo == 1){
    stepper.moveTo(cicloRespiratorio.posicion_Final_subida-2000);
    stepper.setSpeed(cicloRespiratorio.velocidad_subida);
    ciclo = 2;
   // Serial.println("Inicia Respiracion");
   }
  // corre a velocidad constante
  else if(stepper.distanceToGo() >0 && ciclo == 2 )stepper.runSpeed();

  // inicio meseta ----------------------------------------------------------------------
  else if(stepper.distanceToGo() <=0 && ciclo == 2 ){
    ciclo = 3 ;
   // Serial.println("Inicia Meseta");
    tiempo = millis();
  }

  else if(ciclo == 3 && millis() <  (tiempo + cicloRespiratorio.Tiempo_meseta*1000)){}//fin meseta
  else if(ciclo == 3 && millis() >= (tiempo + cicloRespiratorio.Tiempo_meseta*1000)){
    ciclo = 4;
    //Serial.println("FIN Meseta");
  }//fin meseta

  // Expiracion
  else if(ciclo == 4 ){
     stepper.setSpeed(cicloRespiratorio.Velocidad_inicial_bajada);
     //stepper.setAcceleration(cicloRespiratorio.acelaracion_bajada);

     stepper.moveTo(0);
     //Serial.println("Inicio Expiracion");
     delay(100);
     ciclo = 5;
    }

  else if(stepper.distanceToGo()<0 && ciclo == 5 ){
    //if(millis()%100 == 0)
      //Serial.println("V" + String(stepper.speed())+" P2" + String(cicloRespiratorio.Velocidad_inicial_bajada));
    stepper.run();
    }

  else if(stepper.distanceToGo()>=0 && ciclo == 5 ){// inicio meseta
    //Serial.println("Inicio pausa");
    ciclo = 6 ;
    tiempo = millis();
    }

  else if(ciclo == 6 && millis() < (tiempo+cicloRespiratorio.Tiempo_pausa*1000)){}//fin meseta
  else if(ciclo == 6 && millis() >= (tiempo+cicloRespiratorio.Tiempo_pausa*1000)){
    ciclo = 1;
   }//fin meseta


    }
  }

void Impresion_lcd_configurando(){
  limpiar_lcd();
  MyLCD.setCursor(0,0);
  MyLCD.print("Vt:"+ String(Poteciometro_volumen.medir_valor()));
  MyLCD.print("Fr:"+ String(Poteciometro_frecuencia.medir_valor()));
  MyLCD.print("Pr:"+ String(Poteciometro_presion.medir_valor()));
  MyLCD.setCursor(0,1);
  MyLCD.print("  Configurando");
}
//ok
void Impresion_lcd_operando(){
  limpiar_lcd();
  MyLCD.setCursor(0,0);
  MyLCD.print("Vt:"+ String(unico.get_frecuencia()));
  MyLCD.print("Fr:"+ String(unico.get_volumen_tidal()));
  MyLCD.print("Pr:"+ String(unico.get_presion()));
  MyLCD.setCursor(0,1);
  MyLCD.print("Vt:"+ String(Poteciometro_volumen.medir_valor()));
  MyLCD.print("Fr:"+ String(Poteciometro_frecuencia.medir_valor()));
  MyLCD.print("Pr:"+ String(Poteciometro_presion.medir_valor()));
}
//ok
void configurar_parametros(){
  unico.Set_parametros(Poteciometro_volumen.medir_valor(),Poteciometro_frecuencia.medir_valor(),Poteciometro_presion.medir_valor());
  limpiar_lcd();
  MyLCD.setCursor(0,0);
  MyLCD.print("Listo");
  delay(500);
}
//ok
void limpiar_lcd(){
  MyLCD.setCursor(0,0);
  MyLCD.print("                ");
  MyLCD.setCursor(0,1);
  MyLCD.print("                ");
}
