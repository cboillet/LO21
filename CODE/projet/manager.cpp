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
