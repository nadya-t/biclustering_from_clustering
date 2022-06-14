#ifndef BICLUSTERING_FROM_CLUSTERING_FUNCTIONS_H
#define BICLUSTERING_FROM_CLUSTERING_FUNCTIONS_H

#include <iostream>
#include <vector>

int distFunc(std::vector<int> first, std::vector<int> second);

int distClusters(std::vector<std::vector<int>> array, std::vector<int> first, std::vector<int> second);

std::vector<std::vector<int>> transpose(std::vector<std::vector<int>> array);

std::vector<std::vector<std::vector<int>>>
biclusters_from_cluster_content(std::vector<std::vector<int>> array, std::vector<std::vector<int>> row_clusters,
                                std::vector<std::vector<int>> col_clusters);

#endif //BICLUSTERING_FROM_CLUSTERING_FUNCTIONS_H
