#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

using std::cin;
using std::string;
using std::vector;

// individual phone record
struct record
{
    string name_ = "temp";
    int number_ = -1;
};

class Node
{
public:
    record rec_;
    Node *next_;

    Node() : next_(NULL)
    {
    }
    Node(record rec) : rec_(rec), next_(NULL)
    {
    }
    ~Node();
    void PrintNode()
    {
        std::cout << "Node contains: "
                  << "Name: " << rec_.name_ << " Number: " << rec_.number_ << " Next Pointer: " << next_ << std::endl;
    }
};

class LinkedList
{
private:
public:
    Node *head_;
    LinkedList()
    {
        head_ = NULL;
    }

    ~LinkedList();

    void PrintLinkedList()
    {
        Node *current_node = head_;
        while (current_node != NULL)
        {
            current_node->PrintNode();
            current_node = current_node->next_;
        }
    }

    void PushFront(record rec)
    {
        Node *n = new Node(rec);
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

    Node *Find(int number)
    {
        Node *current_node = head_;
        while (current_node != NULL)
        {
            if (current_node->rec_.number_ == number)
            {
                return current_node;
            }
            current_node = current_node->next_;
        }
        return NULL;
    }

    void Delete(int number)
    {
        if (head_->rec_.number_ == number)
        {
            Node *temp = new Node();
            temp = head_;
            head_ = head_->next_;
            free(temp);
        }
        else
        {
            Node *previous_node = head_;
            Node *current_node = head_->next_;
            while (current_node != NULL)
            {
                if (current_node->rec_.number_ == number)
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
};

class PhoneBook
{
private:
    vector<LinkedList *> book_;
    long long a_, b_, p_ = 100000229;
    int table_size_ = 4;
    int n_keys_ = 0;
    float load_factor = 0.0;

    void ResizePhoneBook(vector<LinkedList *> &b)
    {
        for (size_t i = 0; i < table_size_; ++i)
        {
            LinkedList *ll = new LinkedList();
            b.push_back(ll);
        }
    }

    int Hash(int num)
    {
        return ((a_ * num + b_) % p_) % table_size_;
    }

    void Rehash()
    {
        vector<LinkedList *> new_book;
        table_size_ *= 2;
        load_factor = (float)n_keys_ / table_size_;
        ResizePhoneBook(new_book);

        for (LinkedList *ll : book_)
        {
            Node *current_node = ll->head_;
            while (current_node != NULL)
            {
                int hashing_index = Hash(current_node->rec_.number_);
                new_book[hashing_index]->PushFront(current_node->rec_);
                current_node = current_node->next_;
            }
        }
        book_ = new_book;
    }

public:
    PhoneBook()
    {
        a_ = std::rand() % p_;
        b_ = std::rand() % p_;
        ResizePhoneBook(book_);
    }

    void Add(string name, int number)
    {
        record rec;
        rec.name_ = name;
        rec.number_ = number;
        int hashing_index = Hash(rec.number_);
        Node *found = book_[hashing_index]->Find(rec.number_);
        if (found == NULL)
        {
            book_[hashing_index]->PushFront(rec);
            n_keys_++;
        }
        else
        {
            found->rec_.name_ = rec.name_;
        }
        load_factor = (float)n_keys_ / table_size_;
        if (load_factor > 0.7)
        {
            Rehash();
        }
    }

    string Find(int number)
    {
        int hashing_index = Hash(number);
        Node *found = book_[hashing_index]->Find(number);
        if (found == NULL)
        {
            return "not found";
        }
        else
        {
            return found->rec_.name_;
        }
    }

    void Delete(int number)
    {
        int hashing_index = Hash(number);
        Node *found = book_[hashing_index]->Find(number);
        if (found != NULL)
        {
            book_[hashing_index]->Delete(number);
        }
    }

    ~PhoneBook();
};

struct Query
{
    string type, name;
    int number;
};

vector<Query> read_queries()
{
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string> &result)
{
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query> &queries)
{
    vector<string> result;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    PhoneBook *new_phone = new PhoneBook();
    vector<Query> contacts;
    for (size_t i = 0; i < queries.size(); ++i)
    {
        if (queries[i].type == "add")
        {
            new_phone->Add(queries[i].name, queries[i].number);
            // bool was_founded = false;
            // // if we already have contact with such number,
            // // we should rewrite contact's name
            // for (size_t j = 0; j < contacts.size(); ++j)
            //     if (contacts[j].number == queries[i].number)
            //     {
            //         contacts[j].name = queries[i].name;
            //         was_founded = true;
            //         break;
            //     }
            // // otherwise, just add it
            // if (!was_founded)
            //     contacts.push_back(queries[i]);
        }
        else if (queries[i].type == "del")
        {
            new_phone->Delete(queries[i].number);
            // for (size_t j = 0; j < contacts.size(); ++j)
            //     if (contacts[j].number == queries[i].number)
            //     {
            //         contacts.erase(contacts.begin() + j);
            //         break;
            //     }
        }
        else
        {
            // string response = "not found";
            // for (size_t j = 0; j < contacts.size(); ++j)
            //     if (contacts[j].number == queries[i].number)
            //     {
            //         response = contacts[j].name;
            //         break;
            //     }
            result.push_back(new_phone->Find(queries[i].number));
        }
    }
    return result;
}

int main()
{
    write_responses(process_queries(read_queries()));
    return 0;
}
