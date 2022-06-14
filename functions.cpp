#include "functions.h"

int distFunc(std::vector<int> first, std::vector<int> second) {
    int dist = 0;
    for (int i = 0; i < first.size(); i++) {
        if (first[i] != second[i])
            dist++;
    }
    return dist;
}

int distClusters(std::vector<std::vector<int>> array, std::vector<int> first, std::vector<int> second) {
    int dist = 0;
    for (auto i : first) {
        for (auto j :second) {
            if (i > -1 && j > -1) {
                dist = dist + distFunc(array[i], array[j]);
            }
        }
    }
    return dist;
}

std::vector<std::vector<int>> transpose(std::vector<std::vector<int>> array) {
    std::vector<std::vector<int>> transposed_array(array[0].size(), std::vector<int>(array.size()));
    for (int i = 0; i < array.size(); ++i)
        for (int j = 0; j < array[0].size(); ++j) {
            transposed_array[j][i] = array[i][j];
        }
    return transposed_array;
};

std::vector<std::vector<std::vector<int>>>
biclusters_from_cluster_content_for_cfp(std::vector<std::vector<int>> array, std::vector<std::vector<int>> row_clusters,
                                std::vector<std::vector<int>> col_clusters) {
    std::vector<std::vector<int>> array_for_clustering = array;
    array_for_clustering.erase(array_for_clustering.cbegin());
    for (int i = 0; i < array_for_clustering.size(); i++) {
        array_for_clustering[i].erase(array_for_clustering[i].cbegin());
    }
    while (col_clusters.size() != row_clusters.size()) {
        if (row_clusters.size() > col_clusters.size()) {
            int dist = INT_MAX, c1, c2;
            for (int i = 0; i < row_clusters.size() - 1; i++) {
                int clust_dist = distClusters(array_for_clustering, row_clusters[i], row_clusters[i + 1]);
                if (clust_dist < dist) {
                    dist = clust_dist;
                    c1 = i;
                    c2 = i + 1;
                }
            }
            row_clusters[c1].insert(row_clusters[c1].end(), row_clusters[c2].begin(), row_clusters[c2].end());
            row_clusters.erase(row_clusters.begin() + c2);
        } else {
            int dist = INT_MAX, c1, c2;
            for (int i = 0; i < col_clusters.size() - 1; i++) {
                int clust_dist = distClusters(transpose(array_for_clustering), col_clusters[i], col_clusters[i + 1]);
                if (clust_dist < dist) {
                    dist = clust_dist;
                    c1 = i;
                    c2 = i + 1;
                }
            }
            col_clusters[c1].insert(col_clusters[c1].end(), col_clusters[c2].begin(), col_clusters[c2].end());
            col_clusters.erase(col_clusters.begin() + c2);
        }
    }
    std::vector<std::vector<std::vector<int>>> biclusters;
    for (int i = 0; i < row_clusters.size(); i++) {
        std::vector<std::vector<int>> this_bicluster;
        this_bicluster.push_back(row_clusters[i]);
        this_bicluster.push_back(col_clusters[i]);
        biclusters.push_back(this_bicluster);
    }
    return biclusters;
};

std::vector<std::vector<std::vector<int>>>
biclusters_from_cluster_content(std::vector<std::vector<int>> array, std::vector<std::vector<int>> row_clusters,
                                        std::vector<std::vector<int>> col_clusters) {
    while (col_clusters.size() != row_clusters.size()) {
        if (row_clusters.size() > col_clusters.size()) {
            int dist = INT_MAX, c1, c2;
            for (int i = 0; i < row_clusters.size() - 1; i++) {
                int clust_dist = distClusters(array, row_clusters[i], row_clusters[i + 1]);
                if (clust_dist < dist) {
                    dist = clust_dist;
                    c1 = i;
                    c2 = i + 1;
                }
            }
            row_clusters[c1].insert(row_clusters[c1].end(), row_clusters[c2].begin(), row_clusters[c2].end());
            row_clusters.erase(row_clusters.begin() + c2);
        } else {
            int dist = INT_MAX, c1, c2;
            for (int i = 0; i < col_clusters.size() - 1; i++) {
                int clust_dist = distClusters(transpose(array), col_clusters[i], col_clusters[i + 1]);
                if (clust_dist < dist) {
                    dist = clust_dist;
                    c1 = i;
                    c2 = i + 1;
                }
            }
            col_clusters[c1].insert(col_clusters[c1].end(), col_clusters[c2].begin(), col_clusters[c2].end());
            col_clusters.erase(col_clusters.begin() + c2);
        }
    }
    std::vector<std::vector<std::vector<int>>> biclusters;
    for (int i = 0; i < row_clusters.size(); i++) {
        std::vector<std::vector<int>> this_bicluster;
        this_bicluster.push_back(row_clusters[i]);
        this_bicluster.push_back(col_clusters[i]);
        biclusters.push_back(this_bicluster);
    }
    return biclusters;
};