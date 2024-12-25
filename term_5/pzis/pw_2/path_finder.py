import numpy as np
import heapq
import random
from colorama import Fore, Back, Style, init

init(autoreset=True)


def colorize_pheromone(value):
    """
    Color the pheromone intensity based on its value.
    """
    if value > 1.0:
        return f"{Back.RED}{value:.2f}{Style.RESET_ALL}"  # High intensity
    elif value > 0.5:
        return f"{Back.YELLOW}{value:.2f}{Style.RESET_ALL}"  # Medium intensity
    elif value > 0.1:
        return f"{Back.GREEN}{value:.2f}{Style.RESET_ALL}"  # Low intensity
    else:
        return f"{Back.BLACK}{Fore.WHITE}{value:.2f}{Style.RESET_ALL}"


class PathFinder:
    def __init__(self, graph):
        self.graph = graph

    def a_star(self, start, goal):
        if start not in self.graph.vertices or goal not in self.graph.vertices:
            return None, float('inf')

        frontier = [(0, start, [start])]
        explored = set()

        while frontier:
            f_score, current, path = heapq.heappop(frontier)

            if current == goal:
                return path, f_score - self.graph.heuristics[current]

            if current in explored:
                continue

            explored.add(current)

            for neighbor, weight in self.graph.get_neighbors(current):
                if neighbor not in explored:
                    g_score = f_score - self.graph.heuristics[current] + weight
                    f_score_new = g_score + self.graph.heuristics[neighbor]
                    heapq.heappush(
                        frontier, (f_score_new, neighbor, path + [neighbor]))

        return None, float('inf')

    def ant_colony(self, start, goal, n_ants=10, n_iterations=5, evaporation_rate=0.1, alpha=1, beta=2):
        pheromone = np.zeros(
            (len(self.graph.vertices), len(self.graph.vertices)))
        vertices_list = list(self.graph.vertices)
        vertex_to_idx = {v: i for i, v in enumerate(vertices_list)}

        best_path = None
        best_length = float('inf')

        for iteration in range(n_iterations):
            ant_paths = []
            ant_lengths = []

            for _ in range(n_ants):
                current = start
                path = [current]
                length = 0

                while current != goal:
                    neighbors = list(self.graph.get_neighbors(current))
                    if not neighbors:
                        break

                    probabilities = []
                    for next_vertex, weight in neighbors:
                        if next_vertex not in path:
                            i, j = vertex_to_idx[current], vertex_to_idx[next_vertex]
                            tau = pheromone[i][j] + 1e-10
                            eta = 1.0 / weight
                            prob = (tau ** alpha) * (eta ** beta)
                            probabilities.append((prob, next_vertex, weight))

                    if not probabilities:
                        break

                    total = sum(p[0] for p in probabilities)
                    normalized_probs = [(p[0]/total, p[1], p[2])
                                        for p in probabilities]
                    r = random.random()
                    cum_prob = 0

                    for prob, next_vertex, weight in normalized_probs:
                        cum_prob += prob
                        if r <= cum_prob:
                            current = next_vertex
                            path.append(current)
                            length += weight
                            break

                if current == goal:
                    ant_paths.append(path)
                    ant_lengths.append(length)

                    if length < best_length:
                        best_length = length
                        best_path = path

            pheromone *= (1 - evaporation_rate)

            for path, length in zip(ant_paths, ant_lengths):
                deposit = 1.0 / length
                for i in range(len(path) - 1):
                    v1, v2 = path[i], path[i + 1]
                    pheromone[vertex_to_idx[v1]][vertex_to_idx[v2]] += deposit

            print(f"Iteration {iteration+1}: Pheromone Matrix")
            print("\t\t" + "\t".join(str(node) for node in vertices_list))
            for i, row in enumerate(pheromone):
                print(f"Node {vertices_list[i]:02}:\t" + "\t".join(colorize_pheromone(value) for value in row))

        return best_path, best_length
