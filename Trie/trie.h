#ifndef TRIE_H
#define TRIE_H

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

/**
 * TrieNode is a generic container for any node in Trie.
**/
class TrieNode{
    public:
        TrieNode(char key_char);

        /**
        * @brief Move constructor for trie node object.
        * @param other_trie_node Old trie node.
        **/
        TrieNode(TrieNode &&other_trie_node);

        virtual ~TrieNode();

        /**
        * @brief Whether this trie node has a child node with specified key char.
        * @param key_char Key char of child node.
        * @return True if this trie node has a child with given key, false otherwise.
        **/
        bool HasChild(char key_char) const;

        /**
        * @brief Whether this trie node has any children at all. This is useful
        * when implementing 'Remove' functionality.
        * @return True if this trie node has any child node, false if it has no child node.
        */
        bool HasChildren() const;

        /**
        * @brief Whether this trie node is the ending character of a key string.
        * @return True if is_end_ flag is true, false if is_end_ is false.
        **/
        bool IsEndNode() const;

        /**
        * @brief Return key char of this trie node.
        * @return key_char_ of this trie node.
        **/
        char GetKeyChar() const;

        /**
        * @brief Insert a child node for this trie node into children_ map, given the key char and
        * unique_ptr of the child node. If specified key_char already exists in children_,
        * return nullptr. If parameter `child`'s key char is different than parameter
        * `key_char`, return nullptr.
        * @param key Key of child node
        * @param child Unique pointer created for the child node. This should be added to children_ map.
        * @return Pointer to unique_ptr of the inserted child node. If insertion fails, return nullptr.
        **/
        std::unique_ptr<TrieNode> *InsertChildNode(char key_char, std::unique_ptr<TrieNode> &&child);

        /**
        * @brief Get the child node given its key char. If child node for given key char does
        * not exist, return nullptr.
        * @param key Key of child node
        * @return Pointer to unique_ptr of the child node, nullptr if child
        *         node does not exist.
        **/
        std::unique_ptr<TrieNode> *GetChildNode(char key_char);

        /**
        * @brief Remove child node from children_ map.
        * @param key_char Key char of child node to be removed
        **/
        void RemoveChildNode(char key_char);

        /**
        * @brief Set the is_end_ flag to true or false.
        * @param is_end Whether this trie node is ending char of a key string
        **/
        void SetEndNode(bool is_end);

    protected:
        /** Key character of this trie node */
        char key_char_;
        /** whether this node marks the end of a key */
        bool is_end_{false};
        /** A map of all child nodes of this trie node, which can be accessed by each
        * child node's key char. */
        std::unordered_map<char, std::unique_ptr<TrieNode>> children_;
};

/**
 * TrieNodeWithValue is a node that marks the ending of a key, and it can
 * hold a value of any type T.
**/
template <typename T>
class TrieNodeWithValue : public TrieNode{
    private:
        T value_;

    public:
        /**
        * @brief Construct a new TrieNodeWithValue object from a TrieNode object
        * and specify its value.
        * @param trieNode TrieNode whose data is to be moved to TrieNodeWithValue
        * @param value
        **/
        TrieNodeWithValue(TrieNode &&trieNode, T value);

        /**
        * @brief Construct a new TrieNodeWithValue. This is used when a new terminal
        * node is constructed.
        * @param key_char Key char of this node
        * @param value Value of this node
        **/
        TrieNodeWithValue(char key_char, T value);

        /**
        * @brief Destroy the Trie Node With Value object
        **/
        ~TrieNodeWithValue();

        /**
        * @brief Get the stored value_.
        * @return Value of type T stored in this node
        **/
        T GetValue() const;
};

/**
 * Trie is a key-value store. Each key is a string and its corresponding
 * value can be any type.
**/
class Trie{
    private:
        /* Root node of the trie */
        std::unique_ptr<TrieNode> root_;

    public:
        /**
        * @brief Construct a new Trie object. Initialize the root node with '\0'
        * character.
        **/
        Trie();

        /**
        * @brief Insert key-value pair into the trie.
        * @param key Key used to traverse the trie and find the correct node
        * @param value Value to be inserted
        * @return True if insertion succeeds, false if the key already exists
        **/
        template <typename T>
        bool Insert(const std::string &key, T value);

        /**
        * @brief Remove key value pair from the trie.
        * @param key Key used to traverse the trie and find the correct node
        * @return True if the key exists and is removed, false otherwise
        **/
        bool Remove(const std::string &key);

        /**
        * @brief Get the corresponding value of type T given its key.
        * @param key Key used to traverse the trie and find the correct node
        * @param success Whether GetValue is successful or not
        * @return Value of type T if type matches
        **/
        template <typename T>
        T GetValue(const std::string &key, bool *success);
};
#include "trie.tpp" 
#endif // TRIE_H