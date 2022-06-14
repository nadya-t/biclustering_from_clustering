#include <iostream>

#include "biclustering.h"
#include "biclustering_for_cfp.h"

int main() {
    int p, m;
    std::cout << "Input number of machines\n";
    std::cin >> m;
    std::cout << "Input number of parts\n";
    std::cin >> p;
    m++;
    p++;
    std::vector<std::vector<int>> array(m, std::vector<int>(p));
    std::cout << "Input your matrix\n";
    for (int i = 0; i < m; i++) {
        if (i == 0) {
            for (int j = 0; j < p; j++) {
                array[i][j] = j;
            }
        } else {
            array[i][0] = i;
            for (int j = 1; j < p; j++) {
                int k = 0;
                std::cin >> array[i][j];
            }
        }
    }
    std::vector<std::vector<std::vector<int>>> biclusters;
    int minPts, eps;
    std::cout << "Input minPts and eps for DBSCAN\n";
    std::cin >> minPts >> eps;
    std::vector<std::vector<int>> clustered_arr = dbscan_biclustering_for_cfp(array, biclusters, minPts, eps);
    std::cout << "After DBSCAN:\n";
    for (auto &i : clustered_arr) {
        for (int j = 0; j < clustered_arr[0].size(); j++) {
            std::cout << i[j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    for (auto &i : biclusters) {
        std::cout << "Machines: ";
        for (auto j : i[0]) {
            std::cout << j + 1 << " ";
        }
        std::cout << "\nParts: ";
        for (auto k : i[1]) {
            std::cout << k + 1 << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    int n;
    std::cout << "Input number of clusters for k-means and hierarchical biclustering\n";
    std::cin >> n;
    clustered_arr = kmeans_biclustering_for_cfp(array, biclusters, n);
    std::cout << "After k-means:\n";
    for (auto &i : clustered_arr) {
        for (int j = 0; j < clustered_arr[0].size(); j++) {
            std::cout << i[j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    for (auto &i : biclusters) {
        std::cout << "Machines: ";
        for (auto j : i[0]) {
            std::cout << j + 1 << " ";
        }
        std::cout << "\nParts: ";
        for (auto k : i[1]) {
            std::cout << k + 1 << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    clustered_arr = hierarchical_biclustering_for_cfp(array, biclusters, n);
    std::cout << "After hierarchical:\n";
    for (auto &i : clustered_arr) {
        for (int j = 0; j < clustered_arr[0].size(); j++) {
            std::cout << i[j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    for (auto &i : biclusters) {
        std::cout << "Machines: ";
        for (auto j : i[0]) {
            std::cout << j + 1 << " ";
        }
        std::cout << "\nParts: ";
        for (auto k : i[1]) {
            std::cout << k + 1 << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    return 0;
}
