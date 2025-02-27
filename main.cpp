#include <iostream>

using namespace std;

///Structure to collect  pair of integer and character
struct Pair
{
    unsigned first;
    char second;

    Pair(unsigned first, char second)
    {
        this->first = first;
        this->second = second;
    }

    /// default constructor to initailize data ashan teddy data ladata ouashan array
    Pair()
    {
        first;
        second='$';
    }

    /// bool operator Overloading_dey petamel chick al-awal baad kada petertep minn sghir alee al-kabir
    bool operator<(Pair other)
    {
        return (this->first < other.first);
    }
};

 ///struct pet3et al-tree
struct Node
{
    Pair data;
    Node *left;
    Node *right;

    ///Constructor petamel node feha frequency character
    Node(char character, unsigned frequency)
    {
        data=Pair(frequency,character);
        left=right=nullptr;
    }
};

///Structure petamel NODE fe QUEUE ashan tebni HUFFMAN TREE
struct Queue_Node
{
    Node *data;
    Queue_Node *next;

    /// Constructor create node with character and frequency
    Queue_Node(Node *node)
    {
        data=node;
        next=nullptr;
    }
};

/// Class implement a linked list
class Linked_list_Queue
{
public:
    Queue_Node *front, *rear;

    Linked_list_Queue()
    {
        front = rear = nullptr;
    }

    // Enqueue node into the queue From the lest to the LARGEST
    void enQueue(Node *node)
    {
        Queue_Node *newNode = new Queue_Node(node);

        if (!front || node->data < front->data->data)
        {
            newNode->next = front;
            front = newNode;
        }
        else
        {
            Queue_Node *current = front;
            while (current->next && !(node->data < current->next->data->data))
            {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
            if (!newNode->next)
            {
                rear = newNode;
            }
        }
    }

    /// dequeue node from the front of queue
    Node *dequeue()
    {
        if (isEmpty())
        {
            return nullptr;
        }

        Queue_Node *temp = front;
        Node *node = temp->data;
        front = front->next;

        if (front == nullptr)
        {
            rear = nullptr;
        }
        return node;
    }

    ///check queue is empty
    bool isEmpty()
    {
        return front == nullptr;
    }
};

///Class to implement the Huffman Tree and wa el haket bt3etha
class Huffman_Tree
{
public:
    /// Build Huffman tree using frequence and return root
    Node *Build_Huffman_tree(int Frequencies[], int size)
    {
        Linked_list_Queue l;
        for (int i = 0; i < size; i++)
        {
            if (Frequencies[i] > 0)
            {
                Node *n = new Node(char(i), Frequencies[i]);
                l.enQueue(n);
            }
        }
        while (!l.isEmpty() && l.front->next != nullptr)
        {
            Node *left = l.dequeue();
            Node *right = l.dequeue();

            Node *root = new Node('$', left->data.first + right->data.first);
            root->left = left;
            root->right = right;

            l.enQueue(root);
        }
        return l.dequeue();
    }

    ///de alle pet3mel edge 1 wa 0
    void printHuffmanTree(Node *root, string code)
    {
        if (!root)
        {
            return;
        }

        if (!root->left && !root->right)
        {
            cout << root->data.second << ": " << code << endl;
        }

        printHuffmanTree(root->left, code + "0");
        printHuffmanTree(root->right, code + "1");
    }

    ///de pet3mel decode lel 3n tareg encode text
    string decodeText(string encodedText, Node *root)
    {
        string decodedText;
        Node *current = root;
        for (char bit : encodedText)
        {
            if (bit == '0' && current->left)
            {
                current = current->left;
            }
            else if (bit == '1' && current->right)
            {
                current = current->right;
            }

            if (!current->left && !current->right)
            {
                decodedText += current->data.second;
                current = root;
            }
        }
        return decodedText;
    }

    /// Helper function to recursively encode
    void encodeCharacterHelper(Node *node, char character, string currentCode, string &result)
    {
        if (!node)
        {
            return;
        }

        if (node->data.second == character)
        {
            result = currentCode;
            return;
        }

        encodeCharacterHelper(node->left, character, currentCode + "0", result);
        encodeCharacterHelper(node->right, character, currentCode + "1", result);
    }

    // Encode a character in the Huffman tree
    string encodeCharacter(Node *root, char character)
    {
        string code;
        encodeCharacterHelper(root, character, "", code);
        return code;
    }

    ///de pet3mel encode text
    string encodeText(string text, Node *root)
    {
        string encodedText;
        for (char c : text)
        {
            encodedText += encodeCharacter(root, c);
        }
        return encodedText;
    }

};

int main()
{
    Linked_list_Queue l;

    int maxSymbols = 256;
    int frequencies[maxSymbols] = {};
    string text;

    cout << "Enter the text: ";
    getline(cin, text);

    Pair p[maxSymbols];

    ///batcm3 el frequencies min el character
    for (char character : text)
    {
        frequencies[character]++;
    }

    ///print lel frequencies bet3et charracter
    for (int i = 0; i < maxSymbols; i++)
    {
        p[i] = Pair(frequencies[i], char(i));
    }

    /// Enqueue node on frequency into linkd listx queue
    for (int i = 0; i < maxSymbols; i++)
    {
        if (p[i].first > 0)
        {
            cout << "(" << p[i].first << ", " << p[i].second << ") ";
        }
    }
  //  cout << "\nEnqueue based on frequency:\n";
    for (int i = 0; i < maxSymbols; i++)
    {
        if (p[i].first > 0)
        {
            Node *newNode = new Node(p[i].second, p[i].first);
            l.enQueue(newNode);
        }
    }

    Huffman_Tree huffmanTree;
    Node *root = huffmanTree.Build_Huffman_tree(frequencies, maxSymbols);

    cout << "\nHuffman Tree:\n";
    huffmanTree.printHuffmanTree(root, "");

    ///dah pey3mel encode and decode lel text el dakhla baad ma nabni el tree

    string encodedText = huffmanTree.encodeText(text, root);
    cout << "\nEncoded Text: " << encodedText << endl;

    string decodedText = huffmanTree.decodeText(encodedText, root);
    cout << "Decoded Text: " << decodedText << endl;


    return 0;
}
