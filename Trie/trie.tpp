#include "trie.h"

// CLASS TRIENODE

TrieNode::TrieNode(char key_char) {
    this->key_char_ = key_char;
}

TrieNode::TrieNode(TrieNode &&other_trie_node) {
    this->key_char_ = other_trie_node.key_char_;
    this->is_end_ = other_trie_node.is_end_;
    this->children_ = std::move(other_trie_node.children_);
    other_trie_node.key_char_ = '\0'; // Dejamos el nodo en un estado válido pero no útil
    other_trie_node.is_end_ = false;
}

TrieNode::~TrieNode() = default;

bool TrieNode::HasChild(char key_char) const {
    return this->children_.find(key_char) != this->children_.end();
}

bool TrieNode::HasChildren() const {
    return !this->children_.empty();
}

bool TrieNode::IsEndNode() const {
    return this->is_end_;
}

char TrieNode::GetKeyChar() const {
    return this->key_char_;
}

std::unique_ptr<TrieNode> *TrieNode::InsertChildNode(char key_char, std::unique_ptr<TrieNode> &&child) {
    if (this->HasChild(key_char) || child->GetKeyChar() != key_char) {
        return nullptr;
    }
    this->children_[key_char] = std::move(child);
    return &this->children_[key_char];
}

std::unique_ptr<TrieNode> *TrieNode::GetChildNode(char key_char) {
    if (!this->HasChild(key_char)) {
        return nullptr;
    }
    return &this->children_[key_char];
}

void TrieNode::RemoveChildNode(char key_char) {
    if (this->HasChild(key_char)) {
        this->children_.erase(key_char);
    }
}

void TrieNode::SetEndNode(bool is_end) {
    this->is_end_ = is_end;
}

// CLASS TRIENODEWITHVALUE

template <typename T>
TrieNodeWithValue<T>::TrieNodeWithValue(TrieNode&& trieNode, T value) 
    : TrieNode(std::move(trieNode)), value_(std::move(value)){}

template <typename T>
TrieNodeWithValue<T>::TrieNodeWithValue(char key_char, T value)
    : TrieNode(key_char), value_(std::move(value)) {}

template <typename T>
TrieNodeWithValue<T>::~TrieNodeWithValue() = default;

template <typename T>
T TrieNodeWithValue<T>::GetValue() const {
    return this->value_;
}

// CLASS TRIE

Trie::Trie() {
    this->root_ = std::make_unique<TrieNode>('\0');
}

template <typename T>
bool Trie::Insert(const std::string &key, T value) {
    TrieNode *current_node = this->root_.get();
    for (const char &key_char : key) {
        if (!current_node->HasChild(key_char)) {
            std::unique_ptr<TrieNode> new_node = std::make_unique<TrieNode>(key_char);
            current_node->InsertChildNode(key_char, std::move(new_node));
        }
        current_node = current_node->GetChildNode(key_char)->get();
    }
    if (current_node->IsEndNode()) {
        return false;
    }
    std::unique_ptr<TrieNodeWithValue<T>> new_node = std::make_unique<TrieNodeWithValue<T>>(current_node->GetKeyChar(), value);
    current_node->InsertChildNode(current_node->GetKeyChar(), std::move(new_node));
    current_node->SetEndNode(true);
    return true;
}

bool Trie::Remove(const std::string &key) {
    TrieNode *current_node = this->root_.get();
    std::vector<std::pair<TrieNode *, char>> nodes_to_remove;
    for (const char &key_char : key) {
        if (!current_node->HasChild(key_char)) {
            return false;
        }
        nodes_to_remove.push_back({current_node, key_char});
        current_node = current_node->GetChildNode(key_char)->get();
    }
    if (!current_node->IsEndNode()) {
        return false;
    }
    current_node->SetEndNode(false);
    for (auto it = nodes_to_remove.rbegin(); it != nodes_to_remove.rend(); ++it) {
        if (!current_node->HasChildren()) {
            it->first->RemoveChildNode(it->second);
        }
        current_node = it->first;
    }
    return true;
}

template <typename T>
T Trie::GetValue(const std::string &key, bool *success){
    TrieNode *current_node = this->root_.get();
    for (const char &key_char : key) {
        if (!current_node->HasChild(key_char)) {
            *success = false;
            return T();
        }
        current_node = current_node->GetChildNode(key_char)->get();
    }
    if (!current_node->IsEndNode()) {
        *success = false;
        return T();
    }
    *success = true;
    return static_cast<TrieNodeWithValue<T>*>(current_node)->GetValue();
}