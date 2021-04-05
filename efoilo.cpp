#include <iostream>
#include <sstream>
#include <string>
#include <regex>

using namespace std;

//nó de lista circular
template<class T>
class CNode {
public:
    CNode() {
        next = nullptr;
    }    
    CNode(T e, CNode<T> *n = nullptr) {
        element = e;
        next = n;
    }
    T element;
    CNode<T> *next;
};

//lista circular
template <class T>
class CLList {
   int tamanho_lista;
   
public:
    CLList() {
        tail = nullptr;
        tamanho_lista = 0;
    }
    ~CLList();
    
    CNode<T> *insert_0(const T&);
    CNode<T> *insert_end(const T&);
    ostream& print_0(ostream&) const;
    ostream& print_end(ostream&) const;
    ostream& print (ostream&) const;
    void delete_0(ostream&);
    void delete_end(ostream&);
    int dim(ostream&) const;
    void clear(ostream&);
    CNode<T>* find(T, ostream&) const;
    CNode<T>* find_max(ostream&) const;
    void delete_pos(int, ostream&);
    CNode<T>* invert_range(T, T, ostream&);
    
    //funcoes auxiliares
    bool isEmpty() const;

protected:
    CNode<T> *tail;
};

template<class T>
CLList<T>::~CLList<T>(){
    if (!isEmpty()){
        CNode<T> *head = tail->next;
        
        do {
            delete head;
            head = head->next;
        } while(head != tail->next);
    }     
}

template<class T> 
CNode<T> *CLList<T>::insert_0(const T& el){
    if(isEmpty()){
        tail = new CNode<T>(el);
        tail->next = tail;
    } else {
        CNode<T> *tmp = new CNode<T>(el, tail->next);
        tail->next = tmp;
    }
    tamanho_lista++;
    return tail;
}

template<class T> 
CNode<T> *CLList<T>::insert_end(const T& el){
    if (isEmpty()){
        tail = new CNode<T>(el);
        tail->next = tail;
    } else {
        tail->next = new CNode<T>(el, tail->next);
        tail = tail->next;
    }
    tamanho_lista++;
    return tail;
}

template<class T>
ostream& CLList<T>::print_0(ostream& out) const {
    if(isEmpty()) 
        return out << "Comando print_0: Lista vazia!\n";
    
    return out << "Lista(0)= " << tail->next->element << "\n";
}

template<class T>
ostream& CLList<T>::print_end(ostream& out) const {
    if(isEmpty()) 
        return out << "Comando print_end: Lista vazia!\n";
    
    return out << "Lista(end)= " << tail->element << "\n";
}

template<class T>
ostream& CLList<T>::print(ostream& out) const {
    if(isEmpty()) 
        return out << "Comando print: Lista vazia!\n";
    
    
    CNode<T> *tmp;
    tmp = tail->next;
    out << "Lista= ";
    do {
        out << tmp->element << " ";
        tmp = tmp->next; 
    } while(tmp != tail->next);
    out << "\n";
    return out;
}

template<class T> 
void CLList<T>::delete_0(ostream& out){
    
    if(isEmpty()) {
        out << "Comando delete_0: Lista vazia!\n";
        return;
    }
    
    if(tail->next == tail) { // so tem um no
        delete tail;
        tail = nullptr;
    } else  {
        CNode<T> *tmp;
        tmp = tail->next->next;
        delete tail->next;
        tail->next = tmp;
    }
    tamanho_lista--;
}

template<class T> 
void CLList<T>::delete_end(ostream& out){
    
    if(isEmpty()) {
        out << "Comando delete_0: Lista vazia!\n";
        return;
    }
    
    if(tail->next == tail) { // so tem um no
        delete tail;
        tail = nullptr;
    } else {
        CNode<T> *head = tail->next;
        while (head->next != tail) {
            head = head->next;
        } 
        head->next = tail->next;
        delete tail;
        tail = head;
    }
    tamanho_lista--;
}

template<class T>
int CLList<T>::dim(ostream& out) const {
    out << "Lista tem " << tamanho_lista << " itens\n";
    return tamanho_lista;
}

template<class T>
void CLList<T>::clear(ostream& out) {
   
    if(isEmpty()) {
        out << "Comando clear: Lista vazia!\n";
        return;
    }
    
    do {
        delete_0(out);
    } while(tail != nullptr);   
}

template<class T>
CNode<T>* CLList<T>::find(T el, ostream& out) const {
    
    if(isEmpty()) {
        out << "Comando find: Lista vazia!\n";
        return nullptr;
    }
    
    CNode<T> *head = tail->next;
    int contador = 0;
    
    do {
        if(head->element == el) {
            out << "Item " << el << " na posicao " << contador << "\n";
            return head;
        }
        contador++;
        head = head->next;
    } while(head != tail->next);
    out << "Item " << el << " nao encontrado!\n";
    return nullptr;
}

template<class T>
CNode<T>* CLList<T>::find_max(ostream& out) const {
    
    if(isEmpty()) {
        out << "Comando find_max: Lista vazia!\n";
        return nullptr;
    }
    
    CNode<T> *head = tail->next;
    CNode<T> *tmp = new CNode<T>(0, nullptr);
    
    int contador = 0;
    int posicao = 0;
    
    do {
        if((head->element > tmp->element) || (head->element == tmp->element && tmp->next == nullptr)) {
            tmp = head;
            posicao = contador;
        }
        ++contador;
        head = head->next;
    } while(head != tail->next);
    
    out << "Max Item " << tmp->element << " na posicao " << posicao << "\n";
    return tmp;
}


template<class T>
void CLList<T>::delete_pos(int pos, ostream& out) {
    
    if(isEmpty()) {
        out << "Comando delete_pos: Lista vazia!\n";
        return;
    }
        
    if(pos == 0 ){ //quer apagar a posicao inicial
        delete_0(out);
        return;
    } else if(pos == tamanho_lista-1) { //quer apagar posicao final
        delete_end(out);
        return;
    } else if (pos > tamanho_lista-1) {
        out << "Comando delete_pos: Posicao invalida!\n";
        return;  
    } 
        
    CNode<T> *head = tail;
    CNode<T> *tmp = tail;
    
    for(int contador = 0; contador < tamanho_lista; ++contador){
        if(pos == contador){
            head->next = tmp->next;
            delete tmp;
            tamanho_lista--;
            return;
        }
        head = head->next;
        tmp = head->next;
    }
}

template<class T>
CNode<T>* CLList<T>::invert_range(T pos1, T pos2, ostream& out) {
    
    if(isEmpty()) {
        out << "Comando invert_range: Lista vazia!\n";
        return tail;
    } else if ((pos1 >= tamanho_lista || pos1 < 0) || (pos2 >= tamanho_lista || pos2 < 0) || (pos1>pos2) ) {
        out << "Comando invert_range: Posicao invalida!\n";
        return tail;
    } else if (pos1 == pos2)
        return tail;
    
    CLList<T> circular_list_aux;
    CNode<T> *head = tail->next;
    
    int contador = 0;    
    
    do {
        if(contador>=pos1 ){
            circular_list_aux.insert_0(head->element);
        }
        head = head->next;
        ++contador;
    } while(contador <= pos2);
    
    
    CNode<T> *head_aux = circular_list_aux.tail->next;
    head = tail->next;
    
    contador = 0;

    do {
        if(contador >= pos1 &&  contador <= pos2){
            head->element = head_aux->element;
            head_aux = head_aux->next;
        }
        ++contador;
        head = head->next;
    } while(head != tail->next);
    return tail;
}


//definicao das funcoes auxiliares
template<class T> 
bool CLList<T>::isEmpty() const {
    return tail==nullptr;
}

int main() {
    
    string input, command, argumentos;
    int argumento = 0;
    regex argumentos_regex("-?[0-9]+");

    CLList<signed int> circular_list;
    
    while (getline(cin, input)){
        command = input.substr(0, input.find(" "));
        if (command == "insert_0" || command == "insert_end" || command == "delete_pos" || command == "find" ){ 
            argumentos = input.substr(command.size()+1, string::npos);
            for( sregex_iterator i = sregex_iterator(argumentos.begin(), argumentos.end(), argumentos_regex); i!= sregex_iterator(); ++i) {
                smatch match = *i;
                argumento = stoi(match.str());
                if (command == "insert_0"){
                    circular_list.insert_0(argumento);
                } else if (command == "insert_end") {
                    circular_list.insert_end(argumento);
                } else if (command == "delete_pos") {
                    circular_list.delete_pos(argumento,cout);
                } else if (command == "find") {
                    circular_list.find(argumento,cout);
                } 
            }            
        } else if (command == "print") {
            circular_list.print(cout);       
        } else if (command == "print_0") {
            circular_list.print_0(cout);       
        } else if (command == "print_end") {
            circular_list.print_end(cout);       
        } else if (command == "delete_0") {
            circular_list.delete_0(cout);       
        } else if (command == "delete_end") {
            circular_list.delete_end(cout);       
        } else if (command == "dim") {
            circular_list.dim(cout);       
        } else if (command == "clear") {
            circular_list.clear(cout);       
        } else if (command == "find_max") {
            circular_list.find_max(cout);       
        } else if (command == "invert_range") { //caso especial tem que ter apenas dois argumentos
            argumentos = input.substr(command.size()+1, string::npos);
            if (distance(sregex_iterator(argumentos.begin(), argumentos.end(), argumentos_regex), sregex_iterator()) == 2) {
                sregex_iterator i = sregex_iterator(argumentos.begin(), argumentos.end(), argumentos_regex);
                smatch match_1 = *i++;
                smatch match_2 = *i;
                circular_list.invert_range(stoi(match_1.str()), stoi(match_2.str()), cout);
            }else
                cout << "O commando invert_range tem que ter 2 argumentos\n";
        }
    }
    return 0;
}