/*
Está declarando token como string sem o tamanho. Deve dar pau. Talvez usar char* token
Pedro carregado.

git pull
git add trab.cpp
git commit -m "mensagem"
git push
        // codPreP << " |Processando token: "<< token << " |\n";//debug de pobre

*/
#include <iostream>
#include <fstream>                           //Para lidar com o arquivo. Nunca usei isso, então não sei comofas
#include <string.h>
#include <list>
#include <ctype.h>                          // Usando na função isalpha
#include <sstream>                          // Para retirar as palavras da linha
#include <algorithm>                        // Para procurar na tabela de simbolos

using namespace std;

typedef struct tabSimItem_s {
    char label[20];
    int endereco;
} tabSimItem;

// As duas funcoes abaixo https://stackoverflow.com/a/23944175
// Servem para fazer uma comparacao case insensitive de strings
bool icompare_pred(unsigned char a, unsigned char b)
{
    return std::tolower(a) == std::tolower(b);
}

bool iequals(std::string const& a, std::string const& b)
{
    if (a.length()==b.length()) {
        return std::equal(b.begin(), b.end(),
                           a.begin(), icompare_pred);
    }
    else {
        return false;
    }
}

int getOP (string token) {
    if (iequals(token,"ADD") == 1) {
        return 2;
    }
    else if (iequals(token,"SUB") == 1) {
        return 2;
    }
    else if (iequals(token,"MULT") == 1) {
        return 2;
    }
    else if (iequals(token,"DIV") == 1) {
        return 2;
    }
    else if (iequals(token,"JMP") == 1) {
        return 2;
    }
    else if (iequals(token,"JMPN") == 1) {
        return 2;
    }
    else if (iequals(token,"JMPP") == 1) {
        return 2;
    }
    else if (iequals(token,"JMPZ") == 1) {
        return 2;
    }
    else if (iequals(token,"COPY") == 1) {
        return 3;
    }
    else if (iequals(token,"LOAD") == 1) {
        return 2;
    }
    else if (iequals(token,"STORE") == 1) {
        return 2;
    }
    else if (iequals(token,"INPUT") == 1) {
        return 2;
    }
    else if (iequals(token,"OUTPUT") == 1) {
        return 2;
    }
    else if (iequals(token,"STOP") == 1) {
        return 1;
    }
    else {
        return -1;
    }
    
}

void inputTemp (string *nome) {
    cout << "Digite o nome do arquivo \n";
    cin >> *nome;
}

// Aqui tem que adequar para as diretivas e áreas .text e .data
// Ele ta supondo que ou é label, ou instrução ou parametro
// Por enquanto ele está apenas fazendo a tabela de símbolos
// Gera um arquivo intermediário sem rótulos e comentários
void primeiraPassagem (list <tabSimItem> *tabSim, string nome) {
    ifstream arquivo;
    ofstream codPreP;
    char colon;
    int tamanho, i=0, endereco=0;
    string token, linha;
    tabSimItem SimAtual;

    arquivo.open(nome); //O nome do arquivo vai ser passado pelo terminal, então não sei ainda como vai fazer
    codPreP.open("codPreProcessado.txt");
    while (getline(arquivo,linha)) {
        stringstream linhaStream(linha);
        endereco = 0;
        while (linhaStream >> token) {
        colon = token.back();
            if (colon == ':') {
                token.pop_back();
                token.copy(SimAtual.label, token.length());
                SimAtual.endereco = endereco;
                tabSim->push_back(SimAtual);
            }
            else if (token[0] == ';') {
                break;                          // Quando chega no comentário vai para a próxima linha sem ler mais nada nessa
            }
            else {
                tamanho = getOP(token);
                endereco += tamanho;
                codPreP << token;
                for (i = tamanho; i > 0; i--) {// Isso ta fazendo o i-- quando? Pode ser que dê treta. Fazer verificação de erro dps
                    linhaStream >> token;
                    codPreP << token;
                }
            }
        }
        codPreP << "\n";
    }
    arquivo.close();
    codPreP.close();
}

// Checar tamanho do token??
// Quais caracteres especiais pode ter?
// Dar um jeito de parar tudo quando der erro e printar warning
void scanner (string token) {
    if (!isalpha(token[0])) {
        // PARA TUDO, ERRO LÉXICO
    }
    else {

    }
}

// WIP
// Assumindo que está sem labels e sem comentários
void segundaPassagem (list <tabSimItem> tabSim,string nome) {
    ifstream arquivo;
    ofstream output;
    int i, op=0;
    string token, linha;
    list <tabSimItem> :: iterator it;

    arquivo.open("codPreProcessado.txt"); //O nome do arquivo vai ser passado pelo terminal, então não sei ainda como vai fazer
    output.open("aout.txt");
    output << "teste \n";
    while (getline(arquivo,linha)) {
        stringstream linhaStream(linha);
        linhaStream >> token;               // Primeiro token da linha, deve obrigatoriamente ser operacao
        scanner(token);
        op=getOP(token);
        output << linha << "\n";            //debug de pobre
        if (op < 0) {
            // Erro, operaçao invalida
        }
        else {
            output << token; // Escreve no arquivo o opcode
            i=0;
            while (linhaStream >> token) {
                scanner(token);
                it = tabSim.begin();
                while (1) {
                    if (it == tabSim.end()) {
                        // Erro, percorreu a tabela de simbolos e nao encontrou, simbolo nao definido
                    }
                    else if (strcmp(token.c_str(),it->label) != 0) {
                        it++;
                    }
                    else {
                        break;
                    }
                }

                output << it->endereco;
                i++;
            }
            if (i != op) {
                //Erro, número de operandos diferente da operaçao
            }
        }
    }
}

int main () {
    list <tabSimItem> tabSim;
    string nome="teste.asm";

    //inputTemp (&nome);
    primeiraPassagem(&tabSim,nome);
    //segundaPassagem(tabSim,nome);
    return 0;
}