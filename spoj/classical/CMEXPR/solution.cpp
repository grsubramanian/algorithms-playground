#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

struct Node {
    char op; // one of +, -, *, /, 0 (0 means expression not operation)
    char letter; // one of a, b, c, ... z, 0 (0 means parenthesis)
    vector<Node *> children;
    Node * parent;

    Node(): parent(NULL) {}

    bool is_op() const {
        return op != 0;
    }

    bool is_paren() const {
        return op == 0 && letter == 0;
    }
};

void print(ostream & os, Node const & node, int indent = 0) {
    string output(indent, ' ');
    if (node.is_op()) {
        output += node.op;
    } else {
        if (node.is_paren()) {
            output += "()";
        } else {
            output += node.letter;
        }
    }
    os << output << "\n";
    for (Node const * child : node.children) {
        print(os, *child, indent + 2);
    }
}

ostream & operator <<(ostream & os, Node const & node) {
    print(os, node, 0);
    return os;
}

Node * op_node(char op) {
    Node * n = new Node();
    n->op = op;
    return n;
}

Node * expression_node(char letter) {
    Node * n = new Node();
    n->letter = letter;
    n->op = 0;
    return n;
}

Node * paren_node() {
    return expression_node(0);
}

void make_child(Node * parent, Node * child, int position) {
    if (parent != NULL) {
        parent->children[position] = child;
    }
    if (child != NULL) {
        child->parent = parent;
    }
}

void add_child(Node * parent, Node * child) {
    parent->children.push_back(child);
    child->parent = parent;
}

vector<Node *> merge_raw_nodes_for_specific_operators(
        vector<Node *> const & raw_nodes,
        vector<char> const & operators_whitelist) {

    vector<Node *> output;
    for (int i = 0; i < raw_nodes.size();) {
        Node * node = raw_nodes[i];
        if (node->is_op() &&
                find(operators_whitelist.begin(), operators_whitelist.end(), node->op) != operators_whitelist.end()) {
            // whitelisted operator.
            Node * prev = output.back(); output.pop_back();
            Node * next = raw_nodes[i + 1];
            node->children.resize(2, NULL);
            make_child(node, prev, 0);
            make_child(node, next, 1);
            i += 2;
        } else {
            i++;
        }
        output.push_back(node);
        
    }
    return output;
}

Node * merge_raw_nodes(vector<Node *> const & raw_nodes) {
    vector<char> muldiv_operators{'*', '/'};

    // We process multiplication and division before addition and subtraction.
    vector<Node *> nodes_with_muldiv_processed =
        merge_raw_nodes_for_specific_operators(raw_nodes, muldiv_operators); 
    vector<char> addsub_operators{'+', '-'};

    vector<Node *> nodes_with_addsub_processed =
        merge_raw_nodes_for_specific_operators(nodes_with_muldiv_processed, addsub_operators);

    // After full processing, there should be only one node.
    return nodes_with_addsub_processed[0];
}

void process_pnode(Node * pnode) {
    vector<Node *> raw_child_nodes_in_pnode = pnode->children;
    pnode->children.clear();

    // The raw nodes are simply a list of atomic nodes representing letters and operators.
    // They need to be merged into a single expression tree node.
    Node * processed_child_node = merge_raw_nodes(raw_child_nodes_in_pnode);
    add_child(pnode, processed_child_node);
}

Node * expression_tree(string const & expr) {

    Node * current_pnode = paren_node(); // sentinel root.
    for (int idx = 0; idx < expr.size(); idx++) {
        char c = expr[idx];
        if (c == '(') {
            Node * pnode = paren_node();
            add_child(current_pnode, pnode);
            current_pnode = pnode;
        } else if (c == ')') {
            process_pnode(current_pnode);
            current_pnode = current_pnode->parent;
        } else if (c >= 'a' && c <= 'z') {
            current_pnode->children.push_back(expression_node(c));
        } else {
            current_pnode->children.push_back(op_node(c));
        }
    }
    process_pnode(current_pnode);

    Node * root = current_pnode->children[0];
    root->parent = NULL;
    delete current_pnode; // we don't really need the sentinel once we are done processing.
    return root;
}

void delete_pnode(Node * parent, Node * pnode, Node * child, int child_num) {
    make_child(parent, child, child_num);
    delete pnode;
}

Node * remove_redundant_parentheses(Node * node, int child_num = 0) {
    if (node->is_paren()) {
        Node * parent = node->parent;
        Node * child = node->children[0];
        while (child->is_paren()) {
            delete_pnode(parent, node, child, child_num);
            node = child;
            child = child->children[0];
        }

        if (!child->is_op()) {
            // no need for printing parenthesis around a single letter.
            delete_pnode(parent, node, child, child_num);
            node = child;
        } else {
            // child is an operator.
            bool needs_deleting = false;
            if (parent == NULL) {
                needs_deleting = true;
            } else {
                bool node_is_right_operand = child_num == 1;
                bool addsub_precedes_muldiv =
                    (parent->op == '*' || parent->op == '/') && (child->op == '+' || child->op == '-');
                bool addsub_precedes_sub =
                    (parent->op == '-' && (child->op == '+' || child->op == '-') && node_is_right_operand);
                bool muldiv_precedes_div =
                    (parent->op == '/' && (child->op == '*' || child->op == '/') && node_is_right_operand);
                if (!addsub_precedes_muldiv && !addsub_precedes_sub && !muldiv_precedes_div) {
                    needs_deleting = true;
                }
            }
            int subchild_num;
            if (needs_deleting) {
                delete_pnode(parent, node, child, child_num);
                node = child;
                subchild_num = child_num;
            } else {
                subchild_num = 0;
            }
            remove_redundant_parentheses(child, subchild_num);
        }
    } else {
        if (node->is_op()) {
            remove_redundant_parentheses(node->children[0], 0);
            remove_redundant_parentheses(node->children[1], 1);
        }
    }
    return node;
}

void print_expr(ostream & os, Node * node) {

    if (node->is_paren()) {
        os << "(";
        print_expr(os, node->children[0]);
        os << ")";
    } else {
        if (node->is_op()) {
            print_expr(os, node->children[0]);
            os << node->op;
            print_expr(os, node->children[1]);
        } else {
            os << node->letter;
        }
    }
}

int main() {

    int T; cin >> T;
    while (T--) {
        string expr; cin >> expr;
        Node * expr_tree = expression_tree(expr);
        expr_tree = remove_redundant_parentheses(expr_tree);
        print_expr(cout, expr_tree);
        cout << "\n";
    }

    return 0;
}
