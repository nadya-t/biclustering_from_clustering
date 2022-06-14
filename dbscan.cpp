#include "dbscan.h"

std::set<int> RangeQuery(std::vector<std::vector<int>> arr, int q, int eps) {
    std::set<int> neighbors;
    for (int i = 0; i < arr.size(); i++) {
        if (distFunc(arr[q], arr[i]) <= eps) {
            neighbors.insert(i);
        }
    }
    return neighbors;
}

std::vector<int> DBSCAN(std::vector<std::vector<int>> arr, int eps, int minPts) {
    int c = 0;
    std::vector<int> clusters(arr.size(), 0);
    for (int i = 0; i < arr.size(); i++) {
        if (clusters[i] != 0) continue;
        std::set<int> neighbors = RangeQuery(arr, i, eps);
        if (neighbors.size() < minPts) {
            clusters[i] = -1;
            continue;
        }
        c++;
        clusters[i] = c;
        std::set<int> this_cluster;
        this_cluster.merge(neighbors);
        for (auto q : this_cluster) {
            if (clusters[q] == -1) {
                clusters[q] = c;
            }
            if (clusters[q] != 0) continue;
            clusters[q] = c;
            neighbors = RangeQuery(arr, q, eps);
            if (neighbors.size() >= minPts) {
                this_cluster.merge(neighbors);
            }
        }
    }
    return clusters;
}

std::vector<int> dbscan_clusters(std::vector<std::vector<int>> &array, int eps, int min) {
    std::vector<std::vector<int>> array_for_clustering = array;
    array_for_clustering.erase(array_for_clustering.cbegin());
    for (auto i: array_for_clustering) {
        i.erase(i.cbegin());
    }
    if (eps == 0) {
        for (int i = 0; i < array_for_clustering.size(); i++)
            for (int j = 0; j < array_for_clustering.size(); j++)
                if (i != j) {
                    int d = distFunc(array_for_clustering[i], array_for_clustering[j]);
                    if (d > eps)
                        eps = d;
                }
        eps = eps / 2;
    }
    std::vector<int> clusters = DBSCAN(array_for_clustering, eps, min);
    std::vector<std::vector<int>> clustered_arr;
    clustered_arr.push_back(array[0]);
    int n = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < clusters.size(); j++) {
            if (i == 0 && clusters[j] > n) {
                n = clusters[j];
            }
            if (clusters[j] == i) {
                clustered_arr.push_back(array[j + 1]);
            }
        }
    }
    array = clustered_arr;
    return clusters;
}
