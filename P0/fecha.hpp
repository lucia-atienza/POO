#ifndef FECHA_HPP_
#define FECHA_HPP_

class Fecha
{
public:
    //constructores
    explicit Fecha(int dia = 0, int mes = 0, int anno = 0);
    Fecha(const char* cadena);

    operator const char*() const;
    
    //constantes de la clase
    static const int AnnoMinimo;
    static const int AnnoMaximo;

    //incrementos
    Fecha operator++(int);
    Fecha& operator++();

    //decrementos 
    Fecha operator--(int);
    Fecha& operator--();

    //operador de asignacion sumas y restas
    Fecha& operator+=(int num);
    Fecha& operator-=(int num);
    Fecha operator+(int num) const;
    Fecha operator-(int num)const;

    //observadores
    const int dia() const;
    const int mes() const;
    const int anno() const;

    class Invalida
    {
    public:
        Invalida(const char* cadena) : mensaje(cadena){};
        const char* por_que() const {return mensaje;} ;
    private:
        const char* mensaje;
    };
    
private:
    int dia_, mes_, anno_;
    void valida();
};


bool operator<(const Fecha& fecha1, const Fecha& fecha2) noexcept;
bool operator<=(const Fecha& fecha1, const Fecha& fecha2) noexcept;
bool operator>(const Fecha& fecha1, const Fecha& fecha2) noexcept;
bool operator>=(const Fecha& fecha1, const Fecha& fecha2) noexcept;
bool operator==(const Fecha& fecha1, const Fecha& fecha2) noexcept;
bool operator!=(const Fecha& fecha1, const Fecha& fecha2) noexcept;


#endif 