#pragma once

#include "Graph.h"
#include "Tile.h"

class Path {
    Graph<Tile> graph;

public:

    Tile source;
    Tile dist;

    Path() = default;

    void setPath(Tile& start, Tile& end, std::vector<Tile> tiles) {
        source = start;
        dist = end;
        std::vector<Edge<Tile>> test_vec;
        int count = 0;
        auto *temp = new Edge<Tile>;
        temp->source = count;
        count++;
        temp->destination = count;
        temp->data = {start, tiles[1]};
        test_vec.push_back(*temp);
        int i = 2;
        for (; i < tiles.size(); i += 2) {
            auto *t1 = new Edge<Tile>;
            t1->source = count;
            count++;
            t1->destination = count;
            t1->data = {tiles[i - 1], tiles[i]};
            test_vec.push_back(*t1);
        }
        auto *t = new Edge<Tile>;
        t->source = count;
        count++;
        t->destination = count;
        t->data = {tiles[i-1], end};
        test_vec.push_back(*t);
//        std::vector<Edge<Tile>> test_vec;
//        int count = 0;
//        for (const auto& tile_first: tiles) {
//            for (const auto& tile_second: tiles) {
//                if (!(tile_first.getX() == tile_second.getX() && tile_first.getY() == tile_second.getY())
//                &&  (tile_first.getX() == tile_second.getX() || tile_second.getY() == tile_first.getY())) {
//                    auto* temp = new Edge<Tile>;
//                    temp->source = count;
//                    count++;
//                    temp->destination = count;
//                    temp->data = {tile_first,tile_second};
//                    test_vec.push_back(*temp);
//                }
//            }
//        }
//
        //Print the graph
        graph = Graph(test_vec, count);

    }

};

