#include <iostream>
#include <vector>
using namespace std;

pair<int, vector<char> > solveDisks(int n){
    int moves=0;
    vector<char> disks(2*n);

    for(int i=0;i<2*n;i++){
        if(i%2==0)
            disks[i]='D';
        else
            disks[i]='L';
    }

    vector<char> goal(2*n);
    for(int i=0;i<n;i++)
        goal[i]='L';
    for(int i=n;i<2*n;i++)
        goal[i]='D';

    while(disks!=goal){
        for(int i=0;i<2*n-1;i+=2){
            if(disks[i]=='D' && disks[i+1]=='L'){
                char t=disks[i];
                disks[i]=disks[i+1];
                disks[i+1]=t;
                moves++;
            }
        }
        for(int i=1;i<2*n-1;i+=2){
            if(disks[i]=='D' && disks[i+1]=='L'){
                char t=disks[i];
                disks[i]=disks[i+1];
                disks[i+1]=t;
                moves++;
            }
        }
    }

    pair<int, vector<char> > res;
    res.first=moves;
    res.second=disks;
    return res;
}

int main(){
    int n;
    cout << "Enter n: ";
    cin >> n;

    pair<int, vector<char> > r = solveDisks(n);
    int moves=r.first;
    vector<char> finalState=r.second;

    cout << "Final arrangement: ";
    for(size_t i=0;i<finalState.size();i++)
        cout<<finalState[i]<<" ";
    cout<<endl;

    cout << "Total moves: " << moves << endl;
    cout << "Expected (n^2): " << n*n << endl;

    return 0;
}
