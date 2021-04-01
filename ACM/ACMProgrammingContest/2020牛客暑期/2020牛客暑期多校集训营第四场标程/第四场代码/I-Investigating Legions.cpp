#include<bits/stdc++.h>
#define N 305
using namespace std;

int n, S, be[N], fa[N];
int a[N][N];
char str[N*N]; 

template <class T>
struct SymMatrix {
    int n;
    std::vector<T> data;
	//T *data;
	
    SymMatrix() {};
    ~SymMatrix() {}; 
    void init(int n, T value) { 
		this->n = n; 
		data = std::vector<T>((n*n+n)/2, value);
		//data = new T[(n*n+n)/2];
		//for (size_t i = 0; i < (n*n+n)/2; i++) data[i] = value;
	};
    int size() {return n;}
    
    size_t getIndex(size_t i, size_t j) {
        size_t sm = std::min(i,j);
        size_t lg = std::max(i,j);
        return (lg+1)*lg/2 + sm;
    };

    T get(size_t i, size_t j) {
        size_t idx = getIndex(i,j);
        T value = data[idx];
        return value;
    };

    void set(size_t i, size_t j, T value) {
        size_t idx = getIndex(i,j);
        data[idx] = value;
    };
    
    void setAll(T value) {
        data.clear();
        data = std::vector<T>((n*n+n)/2, value);
        //if (data == nullptr) data = new T[(n*n+n)/2];
		//for (size_t i = 0; i < (n*n+n)/2; i++) data[i] = value;
    };
};


struct Params {
    int iteration;
    vector<list<int>> neighbors;
    SymMatrix<float> energy_pos;
    SymMatrix<float> energy_neg;
    SymMatrix<bool> sign;
    SymMatrix<bool> update;
    vector<vector<bool>> updated;
    int num_update;
    double loss;
};

/*main iteration*/
inline float addEnergy(int i, int j, int k, SymMatrix<float> &energy_pos,SymMatrix<float> &energy_neg, float &ep_temp, float &en_temp) {
	//this step is what is said in paper: do not appear the situation like (1,1,0)
	
	//for (i,j) = 1, do not appear (1,0,1), so calculate (1,0,0) and (1,1,1)
	ep_temp += std::min(energy_pos.get(i,k) + energy_pos.get(j,k),
						energy_neg.get(i,k) + energy_neg.get(j,k));
	//for (i,j) = 0, do not appear (0,1,1), so calculate (0,0,0), (0,0,1) and (0,1,0)
	en_temp += std::min(std::min(energy_pos.get(i,k) + energy_neg.get(j,k), 
						energy_neg.get(i,k) + energy_pos.get(j,k)), 
						energy_neg.get(i,k) + energy_neg.get(j,k));
}

// for each pair of (i,j), enumerate k and calculate energy_pos_new and energy_neg_new for (i,j)
inline void computeElement(int i, int j, vector<list<int>> &neighbors,
                    SymMatrix<float> &energy_pos, SymMatrix<float> &energy_neg,
                    list<int> &neighbor_pos, list<int> &neighbor_neg,
                    float &energy_pos_new, float &energy_neg_new) {

	int active_edge = 0;
    float ep_temp=0, en_temp=0;
    neighbor_neg.clear(); // the vertex near both a and b
    neighbor_pos.clear(); // the vertex near one of a and b
    list<int>::iterator a = neighbors[i].begin();
    list<int>::iterator b = neighbors[j].begin();
	
	//try to find a vertex k near a or b
    while (!(a == neighbors[i].end() && b == neighbors[j].end())) {
        if (a != neighbors[i].end() && *a == j) {
            a++;
            continue;
        } 
		if (b != neighbors[j].end() && *b == i) { 
            b++;
            continue;
        }
        if (a != neighbors[i].end() && b != neighbors[j].end() && *a == *b) {
            addEnergy(i, j, *a, energy_pos, energy_neg, ep_temp, en_temp);
			active_edge++;
            neighbor_pos.push_back(*a);
            a ++;
            b ++;
        } else if (a != neighbors[i].end() && (b == neighbors[j].end() || *a < *b)) {
            addEnergy(i, j, *a, energy_pos, energy_neg, ep_temp, en_temp);
            neighbor_neg.push_back(*a);
			active_edge++;
            a ++;
        } else {
            addEnergy(i, j, *b, energy_pos, energy_neg, ep_temp, en_temp);
            neighbor_neg.push_back(*b);
			active_edge++;
            b ++;
        }
    }
	//normalize
    energy_pos_new = (ep_temp) / energy_pos.size();
    energy_neg_new = (en_temp) / energy_neg.size();
	
	// iterative result : own_edge = 1 : 1
	int alpha = energy_pos.size(), beta = active_edge;
	energy_pos_new = (energy_pos_new * alpha + energy_pos.get(i, j) * beta) / (alpha + beta);
	energy_neg_new = (energy_neg_new * alpha + energy_neg.get(i, j) * beta) / (alpha + beta);
}

inline void insertUpdate(SymMatrix<bool> &update, int i, int j) {
    // int mmin = std::min(i,j);
    // int mmax = std::max(i,j);
    update.set(i, j, true);
}

struct Mapper {
    Params *params;
    Params *params_new;

    Mapper(Params *params_pt, Params *params_new_pt){
        params = params_pt;
        params_new = params_new_pt;
    }

    void solve(){
        int n = params_new->energy_pos.size();
        double loss = 0;
        int num_update = 0;
        list<int>::iterator a;
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                if (!params->update.get(i, j)) continue;	// (i,j) is stable
                if (params->neighbors[i].empty() && params->neighbors[j].empty()) continue;		//no such k in triple cycle
				
				// (i,j) has been updated before, just update edges.
                if (params_new->updated[j][i]) {
                    bool Q_old = params->sign.get(i,j);
                    bool Q_new = params_new->sign.get(i,j);
                    if (Q_new!=Q_old && Q_new) {
                        // add connectivity
                        a = params_new->neighbors[i].begin();
                        while (a!=params_new->neighbors[i].end() && *a < j) a++;
                        params_new->neighbors[i].insert(a,j);
                    }
                    else if (Q_new!=Q_old && !Q_new) {
                        // delete connectivity
                        params_new->neighbors[i].remove(j);
                    }    
                    continue;
                }

                num_update ++;
                float ep, en;
                list<int> neighbor_pos, neighbor_neg;
				
				// calculate ep and en, update neighbor_pos and neighbor_neg
                computeElement(i, j, params->neighbors, params->energy_pos, params->energy_neg,
                            neighbor_pos, neighbor_neg, ep, en);
                bool Q_old = params->sign.get(i,j);
                bool Q_new = Q_old;
                if (ep < en) Q_new = true;
                else if (en < ep) Q_new = false;
				
				// the status of (i,j) is reversed, so the neighbor must get updated
                if (Q_old != Q_new) {
                    if (Q_new) {
                        // add connectivity 
                        params_new->sign.set(i, j, true);
                        a = params_new->neighbors[i].begin();
                        while (a!=params_new->neighbors[i].end() && *a < j) a++;
                        params_new->neighbors[i].insert(a,j);
                    } else {
                        params_new->sign.set(i, j, false);
                        // delete connectivity
                        params_new->neighbors[i].remove(j);
                    }
                    for (a = neighbor_neg.begin(); a != neighbor_neg.end(); a++) {
                        insertUpdate(params_new->update, i, *a);
                        insertUpdate(params_new->update, j, *a);
                    }
                    for (a = neighbor_pos.begin(); a != neighbor_pos.end(); a++) {
                        insertUpdate(params_new->update, i, *a);
                        insertUpdate(params_new->update, j, *a);
                    }
                }
				
				//calculate loss
                if (Q_old && neighbor_neg.size() > 0){
                    loss += neighbor_neg.size();
                } else if (!Q_old && neighbor_pos.size() > 0){
                    loss += neighbor_pos.size();
                }
                if (Q_new && neighbor_neg.size() > 0 ||
                    !Q_new && neighbor_pos.size() > 0){
                    insertUpdate(params_new->update, i, j);
                }
                params_new->energy_pos.set(i, j, ep);
                params_new->energy_neg.set(i, j, en);
                params_new->updated[i][j] = true;
            }
        }
        params_new->loss += loss;
        params_new->num_update += num_update;
        return;
    }
};

void initializeUpdate(Params *params) {
    list<int>::iterator a,b;
    for (size_t i = 0; i < n; i++) {
        for (a=params->neighbors[i].begin(); a!=params->neighbors[i].end(); a++) {
            b = a;
            b ++;
            for (; b!=params->neighbors[i].end(); b++)
                insertUpdate(params->update, *a, *b);
            insertUpdate(params->update, i, *a);
        }
    }
}

int get(int x){
	return fa[x] == x ? x : fa[x] = get(fa[x]);
}

void doIteration()
{
	Params params;
	params.neighbors.resize(n);
	params.energy_pos.init(n, 0);
	params.energy_neg.init(n, 0);
	params.sign.init(n, false);
	params.update.init(n, false);
	
	for (size_t i = 0; i < n; i++)
		for (size_t j = i; j < n; j++){
			double t = 1.0 / S;
			if (a[i][j]) t = 1.0 - t;
			float ep = -log(t / (1.0 - t)), en = 0;	
			//use probability-matrix[i][j] to initial
			params.energy_pos.set(i, j, ep);
			params.energy_neg.set(i, j, en);
			if (i!=j) {
				if (ep<=en) {
					//link all edges which are active at the first time
					params.neighbors[i].push_back(j);
					params.neighbors[j].push_back(i);
					params.sign.set(i, j, true);
				}
			}
		}
	
    initializeUpdate(&params);
    Params params_alt = params;

    /* iterated update */
    int iteration = 0, max_iter = 10;
    bool exchange = false;
    Params *params_result;
    while (iteration==0 || iteration < max_iter && params_alt.loss != params.loss) {
		
        Mapper mapper(&params, &params_alt);
        *(mapper.params) = *(mapper.params_new);
		
        mapper.params_new->loss = 0;
        mapper.params_new->num_update = 0;
        mapper.params_new->update.setAll(false);
        mapper.params_new->updated = vector<vector<bool> >(n, vector<bool>(n, false));

        mapper.solve();
		
		//output some information in this round
        //fprintf(stderr, "iteration: %d updated: %d loss: %f \n", iteration, mapper.params_new->num_update, mapper.params_new->loss);
        
        params_result = mapper.params_new;
        iteration ++;
        params.iteration = params_alt.iteration = iteration;
        exchange = !exchange;
    }
	
	//simply use DSU to get the final result
	int ID[n];
	for (int i = 0; i < n; i++) ID[i] = -1;
	for (int i = 0; i < n; i++) fa[i] = i;
	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++)
			if (params_result->sign.get(i, j))
				fa[get(j)] = get(i);
	int number = 0;
	for (int i = 0; i < n; i++){
		get(i);
		if (ID[fa[i]] == -1)
			ID[fa[i]] = number++;
	}
	for (int i = 0; i < n; i++)
		fa[i] = ID[fa[i]];
	
	int adjust = 1;
	while (adjust){
		int num[number];
		adjust = 0;
		for (int i = 0; i < n && !adjust; i++){
			memset(num, 0, sizeof(num));
			for (int j = 0; j < n; j++)
				num[fa[j]] += a[i][j];
			int k = fa[i];
			for (int j = 0; j < number; j++)
				if (num[j] > num[k]) k = j;
			//printf("%d %d\n", i, k);
			if (k != fa[i]){
				fprintf(stderr, "adjust!!! %d %d %d %d!!!\n", number, fa[i], num[fa[i]],num[k]);
				fa[i] = k;
				adjust = 1;
				break;
			}
		}
	}
}

int main(){
	//freopen("7.in","r",stdin);
	//freopen("7.out","w",stdout);
	int T;
	scanf("%d",&T);
	while (T--){
		scanf("%d%d", &n, &S);
		scanf("%s", str);
		int cnt = 0;
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
				a[i][j] = a[j][i] = str[cnt++] - '0';
		for (int i = 0; i < n; i++)
			a[i][i] = 1;
		//printf("%d %d\n", n, S);
		doIteration();
		for (int i = 0; i < n; i++)
			printf("%d%c", fa[i], i == n-1 ? '\n' : ' '); 
	}
}