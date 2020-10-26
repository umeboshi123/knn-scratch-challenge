#include <bits/stdc++.h>
#define rep(i, a, b) for (ll i = ll(a); i < ll(b); i++)
#define eb emplace_back
#define pll pair<ll, ll>
using ll = long long;
using namespace std;

vector<tuple<ll, ll, ll>> t; //学習パターンの (x座標,y座標,クラス)
vector<pll> s;               //テストパターンと各学習パターンの点の　(距離,学習パターンのクラス)
ll cl[100];                  //k番目までの最短距離に含まれるクラスナンバ－の管理
vector<pll> cl2;             //clをcl2に(含まれた数、クラスナンバー)として格納。のちにvalueでソート
int main()
{
    ll n, m, k, x, y, z;
    cout << "input Number of train patern" << endl;
    cin >> n; //学習パターン数
    cout << "inmput train paterns (x,y,class)*N" << endl;
    rep(i, 0, n)
    {
        cin >> x >> y >> z;
        t.eb(x, y, z); //タプルtに学習パターン(x座標,y座標,クラス)を格納
    }
    cout << "input Number k" << endl;
    cin >> k; //kNNのk=
    cout << "input Number of test paterns" << endl;
    cin >> m; //テストパターン数

    rep(i, 0, m)
    { //それぞれのテストパターンは独立に行う
        cout << "input test patern (x,y)" << endl;
        cin >> x >> y; //テストパターンの座標
        rep(j, 0, n)
        {
            //学習パターンとテストパターンの距離計算
            ll dis = pow((x - get<0>(t[j])), 2) + pow((y - get<1>(t[j])), 2);
            s.eb(dis, get<2>(t[j])); //(距離,クラス)としてpair型sに格納
        }
        sort(s.begin(), s.end()); //距離の小さい順にソート
        ll pos = min(k, n);       //もしk>nの場合、k=nとする
        pll m0 = s[pos - 1];      //小さい順からpos(=k)番目の点の情報(距離,クラス)
        rep(j, 0, 100) cl[j] = 0; //clはここで初期化

        rep(j, 0, pos) cl[s[j].second]++;         //距離の小さいものからpos(=k)番目を配列clに格納

        while (m0.first == s[pos].first && pos < n)//k番目以降も、k番目と同じ距離の可能性=考慮すべき点として格納
        {
            cl[s[pos].second]++;
            pos++;
        }

        rep(j, 0, 100)cl2.eb(cl[j], j);
        //cl2にpairとして詰めることで、value(k番目までの最短距離の点の数)でソートし、頻出のクラスを取り出せる
        sort(cl2.rbegin(), cl2.rend());

        if (cl2[1].first >= ceil(k/2.0) || (cl2[0].first == cl2[1].first))
            cout << 0 << endl;//45行のwhileにより、cl2[0]がkを超えたり,cl2[1]がkの半分以上になったりする可能性
        else
            cout << cl2[0].second << endl;

        s.clear();
        cl2.clear();
    }
}