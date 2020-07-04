#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cin;
using std::string;
using std::vector;

class Node
{
public:
    string str_;
    Node *next_;

    Node() : str_(""), next_(NULL) {}
    Node(string s) : str_(s), next_(NULL) {}
    ~Node();
};

class LinkedList
{
public:
    Node *head_;
    LinkedList() : head_(NULL) {}
    ~LinkedList();

    void AddFront(string s)
    {
        string found = Find(s);
        if (found.compare("yes") == 0)
            return;
        Node *n = new Node(s);
        if (head_ == NULL)
        {
            head_ = n;
        }
        else
        {
            n->next_ = head_;
            head_ = n;
        }
    }

    string Find(string s)
    {
        Node *current_node = head_;
        while (current_node != NULL)
        {
            if (s.compare(current_node->str_) == 0)
            {
                return "yes";
            }
            current_node = current_node->next_;
        }
        return "no";
    }

    void Delete(string s)
    {
        if (head_ == NULL)
            return;
        if (s.compare(head_->str_) == 0)
        {
            Node *temp = new Node();
            temp = head_;
            head_ = head_->next_;
            free(temp);
        }
        else
        {
            Node *current_node = new Node();
            Node *previous_node = new Node();
            previous_node = head_;
            current_node = head_->next_;
            while (current_node != NULL)
            {
                if (s.compare(current_node->str_) == 0)
                {
                    previous_node->next_ = current_node->next_;
                    free(current_node);
                    return;
                }
                previous_node = current_node;
                current_node = current_node->next_;
            }
        }
    }

    void PrintList()
    {
        Node *temp = new Node();
        temp = head_;
        while (temp != NULL)
        {
            std::cout << temp->str_ << " ";
            temp = temp->next_;
        }
        std::cout << std::endl;
        free(temp);
    }
};

struct Query
{
    string type, s;
    size_t ind;
};

class QueryProcessor
{
    int bucket_count;
    // store all strings in one vector
    vector<string> elems;
    vector<LinkedList *> hash_map;
    size_t hash_func(const string &s) const
    {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count) : bucket_count(bucket_count)
    {
        for (size_t i = 0; i < bucket_count; ++i)
        {
            LinkedList *ll = new LinkedList();
            hash_map.push_back(ll);
        }
    }

    Query readQuery() const
    {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const
    {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query &query)
    {
        int hash_index = hash_func(query.s);
        if (query.type == "check")
        {
            // use reverse order, because we append strings to the end
            // for (int i = static_cast<int>(elems.size()) - 1; i >= 0; --i)
            //     if (hash_func(elems[i]) == query.ind)
            //         std::cout << elems[i] << " ";
            // std::cout << "\n";
            hash_map[query.ind]->PrintList();
        }
        else
        {
            vector<string>::iterator it = std::find(elems.begin(), elems.end(), query.s);
            if (query.type == "find")
            {
                // writeSearchResult(it != elems.end());
                std::cout << hash_map[hash_index]->Find(query.s) << std::endl;
            }
            else if (query.type == "add")
            {
                // if (it == elems.end())
                //     elems.push_back(query.s);
                hash_map[hash_index]->AddFront(query.s);
            }
            else if (query.type == "del")
            {
                // if (it != elems.end())
                //     elems.erase(it);
                hash_map[hash_index]->Delete(query.s);
            }
        }
    }

    void processQueries()
    {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    int x;
    std::cin >> x;
    return 0;
}
