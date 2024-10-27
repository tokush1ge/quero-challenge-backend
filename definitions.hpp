#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#include <string>
#include <vector>

struct Offer {
    std::string courseName;
    std::string level;
    std::string kind;
    double fullPrice;
    double offeredPrice;
    double rating;

    double getDiscount() const {
        return (1 - (offeredPrice / fullPrice)) * 100;
    }
};

// Declaração de funções
std::vector<Offer> loadOffers(const std::string& filePath);
void displayOffers(const std::vector<Offer>& offers, int itemsPerPage = 5);
std::vector<Offer> searchByName(const std::vector<Offer>& offers, const std::string& name);
std::vector<Offer> filterByLevel(const std::vector<Offer>& offers, const std::string& level);
std::vector<Offer> filterByKind(const std::vector<Offer>& offers, const std::string& kind);
std::vector<Offer> filterByPriceRange(const std::vector<Offer>& offers, double minPrice, double maxPrice);
void sortByName(std::vector<Offer>& offers);
void sortByPrice(std::vector<Offer>& offers);
void sortByRating(std::vector<Offer>& offers);
bool askUser(const std::string& question);
std::vector<Offer> applyFilters(const std::vector<Offer>& offers);

#endif
