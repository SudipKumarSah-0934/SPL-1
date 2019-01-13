#include<iostream>
#include<vector>
#include<bits/stdc++.h>
using namespace std;
struct process{
    int id;
    int time;
};
struct process_with_prio{
    int id;
    int time;
    int priority;
};
vector <process_with_prio> prio;
vector <process> p;
bool myComp(process &a,process &b){

    return a.time < b.time;
}
bool myComp2(process_with_prio &a,process_with_prio &b){

    return a.priority > b.priority;
}
fcfs(vector <process> &p)
{
    cout<<"First come first serve:"<<endl;
    for(int i=0;i<p.size();i++)
    {
     cout<<"P"<<p[i].id<<endl;
    }

}
shortJobFirst(vector<process> &p)
{
    sort(p.begin(),p.end(),myComp);
    cout<<"Shortest Job First:"<<endl;
    for(int i=0;i<p.size();i++)
    {

        cout<<"p"<<p[i].id<<endl;

    }
}
prioBase(vector<process_with_prio> &prio){

    sort(prio.begin(),prio.end(),myComp2);
    for(int i=0;i<prio.size();i++)
    {

        cout<<"p"<<prio[i].id<<endl;

    }
}
int main (){
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        process temp;
        int tTime;
        int tId;

        cin>>tId>>tTime;
        temp.id=tId;
        temp.time=tTime;


        p.push_back(temp);

    }
    fcfs(p);
    shortJobFirst(p);

    cout<<"input for priority first test"<<endl;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        process_with_prio temp;
        int tTime;
        int tId;
        int tPrio;
        cin>>tId>>tTime>>tPrio;
        temp.id=tId;
        temp.time=tTime;
        temp.priority=tPrio;

        prio.push_back(temp);

    }

    prioBase(prio);


}
