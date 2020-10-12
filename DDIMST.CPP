#include<bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3")
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("unroll-loops")
int n;
int DIM;
auto clk=clock();

/**
 * CODE TEMPLATE taken from https://github.com/AndrewB330/EuclideanMST/blob/master
 */

template<size_t DIM>
class Point {

public:
    Point();

    const long long int & operator[](size_t i) const;
    long long int & operator[](size_t i);

    /**
     * Distance between two points
     */
    template<size_t DIM_>
    friend long long int distance(const Point<DIM_> & a, const Point<DIM_> & b);

private:
    long long int data[DIM];
};

/**
 * Point with id
 */
template<size_t DIM>
class UPoint : public Point<DIM> {
public:

    UPoint(const Point<DIM> & ref, size_t id = 0);
    UPoint(size_t id = 0);

    size_t get_id() const;

private:
    size_t id;
};

/**
 * Bounding box in DIM-dimensional space
 */
template<size_t DIM>
class AABB {
public:
    AABB();
    /**
     * Construct bounding box from vector iterator
     */
    AABB(typename std::vector<UPoint<DIM>>::const_iterator iter, typename std::vector<UPoint<DIM>>::const_iterator end);

    /**
     * Size of the k-th dimension
     */
    long long int size(size_t k) const;

    /**
     * Get the index of a dimension with the largest size
     */
    size_t get_largest_dim() const;

    /**
     * Distance between two bounding boxes
     */
    template<size_t DIM_>
    friend long long int distance(const AABB<DIM_> & a, const AABB<DIM_> & b);

private:
    Point<DIM> minimal;
    Point<DIM> maximal;
};

// Implementation

template<size_t DIM>
Point<DIM>::Point() {
    std::fill(data, data + DIM, 0.0);
}

template<size_t DIM>
const long long int & Point<DIM>::operator[](size_t i) const {
    return data[i];
}

template<size_t DIM>
long long int &  Point<DIM>::operator[](size_t i) {
    return data[i];
}

template<size_t DIM>
UPoint<DIM>::UPoint(const Point<DIM> & ref, size_t id) : Point<DIM>(ref), id(id) {}

template<size_t DIM>
UPoint<DIM>::UPoint(size_t id) :id(id) {}

template<size_t DIM>
size_t UPoint<DIM>::get_id() const {
    return id;
}

template<size_t DIM>
AABB<DIM>::AABB() {}

template<size_t DIM>
AABB<DIM>::AABB(typename std::vector<UPoint<DIM>>::const_iterator iter, typename std::vector<UPoint<DIM>>::const_iterator end) {
    minimal = maximal = *iter;
    for (; iter != end; ++iter) {
        for (size_t k = 0; k < DIM; k++) {
            minimal[k] = std::min(minimal[k], (*iter)[k]);
            maximal[k] = std::max(maximal[k], (*iter)[k]);
        }
    }
}

template<size_t DIM>
long long int AABB<DIM>::size(size_t k) const {
    return maximal[k] - minimal[k];
}

template<size_t DIM>
size_t AABB<DIM>::get_largest_dim() const {
    size_t biggest_dim = 0;
    for (size_t k = 1; k < DIM; k++) {
        if (size(k) > size(biggest_dim))
            biggest_dim = k;
    }
    return biggest_dim;
}

template<size_t DIM>
long long int distance(const Point<DIM> & a, const Point<DIM> & b) {
    long long int distance_sqr = 0;
    for (size_t k = 0; k < DIM; k++) {
        long long int diff = a[k] - b[k];
        distance_sqr += abs(diff);
    }
    return -distance_sqr;
}

template<size_t DIM>
long long int distance(const AABB<DIM> & a, const AABB<DIM> & b) {
    long long int distance_sqr = 0;
    for (size_t k = 0; k < DIM; k++) {
        long long int diff = std::max(a.minimal[k], b.minimal[k]) - std::min(a.maximal[k], b.maximal[k]);
        if (diff > 0) {
            distance_sqr += abs(diff);
        }
    }
    return -distance_sqr;
}



template<size_t DIM>
struct KdTree {
public:
    KdTree();
    /**
     * Construct K-d tree with height at most max_height from a given set of points
     */
    KdTree(const std::vector<Point<DIM>> & points, size_t max_height);

    size_t get_root_id() const;
    size_t get_maximal_id() const;
    size_t get_left_child_id(size_t id) const;
    size_t get_right_child_id(size_t id) const;
    const AABB<DIM> & get_bounding_box(size_t id) const;
    bool is_leaf(size_t id) const;

    typename std::vector<UPoint<DIM>>::const_iterator points_begin(size_t node_id) const;
    typename std::vector<UPoint<DIM>>::const_iterator points_end(size_t node_id) const;

private:
    /**
     * K-d tree node. Represents part of space with points from (start) to (start+size-1) position in points array
     */
    struct KdNode {
        KdNode() : start(0), is_leaf(false), size(0) {}
        AABB<DIM> aabb;
        bool is_leaf; //is this node a leaf node and has no childs
        size_t start;
        size_t size;
    };
    /**
     * Recursively build tree for current node node_id, for points from position (start) to position (start+size-1)
     */
    void build(size_t node_id, size_t start, size_t size, size_t remaining_height);

    std::vector<UPoint<DIM>> points;
    std::vector<KdNode> nodes;
};

// Implementation

template<size_t DIM>
KdTree<DIM>::KdTree() {}

template<size_t DIM>
KdTree<DIM>::KdTree(const std::vector<Point<DIM>> & points, size_t max_height) {
    this->points.reserve(points.size());
    for (auto & p : points) {
        this->points.push_back(UPoint<DIM>(p, this->points.size()));
    }
    nodes.resize(points.size() * 4);
    build(1, 0, points.size(), max_height);
}

template<size_t DIM>
size_t KdTree<DIM>::get_root_id() const {
    return 1;
}

template<size_t DIM>
size_t KdTree<DIM>::get_maximal_id() const {
    return (nodes.empty() ? 0 : nodes.size() - 1);
}

template<size_t DIM>
size_t KdTree<DIM>::get_left_child_id(size_t id) const {
    return id * 2;
}

template<size_t DIM>
size_t KdTree<DIM>::get_right_child_id(size_t id) const {
    return id * 2 + 1;
}


template<size_t DIM>
bool KdTree<DIM>::is_leaf(size_t id) const {
    return nodes[id].is_leaf;
}

template<size_t DIM>
const AABB<DIM> & KdTree<DIM>::get_bounding_box(size_t id) const {
    return nodes[id].aabb;
}

template<size_t DIM>
typename std::vector<UPoint<DIM>>::const_iterator KdTree<DIM>::points_begin(size_t node_id) const {
    return points.begin() + nodes[node_id].start;
}

template<size_t DIM>
typename std::vector<UPoint<DIM>>::const_iterator KdTree<DIM>::points_end(size_t node_id) const {
    return points.begin() + nodes[node_id].start + nodes[node_id].size;
}

template<size_t DIM>
void KdTree<DIM>::build(size_t node_id, size_t start, size_t size, size_t remaining_height) {
    nodes[node_id].aabb = AABB<DIM>(points.cbegin() + start, points.cbegin() + start + size);
    nodes[node_id].start = start;
    nodes[node_id].size = size;

    if (size == 1 || remaining_height == 0) {
        nodes[node_id].is_leaf = true;
        return;
    }

    size_t biggest = nodes[node_id].aabb.get_largest_dim();

    std::nth_element(points.begin() + start, points.begin() + start + size / 2, points.begin() + start + size,
        [&biggest](const Point<DIM> & a, const Point<DIM> & b) {
        return a[biggest] < b[biggest];
    });

    // recursively call build for two parts
    build(node_id * 2, start, size / 2, remaining_height - 1);
    build(node_id * 2 + 1, start + size / 2, (size + 1) / 2, remaining_height - 1);
}



/**
 * Disjoint-set-union data structure
 */
class DSU {

public:

    DSU(size_t n = 0);

    size_t get_set(size_t x) const;
    bool is_in_same_set(size_t x, size_t y) const;

    void reset(size_t n);
    bool unite(size_t x, size_t y);

private:

    mutable std::vector<size_t> p;
    std::vector<size_t> rank;
};

// Implementation

DSU::DSU(size_t n) {
    reset(n);
}


size_t DSU::get_set(size_t x) const {
    return p[x] == x ? x : p[x] = get_set(p[x]);
}

bool DSU::is_in_same_set(size_t x, size_t y) const {
    return get_set(x) == get_set(y);
}

void DSU::reset(size_t n) {
    p.resize(n);
    rank.assign(n, 0);
    for (size_t i = 0; i < n; i++) {
        p[i] = i;
    }
}

bool DSU::unite(size_t x, size_t y) {
    size_t set_a = get_set(x);
    size_t set_b = get_set(y);
    if (set_a == set_b) {
        return false;
    }
    if (rank[set_a] > rank[set_b]) {
        std::swap(set_a, set_b);
    }
    if (rank[set_a] == rank[set_b]) {
        rank[set_b]++;
    }
    p[set_a] = set_b;
    return true;
}



typedef std::pair<size_t, size_t> Edge;

template<size_t DIM>
class EmstSolver {
public:
    EmstSolver() {}

    const std::vector<Edge> & get_solution() const { return solution; }
    const long long int & get_total_length() const { return total_length; }

protected:
    std::vector<Edge> solution;
    long long int total_length = 0;
};

/**
 * Implementation of EMST algorithm using K-d tree
 * "Fast Euclidean Minimum Spanning Tree: Algorithm, Analysis, and Applications. William B. March, Parikshit Ram, Alexander G. Gray"
 * Time complexity: O(cNlogN), extra constant c depends on the distribution of points
 */
template<size_t DIM>
class KdTreeSolver : public EmstSolver<DIM> {
public:
    KdTreeSolver(const std::vector<Point<DIM>> & points) :num_points(points.size()) {
        dsu.reset(num_points);
        tree = KdTree<DIM>(points, static_cast<size_t>(floor(log2(num_points)) - 1));
        is_fully_connected.assign(tree.get_maximal_id() + 1, false);
        solve();
        // todo: clear containers
    }

private:
    void solve() {
        auto & solution = EmstSolver<DIM>::solution;
        auto & total_length = EmstSolver<DIM>::total_length;

        while (solution.size() + 1 < num_points) {
            node_approximation.assign(tree.get_maximal_id() + 1, std::numeric_limits<long long int>::max());
            nearest_set.assign(num_points, { std::numeric_limits<long long int>::max(), Edge(0,0) });

            check_fully_connected(tree.get_root_id());

            find_component_neighbors(tree.get_root_id(), tree.get_root_id());

            for (size_t i = 0; i < num_points; i++) {
                if (i == dsu.get_set(i)) {
                    Edge e = nearest_set[i].second;
                    if (dsu.unite(e.first, e.second)) {
                        solution.push_back(e);
                        total_length += nearest_set[i].first;
                    }
                }
            }
        }
    }

    void find_component_neighbors(size_t q, size_t r, size_t depth = 0) {
        if (is_fully_connected[q] && is_fully_connected[r] &&
            dsu.is_in_same_set(tree.points_begin(q)->get_id(), tree.points_begin(r)->get_id())) {
            return;
        }
        if (distance(tree.get_bounding_box(q), tree.get_bounding_box(r)) > node_approximation[q]) {
            return;
        }
        if (tree.is_leaf(q) && tree.is_leaf(r)) {
            node_approximation[q] = 0.0;
            for (auto i = tree.points_begin(q); i != tree.points_end(q); i++) {
                for (auto j = tree.points_begin(r); j != tree.points_end(r); j++) {
                    if (!dsu.is_in_same_set(i->get_id(), j->get_id())) {
                        long long int dist = distance(*i, *j);
                        if (dist < nearest_set[dsu.get_set(i->get_id())].first) {
                            nearest_set[dsu.get_set(i->get_id())] = { dist, { i->get_id(), j->get_id() } };
                        }
                    }
                }
                node_approximation[q] = std::max(node_approximation[q], nearest_set[dsu.get_set(i->get_id())].first);
            }
        } else {
            size_t qleft = tree.get_left_child_id(q);
            size_t qright = tree.get_right_child_id(q);
            size_t rleft = tree.get_left_child_id(r);
            size_t rright = tree.get_right_child_id(r);
            if (tree.is_leaf(q)) {
                find_component_neighbors(q, rleft, depth);
                find_component_neighbors(q, rright, depth);
                return;
            }
            if (tree.is_leaf(r)) {
                find_component_neighbors(qleft, r, depth);
                find_component_neighbors(qright, r, depth);
                node_approximation[q] = std::max(node_approximation[qleft], node_approximation[qright]);
                return;
            }
            find_component_neighbors(qleft, rleft, depth + 1);
            find_component_neighbors(qleft, rright, depth + 1);
            find_component_neighbors(qright, rright, depth + 1);
            find_component_neighbors(qright, rleft, depth + 1);
            node_approximation[q] = std::max(node_approximation[qleft], node_approximation[qright]);
        }
    }

    void check_fully_connected(size_t node_id) {
        if (is_fully_connected[node_id]) {
            return;
        }
        if (tree.is_leaf(node_id)) {
            bool fully_connected = true;
            for (auto iter = tree.points_begin(node_id); iter + 1 != tree.points_end(node_id); ++iter) {
                fully_connected &= dsu.is_in_same_set(iter->get_id(), (iter + 1)->get_id());
            }
            is_fully_connected[node_id] = fully_connected;
            return;
        }
        size_t left = tree.get_left_child_id(node_id);
        size_t right = tree.get_right_child_id(node_id);
        check_fully_connected(left);
        check_fully_connected(right);
        if (is_fully_connected[left] && is_fully_connected[right] &&
            dsu.is_in_same_set(tree.points_begin(left)->get_id(), tree.points_begin(right)->get_id())) {
            is_fully_connected[node_id] = true;
        }
    }

    size_t num_points;
    DSU dsu;
    KdTree<DIM> tree;
    std::vector<bool> is_fully_connected;
    std::vector<long long int> node_approximation;
    std::vector<std::pair<long long int, Edge>> nearest_set;
};

template<size_t p>
void example(int n){
    DIM = p;
    vector<Point<p>> points(n);

    for (int i = 0; i < n; i++) {
        for (int k = 0; k < DIM; k++) {
            cin >> points[i][k];
        }
    }

    KdTreeSolver<p> solver_fast(points);
    cout << -1*solver_fast.get_total_length() << endl;
}
int main() {
#ifdef LOCAL 
    freopen("input.txt", "r", stdin);freopen("output.txt", "w", stdout);
#endif 
    ios_base::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);


    cin >> n >> DIM;
    if(DIM == 1)
        example<1>(n);
    if(DIM == 2)
        example<2>(n);
    if(DIM == 3)
        example<3>(n);
    if(DIM == 4)
        example<4>(n);
    if(DIM == 5)
        example<5>(n);

#ifdef LOCAL
	cerr<<"Time elapsed: "<<(double)(clock()-clk)/CLOCKS_PER_SEC<<"  seconds" << "\n";
#endif
    return 0;
}