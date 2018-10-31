/* * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  A SIMPLE & COMPACT TRIE CLASS W/O DEPENDENCIES   *
 *                  (C++11 required)                 *
 * Tp = type, RANGE = # of possible adjacent values  *
 *                                                   *
 *             by Kostas Tsiampouris                 *        
 * * * * * * * * * * * * * * * * * * * * * * * * * * */

template<class Tp, int RANGE, int MIN_VAL = 0, class Iter = typename Tp::iterator >
class Trie {
        struct Node {
                bool insert(Iter fst, Iter last) {
                        if (fst == last) return endp++;
                        
                        Node *&next_ = next[*fst - MIN_VAL];
                        if (!next_) next_ = new Node;
                        return next_ -> insert(++fst, last);
                }
        
                bool find(Iter fst, Iter last) {
                        if (fst == last) return endp;

                        Node *&next_ = next[*fst - MIN_VAL];
                        return next_ && next_ -> find(++fst, last);
                }

                ~Node() {
                        for (int i = 0; i < RANGE; ++i)
                                delete next[i];
                }

                bool endp = false;
                Node *next[RANGE] = {nullptr};
        };
        Node *root = new Node;

public:
        // returns if element already in Trie
        bool insert(Iter fst, Iter last) { return root -> insert(fst, last); }
        bool find  (Iter fst, Iter last) { return root -> find  (fst, last); }

        bool insert(Tp &el) { return root -> insert(el.begin(), el.end()); } 
        bool find  (Tp &el) { return root -> find  (el.begin(), el.end()); }

        ~Trie() { delete root; }
};
