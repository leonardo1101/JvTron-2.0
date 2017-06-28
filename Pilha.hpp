#include <iostream>

struct NodeP{
  int Info;
  NodeP *Next;
};
typedef struct NodeP *NodePPtr;

class Pilha
{
    public:
        Pilha();
        virtual ~Pilha();
        void Empilha(int X, bool DeuCerto);
        void Desempilha(int X, bool DeuCerto);
        bool Vazia();
        bool Cheia();
        int getTopo();
        int getNumeroElementos() const;
    private:
        NodePPtr P_Topo;
        int numeroElementos;
};

Pilha::Pilha()
{
    numeroElementos = 0;
    P_Topo = NULL;
}

Pilha::~Pilha()
{
    int X;
    bool DeuCerto;
    while(!Vazia()){
        DeuCerto = true;
        Desempilha(X, DeuCerto);
    }
}

void Pilha::Empilha(int X, bool DeuCerto){
    NodePPtr P_Aux;
    if(Cheia()==true)
        DeuCerto = false;
    else{
        numeroElementos++;
        DeuCerto = true;
        P_Aux = new NodeP;
        P_Aux->Info = X;
        P_Aux->Next = P_Topo;
        P_Topo = P_Aux;
    }
}

void Pilha::Desempilha(int X, bool DeuCerto){
    NodePPtr P_Aux;
    if(Vazia()==true)
        DeuCerto = false;
    else{
        DeuCerto = true;
        X = P_Topo->Info;
        P_Aux = P_Topo;
        P_Topo = P_Topo->Next;
        delete(P_Aux);
    }
}

bool Pilha::Cheia(){
    return false;
}

bool Pilha::Vazia(){
    if(P_Topo == NULL)
        return true;
    else
        return false;
}

int Pilha::getTopo(){
    return P_Topo->Info;
}

int Pilha::getNumeroElementos() const{
    return numeroElementos;
}