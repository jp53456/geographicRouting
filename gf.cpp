#include <iostream>
#include <string.h> 
#include <fstream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <math.h>
using namespace std;

/*
 * structure to store node info, each node has a neighbor table 
 * to store the nodes within range
 */
struct Node {
    int id;
    int x;
    int y;
    vector<Node> neighbor_table;
};

/*
 * Assign a node to another node
 */
void set_Node(Node n1, Node& n2)
{
    n2.id = n1.id;
    n2.x = n1.x;
    n2.y = n1.y;
    n2.neighbor_table = n1.neighbor_table;
}

/*
 * Take in (x,y) from 2 node and compute the 
 * distance between them
 */
int get_distance(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(abs(x2-x1), 2) + pow(abs(y2-y1), 2));
} 

/*
 * Take in the id of a node, and the destination node,
 * the node table that store all the node from config file.
 * Return the distance between the node and destination node
 */
int get_distance_with_id(int id, Node dest, vector<Node> n_table)
{
    for(int i = 0; i < n_table.size(); i++)
    {
        if(n_table[i].id == id)
            return get_distance(n_table[i].x, n_table[i].y, dest.x, dest.y);
    }
}

int main(int argc, char* argv[])
{

    vector<Node> node_table;

    string gf_file = argv[1];
    int range = stoi(string(argv[2]));
    int src = stoi(string(argv[3]));
    int dest = stoi(string(argv[4]));
    cout << "Filename: " << gf_file << ", range: " << range << ", src: " << src << ", dest: " << dest << endl << endl << "route: " ;

    // Read in all the node info from config file
    ifstream infile(gf_file); 
    int a, b, c;
    while(infile >> a >> b >> c)
    {
        Node tmp_n;
        tmp_n.id =a;
        tmp_n.x = b;
        tmp_n.y = c;
        node_table.push_back(tmp_n);
    }

    // populate neighbor_table for each node
    for(int i = 0; i < node_table.size(); i++)
    {
        int cur_id = node_table[i].id;
        int cur_x = node_table[i].x;
        int cur_y = node_table[i].y;

        vector<Node> insert_table;

        for(int j = 0; j < node_table.size(); j++)
        {
            if(node_table[j].id != cur_id)
            {
                Node tmp_node;
                set_Node(node_table[j], tmp_node);
                int d = get_distance(cur_x, cur_y, tmp_node.x, tmp_node.y);
                if(d <= range)
                    insert_table.push_back(tmp_node);
            }
        }
        node_table[i].neighbor_table = insert_table;
    }

    /*for(int i = 0; i < node_table.size(); i++)
    {
        cout << "parent_id: " << node_table[i].id << ", parent_x: " << node_table[i].x << ", parent_y: " << node_table[i].y << endl;
        for(int j = 0; j < node_table[i].neighbor_table.size(); j++)
            cout << "id: " << node_table[i].neighbor_table[j].id << ", x: " << node_table[i].neighbor_table[j].x << ", y: " << node_table[i].neighbor_table[j].y << endl;
        cout << endl << endl;
    }*/

    Node cur_node;
    Node dest_node;
    vector<int> route;

    for(int i = 0; i < node_table.size(); i++)
    {
        if(node_table[i].id == src)
            set_Node(node_table[i], cur_node);
        if(node_table[i].id == dest)
            set_Node(node_table[i], dest_node);
    }
    route.push_back(src);

    int flag = 0; // flag to check if the destination node is in current node's neighbor table

    // This while loop traverse through the neighbor table of
    // each node and compute the distance between all the 
    // neighbor node and the destination node to decide the 
    // next node to hop to, will be choosing the one with the
    // minimum distance difference
    while(cur_node.neighbor_table.size() > 0)
    { 
        for(int i = 0; i < cur_node.neighbor_table.size(); i++)
        {
            if(cur_node.neighbor_table[i].id == dest_node.id)
                flag = 1; // means destination is within range
        }

        if(flag == 1) break;

        int min = get_distance(cur_node.x, cur_node.y, dest_node.x, dest_node.y); 
        int next_id;
        int flag2 = min; // flag to check if reaching a dead end
        for(int i = 0; i < cur_node.neighbor_table.size(); i++)
        {
            int g = get_distance_with_id(cur_node.neighbor_table[i].id, dest_node, node_table);
            if(g < min)
            {
                min = g;
                next_id = cur_node.neighbor_table[i].id;
            }
        }
        if(flag2 == min)
            break;

        route.push_back(next_id);
        for(int i = 0; i < node_table.size(); i++)
        {
            if(node_table[i].id == next_id)
                set_Node(node_table[i], cur_node);
        }
    }

    for(int i = 0; i < route.size(); i++)
        cout << route[i] << " ---> ";

    if(flag == 0)
        cout << "stop" << endl;
    else
        cout << dest_node.id << endl;


    return 0;
}