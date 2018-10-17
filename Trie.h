//
//
// Created by mateo on 14/10/18.
//

#ifndef TRIE_TRIE_H
#define TRIE_TRIE_H

#include <string>
namespace FJA {
class Trie {

public:
  Trie();
  void Insert(const std::string &v);
  bool Search(const std::string &v);
  std::string Coincidence(const std::string &query, std::string &r);

protected:
  class TrieNode {
  public:
    TrieNode();
    void Insert(const std::string &v);
    bool Search(const std::string &v);
    std::string Coincidence(const std::string &query, std::string &r);
    bool Last();

  public:
    TrieNode *children[95];
    bool End;

  };
protected:
  TrieNode *m_Root;
};
}

#endif //TRIE_TRIE_H