class movimiento{
  public : 
    byte Frecuencia;                  // Valor configurado por el medico 
    byte volumen;                     // Valor Configurado por el medico
    byte Relacion;                    // Valor Configurado por el medico      
    double velocidad_subida;             // Calculado Inspiracion           
    double aceleracion_subida;           // Calculado Inspiracion
    double posicion_Final_subida;        // Calculado Inspiracion
    double Tiempo_meseta;                // Calculado Meseta
    double Velocidad_inicial_bajada;     // Calculado espiracion
    double acelaracion_bajada;   // Calculado espiracion
    double modo_motor;
    float coeficiente;
    double Tiempo_pausa; 
    
  //Constructor 
  movimiento (){
    Frecuencia = 0;               
    volumen = 0;                     
    Relacion = 0;                    
    velocidad_subida = 0;             
    aceleracion_subida = 0;           
    posicion_Final_subida = 0;        
    Tiempo_meseta = 0;                
    Velocidad_inicial_bajada = 0;     
    acelaracion_bajada = 0;
    modo_motor = 0.5;
    coeficiente = 0;
    Tiempo_pausa = 0;
  }

  int get_velocidad_subida(){return velocidad_subida;}
  int get_posicion_Final_subida(){return posicion_Final_subida;}

  
  void SetParametros(byte frec, byte vol,byte rela){
    //relacion de tiempo sirve para definir subida y bajada 
    double tiempo_Ciclo = 60 /(2*frec+10);
    // Inspiracion 
    posicion_Final_subida  = ((vol*100.0)/5.7+40)*(200.0/(8*modo_motor)); // 40 es un offset del tornillo
    velocidad_subida = ((posicion_Final_subida- (40)*(200.0/(8*modo_motor)))/((tiempo_Ciclo*(1.0/(rela+1)))*0.65));   
    aceleracion_subida = 0;
    
    // se calcula tiempo de meseta 
    Tiempo_meseta = tiempo_Ciclo*(1.0/(rela+1))*.35;
    
    // Espiracion
    double Tiempo_bajada = tiempo_Ciclo*(double(rela)/(rela+1))*0.7;
    Tiempo_pausa =  tiempo_Ciclo*(double(rela)/(rela+1))*0.3;
    double Tiempo_inicio =  tiempo_Ciclo*(1.0/(rela+1));
    double Tiempo_final =  Tiempo_inicio + Tiempo_bajada;
    double delta_tiempo = Tiempo_inicio  - Tiempo_final;
  
    coeficiente = (vol*100.0)/((delta_tiempo )*(delta_tiempo ));  
    acelaracion_bajada = ((2*coeficiente)/5.7)*(200.0/(8*modo_motor));
    Velocidad_inicial_bajada = ((2*coeficiente*delta_tiempo)/5.7)*(200.0/(8*modo_motor));
    //return tiempo_Ciclo*(1.0/(rela+1))*0.65;
  }  
};
