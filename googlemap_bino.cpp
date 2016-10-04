#include<iostream>
#include<vector>
#include<list>
#include<queue>
#include<fstream>
#include<string>
#include<stack>
#include<map>
#include<ctime>
using namespace std;

map<string,int> visited;
map<string,string> path;
map<string,int> pathc;
map<string,int> heu;

struct node
{
    string name;
    int distance;
};

struct npc
{
    string name;
    int cost;
    string parent;
};

struct npca
{
    string name;
    int cost;
    string parent;
    int cost_h;
};

map<string,vector<node> > adjlist;

bool compare_cost(const struct npc &a,const struct npc &b)
{
    if(a.cost<b.cost)
    return true;

    return false;
}

bool compare_costa(const struct npca &a,const struct npca &b)
{
    if(a.cost_h<b.cost_h)
    return true;

    return false;
}

void BFS(string start,string goal)
{
    ofstream op;
    op.open("output.txt");
    if(start.compare(goal)==0)
    {
        op<<start<<" "<<"0";
        op.close();
        return;
    }
    int found=-1;
    stack<string> S;
    queue<string> Q;
    vector<node> v1;

    Q.push(start);
    while(!Q.empty())
    {
        vector<node> v2;
        map<string,vector<node> >::iterator ite;
        string s,p;
        s=Q.front();
        Q.pop();
        if(s==goal)
        {
            found=0;
            break;
        }
        ite=adjlist.find(s);

        if(ite!=adjlist.end())
        {
            v2=adjlist.find(s)->second;
            unsigned int k=0;
            while(k<=v2.size()-1)
            {
                if(visited.find(v2[k].name)->second==-1)
                {
                    visited.find(v2[k].name)->second=1;
                    path.insert(pair<string,string>(v2[k].name,s));
                    Q.push(v2[k].name);
                }
                k++;
            }
        }
    }
    if(found==0)
    {
       // cout<<"The path is"<<endl;
       // cout<<goal<<"-->";
        string a;
        string b;
        b=goal;
        a=start;
        int count=1;
        op<<start<<" 0"<<endl;
        S.push(goal);
        while((path.at(b)!=a))
        {
            //cout<<path.at(b)<<"-->";
            b=path.at(b);
            S.push(b);
        }
        while(!S.empty())
        {
            string r;
            r=S.top();
            op<<r<<" "<<count++<<endl;
            S.pop();
        }
        //cout<<start;
        op.close();
    }
}

void DFS(string start,string goal)
{
    ofstream op;
    op.open("output.txt");
    if(start.compare(goal)==0)
    {
        op<<start<<" 0";
        op.close();
        return;
    }
    int found=-1;
    stack<string> S;
    stack<string> Y;
    int count=0;

    S.push(start);
    while(!S.empty())
    {
        vector<node> v2;
        map<string,vector<node> >::iterator ite;
        string s,p;
        s=S.top();
       // cout<<s<<count++<<endl;
        S.pop();
        if(s==goal)
        {
            found=0;
            break;
        }
        ite=adjlist.find(s);

        if(ite!=adjlist.end())
        {
            v2=adjlist.find(s)->second;
            int k=v2.size()-1;
            while(k>=0)
            {
                if(visited.find(v2[k].name)->second==-1)
                {
                    visited.find(v2[k].name)->second=1;
                    path.insert(pair<string,string>(v2[k].name,s));
                    S.push(v2[k].name);
                }
                k--;
            }
        }
    }
    if(found==0)
    {
        //cout<<"The path is"<<endl;
        //cout<<goal<<"-->";
        string a;
        string b;
        b=goal;
        a=start;
        op<<start<<" 0"<<endl;
        int count=1;
        Y.push(goal);
        while((path.at(b)!=a))
        {
          //  cout<<path.at(b)<<"-->";
            b=path.at(b);
            Y.push(b);
        }
        while(!Y.empty())
        {
            string r;
            r=Y.top();
            op<<r<<" "<<count++<<endl;
            Y.pop();
        }
        op.close();
        //cout<<start;
    }
}

void UCS(string start,string goal)
{
    ofstream op;
    stack<string> q;
    stack<int> o;
    op.open("output.txt");
    if(start.compare(goal)==0)
    {
        op<<start<<" 0";
        op.close();
        return;
    }
    int found=-1;
    list<npc> open;
    list<npc> closed;
    npc temp;
    npc temp1;
    npc n1;
    n1.cost=0;
    n1.name=start;
    n1.parent="Start";
    open.push_back(n1);
    while(!open.empty())
    {
        npc n2;
        vector<node>v2;
        map<string,vector<node> >::iterator ite;
        string s;
        int cost_i;
        n2=open.front();
        s=n2.name;
        cost_i=n2.cost;
        open.pop_front();
        if(n2.name==goal)
        {
            found=0;
            break;
        }

        ite=adjlist.find(s);

        if(ite!=adjlist.end())
        {
                unsigned int k=0;
                v2=adjlist.find(s)->second;
                while(k<=v2.size()-1)
                {
                    string child;
                    child=v2[k].name;
                    string parent=s;
                    int cost=cost_i+v2[k].distance;
                    npc node_i;
                    node_i.cost=cost;
                    node_i.name=child;
                    node_i.parent=parent;
                    int f=-1;
                    int f1=-1;
                    list<npc>::iterator it,it1;
                    if(open.size()!=0)
                    {
                        for(it=open.begin();it!=open.end();it++)
                        {
                            temp=*it;
                            if(temp.name==child)
                            {
                                f=0;
                                break;
                            }
                        }
                    }
                    if(closed.size()!=0)
                    {
                        for(it1=closed.begin();it1!=closed.end();it1++)
                        {
                            temp1=*it1;
                            if(temp1.name==child)
                            {
                                f1=0;
                                break;
                            }
                        }
                    }
                    if(f1==-1&&f==-1)
                    {
                        open.push_back(node_i);
                        if(path.find(node_i.name)==path.end())
                        {
                            path.insert(pair<string,string>(node_i.name,s));
                            pathc.insert(pair<string,int>(node_i.name,node_i.cost));
                        }
                        else
                        {
                            path.find(node_i.name)->second=s;
                            pathc.find(node_i.name)->second=node_i.cost;
                        }
                    }
                    else if(f==0)
                    {
                        if(node_i.cost<temp.cost)
                        {
                            open.erase(it);
                            open.push_back(node_i);
                            if(path.find(node_i.name)==path.end())
                            {
                                path.insert(pair<string,string>(node_i.name,s));
                                pathc.insert(pair<string,int>(node_i.name,node_i.cost));
                            }
                            else
                            {
                                path.find(node_i.name)->second=s;
                                pathc.find(node_i.name)->second=node_i.cost;
                            }
                        }

                    }
                    else if(f1==0)
                    {
                        if(node_i.cost<temp1.cost)
                        {
                            closed.erase(it1);
                            open.push_back(node_i);
                            if(path.find(node_i.name)==path.end())
                            {
                                path.insert(pair<string,string>(node_i.name,s));
                                pathc.insert(pair<string,int>(node_i.name,node_i.cost));
                            }
                            else
                            {
                                path.find(node_i.name)->second=s;
                                pathc.find(node_i.name)->second=node_i.cost;
                            }
                        }
                    }

                k++;
                }
            }

        closed.push_back(n2);
        open.sort(compare_cost);
       // cout<<"New Iteration"<<endl;
        list<npc>::iterator it3;
            for(it3=open.begin();it3!=open.end();it3++)
            {

                    npc temp;
                    temp=*it3;
                    //cout<<temp.name<<" "<<temp.parent<<" "<<temp.cost<<endl;
            }
        }
    if(found==0)
    {
        //cout<<"The path is"<<endl;
        //cout<<goal<<"-->";
        string a;
        string b;
        b=goal;
        a=start;
        op<<start<<" 0"<<endl;
        q.push(goal);
        o.push(pathc.at(goal));
        while((path.at(b)!=a))
        {
          //  cout<<path.at(b)<<"-->";
            b=path.at(b);
            q.push(b);
            o.push(pathc.at(b));
        }
        while(!q.empty())
        {
            string r;
            r=q.top();
            int c;
            c=o.top();
            op<<r<<" "<<c<<endl;
            q.pop();
            o.pop();
        }
        op.close();
        //cout<<start;
    }
}

void ASTAR(string start,string goal)
{
    ofstream op;
    stack<string> q;
    stack<int> o;
    op.open("output.txt");
    if(start.compare(goal)==0)
    {
        op<<start<<" 0";
        op.close();
        return;
    }
    int found=-1;
    list<npca> open;
    list<npca> closed;
    npca temp;
    npca temp1;
    npca n1;
    n1.cost=0;
    n1.name=start;
    n1.parent="Start";
    open.push_back(n1);
    while(!open.empty())
    {
        npca n2;
        vector<node>v2;
        map<string,vector<node> >::iterator ite;
        string s;
        int cost_i;
        n2=open.front();
        s=n2.name;
        cost_i=n2.cost;
        open.pop_front();
        if(n2.name==goal)
        {
            found=0;
            break;
        }
        ite=adjlist.find(s);

        if(ite!=adjlist.end())
        {
            unsigned int k=0;
            v2=adjlist.find(s)->second;
            while(k<=v2.size()-1)
            {
                    string child;
                    child=v2[k].name;
                    string parent=s;
                    int cost=cost_i+v2[k].distance;
                    npca node_i;
                    node_i.cost=cost;
                    int he;
                    he=heu.find(child)->second;
                    node_i.cost_h=cost+he;
                    node_i.name=child;
                    node_i.parent=parent;
                    int f=-1;
                    int f1=-1;
                    list<npca>::iterator it,it1;
                    if(open.size()!=0)
                    {
                        for(it=open.begin();it!=open.end();it++)
                        {
                            temp=*it;
                            if(temp.name==child)
                            {
                                f=0;
                                break;
                            }
                        }
                    }
                    if(closed.size()!=0)
                    {
                        for(it1=closed.begin();it1!=closed.end();it1++)
                        {
                            temp1=*it1;
                            if(temp1.name==child)
                            {
                                f1=0;
                                break;
                            }
                        }
                    }
                    if(f1==-1&&f==-1)
                    {
                        open.push_back(node_i);
                        if(path.find(node_i.name)==path.end())
                        {
                            path.insert(pair<string,string>(node_i.name,s));
                            pathc.insert(pair<string,int>(node_i.name,node_i.cost));
                        }
                        else
                        {
                            path.find(node_i.name)->second=s;
                            pathc.find(node_i.name)->second=node_i.cost;
                        }
                    }
                    else if(f==0)
                    {
                        if(node_i.cost_h<temp.cost_h)
                        {
                            open.erase(it);
                            open.push_back(node_i);

                            if(path.find(node_i.name)==path.end())
                            {
                                path.insert(pair<string,string>(node_i.name,s));
                                pathc.insert(pair<string,int>(node_i.name,node_i.cost));
                            }
                            else
                            {
                                path.find(node_i.name)->second=s;
                                pathc.find(node_i.name)->second=node_i.cost;
                            }

                        }

                    }
                    else if(f1==0)
                    {
                        if(node_i.cost_h<temp1.cost_h)
                        {
                            closed.erase(it1);
                            open.push_back(node_i);
                            if(path.find(node_i.name)==path.end())
                            {
                                path.insert(pair<string,string>(node_i.name,s));
                                pathc.insert(pair<string,int>(node_i.name,node_i.cost));
                            }
                            else
                            {
                                path.find(node_i.name)->second=s;
                                pathc.find(node_i.name)->second=node_i.cost;
                            }
                        }
                    }
                k++;
            }
        }

        closed.push_back(n2);
        open.sort(compare_costa);
        cout<<"Iteration"<<endl;
        list<npca>::iterator it3;
        for(it3=open.begin();it3!=open.end();it3++)
        {
                npca temp;
                temp=*it3;
                //cout<<temp.name<<" "<<temp.parent<<" "<<temp.cost<<" "<<temp.cost_h<<endl;
        }
    }
    if(found==0)
    {
        cout<<"The path is"<<endl;
        cout<<goal<<"-->";
        string a;
        string b;
        b=goal;
        a=start;
        op<<start<<" 0"<<endl;
        q.push(goal);
        o.push(pathc.at(goal));
        while((path.at(b)!=a))
        {
          cout<<path.at(b)<<"-->";
            b=path.at(b);
            q.push(b);
            o.push(pathc.at(b));
        }
         while(!q.empty())
        {
            string r;
            r=q.top();
            int c;
            c=o.top();
            op<<r<<" "<<c<<endl;
            q.pop();
            o.pop();
        }
        op.close();
        cout<<start;
    }
}

int main() {

    ifstream f1;
    ofstream f2;
    int x,y;
    string start,goal,in;
    string s;
    string algo;
    int distance;
    vector<node> v3;
    map<string,int>::iterator it,it1;
    map<string,vector<node> >::iterator ite;
    node n1;
     int start_s=clock();
        f1.open("inputstress.txt");
        f1>>algo;
        f1>>start;
        f1>>goal;
        f1>>x;

        for(int j=1;j<=x;j++)
        {
            f1>>in;
            f1>>s;
            f1>>distance;

            it=visited.find(in);
            if(it==visited.end())
            visited.insert(pair<string,int>(in,-1));

            it1=visited.find(s);
            if(it1==visited.end())
            visited.insert(pair<string,int>(s,-1));


                ite=adjlist.find(in);
                if(ite==adjlist.end())
                {
                    node n1;
                    vector<node> v1;
                    n1.name=s;
                    n1.distance=distance;
                    v1.push_back(n1);
                    adjlist.insert(pair<string,vector<node> >(in,v1));
                }
                else
                {
                    node n1;
                    vector<node> v1;
                    n1.name=s;
                    n1.distance=distance;
                    v1=adjlist.find(in)->second;
                    v1.push_back(n1);
                    adjlist.find(in)->second=v1;
                }

        }
        f1>>y;
        for(int k=1;k<=y;k++)
        {
            node n1;
            f1>>s;
            f1>>distance;
            n1.name=s;
            n1.distance=distance;
            heu.insert(pair<string,int>(s,distance));
            v3.push_back(n1);
        }

        if(algo=="BFS")
        {
            BFS(start,goal);
        }
        else if(algo=="DFS")
        {
            DFS(start,goal);
        }
        else if(algo=="UCS")
        {
            UCS(start,goal);
        }
        else if(algo=="A*")
        {
            ASTAR(start,goal);
        }
    f1.close();
    int stop_s=clock();
cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
    return 0;
}
