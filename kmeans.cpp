#include "kmeans.h"

void data_distribution(std::vector<std::vector<int>> array, std::vector<std::vector<int>> &cluster,
                       std::vector<std::vector<int>> &cluster_content) {
    int dim = array[0].size();
    int n = array.size();
    int k = cluster_content.size();
    for (int i = 0; i < k; i++)
        for (int j = 0; j < n; j++) {
            cluster_content[i][j] = -1;
        }
    for (int i = 0; i < n; i++) {
        int min_distance = INT_MAX;
        int suitable_cluster = -1;
        for (int j = 0; j < k; j++) {
            int distance = 0;
            for (int q = 0; q < dim; q++) {
                distance += pow((array[i][q] - cluster[j][q]), 2);
            }
            distance = pow(distance, 0.5);
            if (distance < min_distance) {
                min_distance = distance;
                suitable_cluster = j;
            }
        }
        for (int q = 0; q < n; q++) {
            if (cluster_content[suitable_cluster][q] == -1) {
                cluster_content[suitable_cluster][q] = i;
                q = n;
            }
        }
    }
}

void cluster_update(std::vector<std::vector<int>> array, std::vector<std::vector<int>> &cluster,
                    std::vector<std::vector<int>> &cluster_content) {
    int dim = array[0].size();
    int n = array.size();
    int k = cluster_content.size();
    for (int i = 0; i < k; i++) {
        for (int q = 0; q < dim; q++) {
            int updated_parameter = 0;
            int len = 0;
            for (int j = 0; j < n && cluster_content[i][j] != -1; j++) {
                updated_parameter += array[cluster_content[i][j]][q];
                len++;
            }
            if (len > 0) {
                updated_parameter = updated_parameter / len;
            }
            cluster[i][q] = updated_parameter;
        }
    }
}

void kmeans(std::vector<std::vector<int>> array, std::vector<std::vector<int>> &cluster_content) {
    int dim = array[0].size();
    int n = array.size();
    int k = cluster_content.size();

    for (int i = 0; i < k; i++)
        for (int j = 0; j < n; j++) {
            cluster_content[i][j] = -1;
        }

    std::vector<std::vector<int>> cluster(k, std::vector<int>(dim));

    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < k; i++) {
        for (int q = 0; q < dim; q++) {
            cluster[i][q] = rand() % 2;
        }
    }

    data_distribution(array, cluster, cluster_content);

    std::vector<std::vector<int>> previous_cluster;
    previous_cluster = cluster;

    while (1) {
        cluster_update(array, cluster, cluster_content);
        data_distribution(array, cluster, cluster_content);
        if (previous_cluster == cluster)
            break;
        previous_cluster = cluster;
    }
}

std::vector<std::vector<int>> kmeans_clusters(std::vector<std::vector<int>> &array, int clusters_number) {
    std::vector<std::vector<int>> array_for_clustering = array;
    array_for_clustering.erase(array_for_clustering.cbegin());
    for (auto i: array_for_clustering) {
        i.erase(i.cbegin());
    }
    std::vector<std::vector<int>> cluster_content(clusters_number, std::vector<int>(array_for_clustering.size()));
    kmeans(array_for_clustering, cluster_content);
    std::vector<std::vector<int>> clustered_arr;
    clustered_arr.push_back(array[0]);
    for (int i = 0; i < clusters_number; i++) {
        for (int j = 0; j < array_for_clustering.size(); j++) {
            if (cluster_content[i][j] != -1) {
                clustered_arr.push_back(array[cluster_content[i][j] + 1]);
            }
        }
    }
    array = clustered_arr;
    return cluster_content;
}

/*std::vector<std::vector<std::vector<int>>> kmeans_biclusters(const std::vector<std::vector<int>> array, int clusters_number=0) {
    std::vector<std::vector<int>> array_for_clustering = array;
    array_for_clustering.erase(array_for_clustering.cbegin());
    for (auto i: array_for_clustering) {
        i.erase(i.cbegin());
    }
    std::vector<std::vector<int>> cluster_content_col(clusters_number, std::vector<int>(array_for_clustering.size()));
    std::vector<std::vector<int>> cluster_content_row(clusters_number, std::vector<int>(array_for_clustering.size()));
    kmeans(array_for_clustering, cluster_content_col);
    std::vector<std::vector<int>> clustered_arr;
    clustered_arr.push_back(array[0]);
    for (int i = 0; i < clusters_number; i++) {
        for (int j = 0; j < array_for_clustering.size(); j++) {
            if (cluster_content[i][j] != -1) {
                clustered_arr.push_back(array[cluster_content[i][j]+1]);
            }
        }
    }
    return clustered_arr;
}*/

