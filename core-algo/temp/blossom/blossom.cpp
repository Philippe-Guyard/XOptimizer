#include<iostream>
#include<unordered_map>
#include<set>
#include<algorithm>
#include<vector>
#include "blossom.hpp"

Matching::Matching(Graph *G)
{
    this->G = *G;
    n_vertices = this->G.get_num_vertices();
    n_edges = this->G.get_num_edges();
    visited.assign(2*n_vertices, 0);

    outer.assign(2*n_vertices, 0);
    forest.assign(2*n_vertices, 0);
    tip.assign(2*n_vertices, 0);
    active.assign(2*n_vertices, 0);
    match.assign(2*n_edges, 0);
    parity.assign(2*n_vertices, 0);
    root.assign(2*n_vertices, 0);

    blocked.assign(2*n_vertices, 0);
    slack.assign(n_edges, 0);
    dual.assign(2*n_vertices, 0);

}


void Matching::grow(){

bool done;
reset();

while(!forest_list.empty())
{
    int w = outer[forest_list.front()]; // We take an element from the forest_list (as it might be in the blossom, we take its outer)
    forest_list.pop_front();

    for(std::list<int>::iterator i = deep[w].begin(); i != deep[w].end(); i++) // We loop over all the elements "inside" the current element blossom
    {
        //We explore all the possible connections from vertices inside the blossom to other vertices
        int u = *i;
        for(int v = 0; v < n_vertices; v++) // As the graph is complete we loop over all the vertices
            {
                if( u == v) continue;
                if(parity[outer[v]] == 1) continue;
                if (is_blocked(u,v)) continue;

                else if(is_matched(outer[v]))
                {
                    if(!in_forest(outer[v]))
                        //outer v is not in the forest so we extend current tree to include it
                    {
                        extend(u, v);

                    }
                    else if(root[outer[v]] != root[outer[u]])
                        // u and v are even in different trees and are thus generating an augmenting path
                    {
                        augment(u,v);
                        reset();
                        done = true;
                        break;
                    }
                    else if(outer[v] != outer[u])
                    // There is a blossom created by connecting u and v
                    {
                        int b = create_blossom(u, v);
                        forest_list.push_front(b);
                        visited[b] = true;
                        done = true;
                        break;

                    }
                }
                if (done) break;


            }
    }

}
    perfect = true;
    for(int i = 0; i < n_vertices; i++)
        if(match[outer[i]] == -1)
            perfect = false;
}


void Matching::extend(int u, int v){

    // We simply add the vectices v and vm to the tree and update the relevant parameters

    int vm = match[outer[v]];
    root[outer[v]] = root[outer[u]];
    root[outer[vm]] = root[outer[u]];
    parity[outer[vm]] = 0;
    parity[outer[v]] = 1;
    forest[outer[vm]] = v;
    forest[outer[v]] = u;
    if(!visited[outer[vm]])
    {
        forest_list.push_back(vm);
        visited[outer[vm]] = true;
    }

}

bool Matching::is_blocked(int u, int v){

    if(slack_edge(u, v) > 0) return true;
    else return false;

}

bool Matching::in_forest(int v){

    if (parity[v] == -1) return false;
    else return true;
    }

bool Matching::is_matched(int v){

    if (match[v] > -1) return true;
    else return false;


}
bool Matching::is_adjacent(int u, int v){

    if(slack_edge(u, v) > 0) return false;
    else return true;
}


double Matching::slack_edge(int u, int v){

    int e = G.get_edge_index(u,v);
    return slack[e];
}

void Matching::augment(int u, int v){
    // We augment the path between even nodes u and v of different trees in a standard manner

    std::vector<int> path_u;
    std::vector<int> path_v;
    // We first construct the two paths to roots from nodes u and v
    if (check_path(u, v)){
        std::vector<int> path_u = path_to_root(u);
        std::vector<int> path_v = path_to_root(v);
    }
    // We alternate the two paths
    alternate_path(path_u);
    alternate_path(path_v);
    // We change the partners of u and v
    match[v] = u;
    match[u] = v;


}

void Matching::alternate_path(std::vector<int> path){

    int u, v;
    // We loop over parent-child pairs of elements: (considering every other pair)
    for(std::vector<int>::iterator i = path.begin() + 1; i < path.end(); i+=2){

        u = *i;
        v = *(i+1);
        match[u] = v;
        match[v] = u;
        //We try to expand in the case that the new matching unblocked a blossom
        expand(u);
        expand(v);
    }
}

std::vector<int> Matching::path_to_root(int u){

    // Follow the tree structure to the root

    std::vector<int> path;
    int v = outer[u];
    path.push_back(v);

    while(is_matched(v)){
        v = outer[forest[v]];
        path.push_back(v);
    }
    return path;
}

bool Matching::check_path(int u, int v){
    // We use BSF to determine if there is a path from root u to root v
    int ur = root[u];
    int vr = root[v];
    std::vector<int> path;
    std::vector<bool> visited;
    if (ur == vr) return ur;
    for (int i = 0; i < v; i++){
        visited[i] = false;
    }
    std::list<int> queue;
    visited[ur] = true;
    queue.push_back(ur);

    while (!queue.empty()){
        int current = queue.front();
        queue.pop_front();
        for (std::vector<int>::iterator i = adjecent[ur].begin(); i != adjecent[ur].end(); ++i)
        {
            if (slack_edge(current, *i) > 0) continue;
            if (*i == vr) return true;
            if (!visited[*i])
            {
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
    return true;
}

int Matching::get_free_blossom()
{
    int i = free_blossom.back();
    free_blossom.pop_back();
    return i;
}

void Matching::add_free_blossom_index(int u){

    free_blossom.push_back(u);
}

void Matching::clear_blossom_indices()
{
    free_blossom.clear();
    for(int i = n_vertices; i < 2*n_vertices; i++)
        add_free_blossom_index(i);
}

int Matching::create_blossom(int u, int v){

    std::vector<int> path_u = path_to_root(u);
    std::vector<int> path_v = path_to_root(v);
    int t0 = first_common(path_u, path_v);
    std::vector<int>circuit = fork_path(u,v,t0);
    int t = get_free_blossom();

    // Updating shallow and deep of t;
    shallow[t].clear();
    deep[t].clear();

    for(std::vector<int>::iterator i=circuit.begin(); i!=circuit.end(); ++i)
    {
        shallow[t].push_back(*i);
        deep[t].insert(deep[t].end(), deep[*i].begin(), deep[*i].end());

    }
    // Updating OUTER for new blossom vertices
    for(std::list<int>::iterator i=deep[t].begin(); i!=deep[t].end(); ++i)
    {
        outer[*i] = t;
    }
    tip[t] = t0;

    forest[t] = forest[tip[t]];
    root[t] = root[tip[t]];
    active[t] = true;
    outer[t] = t;
    match[t] = match[tip[t]];
    parity[t] = 0;

    return t;

}



int Matching::first_common(std::vector<int> path_u, std::vector<int> path_v){

    std::vector<int>::iterator iw = std::find_first_of(path_u.begin(), path_u.end(), path_v.begin(), path_v.end());
    int w = *iw;
    return w;

}

std::vector<int> Matching::fork_path(int u, int v, int t0){

    int w = outer[u];
    std::vector<int> path;
    path.push_back(w);

    while(w!=t0)
    {
        w = outer[forest[w]];
        path.push_back(w);
    }

    w = outer[v];
    while(w!=t0)
    {
        w = outer[forest[w]];
        path.push_back(w);
    }
    return path;
}


// The function bellow is copied from the source mentioned in the report.
void Matching::expand(int u, bool expandBlocked)
{
    int v = outer[match[u]];

    int index = n_edges;
    int p = -1, q = -1;
    //Find the regular edge {p,q} of minimum index connecting u and its match
    //We use the minimum index to grant that the two possible blossoms u and v will use the same edge for a match
    for(std::list<int>::iterator it = deep[u].begin(); it != deep[u].end(); it++)
    {
        int di = *it;
        for(std::list<int>::iterator jt = deep[v].begin(); jt != deep[v].end(); jt++)
        {
            int dj = *jt;
            if(is_adjacent(di, dj) and G.get_edge_index(di, dj) < index)
            {
                index = G.get_edge_index(di, dj);
                p = di;
                q = dj;
            }
        }
    }

    match[u] = q;
    match[v] = p;
    //If u is a regular vertex, we are done
    if(u < n_vertices or (blocked[u] and not expandBlocked)) return;

    bool found = false;
    //Find the position t of the new tip of the blossom
    for(std::list<int>::iterator it = shallow[u].begin(); it != shallow[u].end() and not found; )
    {
        int si = *it;
        for(std::list<int>::iterator jt = deep[si].begin(); jt != deep[si].end() and not found; jt++)
        {
            if(*jt == p )
                found = true;
        }
        it++;
        if(not found)
        {
            shallow[u].push_back(si);
            shallow[u].pop_front();
        }
    }

    std::list<int>::iterator it = shallow[u].begin();
    //Adjust the match of the tip
    match[*it] = match[u];
    it++;
    //
    //Now we go through the odd circuit adjusting the new matchs
    while(it != shallow[u].end())
    {
        std::list<int>::iterator itnext = it;
        itnext++;
        match[*it] = *itnext;
        match[*itnext] = *it;
        itnext++;
        it = itnext;
    }

    //We update the sets blossom, shallow, and outer since this blossom is being deactivated
    for(std::list<int>::iterator it = shallow[u].begin(); it != shallow[u].end(); it++)
    {
        int s = *it;
        outer[s] = s;
        for(std::list<int>::iterator jt = deep[s].begin(); jt != deep[s].end(); jt++)
            outer[*jt] = s;
    }
    active[u] = false;
    add_free_blossom_index(u);

    //Expand the vertices in the blossom
    for(std::list<int>::iterator it = shallow[u].begin(); it != shallow[u].end(); it++)
        expand(*it, expandBlocked);

}



void Matching::destroy_blossom(int t){

    if (dual[t]>0 && blocked[t]){return;} // If the slack is not zero we cannot
    if(t < n_vertices){return;} //It is a simple node, not a blossom
    active[t] = false;
    blocked[t] = false;
    match[t] = -1;
    // We set the outer of all the shallow elements of t to themselves
    for(std::list<int>::iterator i = shallow[t].begin(); i != shallow[t].end(); i++)
    {
        int u = *i;
        outer[u] = u;
        // We set the outer of deep elements of t to the first smaller blossom
        for(std::list<int>::iterator j = deep[u].begin(); j!= shallow[u].end(); j++)
        {
                        outer[*j] = u;
        }
        destroy_blossom(*i);

    }
      add_free_blossom_index(t);

}

void Matching::clear()
{
    // We first reset all data for nodes:
    for(int i = 0; i<n_vertices; i++)
    {
        forest[i] = -1;
        root[i] = i;
        shallow[i].clear();
        deep[i].clear();
        deep[i].push_back(i);
        parity[i] = -1;
        dual[i] = 0;
        tip[i] = i;
        blocked[i] = false;
        active[i] = true;
        outer[i] = i;
        match[i] = -1;

    }
    // For pseudonodes:
    for(int i = 0; i<n_vertices; i++)
    {
        forest[i] = -1;
        root[i] = i;
        shallow[i].clear();
        deep[i].clear();
        parity[i] = -1;
        dual[i] = 0;
        tip[i] = i;
        blocked[i] = false;
        outer[i] = i;
        match[i] = -1;
        active[i] = false;

    }
    clear_blossom_indices();
    slack.assign(n_edges, 0);

}

void Matching::reset()
{
    visited.assign(2*n_vertices, 0);
    forest_list.clear();

    // We first loop over the "real vertices" and update their variables
    for(int i = 0; i<n_vertices; i++)
    {
        forest[i] = -1;
        root[i] = i;
        if(match[outer[i]] == -1)
                {
                    parity[outer[i]] = 0;
                    if(!visited[outer[i]])
                        forest_list.push_back(i);
                    visited[outer[i]] = true;
                 }
         else parity[outer[i]] = -1;
     }

    // We now loop over the blossom pseudonodes and destroy them if they are active
    for(int i = n_vertices; i< 2*n_vertices; i++)
    {
        forest[i] = -1;
        root[i] = i;
        if(active[i] and outer[i] == i)
            {
                    destroy_blossom(i);
            }
    }

}

void Matching::update_dual_cost(){

    //This function follows the algorithm explained in the book "Combinatorial Optimization" by Wiliam J.Cook
    double e1 = 0, e2 = 0, e3 = 0, e = 0, edge;
    bool init1 = false, init2 = false, init3 = false;

    for(int u = 0; u<n_vertices; u++)
    {
        for(int v = 0; v<n_vertices; v++)
        {

            // First two if statements present the first e update rule
            if (parity[outer[u]] == 0 && parity[outer[v]] == -1)
            {
                edge = G.get_edge_index(u, v);
                if(!init1 || slack[edge]<e1)
                {e1 = slack[edge];
                init1 = true;}
            }
            else if (parity[outer[u]] == -1 && parity[outer[v]] == 0)
            {
                edge = G.get_edge_index(u, v);
                if(!init1 || slack[edge]<e1)
                {e1 = slack[edge];
                init1 = true;}
            }
            // the second e update rule:
            else if( (outer[u] != outer[v]) and parity[outer[u]] == 0 and parity[outer[v]] == 0 )
            {
                edge = G.get_edge_index(u, v);
                if( !init2 || slack[edge]/2.0 < e2)
                    {
                        e2 = slack[edge]/2.0;
                        init2 = true;
                    }
            }


        }

    }
    // Rule for computing e3
    for(int t = n_vertices; t < 2*n_vertices; t++)
        {
            if(!init3 && active[t] && t == outer[t] && parity[outer[t]] == 1)
            {
                e3 = dual[t];
                init3 = true;
            }
            if(active[t] && t == outer[t] && parity[outer[t]] == 1 && e3 > dual[t])
            {
                e3 = dual[t];
            }
        }
    // e is the non zero minimum of e1, e2, e3:
    if (init1 && init2 && init3)
    {
        e = std::min({e1, e2, e3});
    }
    else if(init1 && init2)
    {
        e = std::min({e1, e2});
    }
    else if(init2 && init3)
    {
        e = std::min({e2, e3});
    }
    else if(init1 && init3)
    {
        e = std::min({e1, e3});
    }
    else if(init1)
    {
        e = e1;
    }
    else if(init2)
    {
        e = e2;
    }
    else if(init3)
    {
        e = e3;
    }
    // We now update the dual variables corresponding to the change:

    for(int u = 0; u < 2*n_vertices; u++)
    {
        if(outer[u] != u){continue;}
        else if(active[u] && parity[u] == 1){dual[u] -= e;}
        else if(active[u] && parity[u] == 0){dual[u] += e;}
    }
    // The change in dual variable induced a change in the slack of edges:
    for(int u = 0; u < n_vertices; u++)
        {
           for(int v = 0; v < n_vertices; v++)
           {

            if(outer[u] != outer[v])
                {
                int i = G.get_edge_index(u, v);
                if(parity[outer[u]] == 0 and parity[outer[v]] == 0)
                    slack[i] -= 2.0*e;
                else if(parity[outer[u]] == 1 and parity[outer[v]] == 1)
                    slack[i] += 2.0*e;
                else if( (parity[outer[v]] == -1 and parity[outer[u]] == 0) || (parity[outer[u]] == -1 and parity[outer[v]] == 0) )
                    slack[i] -= e;
                else if( (parity[outer[v]] == -1 and parity[outer[u]] == 1) || (parity[outer[u]] == -1 and parity[outer[v]] == 1) )
                    slack[i] += e;
                }
            }

        }
     // Lastly we have to check which blossoms bacame blocked or unblocked due to this change:
    for(int i = n_vertices; i < 2*n_vertices; i++)
        {
            if(dual[i] > 0)
            {
                blocked[i] = true;
            }
            else if(active[i] and blocked[i])
            {
                if(match[i] == -1)
                {
                    destroy_blossom(i);
                }
                else
                {
                    blocked[i] = false;
                    expand(i);
                }
            }
          }
}

std::pair<std::vector<std::pair<int,int>>, double > Matching::solve(const std::vector<double> & weight)
{
    clear();
    slack = weight;
    //If the matching on the compressed graph is perfect, we are done
    perfect = false;
    while(not perfect)
    {
        initial_matching(); //Run an initial maximum matching algorithm
        // Perform the blossom weighted:
        grow();
        update_dual_cost();
        reset();
    }

    std::vector<int> edges;
    std::vector<std::pair<int, int>> matching;

    for(int i = 0; i < 2*n_vertices; i++)
    {
        if(active[i] and match[i] != -1 and outer[i] == i){expand(i, true);}
    }

    for(int u = 0; u < n_vertices; u++)
    {
        for(int v = 0; v<n_vertices; v++)
        {
            if (match[v] == u)
            {
                edges.push_back(G.get_edge_index(u, v));
                std::pair<int, int> e = std::make_pair(u, v);
                matching.push_back(e);
            }
        }


    }
    double cost = 0;
        for(std::vector<int>::iterator i = edges.begin(); i != edges.end(); i++)
            cost += weight[*i];

    return std::pair<std::vector<std::pair<int,int>>, double >  (matching, cost);
}

void Matching::initial_matching()
{
    long BIG = 900000;
    std::vector<long> edge_weights;
    int mate;

    for(int i = 0; i<n_vertices; i++)
    {
        if(match[outer[i]] > -1){continue;}
        for(int j = 0; j<n_vertices; j++)
        {
            if (is_blocked(i, j)) {edge_weights[j] = BIG;}
            else if(outer[i] == outer[j] || match[j] >= 0){edge_weights[j] = BIG;}
            else {edge_weights[j] = G.get_edge_weight(i, j);}
        }
        mate = std::min_element(edge_weights.begin(), edge_weights.end()) - edge_weights.begin();
        if(edge_weights[mate] < BIG-1)
        {
            match[outer[i]] = mate;
            match[outer[mate]] = i;
        }
    }

}
