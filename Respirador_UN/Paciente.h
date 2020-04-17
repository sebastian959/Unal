class Paciente{
  
  public:
  // parametros ------------------------------------
  byte frecuencia;
  byte volumen_tidal;
  byte presion;
  
  // funciones -------------------------------------
  
  // constructor
  Paciente(){
    frecuencia = 0;
    volumen_tidal = 0;
    presion = 0;
    }
  // getters
  byte get_frecuencia(){return frecuencia;}
  byte get_volumen_tidal(){return volumen_tidal;}
  byte get_presion(){return presion;}
  // setters
  void set_frecuencia(byte valor){frecuencia = valor;}
  void set_volumen_tidal(byte valor){volumen_tidal = valor;}
  void set_presion(byte valor){presion = valor;}

  void Set_parametros(byte valor , byte valor2, byte valor3){
    frecuencia = valor;
    volumen_tidal = valor2;
    presion = valor3;
  }
};
