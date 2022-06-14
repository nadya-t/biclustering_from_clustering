#ifndef BICLUSTERING_FROM_CLUSTERING_HIERARCHICAL_H
#define BICLUSTERING_FROM_CLUSTERING_HIERARCHICAL_H

#include <iostream>
#include <vector>
#include "functions.h"

std::vector<std::vector<int>> hierarchy(std::vector<std::vector<int>> array, int clusters_number);

std::vector<std::vector<int>> hierarchical_clusters(std::vector<std::vector<int>> &array, int clusters_number = 2);

std::vector<std::vector<int>>
hierarchical_clusters_for_cfp(std::vector<std::vector<int>> &array, int clusters_number = 2);

#endif //BICLUSTERING_FROM_CLUSTERING_HIERARCHICAL_H
