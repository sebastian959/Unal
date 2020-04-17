class Entrada{
  public:
  // parametros ------------------------------------
  byte tipo;    // 0 analogo  1 digital
  byte medida;  // valor de 1 a 10 que al imprimise se debe ajustar
  byte pin;     // pin asociado 
  
  // funciones -------------------------------------
  
  // constructor
  //  Entrada(){}
  Entrada(byte P ){
    tipo = 0;    // se inicializa como analogo
    medida = 0;   
    pin = P;       
    configurar_pin();
  }
  Entrada(byte P ,byte T){
    tipo = 1;    // 0 analogo  1 digital
    medida = 0;  // valor de 1 a 10 que al imprimise se debe ajustar
    pin = P;     // pin asociado 
    configurar_pin();
  }
  // getters
  byte get_tipo(){return tipo;}
  byte get_medida(){return medida;}
  byte get_pin(){return pin;}
  
  // setters
  
  void set_tipo(byte valor){tipo = valor;}
  void set_medida(byte valor){medida = valor;}
  void set_pin(byte valor){pin = valor;}

  // configurar pin 
  void configurar_pin(){pinMode(pin,INPUT);}  
    
  // devuelve el valor medido en una escala de 1 a 10
  byte medir_valor(){
   if (tipo == 0 )return map(analogRead(pin),0,1021,0,10);
   return bool(digitalRead(pin));
   }
};
