#include "hierarchical.h"

std::vector<std::vector<int>> hierarchy(std::vector<std::vector<int>> array, int clusters_number) {
    std::vector<std::vector<int>> clusters;
    for (int i = 0; i < array.size(); i++) {
        clusters.push_back({i});
    }
    while (clusters.size() > clusters_number) {
        int min_dist = INT_MAX;
        int c1, c2;
        for (int i = 0; i < clusters.size(); i++) {
            for (int j = 0; j < clusters.size(); j++) {
                if (i != j) {
                    int dist = distClusters(array, clusters[i], clusters[j]);
                    if (dist < min_dist) {
                        min_dist = dist;
                        c1 = i;
                        c2 = j;
                    }
                }
            }
        }
        clusters[c1].insert(clusters[c1].end(), clusters[c2].begin(), clusters[c2].end());
        clusters.erase(clusters.begin() + c2);
    }
    return clusters;
}

std::vector<std::vector<int>> hierarchical_clusters_for_cfp(std::vector<std::vector<int>> &array, int clusters_number) {
    std::vector<std::vector<int>> array_for_clustering = array;
    array_for_clustering.erase(array_for_clustering.cbegin());
    for (auto i: array_for_clustering) {
        i.erase(i.cbegin());
    }
    std::vector<std::vector<int>> clusters = hierarchy(array_for_clustering, clusters_number);
    std::vector<std::vector<int>> clustered_arr;
    clustered_arr.push_back(array[0]);
    for (int i = 0; i < clusters_number; i++) {
        for (int j = 0; j < clusters[i].size(); j++) {
            clustered_arr.push_back(array[clusters[i][j] + 1]);
        }
    }
    array = clustered_arr;
    return clusters;
}

std::vector<std::vector<int>> hierarchical_clusters(std::vector<std::vector<int>> &array, int clusters_number) {
    std::vector<std::vector<int>> clusters = hierarchy(array, clusters_number);
    std::vector<std::vector<int>> clustered_arr;
    for (int i = 0; i < clusters_number; i++) {
        for (int j = 0; j < clusters[i].size(); j++) {
            clustered_arr.push_back(array[clusters[i][j]]);
        }
    }
    array = clustered_arr;
    return clusters;
}