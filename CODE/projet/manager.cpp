#include "manager.h"

template <class T>
void Manager<T>::addItem(T* tem){
    if (nb==nbMax){
        T** newtab=new T*[nbMax+10];
        for(unsigned int i=0; i<nb; i++) newtab[i]=t[i];
        nbMax+=10;
        T** old=t;
        t=newtab;
        delete[] old;
    }
    t[nb++]=tem;
}

template <class T>
typename Manager<T>::Handler Manager<T>::handler=Handler();

template <class T>
Manager<T>& Manager<T>::getInstance(){
    if (!handler.instance) handler.instance = new Manager; /* instance cr��e une seule fois lors de la premi�re utilisation*/
    return *handler.instance;
}

template <class T>
void Manager<T>::libererInstance(){
    if (handler.instance) { delete handler.instance; handler.instance=0; }
}

template <class T> UV* UVManager<T>::trouver<T>(const QString& c)const{
    for(unsigned int i=0; i<nb; i++)
        if (c==t[i]->getCode()) return t[i];
    return 0;
}

template <class T> UV& UVManager<T>::get<T>(const QString& code){
    UV* uv=trouver<T>(code);
    if (!uv) throw UTProfilerException("erreur, UVManager, UV inexistante");
    return *uv;
}


template <class T>const UV& UVManager<T>::get<T>(const QString& code)const{
    return const_cast<UVManager*>(this)->get<T>(code);
        // on peut aussi dupliquer le code de la m�thode non-const
}
