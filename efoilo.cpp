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
    void clear();
    void delete_0();
    void delete_end();



protected:
    CNode<T> *tail;
};

template<class T>
CLList<T>::~CLList<T>(){
    clear();    
}

template<class T> 
CNode<T> *CLList<T>::insert_0(const T& el){
    if(isEmpty()){ // se a lista está vazia, cria um novo nó e aponta-lhe tail
        tail = new CNode<T>(el);
        tail->next = tail;
    } else { // caso contrário, cria um novo apontador com auxílio do constructor de nós
             // atribuindo-lhe o valor de el e a apontar para o ex-primeiro elemento
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
    } else { //caso a lista nao esteja vazia, cria um novo nó com auxílio do constructor
             //apontando-lhe o apontador do seguinte de tail
        tail->next = new CNode<T>(el, tail->next);
        tail = tail->next; //aponta tail para o novo nó criado que é apontado pelo seguinte de tail
    }
    tamanho_lista++;
    return tail;
}

template<class T>
ostream& CLList<T>::print_0(ostream& out) const {
    if(isEmpty()) 
        return out << "Comando print_0: Lista vazia!\n";
    
    return out << "Lista(0)= " << tail->next->element << "\n"; //imprime o nó seguinte a tail, o primeiro.
}

template<class T>
ostream& CLList<T>::print_end(ostream& out) const {
    if(isEmpty()) 
        return out << "Comando print_end: Lista vazia!\n";
    
    return out << "Lista(end)= " << tail->element << "\n"; //imprime o nó apontado por tail
}

template<class T>
ostream& CLList<T>::print(ostream& out) const {
    if(isEmpty()) 
        return out << "Comando print: Lista vazia!\n";
    
    
    CNode<T> *tmp;
    tmp = tail->next;
    out << "Lista= ";
    do { //com auxílio de um apontador temporário, percorre a lista (iterando-a)
         //e imprimindo os seus elementos
        out << tmp->element << " ";
        tmp = tmp->next; //aponta o apontador temporário para o nó seguinte (iterando a lista)
    } while(tmp != tail->next); //caso o apontador temporário aponte para o primeiro elemento (o seguinte a tail) 
                                // significa que atingiu o fim da lista.
    out << "\n";
    return out;
}

template<class T> 
void CLList<T>::delete_0(ostream& out){
    
    if(isEmpty()) {
        out << "Comando delete_0: Lista vazia!\n";
        return;
    }
    
    if(tail->next == tail) { //so tem um no, logo apaga o nó apontado por tail
                             //apontando tail para nullptr
        delete tail;
        tail = nullptr;
    } else  { //caso contrário, com auxílio de um apontador temporário para salvaguardar
              //o apontador seguinte ao do primeiro nó, apaga o nó seguinte a tail
              //(o primeiro), e aponta tail para o nó temporário (que aponta para o ex-segundo nó)
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
    } else { //com auxílio de um apontador temporário de nome head, percorre a lista
             //até o seguinte de head apontar para tail. Neste caso aponta o seguinte
             //de head, para o seguinte de tail (o primeiro nó), e apaga o apontador
             //tail, igualando-o depois ao apontador temporário head.
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
    out << "Lista tem " << tamanho_lista << " itens\n"; //retorna o valor da variavel tamanho_lista
    return tamanho_lista;
}

template<class T>
void CLList<T>::clear(ostream& out) {
   
    if(isEmpty()) {
        out << "Comando clear: Lista vazia!\n";
        return;
    }
    
    do { //percorre toda a lista apagando, a cada iteracção, o primeiro
         //nó, quando tail apontar para nullptr significa que todos os elementos foram removidos
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
    
    do { //percorre a lista, com auxílio de um apontador temporário head testando o seu
         //elemento contra o elemento recebido como parâmetro, retornando o apontador head
        if(head->element == el) {
            out << "Item " << el << " na posicao " << contador << "\n";
            return head;
        }
        contador++;
        head = head->next; //aponta head para o seu seguinte, de modo a iterar a lista
    } while(head != tail->next); //caso head aponte para o seguinte de tail (primeiro nó da lista)
                                 //significa que o valor de el não foi encontrado
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
    
    do { //percorre a lista com auxílio do apontador temporário head, testando cada posição contra uma cópia de apontador tmp, 
         //tmp contêm uma cópia do maior valor de head para uma dada posição
         //como queremos a primeira posiçao onde o maior valo ocorre testamos apenas para > e não para >=
         //De notar que se tmp->next for igual a nullptr, significa que ainda nenhum elemento para o maior valor foi guardado
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
        delete_0();
        return;
    } else if(pos == tamanho_lista-1) { //quer apagar posicao final
        delete_end();
        return;
    } else if (pos > tamanho_lista-1) {
        out << "Comando delete_pos: Posicao invalida!\n";
        return;  
    } 
        
    CNode<T> *head = tail;
    CNode<T> *tmp = tail;
    
    for(int contador = 0; contador < tamanho_lista; ++contador){ 
        //com auxílio de uma variavel contador, conta as iterações de head
        //quando a variavel atinge o mesmo valor de pos, apaga essa posição
        //com auxílio de uma apontador temporário que aponta para o nó seguinte
        //de head
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
    
    do { //com o auxílio de um apontador temporário head, percorre a lista entre o primeiro elemento e pos2
         //adicionando os valores situados entre pos1 e pos2 a uma nova lista temporária por ordem inversa
        if(contador>=pos1 ){
            circular_list_aux.insert_0(head->element);
        }
        head = head->next;
        ++contador;
    } while(contador <= pos2);
    
    
    CNode<T> *head_aux = circular_list_aux.tail->next;
    head = tail->next;
    
    contador = 0;

    do { //para cada nó situado entre pos1 e pos2 copia o valor do elemento da lista auxiliar
         //para a lista principal, apontando o apontador temporário auxiliar head_aux para o elemento
         //seguinte da lista auxiliar
        if(contador >= pos1 &&  contador <= pos2){
            head->element = head_aux->element;
            head_aux = head_aux->next;
        }
        ++contador;
        head = head->next;
    } while(head != tail->next);
    circular_list_aux.clear();
    return tail;
}


//definicao das funcoes auxiliares
template<class T> 
bool CLList<T>::isEmpty() const {
    return tail==nullptr; //retorna o resultado do teste se o apontador tail aponta para nullptr.
}

//overload da funcao clear para apagar a lista sem escrever mensagens
template<class T>
void CLList<T>::clear(){
    if(isEmpty()) {
        return;
    }
    do { 
        delete_0();
    } while(tail != nullptr);  
}

//overload da funcao delete_0 para apagar a lista sem escrever mensagens
template<class T>
void CLList<T>::delete_0(){
    if(isEmpty()) {
        return;
    }
    
    if(tail->next == tail) { 
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

//overload da funcao delete_end para apagar a lista sem escrever mensagens
template<class T>
void CLList<T>::delete_end(){
    if(isEmpty()) {
        return;
    }
    
    if(tail->next == tail) { 
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

int main() {
    
    string input, command, argumentos;
    int argumento = 0;
    regex argumentos_regex("-?[0-9]+");

    CLList<signed int> circular_list;
    
    while (getline(cin, input)){
        //os comandos insert_0, insert_end, delete_pos, find têm argumentos, logo temos que proceder à extracção dos mesmos
        //após extrairmos o respectivo comando da string input até ao primeiro caractere " "
        command = input.substr(0, input.find(" "));
        if (command == "insert_0" || command == "insert_end" || command == "delete_pos" || command == "find" ){ 
            //extraímos os argumentos com auxílio novamente da função substr, mas desta vez com início na posição
            //seguinte ao tamanho de command.size()+1 para ignorarmos o comando já extraído. De notar que iremos 
            //separar todos os argumentos até ao fim da string de input.
            argumentos = input.substr(command.size()+1, string::npos);
            //como os comandos podem ter mais que um argumento, percorremos todas as iterações as strings extraídas anteriormente
            //convertendo-as em inteiros e chamando a respectiva função para um dado comando
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
        //os comandos seguintes não necessitam de argumentos a serem extraídos com a excepção do ultímo comando invert_range
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