#ifndef LISTA_H
#define LISTA_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Inimigo.hpp"
#include "Disco.hpp"
// Estrutura da Lista
template <class Gen> struct Node{
    Gen info;
    struct Node<Gen> *dir;
    struct Node<Gen> *esq;
};

template<class Gen>
class Lista{
    private:
        int quant;
        struct Node<Gen> *Primeiro;
        struct Node<Gen> *Atual;
        struct Node<Gen> *header;
    public:
        Lista();
        void PegaOProximo(Gen&,bool&);
        void PegaOPrimeiro(Gen&,bool&);
        void cria();
        int getQuant();
        void insere(Gen&,bool&);
        bool estaNaLista(Gen& x);
        void insereAEsquerdaDeP(struct Node <Gen> *N,Gen&,bool&);
        void removeP(Gen&,bool&);
        void remove(Gen& x,bool& deuCerto);
};

template<class Gen>
Lista<Gen>::Lista(){
    
    quant=0;
}
template<class Gen>
int Lista<Gen>::getQuant(){
    
    return quant;
};
template<class Gen>
void Lista<Gen>::cria(){
    quant=0;
    struct Node<Gen> *Paux = new Node<Gen>();
    header=Paux;
    header->esq=header;
    header->dir=header;
    Paux=NULL;
    delete Paux;
}
template<class Gen>
void Lista<Gen>::PegaOPrimeiro(Gen& x,bool& deuCerto){
    Atual=header->dir;
    Primeiro=Atual;
    if(Primeiro == NULL){
        deuCerto= false;
    }else{
        x=Primeiro->info;
        deuCerto= true;
    }
};
template<class Gen>
void Lista<Gen>::PegaOProximo(Gen& x,bool& deuCerto){
    if(Atual != NULL)
        Atual=Atual->dir;
    if(Atual == NULL){
        deuCerto=false;
    }else{
        deuCerto=true;
        x=Atual->info;
    }
};
template<class Gen>
void Lista<Gen>::insere(Gen& x,bool& deuCerto){
    quant++;
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

template<>
void Lista<Inimigo>::removeP(Inimigo& x,bool& deuCerto){
    struct Node <Inimigo> *Paux;
    Paux= header->esq;;
    header->info=x;
    while(Paux->info.id != x.id)
        Paux=Paux->esq;
    
    if(Paux != header){
        quant--;
        deuCerto=true;
        Paux->esq->dir=Paux->dir;
        Paux->dir->esq=Paux->esq;
        delete Paux;
    }else{
        deuCerto=false;
    }
    
}
template<>
void Lista<Disco>::removeP(Disco& x,bool& deuCerto){
    struct Node <Disco> *Paux;
    Paux= header->esq;;
    header->info=x;
    while(Paux->info.id != x.id)
        Paux=Paux->esq;
    
    if(Paux != header){
        quant--;
        deuCerto=true;
        Paux->esq->dir=Paux->dir;
        Paux->dir->esq=Paux->esq;
        delete Paux;
    }else{
        deuCerto=false;
    }
    
}
template<>
void Lista<Item>::removeP(Item& x,bool& deuCerto){
    struct Node <Item> *Paux;
    Paux= header->esq;;
    header->info=x;
    while(Paux->info.getId() != x.getId())
        Paux=Paux->esq;
    
    if(Paux != header){
        quant--;
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
    if(header->dir != header){
        quant--;
        deuCerto=true;
        Paux=header->dir;
        x=Paux->info;
        header->dir=Paux->dir;
        Paux->dir->esq=header;
        delete Paux;
    }else{
        deuCerto=false;
        
    }
}
template <>
bool Lista<Inimigo>::estaNaLista(Inimigo& x){
    struct Node <Inimigo>  *Paux;
    Paux=header->esq;
    while(Paux != header){
        if(Paux->info.id == x.id)
            return true;
    }
    return false;
}
// inline bool operator==(const Item &lhs, const Item & rhs){ 
//     if(lhs.getId() == rhs.getId())
//         return true;
//     return false;
// }
#endif
