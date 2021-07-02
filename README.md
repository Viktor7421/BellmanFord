# Bellman Ford

![imagen de muestra](/imgs/img.png)

Este código es un algoritmo de Bellman Ford que nos ayuda a resolver el grafo presentado. Además la función tiene la capacidad de resolver cualquier grafo que se le envia al igual que un Bellmand Ford.

### Estructura Arista
```{c++}
template <class W>
struct Edge
{
  char source;
  char destiny;
  W weight;
};
```

### Clase Grafo
```{c++}
class Graph
{
public:
  list<char> vertices;
  list<Edge<W>> edges;

  Graph(list<char> _vertices, list<Edge<W>> _edges, bool bidirectional = false)
  {
    vertices = _vertices;
    edges = _edges;
    if(bidirectional)
    {
      for(Edge e : _edges)
      {
        auto temp = e.source;
        e.source = e.destiny;
        e.destiny = temp;
        edges.push_back(e);
      }
    }

  }
  ~Graph(){}
};
```

### Función Bellman Ford
```{c++}
template <class W>
map<char, pair<char,W>> BellmanFord(Graph<W> graph, char source, W MAX)
{
  list<char> vertices = graph.vertices;
  list<Edge<W>> edges = graph.edges;
  map<char, pair<char,W>> solution;

  // Crea una lista de solución con todos los vertices del Grafo

  for(char v : vertices)
  {
    solution[v] = {source, MAX};
  }
  
  // Actualiza el primer vertice con un peso de viaje 0

  solution[source] = {source, 0};

  // Recorre todos las aristas actualizando los viajes en función de la solución y esto se itera por la cantidad de vertices

  for(char v : vertices)
  {
    for(Edge e : edges)
    {
      if(solution[e.source].second + e.weight <= solution[e.destiny].second)
      {
        solution[e.destiny] = {e.destiny, solution[e.source].second + e.weight};
      }
    }
  }

  return solution;
}
```

### Complejidad de Tiempo
El código cumple con la complejidad del Bellman Ford que es **O(VE)** siendo V los vertices del grafo y E las aristas del grafo.


