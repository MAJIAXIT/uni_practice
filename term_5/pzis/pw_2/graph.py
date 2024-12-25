import json
from collections import defaultdict


class Graph:
    def __init__(self):
        self.vertices = set()
        self.edges = defaultdict(dict)
        self.heuristics = {}

    def add_vertex(self, vertex, heuristic=0):
        self.vertices.add(vertex)
        self.heuristics[vertex] = heuristic

    def add_edge(self, from_vertex, to_vertex, weight):
        self.edges[from_vertex][to_vertex] = weight

    def get_neighbors(self, vertex):
        return self.edges[vertex].items()

    @classmethod
    def from_json(cls, json_data):
        """Create a graph from JSON data"""
        graph = cls()
        data = json.loads(json_data) if isinstance(
            json_data, str) else json_data

        # Add vertices
        for vertex in data['vertices']:
            vertex_name = int(vertex['name'])
            graph.add_vertex(vertex_name)

        # Add edges
        for edge in data['edges']:
            from_vertex = int(data['vertices'][edge['vertex1']]['name'])
            to_vertex = int(data['vertices'][edge['vertex2']]['name'])
            weight = float(edge['weight']) if edge['weight'] else 1.0
            graph.add_edge(from_vertex, to_vertex, weight)

        return graph
