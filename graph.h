#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <set>
#include <map>

template <typename VertexT, typename WeightT>
class graph
{
private:
    struct VertexData
    {
        std::map<VertexT, WeightT> neighbors;
        std::set<VertexT> neighborsV;
    };

    std::map<VertexT, VertexData> vertices;
    int numEdges;

public:
    graph()
    {
        this->numEdges = 0;
    }

    graph(const graph &other)
    {
        this->vertices = other.vertices;
        this->numEdges = other.numEdges;
    }

    graph &operator=(const graph &other)
    {
        this->vertices = other.vertices;
        this->numEdges = other.numEdges;

        return *this;
    }

    int NumVertices() const
    {
        return this->vertices.size();
    }

    int NumEdges() const
    {
        return this->numEdges;
    }

    //
    // addVertex
    //
    // Adds the vertex v to the graph if there's room, and if so
    // returns true.  If the vertex already
    // exists in the graph, then false is returned.
    //
    bool addVertex(VertexT v)
    {
        if (this->vertices.find(v) != this->vertices.end())
            return false;

        this->vertices.emplace(v, VertexData{});
        return true;
    }

    //
    // addEdge
    //
    // Adds the edge (from, to, weight) to the graph, and returns
    // true.  If the vertices do not exist, false is returned.
    //
    // NOTE: if the edge already exists, the existing edge weight
    // is overwritten with the new edge weight.
    //
    bool addEdge(VertexT from, VertexT to, WeightT weight)
    {
        auto it = this->vertices.find(from);
        if (it == this->vertices.end())
            return false; // Vertex not found, so return false

        if (this->vertices.find(to) == this->vertices.end())
            return false;

        // If value is found replace with newer weight
        auto found = it->second.neighbors.find(to);
        if (found != it->second.neighbors.end())
        {
            found->second = weight;
            return true;
        }
        it->second.neighbors.emplace(to, weight);
        it->second.neighborsV.emplace(to);
        this->numEdges++;
        return true;
    }

    //
    // getWeight
    //
    // Returns the weight associated with a given edge.  If
    // the edge exists, the weight is returned via the reference
    // parameter and true is returned.  If the edge does not
    // exist, the weight parameter is unchanged and false is
    // returned.
    //
    bool getWeight(VertexT from, VertexT to, WeightT &weight)
    {
        auto it = this->vertices.find(from);
        if (it == this->vertices.end())
            return false;

        if (this->vertices.count(to) == 0)
            return false;

        auto itInner = it->second.neighbors.find(to);
        if (itInner == it->second.neighbors.end())
            return false;

        weight = itInner->second;
        return true;
    }

    //
    // neighbors
    //
    // Returns a set containing the neighbors of v, i.e. all
    // vertices that can be reached from v along one edge.
    // Since a set is returned, the neighbors are returned in
    // sorted order; use foreach to iterate through the set.
    //
    std::set<VertexT> neighbors(VertexT v)
    {
        auto it = this->vertices.find(v);
        if (it == this->vertices.end())
            return std::set<VertexT>{};
        return this->vertices.find(v)->second.neighborsV;
    }

    //
    // getVertices
    //
    // Returns a vector containing all the vertices currently in
    // the graph.
    //
    std::vector<VertexT> getVertices()
    {
        std::vector<VertexT> v;
        for (auto i : this->vertices)
            v.push_back(i.first);
        return v; // returns a copy:
    }

    //
    // dump
    //
    // Dumps the internal state of the graph for debugging purposes.
    //
    // Example:
    //    graph<string,int> G();
    //    ...
    //    G.dump(std::cout);  // dump to console
    //
    void dump(std::ostream &output) const
    {
        output << "***************************************************" << std::endl;
        output << "********************* GRAPH ***********************" << std::endl;

        output << "**Num vertices: " << this->NumVertices() << std::endl;
        output << "**Num edges: " << this->NumEdges() << std::endl;

        output << std::endl;
        output << "**Vertices:" << std::endl;
        auto it = this->vertices.begin();

        for (int i = 0; i < this->NumVertices(); ++i)
        {
            output << " " << i << ". " << it->first << std::endl;
            it++;
        }

        output << std::endl;
        output << "**Edges:" << std::endl;
        it = this->vertices.begin();

        for (int row = 0; row < this->NumVertices(); ++row)
        {
            output << " row " << row << ": ";
            auto itInner = this->vertices.begin();

            for (int col = 0; col < this->NumVertices(); ++col)
            {
                auto elem = it->second.neighbors.find(itInner->first);
                if (elem == it->second.neighbors.end())
                    output << "F ";
                else
                    output << "(T," << elem->second << ") ";
                itInner++;
            }
            it++;
            output << std::endl;
        }

        output << "**************************************************" << std::endl;
    }
};
