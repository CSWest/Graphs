/*
Graphs - Copyright (C) 2016 - Olivier Deiss - olivier.deiss@gmail.com

Graphs is a toolbox for graph theory. It includes graph algorithms
and an interface to visualize them, using OpengGL. The project
comes with a function to generate random Gabriel graphs. These
graphs look like road maps and are therefore nice for the study of
lots of graph algorithms.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef Graph_hpp
#define Graph_hpp

#include <map>
#include <vector>
#include <set>

#include "components/Edge.hpp"
#include "graph_representation/GraphRepresentation.hpp"
#include "components/Vertex.hpp"
#include "rendering/Window.hpp"

class Graph {

    public:

        Graph(GRAPH_TYPE, int);
        Graph(const Graph&);
        ~Graph();
        Graph& operator=(const Graph&);
    
 static void setWindow(Window* w) { window = w; }
    
        int        getNbVertices() const { return nb_vertices; }
        GRAPH_TYPE getType()       const { return type; }
        int        getWindowId()   const { return window_id; }
    
        void setDisplayed(bool displayed)        { is_displayed = displayed; }
        void setOrientation(GRAPH_ORIENTATION o) { orientation = o; }
        void setWindowId(int id)                 { window_id = id; }
    
        Edge*                       add_edge(const Vertex*, const Vertex*, double=Constants::EDGE_DEFAULT_CAPACITY);
        Vertex*                     add_vertex(double=0, double=0);
        void                        clear();
        void                        clear_color();
        void                        clear_color_edges();
        void                        clear_color_vertices();
        void                        delete_graph();
        bool                        display();
        void                        draw() const;
        void                        generate();
        void                        generate_gabriel_naive();
        void                        generate_random_arc_integer_capacities();
        void                        generate_random_arc_directions();
        void                        generate_random_vertices();
        void                        generate_random_vertices_spacing();
        double                      get_total_weight();
        std::vector<const Edge*>*   handler_astar(Vertex* =0, Vertex* =0);
        std::set<const Vertex*>*    handler_bron_kerbosch();
        std::vector<const Edge*>*   handler_dijkstra(Vertex* =0, Vertex* =0);
        int                         handler_edmonds_karp(Vertex* =0, Vertex* =0);
        int                         handler_ford_fulkerson(Vertex* =0, Vertex* =0);
        std::vector<const Edge*>*   handler_prim();
        std::vector<const Vertex*>* handler_traveling_salesman(Vertex* =0, std::vector<const Vertex*>* =0);
        void                        keyboard(unsigned char, int, int);
        Graph*                      rebuild_graph(int);
        void                        set_ready_for_algo(GRAPH_ALGO algo);
 
    private:
    
        class IncidenceMatrix;
        class IncidenceList;
        class AdjacencyMatrix;
        class AdjacencyList;
    
 static int     graph_counter;
 static Window* window;

        std::vector<const Edge*>*   algo_astar(const Vertex*, const Vertex*, bool=false);
        std::set<const Vertex*>*    algo_bron_kerbosch();
        bool                        algo_bron_kerbosch_callback(std::vector<std::set<const Vertex*>>*, std::set<const Vertex*>, std::set<const Vertex*>, std::set<const Vertex*>);
        std::vector<const Edge*>*   algo_dijkstra(const Vertex*, const Vertex*);
        int                         algo_edmonds_karp(const Vertex*, const Vertex*);
        bool                        algo_edmonds_karp_bfs(const Graph*, std::map<const Vertex*, double>*, std::map<const Vertex*, const Vertex*>*, const Vertex*, const Vertex*);
        int                         algo_ford_fulkerson(const Vertex*, const Vertex*);
        bool                        algo_ford_fulkerson_dfs(const Graph*, std::vector<const Vertex*>*, std::set<const Vertex*>*, const Vertex*, const Vertex*);
        std::vector<const Edge*>*   algo_prim();
        std::vector<const Vertex*>* algo_traveling_salesman(const Vertex*, std::vector<const Vertex*>*);
        void                        algo_traveling_salesman_callback(double**, std::map<const Vertex*, unsigned long int>, const Vertex*, std::vector<const Vertex*>*, std::vector<const Vertex*>*, std::vector<const Vertex*>*, std::set<const Vertex*>*, double, double*);
        double**                    algo_traveling_salesman_cost_matrix(const Vertex*, std::vector<const Vertex*>*);
        void                        draw_edges()               const;
        void                        draw_edge_capacity(Edge*)  const;
        void                        draw_edge_direction(Edge*) const;
        void                        draw_vertices()            const;
        void                        keyboard_capacities();
        void                        keyboard_directions();
        bool                        keyboard_dupplicate();
        void                        select_one_random_vertices(const Vertex**)                                 const;
        void                        select_two_random_vertices(const Vertex**, const Vertex**)                 const;
        void                        select_n_random_vertices(std::vector<const Vertex*>**, int, const Vertex*) const;

  const int                  nb_vertices;                      /* number of vertices of the graph - see enum in Constants.hpp */
  const GRAPH_TYPE           type;                             /* defines the type of the graph (adjacency, list...) */
        bool                 arc_integer_capacities_defined;   /* defines if the graph's adges have capacities or not */
        GraphRepresentation* graph_representation;             /* holds the vertices and edges of the graph */
        bool                 is_displayed;                     /* true is the graph is being displayed */
        GRAPH_ORIENTATION    orientation;                      /* defines if the graph is oriented - see enum in Constants.hpp */
        int                  window_id;                        /* if the graph is displayed, its window's id */

};

#endif
