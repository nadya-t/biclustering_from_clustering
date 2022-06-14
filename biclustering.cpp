#include "biclustering.h"

std::vector<std::vector<int>>
kmeans_biclustering(std::vector<std::vector<int>> array, std::vector<std::vector<std::vector<int>>> &biclusters,
                    int clusters_number) {
    if (clusters_number <= 0) {
        clusters_number = array.size() - 1;
    }
    std::vector<std::vector<int>> clustered_arr = transpose(array);
    std::vector<std::vector<int>> cluster_content_col = kmeans_clusters(clustered_arr, clusters_number);
    clustered_arr = transpose(clustered_arr);
    std::vector<std::vector<int>> cluster_content_row = kmeans_clusters(clustered_arr, clusters_number);
    clusters_number = cluster_content_col.size();
    for (int i = 0; i < clusters_number; i++) {
        while (i < cluster_content_col.size() && cluster_content_col[i][0] == -1) {
            cluster_content_col.erase(cluster_content_col.cbegin() + i);
        }
        while (i < cluster_content_row.size() && cluster_content_row[i][0] == -1) {
            cluster_content_row.erase(cluster_content_row.cbegin() + i);
        }
        for (int j = 0; j < array.size(); j++) {
            while (i < cluster_content_col.size() && j < cluster_content_col[i].size() &&
                   cluster_content_col[i][j] == -1) {
                cluster_content_col[i].erase(cluster_content_col[i].cbegin() + j);
            }
            while (i < cluster_content_row.size() && j < cluster_content_row[i].size() &&
                   cluster_content_row[i][j] == -1) {
                cluster_content_row[i].erase(cluster_content_row[i].cbegin() + j);
            }
        }
        if (i < cluster_content_col.size())
            for (int j = 0; j < cluster_content_col[i].size(); j++)
                if (cluster_content_col[i][j] == -1) {
                    cluster_content_col[i].erase(cluster_content_col[i].cbegin() + j);
                }
    }
    biclusters = biclusters_from_cluster_content(array, cluster_content_row, cluster_content_col);
    return clustered_arr;
}

std::vector<std::vector<int>>
dbscan_biclustering(std::vector<std::vector<int>> array, std::vector<std::vector<std::vector<int>>> &biclusters,
                    int min, int eps) {
    std::vector<std::vector<int>> clustered_arr = transpose(array);
    std::vector<int> clusters_col = dbscan_clusters(clustered_arr, eps, min);
    clustered_arr = transpose(clustered_arr);
    std::vector<int> clusters_row = dbscan_clusters(clustered_arr, eps, min);
    int c = 0;
    for (int j = 0; j < clusters_col.size(); j++) {
        if (clusters_col[j] > c)
            c = clusters_col[j];
    }
    std::vector<std::vector<int>> cluster_content_col(c);
    for (int i = 0; i < clusters_col.size(); i++) {
        cluster_content_col[clusters_col[i] - 1].push_back(i);
    }
    c = 0;
    for (int j = 0; j < clusters_row.size(); j++) {
        if (clusters_row[j] > c)
            c = clusters_row[j];
    }
    std::vector<std::vector<int>> cluster_content_row(c);
    for (int i = 0; i < clusters_row.size(); i++) {
        cluster_content_row[clusters_row[i] - 1].push_back(i);
    }
    biclusters = biclusters_from_cluster_content(array, cluster_content_row, cluster_content_col);
    return clustered_arr;
}

std::vector<std::vector<int>>
hierarchical_biclustering(std::vector<std::vector<int>> array, std::vector<std::vector<std::vector<int>>> &biclusters,
                          int clusters_number) {
    std::vector<std::vector<int>> clustered_arr = transpose(array);
    std::vector<std::vector<int>> cluster_content_col = hierarchical_clusters(clustered_arr, clusters_number);
    clustered_arr = transpose(clustered_arr);
    std::vector<std::vector<int>> cluster_content_row = hierarchical_clusters(clustered_arr, clusters_number);
    biclusters = biclusters_from_cluster_content(array, cluster_content_row, cluster_content_col);
    return clustered_arr;
}