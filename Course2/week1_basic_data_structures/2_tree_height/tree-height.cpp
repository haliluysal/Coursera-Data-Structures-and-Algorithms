#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

class Node;

class Node
{
public:
    int key;
    Node *parent;
    std::vector<Node *> children;

    Node()
    {
        this->parent = NULL;
    }

    void setParent(Node *theParent)
    {
        parent = theParent;
        parent->children.push_back(this);
    }
};

int main_with_large_stack_space()
{
    std::ios_base::sync_with_stdio(0);
    int n;
    std::cin >> n;
    if (n < 1)
    {
        return 0;
    }

    std::vector<Node> nodes;
    nodes.resize(n);
    int root_index = -1;
    for (int child_index = 0; child_index < n; child_index++)
    {
        int parent_index;
        std::cin >> parent_index;
        if (parent_index >= 0)
        {
            nodes[child_index].setParent(&nodes[parent_index]);
        }
        else
        {
            root_index = child_index;
        }
        nodes[child_index].key = child_index;
    }

    std::vector<int> heights(nodes.size(), 1);

    int number_of_visited_nodes = 1;
    std::stack<Node> parent_stack;
    parent_stack.push(nodes[root_index]);
    while (!parent_stack.empty())
    {
        Node prnt = parent_stack.top();
        parent_stack.pop();
        for (size_t i = 0; i < prnt.children.size(); ++i)
        {
            heights[prnt.children[i]->key] = 1 + heights[prnt.key];
            parent_stack.push(*prnt.children[i]);
        }
    }
    

    // int maxHeight = 0;
    // for (int leaf_index = 0; leaf_index < n; leaf_index++)
    // {
    //     int height = 0;
    //     for (Node *v = &nodes[leaf_index]; v != NULL; v = v->parent)
    //         height++;
    //     maxHeight = std::max(maxHeight, height);
    // }
    int max_height = -1;
    for (size_t i = 0; i < heights.size(); i++)
    {
        if (max_height < heights[i])
        {
            max_height = heights[i];
        }
    }

    std::cout << max_height << std::endl;
    int x = 0;
    std::cin >> x;
    return 0;
}

int main(int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
    // Allow larger stack space
    const rlim_t kStackSize = 16 * 1024 * 1024; // min stack size = 16 MB
    struct rlimit rl;
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0)
    {
        if (rl.rlim_cur < kStackSize)
        {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0)
            {
                std::cerr << "setrlimit returned result = " << result << std::endl;
            }
        }
    }

#endif
    return main_with_large_stack_space();
}
