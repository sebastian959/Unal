class Motor{
  
  public:
  // parametros ------------------------------------
  byte pin;
  byte velocidad;
  
  // funciones -------------------------------------
  
  // constructor
  Motor(byte p){
    pin = p;
    velocidad = 0;
    configurar_pin()
    }
  // getters
  byte get_frecuencia(){return frecuencia;}
  byte get_volumen_tidal(){return volumen_tidal;}
  byte get_presion(){return frecuencia;}
  // setters
  void set_frecuencia(byte valor){frecuencia = valor;}
  void set_volumen_tidal(byte valor){volumen_tidal = valor;}
  void set_presion(byte valor){frecuencia = valor;}

  // 
  void configurar_pin(){pinMode(pin,OUTPUT);}  
 
 
};
