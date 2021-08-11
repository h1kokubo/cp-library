vector<vector<int>> shrinked_graph(vector<vector<int>> &graph,vector<int> &shrink_comp){
    vector<bool> is_shrink_comp(graph.size(),false);
    for(int v:shrink_comp)is_shrink_comp[v]=true;
    vector<bool> in(graph.size(),false),out(graph.size(),false);//縮約成分に頂点vから辺が入る⇔in[v]=true,縮約成分から頂点vに辺が出る⇔out[v]=true
    vector<vector<int>> res_graph(graph.size()+1);
    for(int v=0;v<graph.size();++v){
        if(is_shrink_comp[v]){
            for(int nv:graph[v]){
                out[nv]|=true;
            }
        }  
        else{
            for(int nv:graph[v]){
                if(is_shrink_comp[nv])out[v]|=true;
                else res_graph[v].push_back(nv);
            }
        }
    }
    for(int v=0;v<graph.size();++v){
        if(in[v])res_graph[v].push_back(graph.size());
        if(out[v])res_graph[graph.size()].push_back(v);
    }
    return res_graph;
}