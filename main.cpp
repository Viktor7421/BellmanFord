#include <iostream>
#include <utility>
#include <list>
#include <map>
#include <limits.h>
#include <float.h>
using namespace std; 

// Estructura de la Arista
template <class W>
struct Edge
{
  char source;
  char destiny;
  W weight;
};

// Clase del Grafo
template <class W>
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

// Función BellmanFord
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

  list<char> temp;
  temp.push_back(source);

  // Actualiza los demas vertices en función de los vertices ya visitados

  while(!temp.empty())
  {
    auto _source = temp.front();
    for(Edge e : edges)
    {
      if(e.source == _source)
      {
        if(solution[_source].second + e.weight <= solution[e.destiny].second)
        {
          solution[e.destiny] = {_source, solution[_source].second + e.weight};
          temp.push_back(e.destiny);
        }
      }
    }
    temp.pop_front();
  }

  return solution;
}

int main() 
{
  // Creación de Aristas
  Edge<double> edge_1;
  edge_1.source = 'A';
  edge_1.destiny = 'B';
  edge_1.weight = 2;

  Edge<double> edge_2;
  edge_2.source = 'A';
  edge_2.destiny = 'C';
  edge_2.weight = 1;

  
  Edge<double> edge_3;
  edge_3.source = 'A';
  edge_3.destiny = 'E';
  edge_3.weight = 0.5;

  Edge<double> edge_4;
  edge_4.source = 'B';
  edge_4.destiny = 'E';
  edge_4.weight = 3;

  Edge<double> edge_5;
  edge_5.source = 'B';
  edge_5.destiny = 'C';
  edge_5.weight = 0.5;
  
  Edge<double> edge_6;
  edge_6.source = 'E';
  edge_6.destiny = 'F';
  edge_6.weight = 2;

  Edge<double> edge_7;
  edge_7.source = 'B';
  edge_7.destiny = 'D';
  edge_7.weight = 2;
  
	Edge<double> edge_8;
  edge_8.source = 'C';
  edge_8.destiny = 'G';
  edge_8.weight = 1;
	
	Edge<double> edge_9;
  edge_9.source = 'D';
  edge_9.destiny = 'F';
  edge_9.weight = 2;

	Edge<double> edge_10;
  edge_10.source = 'D';
  edge_10.destiny = 'G';
  edge_10.weight = 3;

	Edge<double> edge_11;
  edge_11.source = 'F';
  edge_11.destiny = 'G';
  edge_11.weight = 1;

  // Creación del Grafo

  Graph<double> graph({'A','B','C','D','E','F','G'},{edge_1,edge_2,edge_3,edge_4,edge_5,edge_6,edge_7,edge_8,edge_9,edge_10,edge_11}, true);

  // Aplicación del codigo BellmanFord

  auto solution = BellmanFord<double>(graph, 'A', DBL_MAX);

  // Impresión del Resultado

  list<char> vertices = {'A','B','C','D','E','F','G'};
  for(char i : vertices)
  {
    cout << i << " : " << solution[i].first << " | " << solution[i].second << '\n';
  }
}