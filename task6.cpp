#include<iostream>
#include  <vector>
using namespace   std;

int weigh(const vector<int>&coins,int leftStart,int leftEnd,int rightStart ,int rightEnd){
    int leftSum=0;
    int rightSum = 0;
    for(int i=leftStart;i<=leftEnd;++i){
        leftSum+=coins[i];
    }
    for(int i = rightStart;i<=rightEnd;++i){
        rightSum+= coins[i];
    }
    if(leftSum==rightSum)return 0;
    return leftSum> rightSum?1: -1;
}

int locateBaseCases(const vector<int>&coins,int start,int end){
    int count=end-start+1;
    if(count==1){
        return start;
    }
    if(count==2){
        int result=weigh(coins,start,start,end,end);
        if(result==0)return start;
        return result==1? start:end;
    }
    return-1;
}

int locateRecursive(const vector<int>&coins,int start,int end){
    int base= locateBaseCases(coins,start,end);
    if(base!=-1){
        return base;
    }
    int count=end-start+1;
    int groupSize=count/3;
    int leftStart=start;
    int leftEnd=leftStart+groupSize-1;
    int middleStart= leftEnd+1;
    int middleEnd=middleStart+groupSize-1;
    int rightStart= middleEnd+1;
    int rightEnd=end;
    int result=weigh(coins,leftStart,leftEnd,middleStart,middleEnd);
    if(result==0){
        return locateRecursive(coins,rightStart,rightEnd);
    }else{
        return locateRecursive(coins,leftStart,middleEnd);
    }
}

int locateFakeCoin(const vector<int>&coins){
    if(coins.empty())return-1;
    return locateRecursive(coins,0,(int)coins.size()-1);
}

bool isFakeHeavier(const vector<int>&coins,int fakeIndex,int genuineIndex){
    int result=weigh(coins,fakeIndex,fakeIndex,genuineIndex,genuineIndex);
    return result==1;
}

int findGenuineReference(int fakeIndex,int n){
    if(n<=1)return-1;
    if(fakeIndex!=0)return 0;
    if(fakeIndex!=1&&n>1)return 1;
    return -1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if(!(cin>>n))return 0;
    vector<int> coins(n);
    for(int i=0;i<n;++i){
        cin>>coins[i];
    }
    int fakeIndex= locateFakeCoin(coins);
    if(fakeIndex<0||fakeIndex>=n){
        cout<<"No fake coin found\n";
        return 0;
    }
    int refIndex= findGenuineReference(fakeIndex,n);
    if(refIndex==-1){
        cout<<"Not enough coins for reference\n";
        return 0;
    }
    bool heavier= isFakeHeavier(coins,fakeIndex,refIndex);
    cout<<"Fake coin index: "<< fakeIndex<<'\n';
    if(heavier){
        cout<<"Fake coin is heavier\n";
    }else{
        cout<<"Fake coin is lighter\n";
    }
    return 0;
}
