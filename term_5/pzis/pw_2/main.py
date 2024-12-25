from graph import Graph
from path_finder import PathFinder
import json


def load_graph_from_file(filename):
    """Load graph from a JSON file"""
    with open(filename, 'r') as f:
        return Graph.from_json(f.read())


def main():
    try:
        # Load graphs from files
        print("Loading graphs...")
        graph1 = load_graph_from_file('dijkstra.graph')
        graph2 = load_graph_from_file('width.graph')

        # Let user choose which graph to use
        print("\nAvailable graphs:")
        print("1. Graph from dijkstra.graph")
        print("2. Graph from width.graph")
        choice = int(input("Choose graph (1 or 2): "))

        graph = graph1 if choice == 1 else graph2
        pathfinder = PathFinder(graph)

        # Get start and end vertices from user
        print("\nAvailable vertices:", sorted(list(graph.vertices)))
        start_vertex = int(input("Enter start vertex: "))
        end_vertex = int(input("Enter end vertex: "))

        # Get algorithm parameters
        print("\nAnt Colony Parameters:")
        n_ants = int(input("Number of ants (default 10): ") or 10)
        n_iterations = int(input("Number of iterations (default 5): ") or 5)

        # Run Ant Colony Optimization with visualization
        print("\nRunning Ant Colony Optimization...")
        path, length = pathfinder.ant_colony(
            start_vertex,
            end_vertex,
            n_ants=n_ants,
            n_iterations=n_iterations
        )

        print("\nAnt Colony Results:")
        print(f"Shortest path: {path}")
        print(f"Path length: {length}")

        print("\nA* Algorithm Results:")
        path, length = pathfinder.a_star(start_vertex, end_vertex)
        print(f"Shortest path: {path}")
        print(f"Path length: {length}")

    except FileNotFoundError as e:
        print(f"Error: Could not find file: {e.filename}")
    except json.JSONDecodeError:
        print("Error: Invalid JSON format in file")
    except Exception as e:
        print(f"Error: An unexpected error occurred: {str(e)}")


if __name__ == "__main__":
    main()
