#include <bits/stdc++.h>
using namespace std;


int n,m;
vector<int>available(100);
int Max[100][100],allocation[100][100],need[100][100];
deque<string>safety_sequence;


void input(){
    cout<<"Enter number of processes & number of resources:"<<endl;
    cin>>n>>m;

    for(int i=0;i<n;i++){
        cout<<"Enter P"<<i<<" resource allocation vector :"<<endl;
        for(int j=0;j<m;j++){
            cin>>allocation[i][j];
        }
    }

    for(int i=0;i<n;i++){
        cout<<"Enter P"<<i<<" maximum resources vector :"<<endl;
        for(int j=0;j<m;j++){
            cin>>Max[i][j];
        }
    }

    cout<<"Enter the available resources vector"<<endl;
    for(int i=0;i<m;i++)cin>>available[i];

    cout<<endl;

}

void output(){
    cout<<"|||||||||||||||||||||||||||||||||||||||||||||||||||Need Matrix|||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl<<endl;
    for(int i=0;i<m;i++)cout<<"\t"<<"R"<<i<<"\t";
    cout<<endl;
    for(int i=0;i<n;i++){
        cout<<"P"<<i<<"\t";
        for(int j=0;j<m;j++){
            need[i][j] = Max[i][j]-allocation[i][j];
            cout<<need[i][j]<<"\t"<<"\t";
        }
        cout<<endl;
    }
    cout<<endl;
}

void print_safe_sequence(){
    cout<<"<";
    for(int i=0;i<safety_sequence.size();i++){
        if(i!=safety_sequence.size()-1){
            cout<<safety_sequence[i]<<",";
        }
        else cout<<safety_sequence[i]<<">"<<endl;
    }
}

bool safety_algorithm(){
    vector<int>work(100);
    vector<bool>finish(100);
    for(int i=0;i<m;i++){
        work[i] = available[i];
    }
    for(int i=0;i<n;i++){
        finish[i] = false;
    }
    safety_sequence.clear();
    int number_of_safe_processes = 0;
    bool safe = false;
    while(true){
        safe = false;
        for(int i=0;i<n;i++){
            if(!finish[i]){
                int flag = 1;
                for(int j=0;j<m;j++){
                    if(need[i][j]>work[j]){
                        flag = 0;
                        break;
                    }
                }
                if(flag){
                    finish[i] = true;
                    safety_sequence.emplace_back("P"+to_string(i));
                    number_of_safe_processes++;
                    safe = true;
                    for(int j=0;j<m;j++){
                        work[j]+=allocation[i][j];
                    }
                }
            }

            if(number_of_safe_processes == n)break;

        }

        if(!safe)break;

    }

    if(number_of_safe_processes == n){

        return true;
    }

    else{

        return false;
    }


}

void resource_request_algorithm(){
    int x;
    cout<<"Enter the number of the process which has the resource request: ";
    cin>>x;

    cout<<endl;
    cout<<"Enter the request vector:";
    vector<int>request(100);
    int flag_claim = 1,flag_available = 1;

    for(int i=0;i<m;i++){
        cin>>request[i];
        if(request[i]>need[x][i])flag_claim = 0;
        if(request[i]>available[i])flag_available=0;
    }

    cout<<endl;

    if(flag_claim){
        if(flag_available){
            for(int i=0;i<m;i++){
                available[i]-=request[i];
                allocation[x][i]+=request[i];
                need[x][i]-=request[i];
            }
            if(safety_algorithm()){
                cout<<"Yes request can be granted with safe state, Safe state";
                safety_sequence.push_front("P"+to_string(x)+"req");
                print_safe_sequence();
            }
            else{
                cout<<"No, request can't be granted "<<endl;
                cout<<"As the system is not in safe state"<<endl;
                cout<<"So the process must wait and also the old resource allocation state is restored"<<endl;
                for(int i=0;i<m;i++){
                    available[i]+=request[i];
                    allocation[x][i]-=request[i];
                    need[x][i]+=request[i];
                }
            }
        }
        else{
            cout<<"No, request can't be granted "<<endl;
            cout<<"So the process must wait since resources are not available"<<endl;
        }
    }
    else{
        cout<<"No, request can't be granted "<<endl;
        cout<<"As the process has exceeded its maximum claim"<<endl;
    }

    cout<<endl;

}



int main() {

    bool flag = false;

    while(true){

        int x;
        cout<<"||||||||||||||||Menu||||||||||||||||"<<endl;
        cout<<"0-Enter new problem"<<endl;
        cout<<"1-See if the system is in safe state"<<endl;
        cout<<"2-Resource request for certain process"<<endl;
        cout<<"3-Exit"<<endl;
        cin>>x;
        cout<<endl;
        if(x==0){
            flag = true;
            input();
            output();
            cout<<endl;
        }
        if(x==1 && flag){
            if(safety_algorithm()){
                cout<<"Yes, Safe state ";
                print_safe_sequence();
            }
            else cout<<"No, Not safe state"<<endl;
            cout<<endl<<endl;
        }
        else if(x==2 && flag){
            resource_request_algorithm();
        }
        else if(x==3)break;
    }

    return 0;
}
