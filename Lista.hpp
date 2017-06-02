

#include <SFML/Graphics.hpp>
#include <iostream>

// Estrutura da fila
template <class Gen>
struct Node{
    Gen info;
    struct Node *dir;
    struct Node *esq;
};

template<class Gen>
class Lista{
    public:
        Node<Gen> *header;
    private:
        void cria();
        void insere(Gen&,bool&);
        void remove(Gen&,bool&);
        void insereADireitaDeP(struct Node <Gen> &N,Gen&,bool&);
        void removeP(struct Node <Gen> &N,Gen&,bool&);
};

template<class Gen>
void Lista<Gen>::cria(){
    Node<Gen> *Paux = new Node<Gen>();
    header=Paux;
    Paux=NULL;
}

template<class Gen>
void Lista<Gen>::insere(Gen& x,bool& deuCerto){
    insereADireitaDeP(header,x,deuCerto);
}
template<class Gen>
void Lista<Gen>::insereADireitaDeP(struct Node <Gen> &N,Gen& x,bool& deuCerto){
      Node<Gen> *Paux = new Node<Gen>();
    
    if(N->esq==NULL)
        N->esq=Paux;
    
    Paux->info=x;
    Paux->dir=N->dir;
    Paux->esq=N;
    N->dir->esq=Paux;
    N->dir=Paux;
    Paux=NULL;
    deuCerto=true;
}
template<class Gen>
void Lista<Gen>::remove(Gen& x,bool& deuCerto){
    Node <Gen> *Paux = header->esq;
    x=Paux->info;
    header->esq=Paux->esq;
    Paux->esq->dir=header;
    delete Paux;
    
}

template<class Gen>
void Lista<Gen>::removeP(struct Node <Gen> &N,Gen& x,bool& deuCerto){
    Node <Gen> *Paux = N;
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
