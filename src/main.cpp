#include <iostream> 
#include <fstream>  
#include <string>
#include <cstring>
#include <vector>
#include <cassert>

int main(int argc, char const *argv[])
{

//================================ ABRIR O ARQUIVO ==============================================
    std::string filename;/// arquivo de configuração. 
    std::ifstream obj;      
    if (argc == 1) /// Entra no laço no caso em que o usuário não informou nenhum arquivo de configuração de entrada.   
    {       
        std::ifstream obj;      
        std::cout << ">>>>> Por favor digite um arquivo de configuração válido (Não utilize o síbolo '.'): ";       
        std::cin >> filename;       
        obj.open(filename);         
        while (obj.is_open() == false) /// Entra no laço caso o arquivo de configuração passado não exista.         
        {           
            std::cout << ">>>>> Por favor digite um arquivo de configuração válido (Não utilize o síbolo '.')(CTRL+C para sair): ";             
            std::cin >> filename;           
            obj.open(filename);         
        }       
        //obj.close();    
    }
    else /// Entra no laço no caso em que o usuário informou o arquivo de configuração de entrada.    
    {       
        filename = argv[1];    
        obj.open(argv[1]);      
        while (obj.is_open() == false) /// Entra no laço caso o arquivo de configuração passado não exista.         
        {           
            std::cout << ">>>>> Por favor digite um arquivo de configuração válido (Não utilize o síbolo '.')(CTRL+C para sair): ";             
            std::cin >> filename;           
            obj.open(filename);         
        }       
        //obj.close();
    }

//====================================== LER O ARQUIVO ==============================================
    std::string line;   
    int count;  
    std::vector<int> tam;
    while ( obj >> count){
        tam.push_back(count);
    }   
    int linhas = tam[0];
    int colunas = tam[1];
    assert (linhas == 15);
    assert (colunas == 10);

    return 0;
}