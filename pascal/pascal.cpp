#include <bits/stdc++.h>
using namespace std;

class node{
public:
    bool covered = true;
    long long value = 0;
};

vector<pair<int,int>> path;

bool triangleWalker(vector<vector<node>>& triangle, long long target, long long currentVal, int x = 0, int y = 0){
    // printf("I am called: %d %d\n", x,y);
    if( x < 0 || y < 0 || x >= triangle.size() || y > x ){
        return false;
    }
    if(currentVal > target || triangle[x][y].covered){
        return false;
    }
    // printf("CurrentVal:%d,   MyVal:%d\n",currentVal,triangle[x][y].value);
    triangle[x][y].covered = true;
    if(triangle[x][y].value + currentVal == target){
        // clean your mess for next TC
        triangle[x][y].covered = false;

        path.push_back(make_pair(x,y));
        return true;
    }
    int ynew = y;
    if(x > 2*y){
        ynew = y+1;
    }

    if(
    // found || // already there
    //larger
    triangleWalker(triangle, target, currentVal + triangle[x][y].value, x+1, ynew) || 
    //equal
    triangleWalker(triangle, target, currentVal + triangle[x][y].value, x, y+1) || 
    triangleWalker(triangle, target, currentVal + triangle[x][y].value, x, y-1) || 
    //smaller
    triangleWalker(triangle, target, currentVal + triangle[x][y].value, x-1, y) || 
    triangleWalker(triangle, target, currentVal + triangle[x][y].value, x-1, y-1) 
    ){
        // clean your mess for next TC
        triangle[x][y].covered = false;

        path.push_back(make_pair(x,y));
        return true;
    }
    // if path does not succeed do not occupy nodes anymore 
    triangle[x][y].covered = false;
    return false;

}

int main(){
    ios_base::sync_with_stdio(false);

    int height = 64;
    vector<vector<node>> triangle(height, vector<node>(height) ); // create triangle

    // initialize triangle

    for(int i = 0; i < height; i++){
        for(int j = 0; j <= i; j++){
            if(i == j || j == 0){
                triangle[i][j].value = 1;
            }else{
                triangle[i][j].value = triangle[i-1][j-1].value + triangle[i-1][j].value;
            }
            triangle[i][j].covered = false;
            // printf("%lld ",triangle[i][j].value);
        }
        // printf("\n");
    }

    long long TC, target;
    scanf("%lld",&TC);
    for(long T = 0; T < TC; T++){
        scanf("%lld",&target);
        // triangle walk
        bool a = triangleWalker(triangle,target,0);
        // cout << a << endl;
        reverse(path.begin(),path.end());
        printf("Case #%d:\n",T+1);
        for(int i = 0; i < path.size(); i++){
            printf("%d %d\n",path[i].first+1,path[i].second+1);
        }
        path.clear();
        // for(int i = 0; i < height; i++){
        //     for(int j = 0; j <= i; j++){
        //         if(triangle[i][j].covered == true){
        //             printf("Clean your trace!!");
        //         }
        //     }
        // }
    }
    
    return 0;
}
