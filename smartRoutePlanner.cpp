#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

int MinimumCost(int n, vector<vector<int>>& path, int src, int des, vector<int>&parent)  {
        vector<pair<int,int>> adj[n];
        for(auto it:path){
            adj[it[0]].push_back({it[2],it[1]});
            adj[it[1]].push_back({it[2],it[0]});
        }
        vector<int> dist(n,1e9);
        dist[src]=0;
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q;
        q.push({0,src});
        
        while(!q.empty()){
        auto it=q.top();
        int node=it.second;
        int dis=it.first;
        q.pop();

        if(node==des) return dist[des];
        
        for(auto it:adj[node]){
            int adjnode = it.second;
            int w = it.first;
            if(w+dis<dist[adjnode]){
                dist[adjnode]=w+dis;
                q.push({w+dis,adjnode});
                parent[adjnode]=node;
            }
        }
        }
        return 0;
    }

int MinimumTime(int n, vector<vector<int>>& path, int src, int des, vector<int>&parent)  {
        vector<pair<int,int>> adj[n];
        for(auto it:path){
            adj[it[0]].push_back({it[3],it[1]});
            adj[it[1]].push_back({it[3],it[0]});
        }
        vector<int> time(n,1e9);
        time[src]=0;
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q;
        q.push({0,src});
        
        while(!q.empty()){
        auto it=q.top();
        int node=it.second;
        int dis=it.first;
        q.pop();

        if(node==des) return time[des];
        
        for(auto it:adj[node]){
            int adjnode = it.second;
            int w = it.first;
            if(w+dis<time[adjnode]){
                time[adjnode]=w+dis;
                q.push({w+dis,adjnode});
                parent[adjnode]=node;
            }
        }
        }
        return 0;
    }
    
void PrintPath(vector<string> &stations,vector<int> &parent,int src, int des){
    vector<int> st;
    while(parent[des]!=des){
        st.push_back(des);
        des=parent[des];
    }
    st.push_back(src);
    reverse(st.begin(),st.end());
    
    for(int i=0;i<st.size();i++){
        cout<<stations[st[i]];
        if(i!=st.size()-1) cout<<" -> ";
    }    
}

int main(){

    vector<string> stations={"gitanjali","netaji","kalighat","parkstreet","mgroad","shyambazar","dumdum","noapara","baranagar","dakshineswar"};
    int n=stations.size();
    string s,d,a;
    cout<<"Enter your Source Station - ";
    cin>>s;
    cout<<endl;
    cout<<"Enter your Destination Station - ";
    cin>>d;
    cout<<endl;
    cout<<"What do You Want to Save - time or money -- ";
    cin>>a;
    
    vector<int> parent(n,0);
    for(int i=0;i<n;i++) parent[i]=i;
    vector<vector<int>> path={{0,1,50,1},{0,2,30,2},{2,3,10,1},{1,2,20,2},{1,5,100,7},{1,3,50,3},{2,4,20,4},{2,6,100,5},{3,4,30,2},{3,5,30,3},{4,5,20,2},{5,6,50,1},
    {6,7,40,2},{7,8,56,4},{8,9,127,12},{6,8,99,5},{6,9,256,14},{3,7,80,9},{4,8,185,7},{2,9,360,20}};
    
    int src=-1,des=-1;
    for(int i=0;i<n;i++){
        if(s==stations[i]) src=i;
        if(d==stations[i]) des=i;
    }

    if(src!=-1 && des !=-1) {
        if(a=="money"){
            cout<<"-------------------------------------------------------------"<<endl;
        cout<<"  Cost-> "<<MinimumCost(n,path,src,des,parent)<<"Rs."<<endl;
        cout<<"-------------------------------------------------------------"<<endl;
        cout<<"  Path --> ";
        PrintPath(stations,parent,src,des);
        cout<<endl;
        cout<<"-------------------------------------------------------------"<<endl;
        }
        else if(a=="time"){
        cout<<"-------------------------------------------------------------"<<endl;    
        cout<<"  Time-> "<<MinimumTime(n,path,src,des,parent)<<" min"<<endl;
        cout<<"-------------------------------------------------------------"<<endl;
        cout<<"  Path --> ";
        PrintPath(stations,parent,src,des);
        cout<<endl;
        cout<<"-----------------------------------------------------"<<endl;
        }
        else cout<<"Enter Valid Information"<<endl;
    }
    else cout<<"Enter Valid Station Name!!"<<endl;
}