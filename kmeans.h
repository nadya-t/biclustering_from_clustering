#ifndef BICLUSTERING_FROM_CLUSTERING_KMEANS_H
#define BICLUSTERING_FROM_CLUSTERING_KMEANS_H

#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "functions.h"

void data_distribution(std::vector<std::vector<int>> array, std::vector<std::vector<int>> &cluster,
                       std::vector<std::vector<int>> &cluster_content);

void cluster_update(std::vector<std::vector<int>> array, std::vector<std::vector<int>> &cluster,
                    std::vector<std::vector<int>> &cluster_content);

void kmeans(std::vector<std::vector<int>> array, std::vector<std::vector<int>> &cluster_content);

std::vector<std::vector<int>> kmeans_clusters(std::vector<std::vector<int>> &array, int clusters_number);

std::vector<std::vector<int>> kmeans_clusters_for_cfp(std::vector<std::vector<int>> &array, int clusters_number);

#endif //BICLUSTERING_FROM_CLUSTERING_KMEANS_H
