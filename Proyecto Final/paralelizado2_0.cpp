#include <bits/stdc++.h>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace chrono;

#define POPULATION_SIZE 100

const string GENES = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOP"\
                     "QRSTUVWXYZ 1234567890, .-;:_!\"#%&/()=?@${[]}";
const string TARGET = "I love GeeksforGeeks I love GeeksforGeeks I love GeeksforGeeks I love GeeksforGeeks I love GeeksforGeeks I love GeeksforGeeks I love GeeksforGeeks I love GeeksforGeeks I love GeeksforGeeks I love GeeksforGeeks I love GeeksforGeeks I love GeeksforGeeks I love GeeksforGeeks I love GeeksforGeeks I love GeeksforGeeks I love GeeksforGeeks I love GeeksforGeeks I love GeeksforGeeks I love GeeksforGeeks I love GeeksforGeeks I love GeeksforGeeks I love GeeksforGeeks I love GeeksforGeeks I love GeeksforGeeks I love GeeksforGeeks I love GeeksforGeeks I love GeeksforGeeks ";

int random_num(int start, int end) {
    int range = (end - start) + 1;
    int random_int = start + (rand() % range);
    return random_int;
}

char mutated_genes() {
    int len = GENES.size();
    int r = random_num(0, len - 1);
    return GENES[r];
}

string create_gnome() {
    int len = TARGET.size();
    string gnome = "";
    for (int i = 0; i < len; i++)
        gnome += mutated_genes();
    return gnome;
}

class Individual {
public:
    string chromosome;
    int fitness;
    Individual(string chromosome);
    Individual mate(Individual parent2);
    int cal_fitness();
};

Individual::Individual(string chromosome) {
    this->chromosome = chromosome;
    fitness = cal_fitness();
}

Individual Individual::mate(Individual par2) {
    string child_chromosome = "";
    int len = chromosome.size();
    for (int i = 0; i < len; i++) {
        float p = random_num(0, 100) / 100;
        if (p < 0.45)
            child_chromosome += chromosome[i];
        else if (p < 0.90)
            child_chromosome += par2.chromosome[i];
        else
            child_chromosome += mutated_genes();
    }
    return Individual(child_chromosome);
}

int Individual::cal_fitness() {
    int len = TARGET.size();
    int fitness = 0;
    for (int i = 0; i < len; i++) {
        if (chromosome[i] != TARGET[i])
            fitness++;
    }
    return fitness;
}

bool operator<(const Individual &ind1, const Individual &ind2) {
    return ind1.fitness < ind2.fitness;
}

int main() {
    srand((unsigned)(time(0)));

    // Configurar el número de hilos
    #pragma omp parallel num_threads(16)

    // Obtener el tiempo de inicio
    auto start_time = high_resolution_clock::now();

    int generation = 0;
    vector<Individual> population;
    bool found = false;

    // Inicialización paralela de la población
    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < POPULATION_SIZE; i++) {
            string gnome = create_gnome();
            {
                population.push_back(Individual(gnome));
            }
        }
    }

    while (!found) {
        #pragma omp parallel
        {
            // Ordenar la población en orden creciente de puntuación de aptitud
            #pragma omp for
            for (int i = 0; i < POPULATION_SIZE; i++) {
                population[i].fitness = population[i].cal_fitness();
            }

            #pragma omp single
            {
                sort(population.begin(), population.end());
            }

            #pragma omp single
            {
                if (population[0].fitness <= 0) {
                    found = true;
                    break;
                }
            }

            vector<Individual> new_generation;

            #pragma omp single
            {
                int s = (10 * POPULATION_SIZE) / 100;
                for (int i = 0; i < s; i++)
                    new_generation.push_back(population[i]);
            }

            int s = (90 * POPULATION_SIZE) / 100;
            #pragma omp for
            for (int i = 0; i < s; i++) {
                int len = population.size();
                int r = random_num(0, 50);
                Individual parent1 = population[r];
                r = random_num(0, 50);
                Individual parent2 = population[r];
                Individual offspring = parent1.mate(parent2);
                new_generation.push_back(offspring);
            }
            #pragma omp critical
            {
                population = new_generation;
            }

            #pragma omp single
            {
                cout << "Generation: " << generation << "\t";
                cout << "String: " << population[0].chromosome << "\t";
                cout << "Fitness: " << population[0].fitness << "\n";
            }

            #pragma omp barrier

            #pragma omp single
            {
                generation++;
            }
        }
    }

    // Obtener el tiempo de finalización
    auto stop_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop_time - start_time);

    // Imprimir el tiempo de ejecución
    cout << "Time taken: " << duration.count() << " milliseconds";

    return 0;
}
