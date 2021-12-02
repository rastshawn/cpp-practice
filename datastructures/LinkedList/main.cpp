#include <iostream>
#include <string>
#include <sstream>
//using namespace std;



template <class value_type>
class ListNode {
    public:
        value_type value;
        ListNode* next;
        ListNode(value_type v) {
            value = v;
            next = NULL;
        };
        ListNode(value_type v, ListNode<value_type> *n) {
            next = n;
            value = v;
        };
};

template <class value_type>
class LinkedList {
    private:
        ListNode<value_type>* head;
        ListNode<value_type>* tail;
        int n;
        ListNode<value_type>* getNode(int i) {
            if (i<0 || i>n-1) {
                throw std::out_of_range(std::to_string(i));
            } else {
                ListNode<value_type> *currentNode = head;
                for (int j = 0; j<i; j++) {
                    currentNode = currentNode->next;
                }
                return currentNode;
            }
        };
    public:
        LinkedList() {
            n = 0;
            head = NULL;
            tail = NULL;
        };
        value_type get(int i) {
            ListNode<value_type>* addr = getNode(i);
            return addr->value;
        };
        value_type set(int i, value_type value) {
            if (i<0 || i>n-1) {
                throw std::out_of_range(std::to_string(i));
            }

            ListNode<value_type>* addr = getNode(i);
            addr->value = value;
        };
        void add(int i, value_type value) {
            n++;
            if (i<0 || i>n-1) {
                throw std::out_of_range(std::to_string(i));
            }

            if (head == NULL) {
                head = new ListNode<value_type>(value);
            } else {
                // find the insert point

                ListNode<value_type>* left = getNode(i-1);
                ListNode<value_type>* right = getNode(i);
                // create new node, with  right node linked
                ListNode<value_type>* newNode = new ListNode<value_type>(value, right);
                // set left's right node to new node
                left->next = newNode;

            }
        };
        value_type remove(int i) {
            ListNode<value_type> *nodeToRemove = getNode(i);
            ListNode<value_type> *left = getNode(i-1);
            left->next = nodeToRemove->next;

            delete nodeToRemove;
            n--;
        };
        void clear() {

        };
        void push_back(value_type value) {
            add(n, value);
        }
        std::string toString() {
            std::ostringstream oss;
            oss << "[ ";
            ListNode<value_type> *currentNode = head;
            while (currentNode != NULL) {
                oss << currentNode->value << ", ";
                currentNode = currentNode->next;
            }
            oss << " ]";
            return oss.str();

        }
        ~LinkedList() {
            // loop through all nodes and destroy them
            ListNode<value_type> *currentNode = head;
            ListNode<value_type> *nextNode;
            while (currentNode != NULL) {
                nextNode = currentNode->next;
                //std::cout << "Deleting " << currentNode << std::endl;
                delete currentNode;
                currentNode = nextNode;
            }
        }

};

int main() {
    //std::cout << "Test" << std::endl;
    // ListNode<std::string> *a = new ListNode<std::string>("test");
    // ListNode<std::string> b = ListNode<std::string>("test2", a);
    // delete a;

    LinkedList<std::string> list = LinkedList<std::string>();

    list.push_back("test1");
    std::cout << list.toString() << std::endl;

    list.push_back("test2");
    std::cout << list.toString() << std::endl;

    for (int i = 3; i<11; i++) {
        list.push_back(std::string("test").append(std::to_string(i)));
    }

    std::cout << list.toString() << std::endl;

    list.set(0, "NewValue1");
    list.set(2, "NewValue3");
    std::cout << list.toString() << std::endl;

    list.add(8, "eight-and-a-half");
    std::cout << list.toString() << std::endl;

    list.remove(8);
    std::cout << list.toString() << std::endl;

    return 0;
}