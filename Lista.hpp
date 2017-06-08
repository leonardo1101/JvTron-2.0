

#include <SFML/Graphics.hpp>
#include <iostream>

// Estrutura da Lista
template <class Gen> struct Node{
    Gen info;
    struct Node<Gen> *dir;
    struct Node<Gen> *esq;
};

template<class Gen>
class Lista{
    private:
    public:
        struct Node<Gen> *header;
        void cria();
        void insere(Gen&,bool&);
        void insereAEsquerdaDeP(struct Node <Gen> *N,Gen&,bool&);
        void removeP(struct Node <Gen> &N,Gen&,bool&);
        void remove(Gen& x,bool& deuCerto);
};

template<class Gen>
void Lista<Gen>::cria(){
    struct Node<Gen> *Paux = new Node<Gen>();
    header=Paux;
    header->esq=header;
    header->dir=header;
    Paux=NULL;
    delete Paux;
}

template<class Gen>
void Lista<Gen>::insere(Gen& x,bool& deuCerto){
    insereAEsquerdaDeP(header,x,deuCerto);
}
template<class Gen>
void Lista<Gen>::insereAEsquerdaDeP(struct Node <Gen> *N,Gen& x,bool& deuCerto){
    struct  Node<Gen> *Paux = new struct Node<Gen>();
    
    
    Paux->info=x;
    Paux->esq=N->esq;
    Paux->dir=N;
    N->esq->dir=Paux;
    N->esq=Paux;
    Paux=NULL;
    deuCerto=true;
    delete Paux;
    
}

template<class Gen>
void Lista<Gen>::removeP(struct Node <Gen> &N,Gen& x,bool& deuCerto){
    struct Node <Gen> *Paux = N;
    header->info=x;
    while(Paux->info != x)
        Paux=Paux->esq;
    
    if(Paux != header){
        deuCerto=true;
        Paux->esq->dir=Paux->dir;
        Paux->dir->esq=Paux->esq;
        delete Paux;
    }else{
        deuCerto=false;
    }
    
}
template <class Gen>
void Lista<Gen>::remove(Gen& x,bool& deuCerto){
    struct Node <Gen> *Paux;
    Paux=header->esq;
    x=Paux->info;
    header->esq=Paux->esq;
    Paux->esq->dir=header;
    delete Paux;
}
