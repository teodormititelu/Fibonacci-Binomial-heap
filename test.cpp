#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100001;

//ofstream fout("heap.in");
ofstream fout("test.out");

default_random_engine RandGenerator( time(0) );
uniform_int_distribution < int > random( 0, 2000000000 );

int N, M;
int ct[NMAX];

void Generate_test( int N ){

    fout << N << '\n';

    int task, h, x, h1, h2;
    for( int i = 1; i <= N; ++i ){
        task = random( RandGenerator ) % 3 + 1;

        if( task == 1 ){
            h = random( RandGenerator ) % M + 1;
            x = random( RandGenerator );

            ct[h]++;

            fout << task << ' ' << h << ' ' << x << '\n';
        }
        if( task == 2 ){
            h = random( RandGenerator ) % M + 1;

            if( ct[h] ){
                ct[h]--;
                fout << task << ' ' << h << '\n';
            }
            else i--;
        }
        if( task == 3 ){
            h1 = random( RandGenerator ) % M + 1;
            h2 = random( RandGenerator ) % M + 1;

            if( h1 == h2 ){
                i--;
                continue;
            }

            fout << task << ' ' << h1 << ' ' << h2 << '\n';
            ct[h1] += ct[h2];
            ct[h2] = 0;
        }
    }
}

int main()
{
    ///number of tasks/ number of heaps
    cin >> N >> M;
    
    Generate_test( N );
    return 0;
}
