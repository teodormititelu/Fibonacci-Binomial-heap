#include <iostream>
#include <fstream>

using namespace std;

const int NMAX = 500000;
const int INF = 2000000001;

ifstream fin("heap.in");
ofstream fout("heap.out");

struct node{
    int key;
    node *child, *sibling;

    node( int x ) : key( x ), child( NULL ), sibling( NULL ) {}
};

class pairing_heap{

    node *root;

    node* merge_heap( node* H1, node* H2 ){

        if( H1 == NULL ){
            H1 = H2;
            return H1;
        }
        if( H2 == NULL ) return H1;

        if( H1 -> key < H2 -> key )
            swap( H1, H2 );

        H2 -> sibling = H1 -> child;
        H1 -> child = H2;

        return H1;
    }

    node* two_pass_merge( node *_node ){

        if( _node == NULL || _node -> sibling == NULL )
            return _node;

        node *heap_1, *heap_2, *next_pair;

        heap_1 = _node;
        heap_2 = _node -> sibling;
        next_pair = _node -> sibling -> sibling;

        heap_1 -> sibling = heap_2 -> sibling = NULL;

        return merge_heap( merge_heap( heap_1, heap_2 ), two_pass_merge( next_pair ) );
    }
public:

    pairing_heap() : root( NULL ) {}

    pairing_heap( int _key ){
        root = new node( _key );
    }

    pairing_heap( node* _node ) : root( _node ) {}

    int top(){
        return root -> key;
    }

    void merge_heap( pairing_heap H ){

        if( root == NULL ){
            root = H.root;
            return;
        }
        if( H.root == NULL ) return;

        if( root -> key < H.root -> key )
            swap( root, H.root );

        H.root -> sibling = root -> child;
        root -> child = H.root;
        H.root = NULL;
    }

    void push( int _key ){
        merge_heap( pairing_heap( _key ) );
    }

    void pop(){

        node* temp = root;
        root = two_pass_merge( root -> child );

        delete temp;
    }

    void heap_union( pairing_heap &H ){
        merge_heap( H );
        H.root = NULL;
    }
};

int N;

pairing_heap Heap[NMAX];

int main()
{
    fin >> N;

    int task, h, x, h1, h2;
    for( int i = 1; i <= N; ++i ){

        fin >> task;//cout << i << '\n';

        if( task == 1 ){
            fin >> h >> x;

            Heap[h].push( x );
        }
        if( task == 2 ){
            fin >> h; //cout << Heap[h].top();

            fout << h << ": " << Heap[h].top() << '\n';
            Heap[h].pop();
        }
        if( task == 3 ){
            fin >> h1 >> h2;

            Heap[h1].heap_union( Heap[h2] );
        }
    }
    return 0;
}
