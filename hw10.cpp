#include <iostream>
#include <list>
#include <stack>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <string>

using namespace std;

int current_component = 0;
int dfs_n = 0;

//vertex class
class vertex{
public:
    int dfs_num;
    int component;
    int high;
    vertex(){
        dfs_num = 0;
        component = 0;
        high = 0;
    }
};

//strongly connected component function(following the pseudocode in the lecture)
void SCC(int i, stack<int>& stk, vector<vertex>& vertices, vector<vector<int>>& adjList,vector<vector<int>>& output){
    //set the dfs number and high
    vertices[i].dfs_num = dfs_n;
    dfs_n--;
    stk.push(i);
    vertices[i].high = vertices[i].dfs_num;

    //check all the neighbors
    for(int j = 0; j < adjList[i].size(); j++){
        //if the neighbor is not visited, do the SCC function
        if(vertices[adjList[i][j]].dfs_num == 0){
            SCC(adjList[i][j], stk, vertices, adjList, output);
            vertices[i].high = max(vertices[i].high, vertices[adjList[i][j]].high);
        }
        //if the neighbor is visited and in the same component, update the high
        else if(vertices[adjList[i][j]].component == 0 && vertices[adjList[i][j]].dfs_num > vertices[i].dfs_num){
            vertices[i].high = max(vertices[i].high, vertices[adjList[i][j]].dfs_num);
        }
    }

    //if the dfs number and high are the same, pop the stack and update the component
    if(vertices[i].high == vertices[i].dfs_num){
        vector<int> temp;
        current_component++;
        while(stk.top() != i){
            temp.push_back(stk.top());
            vertices[stk.top()].component = current_component;
            stk.pop();
        }
        temp.push_back(stk.top());
        vertices[stk.top()].component = current_component;
        stk.pop();
        output.push_back(temp);
    }
}

int main(){

    int total = 0;
    cin >> total;

    //ignore the rest of the line
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    stack<int> stk;
    vector<vector<int>> output;
    vector<vector<int>> adjList;
    vector<vertex> vertices(total);

    dfs_n = total;

    for (int i = 0; i < total; i++)
    {
        string s;
        getline(cin, s);
        istringstream iss(s);
        vector<int> input((istream_iterator<int>(iss)), istream_iterator<int>());

        //erase the first element
        input.erase(input.begin());

        //decrease all the elements by 1 by using iterator
        for (auto it = input.begin(); it != input.end(); ++it){
               *it = *it - 1;
        }
        
        adjList.push_back(input);
    }

    //initialize the vertices
    for(int i = 0; i < total; i++){
        vertices[i].dfs_num = 0;
        vertices[i].component = 0;
        vertices[i].high = 0;
    }
    
    //do the SCC function(following the pseudocode in the lecture)
    for(int i = 0; i < total; i++){
        if(vertices[i].dfs_num == 0){
            SCC(i, stk, vertices, adjList, output);
        }
    }
    
    /*
    for(int i = 0; i < total; i++){
        cout << "vertex" << i+1 << "'s component: "<< vertices[i].component << endl;
    }
    */
    
    //print the output
    for(int i = 0; i < output.size(); i++){
        //cout << "component" << i+1 << ": ";
        for(int j = int(output[i].size())-1; j >= 0; j--){
            cout << output[i][j]+1 << " ";
        }
        cout << endl;
    }
    
    return 0;
}
