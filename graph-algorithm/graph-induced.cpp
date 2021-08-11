vector<vector<int>> graph_induced(vector<vector<int>> &graph,vector<int> erase_lst){
    vector<bool> erase(graph.size(),false);
    vector<vector<int>> induced_graph(graph.size());
    for(auto &v:erase_lst)erase[v]=true;
    for(int v=0;i<graph.size();++i){
        
        if(!erase[v]){
            for(int nv:graph[v]){
                if(!erase[nv])induced_graph[v].push_back(nv);
            }
        }
    }
    return induced_graph;
}