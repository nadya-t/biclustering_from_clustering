#ifndef BICLUSTERING_FROM_CLUSTERING_BICLUSTERING_FOR_CFP_H
#define BICLUSTERING_FROM_CLUSTERING_BICLUSTERING_FOR_CFP_H

#include "dbscan.h"
#include "kmeans.h"
#include "hierarchical.h"
#include "functions.h"

std::vector<std::vector<int>>
dbscan_biclustering_for_cfp(std::vector<std::vector<int>> array, std::vector<std::vector<std::vector<int>>> &biclusters,
                    int min = 1, int eps = 0);

std::vector<std::vector<int>>
kmeans_biclustering_for_cfp(std::vector<std::vector<int>> array, std::vector<std::vector<std::vector<int>>> &biclusters,
                    int clusters_number = 0);

std::vector<std::vector<int>>
hierarchical_biclustering_for_cfp(std::vector<std::vector<int>> array, std::vector<std::vector<std::vector<int>>> &biclusters,
                          int clusters_number = 2);

#endif //BICLUSTERING_FROM_CLUSTERING_BICLUSTERING_FOR_CFP_H
