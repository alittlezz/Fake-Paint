#include <bits/stdc++.h>
using namespace std;
#define ll long long

int vote[200005];
int n;

double getNeed(double x){
    if((double)1 / n * 100 >= 1.0){
        for(int i = 1;;i++){
            int intreg = (int)((x + (double)i / n * 100) * 100)%100;
            if(intreg >= 50){
                return i;
            }
        }
    }
    int per = (int)(x * 100) % 100;
    int need = 0;
    if(per >= 50){
        need += 100 - per;
        per = 0;
    }
    need += 50 - per;
    return (double)need  * n / 10000;
}

int main(){
    int T;
    cin >> T;
    for(int t = 1;t <= T;t++){
        cout << "Case #" << t << ": ";
        int ans = 0;
        int l;
        cin >> n >> l;
        int have = 0;
        priority_queue <pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        for(int i = 1;i <= l;i++){
            cin >> vote[i];
            double cr = (double)vote[i] / n * 100;
            ans += round(cr);
            double need = getNeed(cr);
            pq.push({ceil(need), i});
            have += vote[i];
        }
        for(int i = 1;i <= n;i++){
            double need = getNeed(0);
            pq.push({ceil(need), i + n});
        }
        while(have < n){
            int need = pq.top().first;
            int id = pq.top().second;
            pq.pop();
            if(have + need > n){
                need = n - have;
            }
            ans -= round((double)vote[id] / n * 100);
            vote[id] += need;
            double cr = (double)vote[id] / n * 100;
            ans += round(cr);
            pq.push({getNeed(cr), id});
            have += need;
        }
        cout << ans << '\n';
        memset(vote, 0, sizeof(vote));
    }
    return 0;
}
