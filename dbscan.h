#ifndef BICLUSTERING_FROM_CLUSTERING_DBSCAN_H
#define BICLUSTERING_FROM_CLUSTERING_DBSCAN_H

#include <iostream>
#include <vector>
#include <set>
#include "functions.h"

std::set<int> RangeQuery(std::vector<std::vector<int>> arr, int q, int eps);

std::vector<int> DBSCAN(std::vector<std::vector<int>> arr, int eps, int minPts);

std::vector<int> dbscan_clusters(std::vector<std::vector<int>> &array, int eps, int min);

std::vector<int> dbscan_clusters_for_cfp(std::vector<std::vector<int>> &array, int eps, int min);

#endif //BICLUSTERING_FROM_CLUSTERING_DBSCAN_H
