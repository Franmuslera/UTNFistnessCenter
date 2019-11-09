#ifndef NOTICIA_H_INCLUDED
#define NOTICIA_H_INCLUDED

class Noticia{
    private:
        char titulo[200], descripcion[2000];
        Fecha fecha_de_noticia;
        bool estado;
    public:
        char* getTitulo(){return titulo;};
        char* getDescripcion(){return descripcion;};
        Fecha getFechaNoticia(){return fecha_de_noticia;};
        bool getEstado(){return estado;};
        void setTitulo(char*t){strcpy(titulo, t);};
        void setDescripcion(char *d){strcpy(descripcion, d);};
        void setFecha(Fecha f){fecha_de_noticia = f;};
        void setEstado(bool e){estado = e;};
        void cargar();
        void mostrar();
};


#endif // NOTICIA_H_INCLUDED
