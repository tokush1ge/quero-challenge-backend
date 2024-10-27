#include "definitions.hpp"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <locale>
#include <cctype>

using json = nlohmann::json;

// Função para carregar ofertas a partir de um arquivo JSON
std::vector<Offer> loadOffers(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        exit(1);
    }

    json offers_json;
    file >> offers_json;

    std::vector<Offer> offers;
    for (const auto& offer_json : offers_json["offers"]) {
        offers.push_back({
            offer_json["courseName"].get<std::string>(),
            offer_json["level"].get<std::string>(),
            offer_json["kind"].get<std::string>(),
            offer_json["fullPrice"].get<double>(),
            offer_json["offeredPrice"].get<double>(),
            offer_json["rating"].get<double>()
        });
    }
    return offers;
}

// Função para exibir ofertas formatadas com paginação
void displayOffers(const std::vector<Offer>& offers, int itemsPerPage) {
    int totalItems = offers.size();
    int currentPage = 0;
    int totalPages = (totalItems + itemsPerPage - 1) / itemsPerPage;

    while (true) {
        int start = currentPage * itemsPerPage;
        int end = std::min(start + itemsPerPage, totalItems);

        std::cout << "\n--- Página " << (currentPage + 1) << " de " << totalPages << " ---\n";
        for (int i = start; i < end; ++i) {
            const Offer& offer = offers[i];
            std::cout << "Curso: " << offer.courseName << "\n";
            std::cout << "Nível: " << offer.level << "\n";
            std::cout << "Modalidade: " << offer.kind << "\n";
            std::cout << std::fixed << std::setprecision(2);
            std::cout << "Preço original: R$ " << offer.fullPrice << "\n";
            std::cout << "Preço com desconto: R$ " << offer.offeredPrice << "\n";
            std::cout << "Desconto: " << offer.getDiscount() << "% 📉\n";
            std::cout << "Avaliação: " << offer.rating << " 🌟\n";
            std::cout << "-----------------------------\n";
        }

        if (totalPages > 1) {
            std::cout << "\nDigite 'p' para página anterior, 'n' para próxima página ou 'q' para sair: ";
            char choice;
            std::cin >> choice;
            if (choice == 'p' || choice == 'P') {
                if (currentPage > 0) currentPage--;
            } else if (choice == 'n' || choice == 'N') {
                if (currentPage < totalPages - 1) currentPage++;
            } else if (choice == 'q' || choice == 'Q') {
                break;
            }
        } else {
            break;
        }
    }
}

std::string toLower(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

std::vector<Offer> searchByName(const std::vector<Offer>& offers, const std::string& name) {
    std::vector<Offer> foundOffers;
    for (const auto& offer : offers) {
        if (toLower(offer.courseName).find(toLower(name)) != std::string::npos) {
            foundOffers.push_back(offer);
        }
    }
    return foundOffers;
}

std::vector<Offer> filterByLevel(const std::vector<Offer>& offers, const std::string& level) {
    std::vector<Offer> filtered;
    for (const auto& offer : offers) {
        if (offer.level == level) {
            filtered.push_back(offer);
        }
    }
    return filtered;
}

std::vector<Offer> filterByKind(const std::vector<Offer>& offers, const std::string& kind) {
    std::vector<Offer> filtered;
    for (const auto& offer : offers) {
        if (offer.kind == kind) {
            filtered.push_back(offer);
        }
    }
    return filtered;
}

std::vector<Offer> filterByPriceRange(const std::vector<Offer>& offers, double minPrice, double maxPrice) {
    std::vector<Offer> filtered;
    for (const auto& offer : offers) {
        if (offer.offeredPrice >= minPrice && offer.offeredPrice <= maxPrice) {
            filtered.push_back(offer);
        }
    }
    return filtered;
}

void sortByName(std::vector<Offer>& offers) {
    std::sort(offers.begin(), offers.end(), [](const Offer& a, const Offer& b) {
        return a.courseName < b.courseName;
    });
}

void sortByPrice(std::vector<Offer>& offers) {
    std::sort(offers.begin(), offers.end(), [](const Offer& a, const Offer& b) {
        return a.offeredPrice < b.offeredPrice;
    });
}

void sortByRating(std::vector<Offer>& offers) {
    std::sort(offers.begin(), offers.end(), [](const Offer& a, const Offer& b) {
        return a.rating > b.rating;
    });
}

// Implementação da função applyFilters para múltiplos critérios de filtro
std::vector<Offer> applyFilters(const std::vector<Offer>& offers) {
    std::vector<Offer> result = offers;

    // Filtro por nome
    std::string name;
    std::cout << "Digite o nome do curso (ou pressione Enter para ignorar): ";
    std::cin.ignore();
    std::getline(std::cin, name);
    if (!name.empty()) {
        result = searchByName(result, name);
    }

    // Filtro por nível
    std::string level;
    std::cout << "Digite o nível (bacharelado, tecnologo, licenciatura) ou pressione Enter para ignorar: ";
    std::getline(std::cin, level);
    if (!level.empty()) {
        result = filterByLevel(result, level);
    }

    // Filtro por modalidade
    std::string kind;
    std::cout << "Digite a modalidade (presencial, EAD) ou pressione Enter para ignorar: ";
    std::getline(std::cin, kind);
    if (!kind.empty()) {
        result = filterByKind(result, kind);
    }

    // Filtro por faixa de preço
    double minPrice, maxPrice;
    std::cout << "Digite o preço mínimo (ou -1 para ignorar): ";
    std::cin >> minPrice;
    std::cout << "Digite o preço máximo (ou -1 para ignorar): ";
    std::cin >> maxPrice;
    if (minPrice >= 0 && maxPrice >= 0) {
        result = filterByPriceRange(result, minPrice, maxPrice);
    }

    return result;
}