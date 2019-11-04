#ifndef CANCHA_H_INCLUDED
#define CANCHA_H_INCLUDED


const char FILE_CANCHAS = "canchas.dat";

class Cancha{
 private:
     int nroCancha;
     char tipoCancha[30];
 public:
    int getNroCancha();
    char getTipoCancha();
    void setNroCancha(int);
    void setTipoCancha(char);
    Cancha(int,char*);
};

int Cancha::getNroCancha(){
   return nroCancha;
   }

char Cancha::getTipoCancha(){
   return tipoCancha;
   }

void setNroCancha(int n){
    nroCancha = n;
    }

void setTipoCancha(char* t){
    tipoCancha = t;
    }

    Cancha::Cancha (int n, char* t_const=""){
    nroCancha = n;
    strcpy(tipoCancha,t_const);
    }

#endif // CANCHA_H_INCLUDED
