·#define MAX_U  255

class Control{
  public :

    float Ki = 0;
    float Kp = 0;
    //float Kd = 0;
    float Ts = 0.1;
    float uOld = 0;
    float eOld = 0;
    uint8 reference = 0;
    float u = 0;

    void calculateU(float measure){

      float e = reference- measure;
      // PI discrete
      u = uOld+(Kp/T+Ki/2)*e+(-Kp/T+Ki/2)*eOld;

      if (u > 255) {
        u = 255;
      }

      // Update variables
      uOld=u;
      eOld=e;

    }

};
