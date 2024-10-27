#include <iostream>
#include <limits>
#include "definitions.hpp"

int main() {
    #ifdef _WIN32
    system("chcp 65001 > nul");  // Configurar UTF-8 no Windows
    #endif

    std::vector<Offer> offers = loadOffers("data.json");

    while (true) {
        std::cout << "\n----- 🖥️  Desafio de Back-End - Quero Educação 🚀 -----\n";
        std::cout << "1. Listar todas as ofertas\n";
        std::cout << "2. Buscar por nome\n";
        std::cout << "3. Aplicar filtros (nome, nível, modalidade, preço)\n";
        std::cout << "4. Ordenar por nome\n";
        std::cout << "5. Ordenar por preço com desconto\n";
        std::cout << "6. Ordenar por avaliação\n";
        std::cout << "7. Sair\n";
        std::cout << "Escolha uma opção (número): ";

        int option;
        std::cin >> option;


        std::vector<Offer> result = offers;

            // Verifica se a entrada foi um número inteiro
        if (std::cin.fail()) {
            std::cin.clear(); // Limpa o estado de erro do std::cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora qualquer entrada residual no buffer
            std::cout << "Entrada inválida! Por favor, insira um número inteiro.\n";
        }

        if (option == 7) {
            std::cout << "Obrigado e volte sempre!";
            break;
        }

        if (option == 1) {
            displayOffers(result);
        } else if (option == 2) {
            std::string name;
            std::cout << "Digite o nome do curso: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            result = searchByName(result, name);
            displayOffers(result);
        } else if (option == 3) {
            result = applyFilters(result);
            displayOffers(result);
        } else if (option == 4) {
            sortByName(result);
            displayOffers(result);
        } else if (option == 5) {
            sortByPrice(result);
            displayOffers(result);
        } else if (option == 6) {
            sortByRating(result);
            displayOffers(result);
        } else 
            std::cout << "Opção inválida!";
    }

    return 0;
}
